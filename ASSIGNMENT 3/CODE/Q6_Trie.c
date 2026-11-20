/* Q6: Trie with insertion, exact search, prefix count, autocomplete and deletion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26
typedef struct Trie{struct Trie*child[ALPHABET];int words;int end;}Trie;
Trie*node(void){Trie*t=calloc(1,sizeof* t);if(!t){perror("calloc");exit(1);}return t;}
int indexOf(char c){if(c>='a'&&c<='z')return c-'a';if(c>='A'&&c<='Z')return c-'A';return -1;}
void insert(Trie*t,const char*w){for(;*w;w++){int i=indexOf(*w);if(i<0)continue;if(!t->child[i])t->child[i]=node();t=t->child[i];t->words++;}t->end=1;}
Trie*prefixNode(Trie*t,const char*p){for(;*p;p++){int i=indexOf(*p);if(i<0)return NULL;t=t->child[i];if(!t)return NULL;}return t;}
int search(Trie*t,const char*w){Trie*n=prefixNode(t,w);return n&&n->end;}
int countPrefix(Trie*t,const char*p){if(!*p)return t->words;Trie*n=prefixNode(t,p);return n?n->words:0;}
void collect(Trie*t,char*buf,int depth){if(!t)return;if(t->end){buf[depth]='\0';printf("%s ",buf);}for(int i=0;i<26;i++)if(t->child[i]){buf[depth]='a'+i;collect(t->child[i],buf,depth+1);}}
void autocomplete(Trie*t,const char*p){Trie*n=prefixNode(t,p);if(!n){printf("No matches");return;}char buf[256];size_t len=strlen(p);if(len>=sizeof buf)return;strcpy(buf,p);collect(n,buf,(int)len);}
int deleteWord(Trie*t,const char*w){if(!*w){if(!t->end)return 0;t->end=0;return 1;}int i=indexOf(*w);if(i<0||!t->child[i])return 0;int removed=deleteWord(t->child[i],w+1);if(removed)t->child[i]->words--;return removed;}
void destroy(Trie*t){if(t){for(int i=0;i<26;i++)destroy(t->child[i]);free(t);}}
int main(void){const char*contacts[]={"anand","anitha","anu","arun","bala","anusuya"};Trie*root=node();for(int i=0;i<6;i++)insert(root,contacts[i]);const char*typed[]={"a","an","anu","b","z"};for(int i=0;i<5;i++)printf("%s:%d ",typed[i],countPrefix(root,typed[i]));printf("\nSearch 'anand': %s\n",search(root,"anand")?"Found":"Not found");printf("Autocomplete 'an': ");autocomplete(root,"an");printf("\nDelete 'anu': %s\n",deleteWord(root,"anu")?"Deleted":"Not found");printf("After deletion, prefix 'anu' count: %d\n",countPrefix(root,"anu"));destroy(root);return 0;}
