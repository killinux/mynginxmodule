#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct _employee{
    char name[32];
    unsigned char age;
} Employee;
int compareEmployee(Employee *e1,Employee *e2){
    return strcmp(e1->name ,e2->name);
}
void displayEmployee(Employee* employee){
    printf("%s\t%d\n",employee->name,employee->age);
}
typedef void(*DISPLAY)(void *);
typedef int(*COMPARE)(void*,void*);
typedef struct _node {
    void *data;
    struct _node *next;
} Node;
typedef struct _linkedList{
    Node *head;
    Node *tail;
    Node *current;
} LinkedList;
void initializeList(LinkedList *);
void addHead(LinkedList*,void*);
void addTail(LinkedList*,void*);
void delete(LinkedList*,Node*);
Node *getNode(LinkedList*,COMPARE,void*);
void displayLinkedList(LinkedList*,DISPLAY);


void initializeList(LinkedList *list){
    list->head=NULL;
    list->tail=NULL;
    list->current=NULL;
}
void addHead(LinkedList *list,void* data){
    Node *node=(Node*)malloc(sizeof(Node));
    node->data=data;
    if(list->head==NULL){
        list->tail=node;
        node->next=NULL;
    }else{
        node->next=list->head;
    }
    list->head=node;
}
int main(int argc,char *args[]){
    LinkedList linkedList;
    Employee *samuel=(Employee*)malloc(sizeof(Employee));
    strcpy(samuel->name,"Samuel");
    samuel->age=32;
    
    initializeList(&linkedList);
    addHead(&linkedList,samuel); 
}
