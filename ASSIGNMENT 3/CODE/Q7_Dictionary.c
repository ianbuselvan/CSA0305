/* Q7: Dictionary design: Trie for exact lookup/autocomplete + sorted array for range listing.
   Sample-sized implementation; input words are lowercase English letters. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 1200
#define MAX_LEN 64
#define A 26
typedef struct Trie{struct Trie*child[A];int end;}Trie;
Trie*newTrie(void){Trie*t=calloc(1,sizeof* t);if(!t){perror("calloc");exit(1);}return t;}
void trieInsert(Trie*t,const char*w){while(*w){if(*w<'a'||*w>'z'){w++;continue;}int i=*w-'a';if(!t->child[i])t->child[i]=newTrie();t=t->child[i];w++;}t->end=1;}
int trieSearch(Trie*t,const char*w){while(*w){if(*w<'a'||*w>'z')return 0;int i=*w-'a';t=t->child[i];if(!t)return 0;w++;}return t->end;}
void autocompleteWalk(Trie*t,char*buf,int d){if(!t)return;if(t->end){buf[d]='\0';printf("%s ",buf);}for(int i=0;i<A;i++)if(t->child[i]){buf[d]='a'+i;autocompleteWalk(t->child[i],buf,d+1);}}
int cmp(const void*a,const void*b){return strcmp((const char*)a,(const char*)b);}
void rangeList(char words[][MAX_LEN],int n,const char*lo,const char*hi){printf("Words in range [%s, %s]: ",lo,hi);for(int i=0;i<n;i++)if(strcmp(words[i],lo)>=0&&strcmp(words[i],hi)<=0)printf("%s ",words[i]);printf("\n");}
void destroy(Trie*t){if(t){for(int i=0;i<A;i++)destroy(t->child[i]);free(t);}}
int main(void){const char*sample[]={"apple","application","apply","banana","band","bank","cat","catalog","cater","dog","door","dove","grape","graph","tree","trie"};int n=(int)(sizeof sample/sizeof sample[0]);char words[MAX_WORDS][MAX_LEN];Trie*root=newTrie();for(int i=0;i<n;i++){snprintf(words[i],MAX_LEN,"%s",sample[i]);trieInsert(root,sample[i]);}qsort(words,n,MAX_LEN,cmp);printf("Exact search 'catalog': %s\n",trieSearch(root,"catalog")?"Found":"Not found");printf("Exact search 'catalyst': %s\n",trieSearch(root,"catalyst")?"Found":"Not found");printf("Autocomplete for 'app': ");/* locate prefix node and enumerate with full prefix */Trie*t=root;const char*p="app";for(;*p&&t;p++)t=t->child[*p-'a'];if(t){char buf[MAX_LEN]="app";autocompleteWalk(t,buf,3);}else printf("No matches");printf("\n");rangeList(words,n,"banana","dog");printf("Sorted dictionary (%d sample words): ",n);for(int i=0;i<n;i++)printf("%s ",words[i]);printf("\n");printf("Design note: for 200,000 words, use the trie for prefix operations and maintain a sorted word array (or sorted file/index) for range listing.\n");destroy(root);return 0;}
