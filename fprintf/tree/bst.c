#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 10
typedef struct node *link;
struct node{
        int item;
        link l,r;
};
link NODE(int item,link l,link r){
        link t=malloc(sizeof *t);
        t->item=item;t->l=l;t->r=r;
        return t;
}
link insert_node(link t,int item){
        if(t==NULL) return  NODE(item,NULL,NULL);
        if(item<t->item)
                t->l=insert_node(t->l,item);
        else
                t->r=insert_node(t->r,item);
        return t;
}
void pprint(link t){
        printf("(");
        if(t!=NULL){ 
                printf("%d",t->item);
                pprint(t->l);
                pprint(t->r);
        }
        printf(")");
}
int bst_search(link t,int item){
        if(t==NULL) return 0;
        if(item<t->item)return bst_search(t->l,item);
        else if(item>t->item) return bst_search(t->r,item);
        else return 1;
}
link bst_remove(link t,int item){
        if(t==NULL) return NULL;
        if(item<t->item)
                t->l=bst_remove(t->l,item);
        else if(item>t->item){
                t->r=bst_remove(t->r,item);
        }else {
                link x;
                if(t->l){
                        for(x=t->l;x->r;x=x->r){;}
                        t->item=x->item;
                        t->l=bst_remove(t->l,t->item);
                }else if(t->r){
                        for(x=t->r;x->l;x=x->l){;}
                        t->item=x->item;
                        t->r=bst_remove(t->l,t->item);
                }else{
                        free(t);t=NULL; 
                }
        }
        return t;
}
int main(){
        srand(time(NULL));
        int i ;link root=NULL;
        for(i=0;i<N;i++) root =insert_node(root,rand()%100);
        printf("\t\\tree");pprint(root);
        printf("\n");
        printf("%d\n",bst_search(root,50));
        root=bst_remove(root,root->item);
        printf("\t\\tree");pprint(root);
        return 0;
}
