#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Pstart 62
#define N 10
//typedef struct node *link;
typedef struct node 
{
    int    key;
    int    item;
    struct node *l,
                *r;
}BTNode;
typedef struct pnode        
{
    int key;                   
    int item;                  
   // struct pnode *left,      
//               *right,     // this no need to use left ,right 
//               *parent;      
    struct pnode *parent;     
    int lrflag,                //left 0,right 1
        space,                 //print point
        level;                 //the node level
}PBTNode;
BTNode* null;//null node
BTNode* CreateBTNode(char *s)
{
    char ch;
    BTNode *p=null,
           *b=null,
           *ps[MaxSize];
    int top=-1,
        tag=-1;
    ch=*s;
    while(ch)
    {
        switch(ch)
        {
            case '(':ps[++top]=p;tag=1;break;
            case ',':tag=2;break;
            case ')':top--;break;
            default:
                     p=(BTNode*)malloc(sizeof(BTNode));
                     p->item=ch;
                     p->l=p->r=null;
                     if(b==null)
                         b=p;
                     else
                     {
                         switch(tag)
                         {
                             case 1:ps[top]->l=p;break;
                             case 2:ps[top]->r=p;break;
                         }
                     }
        }
        ch=*(++s);
    }
    return b;
}

//print ()()
void DispBTNode(BTNode *b)
{
    if(b!=null)
    {
        printf("%d",b->item);
        if(b->l!=null||b->r!=null)
        {
            printf("(");
            DispBTNode(b->l);
            if(b->r!=null)printf(",");
            DispBTNode(b->r);
            printf(")");
        }
    }
}
int BTNodeHeight(BTNode *b)
{
    int lh,rh;
    if(b==null)return 0;
    else
    {
        lh=BTNodeHeight(b->l);
        rh=BTNodeHeight(b->r);
        return (lh>rh)?(lh+1):(rh+1);
    }
}

void SetPBTNodeInfo(BTNode *b,PBTNode *parent,PBTNode *pb,int level,int lrflag)
{
    int f=3;
    pb->item=b->item;
    pb->key =b->key;
    pb->parent=parent;
    pb->level=level;
    pb->lrflag=lrflag;
    pb->space=-3;
}

/*Level Order BTNode----->PBTNode*/
int CreatePBTNode(BTNode *b,PBTNode *pqu[])
{
    BTNode *p;
    BTNode *qu[MaxSize];
    int front=-1,
        rear=-1;
    rear++;
    qu[rear]=b;
    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
    SetPBTNodeInfo(b,NULL,pqu[rear],1,-1);
    while(rear!=front)
    {
        front++;
        p=qu[front];
        if(p->l!=null)
        {
            rear++;
            qu[rear]=p->l;
                printf("btnode:begin %d\n",rear);
            pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
                printf("btnode:end\n");
            SetPBTNodeInfo(p->l,pqu[front],pqu[rear],pqu[front]->level+1,0);
        }
        if(p->r!=null)
        {
            rear++;
            qu[rear]=p->r;
            pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
            SetPBTNodeInfo(p->r,pqu[front],pqu[rear],pqu[front]->level+1,1);
        }
    }
    return rear;
}
//打印一层结点，及该层结点与父结点的连线路径。
void PBTNodePrint(PBTNode *pb[],int n,int h)
{
    int l=-1,
        r=0,
        i,j,k,
        end;
    char c;
    PBTNode *p;
    if(n<=0||h<=0)
    {
        return;
    }
    else if(n==1)
    {
        for(i=0;i<pb[0]->space;i++)
            printf(" ");
                printf("%d%c",pb[0]->item,pb[0]->key?'+':' ');
        printf("\n");
        return;
    }
    h=h-pb[0]->level+2;
    for(k=0;k<h;k++)
    {
        j=0;
        l--;
        r++;

        for(i=0;i<n;i++)//print line
        {
            p=pb[i];
            end=(p->lrflag==0)?l:r;
            end+=p->parent->space;
            for(;j<end;j++)
                printf(" ");
            c=(p->lrflag==0)?'/':'\\';
            printf("%c",c);
        }
        printf("\n");
    }
    for(i=0;i<n;i++)//this level ,the node should point
    {
        p=pb[i];
        if(p->lrflag==0)
            p->space=p->parent->space+l;
        else
            p->space=p->parent->space+r;
    }
    for(i=0,j=0;i<n;i++)//data
    {
        p=pb[i];
        for(;j<p->space;j++)
            printf(" ");
                printf("%d%c",p->item,p->key?'+':' ');
    }
    printf("\n");
}
void DispBTree(BTNode *b)
{
    int n,i,j,high,
        level;
    PBTNode *p;
    PBTNode *pqu[MaxSize];
    PBTNode *levelpqu[MaxSize];
        printf("DispBtree\n");
    n=CreatePBTNode(b,pqu);
    high=BTNodeHeight(b);
    j=0;
    level=1;
    pqu[0]->space=Pstart;
    for(i=0;i<=n;i++)
    {
        p=pqu[i];
        if(p->level==level)
        {
            levelpqu[j]=p;
            j++;
        }
        else
        {
            PBTNodePrint(levelpqu,j,high);
            level=p->level;
            j=0;
            levelpqu[j]=p;
            j++;
        }
    }
    PBTNodePrint(levelpqu,j,high);

}

//----------------------rbtree2.c
BTNode* NODE(int item,BTNode* l,BTNode* r,int key){
        BTNode* t=malloc(sizeof *t);
        t->item=item;t->l=l;t->r=r;t->key=key;
        return t;
}
BTNode* rotR(BTNode* t){
        BTNode* x=t->l;t->l=x->r;x->r=t;return x;
}
BTNode* rotL(BTNode* t){
        BTNode* x=t->r;t->r=x->l;x->l=t;return x;
}
void pprint(BTNode* t){
        printf("(");
        if(t!=null){ 
                printf("%d%c",t->item,t->key?'+':' ');
                pprint(t->l);
                pprint(t->r);
        }
        printf(")");
}
BTNode* RBinit(){
        null=NODE(0,null,null,0);
        null->l=null;null->r=null;
        return null;
}
BTNode* insert_node(BTNode* t ,int item, int sw){
        if(t==null) return NODE(item,null,null,1);
        if(t->l->key && t->r->key){
                t->key=1;t->l->key=0;t->r->key=0;
        }
        if(item<t->item){
                t->l=insert_node(t->l,item,0);
                if(t->key && t->l->key && sw) t=rotR(t);
                if(t->l->key && t->l->l->key)
                { t=rotR(t); t->key=0; t->r->key=1; }
        }else{
                t->r=insert_node(t->r,item,1);
                if(t->key && t->r->key && !sw) t=rotL(t);
                if(t->r->key && t->r->r->key)
                { t=rotL(t); t->key=0; t->l->key=1; }
        }
        return t;
}
BTNode* RBinsert(BTNode* root,int item){
        root=insert_node(root,item,0);
        root->key=0;
        return root;
}
int main(){
        int i=0;
        srand(time(NULL));
        BTNode* root=RBinit();
        for(i=0;i<N;i++)
                root=RBinsert(root,rand()%100);
        printf("pprint:\n");
        printf("\t\\tree");
        pprint(root);
        printf("\n");

        printf("DispBtnode:\n");
        DispBTNode(root);printf("\n");
        printf("DispBTree:\n");
        DispBTree(root);
        return 0;
}

