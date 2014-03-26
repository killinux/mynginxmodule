#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
typedef struct nodet 
{
    elemType data;
    struct nodet * next;
} node_t;            // 节点的结构
typedef struct queuet
{
    node_t * head;
    node_t * tail;
} queue_t;          // 队列的结构
/*1. 初始化链队列*/
// 其  初始化的 操作就是初始化队列的队头和队尾的两个标志位，  
// 所以就有删除或是插入的时候，会判断有没有 队列为空的时候。
void initQueue(queue_t * queue_eg)
{
    queue_eg->head = NULL; //队头标志位
    queue_eg->tail = NULL; //队尾标志位
}
/*2.向链队的队尾插入一个元素x*/
void enQueue(queue_t *hq, elemType x)
{
    node_t * new_p;
    new_p = (node_t *)malloc(sizeof(queue_t));
    if (new_p == NULL )
    {
        printf("分配空间出错！");
        exit(1);
    }
    new_p->data = x;
    new_p->next = NULL;
    if (hq->head == NULL)
    {
        hq->head = new_p;
        hq->tail = new_p;
    } else {
        //hq->tail->data = x;
        hq->tail->next = new_p;
        hq->tail = new_p;
    }
    return;
}
/*3. 从列队中队首删除一个元素*/
elemType outQueue(queue_t * hq)
{
    node_t * p;
    elemType temp;
    if (hq->head == NULL)
    {
        printf("队列为空，不能删除！");
        exit(1);
    }
    temp = hq->head->data;
    p = hq->head;
    hq->head = hq->head->next;
    if(hq->head == NULL)
    {
        hq->tail = NULL;
    }
    free(p);
    return temp;
}
/*4. 读取队首元素 */
elemType peekQueue(queue_t * hq)
{
    if (hq->head == NULL)
    {
        printf("队列为空。");
        exit(1);
    } 
    return hq->head->data;
}
/*5. 检查队列是否为空，若是空返回1，若不为空返回0 。*/
int is_emptyQueue(queue_t * hq)
{
    if (hq->head == NULL)
    {
        return 1;
    } else {
        return 0;
    }
}
/*6. 清除链队中的所有元素*/
void clearQueue(queue_t * hq)
{
    node_t * p = hq->head;
    while(p != NULL)
    {
        hq->head = hq->head->next;
        free(p);
        p = hq->head;
    }
    hq->tail = NULL;
    return;
}
/*main()函数*/
int main(int argc, char* argv[])
{
    queue_t q;
    int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i;
    initQueue(&q);
    for(i=0; i<8; i++)
    {
        enQueue(&q, a[i]);
    }
 //   printf("%d",outQueue(&q));
    enQueue(&q, 68);
//    printf("%d", peekQueue(&q));
    while (!is_emptyQueue(&q))
    {
        printf(" %d.\n", outQueue(&q));
    }
    printf(" \n");
    clearQueue(&q);
}
