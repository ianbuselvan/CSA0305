/* Q5: Splay tree - zig, zig-zig, zig-zag rotations and adaptive search */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{int key;struct Node*left,*right;}Node;
Node*make(int k){Node*n=malloc(sizeof*n);if(!n){perror("malloc");exit(1);}n->key=k;n->left=n->right=NULL;return n;}
Node*rightRotate(Node*x){Node*y=x->left;x->left=y->right;y->right=x;return y;}Node*leftRotate(Node*x){Node*y=x->right;x->right=y->left;y->left=x;return y;}
Node*splay(Node*r,int k){if(!r||r->key==k)return r;if(k<r->key){if(!r->left)return r;if(k<r->left->key){r->left->left=splay(r->left->left,k);r=rightRotate(r);}else if(k>r->left->key){r->left->right=splay(r->left->right,k);if(r->left->right)r->left=leftRotate(r->left);}return r->left?rightRotate(r):r;}else{if(!r->right)return r;if(k>r->right->key){r->right->right=splay(r->right->right,k);r=leftRotate(r);}else if(k<r->right->key){r->right->left=splay(r->right->left,k);if(r->right->left)r->right=rightRotate(r->right);}return r->right?leftRotate(r):r;}}
Node*insert(Node*r,int k){if(!r)return make(k);r=splay(r,k);if(r->key==k)return r;Node*n=make(k);if(k<r->key){n->left=r->left;n->right=r;r->left=NULL;}else{n->right=r->right;n->left=r;r->right=NULL;}return n;}
Node*search(Node*r,int k,int*visits){*visits=0;Node*t=r;while(t){(*visits)++;if(k==t->key)break;t=k<t->key?t->left:t->right;}return splay(r,k);}
void inorder(Node*r){if(r){inorder(r->left);printf("%d ",r->key);inorder(r->right);}}void destroy(Node*r){if(r){destroy(r->left);destroy(r->right);free(r);}}
int main(void){int a[]={1,2,3,4,5,6,7,8,9,10},visits;Node*r=NULL;for(int i=0;i<10;i++)r=insert(r,a[i]);printf("Initial inorder: ");inorder(r);printf("\n");r=search(r,3,&visits);printf("Access 3: visits=%d, new root=%d\n",visits,r->key);r=search(r,9,&visits);printf("Access 9: visits=%d, new root=%d\n",visits,r->key);int hot[]={3,3,3,3,9,3,9,3};long total=0;for(int i=0;i<8;i++){r=search(r,hot[i],&visits);total+=visits;}printf("Average nodes visited for sample repeated accesses: %.2f\n",total/8.0);destroy(r);return 0;}
