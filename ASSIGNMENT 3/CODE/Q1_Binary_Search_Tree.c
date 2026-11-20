/* Q1: Binary Search Tree - insert, search, traversals, height, delete and comparison count */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int key; struct Node *left, *right; } Node;
Node *newNode(int k){ Node *n=malloc(sizeof *n); if(!n){perror("malloc");exit(1);} n->key=k;n->left=n->right=NULL;return n; }
Node *insert(Node *r,int k){ if(!r)return newNode(k); if(k<r->key)r->left=insert(r->left,k); else if(k>r->key)r->right=insert(r->right,k); return r; }
int search(Node *r,int k,int *cmp){ *cmp=0; while(r){(*cmp)++; if(k==r->key)return 1; r=k<r->key?r->left:r->right;} return 0; }
int height(Node *r){ if(!r)return -1; int a=height(r->left),b=height(r->right);return 1+(a>b?a:b); }
void inorder(Node*r){if(r){inorder(r->left);printf("%d ",r->key);inorder(r->right);}}
void preorder(Node*r){if(r){printf("%d ",r->key);preorder(r->left);preorder(r->right);}}
void postorder(Node*r){if(r){postorder(r->left);postorder(r->right);printf("%d ",r->key);}}
void levelorder(Node*r){if(!r)return; int cap=10000,front=0,rear=0;Node **q=malloc(cap*sizeof *q);q[rear++]=r;while(front<rear){Node*n=q[front++];printf("%d ",n->key);if(n->left)q[rear++]=n->left;if(n->right)q[rear++]=n->right;}free(q);}
Node *minimum(Node*r){while(r&&r->left)r=r->left;return r;}
Node *deleteNode(Node*r,int k){if(!r)return NULL;if(k<r->key)r->left=deleteNode(r->left,k);else if(k>r->key)r->right=deleteNode(r->right,k);else{if(!r->left){Node*t=r->right;free(r);return t;}if(!r->right){Node*t=r->left;free(r);return t;}Node*s=minimum(r->right);r->key=s->key;r->right=deleteNode(r->right,s->key);}return r;}
void saveInorder(Node*r,FILE*f){if(r){saveInorder(r->left,f);fprintf(f,"%d\n",r->key);saveInorder(r->right,f);}}
void destroy(Node*r){if(r){destroy(r->left);destroy(r->right);free(r);}}
int main(void){int a[]={50,30,70,20,40,60,80,65},cmp;Node*r=NULL;for(int i=0;i<8;i++)r=insert(r,a[i]);printf("Inorder: ");inorder(r);printf("\nPreorder: ");preorder(r);printf("\nPostorder: ");postorder(r);printf("\nLevel order: ");levelorder(r);printf("\nHeight: %d\n",height(r));int found=search(r,65,&cmp);printf("Search 65: %s (%d comparisons)\n",found?"Found":"Not found",cmp);r=deleteNode(r,20);r=deleteNode(r,30);r=deleteNode(r,50);printf("After deleting 20, 30, 50: ");inorder(r);printf("\n");FILE*f=fopen("bst_data.txt","w");if(f){saveInorder(r,f);fclose(f);printf("Sorted tree data saved to bst_data.txt\n");}destroy(r);return 0;}
