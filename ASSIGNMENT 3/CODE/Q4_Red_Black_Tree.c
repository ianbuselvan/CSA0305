/* Q4: Red-Black Tree insertion and finding the smallest key */
#include <stdio.h>
#include <stdlib.h>
typedef enum{RED,BLACK}Color;typedef struct Node{int key;Color color;struct Node*left,*right,*parent;}Node;
Node*NIL;
Node*newNode(int k){Node*n=malloc(sizeof*n);if(!n){perror("malloc");exit(1);}n->key=k;n->color=RED;n->left=n->right=n->parent=NIL;return n;}
void leftRotate(Node**root,Node*x){Node*y=x->right;x->right=y->left;if(y->left!=NIL)y->left->parent=x;y->parent=x->parent;if(x->parent==NIL)*root=y;else if(x==x->parent->left)x->parent->left=y;else x->parent->right=y;y->left=x;x->parent=y;}
void rightRotate(Node**root,Node*y){Node*x=y->left;y->left=x->right;if(x->right!=NIL)x->right->parent=y;x->parent=y->parent;if(y->parent==NIL)*root=x;else if(y==y->parent->right)y->parent->right=x;else y->parent->left=x;x->right=y;y->parent=x;}
void fixInsert(Node**root,Node*z){while(z->parent->color==RED){if(z->parent==z->parent->parent->left){Node*y=z->parent->parent->right;if(y->color==RED){z->parent->color=BLACK;y->color=BLACK;z->parent->parent->color=RED;z=z->parent->parent;}else{if(z==z->parent->right){z=z->parent;leftRotate(root,z);}z->parent->color=BLACK;z->parent->parent->color=RED;rightRotate(root,z->parent->parent);}}else{Node*y=z->parent->parent->left;if(y->color==RED){z->parent->color=BLACK;y->color=BLACK;z->parent->parent->color=RED;z=z->parent->parent;}else{if(z==z->parent->left){z=z->parent;rightRotate(root,z);}z->parent->color=BLACK;z->parent->parent->color=RED;leftRotate(root,z->parent->parent);}}}(*root)->color=BLACK;}
void insert(Node**root,int k){Node*z=newNode(k),*y=NIL,*x=*root;while(x!=NIL){y=x;if(k==x->key){free(z);return;}x=k<x->key?x->left:x->right;}z->parent=y;if(y==NIL)*root=z;else if(k<y->key)y->left=z;else y->right=z;fixInsert(root,z);}
void inorder(Node*n){if(n!=NIL){inorder(n->left);printf("%d(%c) ",n->key,n->color==RED?'R':'B');inorder(n->right);}}
Node*minimum(Node*n){while(n->left!=NIL)n=n->left;return n;}int height(Node*n){if(n==NIL)return -1;int a=height(n->left),b=height(n->right);return 1+(a>b?a:b);}void destroy(Node*n){if(n!=NIL){destroy(n->left);destroy(n->right);free(n);}}
int main(void){NIL=malloc(sizeof* NIL);if(!NIL)return 1;NIL->color=BLACK;NIL->left=NIL->right=NIL->parent=NIL;Node*root=NIL;int a[]={10,20,30,15,25,5};for(int i=0;i<6;i++){insert(&root,a[i]);printf("After %d: ",a[i]);inorder(root);printf("\n");}printf("Smallest process key: %d\n",minimum(root)->key);printf("Tree height: %d\n",height(root));destroy(root);free(NIL);return 0;}
