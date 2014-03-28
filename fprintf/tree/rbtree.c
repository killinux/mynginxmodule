#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 10
typedef struct node *link;
struct node{
    int item,red;link l,r;
};
link null;
link NODE(int item,link l,link r,int red){
    link t=malloc(sizeof *t);
    t->item=item;t->l=l;t->r=r;t->red=red;
    return t;
}
link rotR(link t){
    link x=t->l;t->l=x->r;x->r=t;return x;
}
link rotL(link t){
    link x=t->r;t->r=x->l;x->l=t;return x;
}
void pprint(link t){
    printf("(");
    if(t!=null){ 
        printf("%d%c",t->item,t->red?'+':' ');
        pprint(t->l);
        pprint(t->r);
    }
    printf(")");
}
link RBinit(){
    null=NODE(0,NULL,NULL,0);
    null->l=null;null->r=null;
    return null;
}
link insert_node(link t ,int item, int sw){
    if(t==null) return NODE(item,null,null,1);
    if(t->l->red && t->r->red){
        t->red=1;t->l->red=0;t->r->red=0;
    }
    if(item<t->item){
        t->l=insert_node(t->l,item,0);
        if(t->red && t->l->red && sw) t=rotR(t);
        if(t->l->red && t->l->l->red)
        { t=rotR(t); t->red=0; t->r->red=1; }
    }else{
        t->r=insert_node(t->r,item,1);
        if(t->red && t->r->red && !sw) t=rotL(t);
        if(t->r->red && t->r->r->red)
        { t=rotL(t); t->red=0; t->l->red=1; }
    }
    return t;
}
link RBinsert(link root,int item){
    root=insert_node(root,item,0);
    root->red=0;
    return root;
}
int main(){
    int i=0;
    srand(time(NULL));
    link root=RBinit();
    for(i=0;i<N;i++)
        root=RBinsert(root,rand()%100);
    printf("\t\\tree");pprint(root);
    printf("\n");
    return 0;
}
