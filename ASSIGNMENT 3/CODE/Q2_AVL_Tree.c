/* Q2: AVL tree insertion with LL, RR, LR and RL rotations */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{int key,height;struct Node *left,*right;}Node;
int h(Node*n){return n?n->height:0;}int max(int a,int b){return a>b?a:b;}void update(Node*n){n->height=1+max(h(n->left),h(n->right));}
Node*make(int k){Node*n=malloc(sizeof*n);if(!n){perror("malloc");exit(1);}n->key=k;n->height=1;n->left=n->right=NULL;return n;}
Node*rightRotate(Node*y){Node*x=y->left,*t=x->right;x->right=y;y->left=t;update(y);update(x);return x;}
Node*leftRotate(Node*x){Node*y=x->right,*t=y->left;y->left=x;x->right=t;update(x);update(y);return y;}
Node*insert(Node*n,int k){if(!n)return make(k);if(k<n->key)n->left=insert(n->left,k);else if(k>n->key)n->right=insert(n->right,k);else return n;update(n);int b=h(n->left)-h(n->right);if(b>1&&k<n->left->key)return rightRotate(n);if(b< -1&&k>n->right->key)return leftRotate(n);if(b>1&&k>n->left->key){n->left=leftRotate(n->left);return rightRotate(n);}if(b< -1&&k<n->right->key){n->right=rightRotate(n->right);return leftRotate(n);}return n;}
Node*search(Node*n,int k,int*cmp){*cmp=0;while(n){(*cmp)++;if(k==n->key)return n;n=k<n->key?n->left:n->right;}return NULL;}
void preorder(Node*n){if(n){printf("%d ",n->key);preorder(n->left);preorder(n->right);}}void destroy(Node*n){if(n){destroy(n->left);destroy(n->right);free(n);}}
int main(void){int a[]={10,20,30,40,50,25},cmp;Node*r=NULL;for(int i=0;i<6;i++){r=insert(r,a[i]);printf("After inserting %d: ",a[i]);preorder(r);printf("| height=%d\n",h(r));}int found=search(r,25,&cmp)!=NULL;printf("Search 25: %s (%d comparisons)\n",found?"Found":"Not found",cmp);Node*sorted=NULL;for(int i=1;i<=100000;i++)sorted=insert(sorted,i);printf("Height after 100000 sorted insertions: %d\n",h(sorted));destroy(r);destroy(sorted);return 0;}
