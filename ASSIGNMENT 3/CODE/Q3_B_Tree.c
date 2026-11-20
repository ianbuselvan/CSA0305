/* Q3: B-tree of minimum degree 2 (maximum 3 keys per node) */
#include <stdio.h>
#include <stdlib.h>
#define T 2
typedef struct BNode{int n,leaf,key[2*T-1];struct BNode*c[2*T];}BNode;
BNode*create(int leaf){BNode*x=calloc(1,sizeof* x);if(!x){perror("calloc");exit(1);}x->leaf=leaf;return x;}
BNode*search(BNode*x,int k,int*visits){if(!x)return NULL;(*visits)++;int i=0;while(i<x->n&&k>x->key[i])i++;if(i<x->n&&k==x->key[i])return x;if(x->leaf)return NULL;return search(x->c[i],k,visits);}
void splitChild(BNode*x,int i){BNode*y=x->c[i],*z=create(y->leaf);z->n=T-1;for(int j=0;j<T-1;j++)z->key[j]=y->key[j+T];if(!y->leaf)for(int j=0;j<T;j++)z->c[j]=y->c[j+T];y->n=T-1;for(int j=x->n;j>=i+1;j--)x->c[j+1]=x->c[j];x->c[i+1]=z;for(int j=x->n-1;j>=i;j--)x->key[j+1]=x->key[j];x->key[i]=y->key[T-1];x->n++;}
void insertNonFull(BNode*x,int k){int i=x->n-1;if(x->leaf){while(i>=0&&k<x->key[i]){x->key[i+1]=x->key[i];i--;}if(i>=0&&x->key[i]==k)return;x->key[i+1]=k;x->n++;}else{while(i>=0&&k<x->key[i])i--;i++;if(x->c[i]->n==2*T-1){splitChild(x,i);if(k>x->key[i])i++;else if(k==x->key[i])return;}insertNonFull(x->c[i],k);}}
void insert(BNode**root,int k){if(!*root){*root=create(1);(*root)->key[0]=k;(*root)->n=1;return;}BNode*r=*root;if(r->n==2*T-1){BNode*s=create(0);s->c[0]=r;splitChild(s,0);int i=(k>s->key[0]);if(k==s->key[0])return;insertNonFull(s->c[i],k);*root=s;}else insertNonFull(r,k);}
void printNode(BNode*x,int level){if(!x)return;printf("Level %d: [",level);for(int i=0;i<x->n;i++)printf("%d%s",x->key[i],i==x->n-1?"":", ");printf("]\n");if(!x->leaf)for(int i=0;i<=x->n;i++)printNode(x->c[i],level+1);}
void destroy(BNode*x){if(x){if(!x->leaf)for(int i=0;i<=x->n;i++)destroy(x->c[i]);free(x);}}
int main(void){int a[]={10,20,5,6,12,30,7,17};BNode*r=NULL;for(int i=0;i<8;i++){insert(&r,a[i]);printf("After inserting %d:\n",a[i]);printNode(r,0);}int visits=0;int keys[]={5,30,99};for(int i=0;i<3;i++){visits=0;printf("Search %d: %s, disk-node visits=%d\n",keys[i],search(r,keys[i],&visits)?"Found":"Not found",visits);}printf("Approximate B-tree height for 5,000,000 keys, order 100: about 4 levels (at most about 4-5 node reads, depending on occupancy).\n");destroy(r);return 0;}
