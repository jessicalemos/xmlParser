#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "interface.h"
#include "auxiliary.h"
#include <stdlib.h>

#define PARENT(i) (i-1)/2
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

typedef struct TCD_community* TAD_community;
int TAD_community_get_usersSize(TAD_community com);
int TAD_community_get_dataSize(TAD_community com);
int TAD_community_get_tagsSize(TAD_community com);
long get_topN(TAD_community com, int i);
long get_topNR(TAD_community com, int i);
char* users_getDisplayName (TAD_community com, int i);
char* users_getAboutMe (TAD_community com, int i);
char* post_getTitle (TAD_community com, int i, long id);
int post_getPostTypeId (TAD_community com, int i, long id);
Date post_getCreationDate (TAD_community com, int i);
char* post_getTag (TAD_community com, int i, long id);
int post_getScore (TAD_community com, int i, long id);
long post_getparentId (TAD_community com, int i, long id);
long post_getOwnerUserId (TAD_community com, int i, long id);
int treeHash_getNumRespostas (TAD_community com, int i);
long treeHash_getContadorR (TAD_community com, int i);
long treeHash_getContadorP (TAD_community com, int i);
void TAD_community_set_usersSize(TAD_community com, int usersSize);
void TAD_community_set_dataSize(TAD_community com, int dataSize);
void TAD_community_set_tagsSize(TAD_community com, int tagsSize);
TAD_community init ();
TAD_community initHashUsers (TAD_community com, int N);
TAD_community initHashTags (TAD_community com, int N);
TAD_community initHashData (TAD_community com, int N);
void addTags (TAD_community com,char* tagName, long id);
int dataHash (Date data, TAD_community com);
void retornaAId (TAD_community com,int i,HashTableQuery7 h,int size);
void addUser (TAD_community com,int reputation, long id, char *name, char *about);
int procuraUser (TAD_community com, long id);
void incrementaPost(TAD_community com, long id);
int tagHash (char* s, TAD_community com);
int userHash (long i, TAD_community com);
void addPost (TAD_community com,int score,int postTypeId,long parentId, long id, char *tag, char *title, long ownerUserId, int answerCount, Date data,int commentCount);
int procuraPost (TAD_community com, long id);
int existeTree (TAD_community com, int i);
void retornaId (TAD_community com, int i, long* p, char* tag, int c, Date* arrayD);
void retornaSId (TAD_community com, long *p, int *s, int N, int i);
void procuraTitulo(TAD_community com, char *word, Date *data, long *id, int N);
int procuraData(TAD_community com, Date data);
void insere_Heap(TAD_community com);
void insere_Heap_Posts(TAD_community com,long ownerUserId, long id, Date data);
int q7Hash (long i, int size);
LONG_list carregaListaQ(TAD_community com,int N,HashTableQuery7 h,int size);
LONG_list carregaListaT(TAD_community com,long* id,Date* d);
LONG_list carregaListaTag(TAD_community com,int N,HashTableQuery11 h,int size);
long* retornaTop10(TAD_community com, int i);
int extraiHeaps(TAD_community com,int chave1,int chave2,int N,long* id);
long procuraRespostas(TAD_community com, long id);
LONG_list contaPosts(TAD_community com, int N, int nOrdenados);
int topNHash (long i, int N);
int pertenceU (TAD_community com, long ownerUserId, int N, HashTableTopN h);
void preencheTopNR (TAD_community com, int tam, int z, int N);
int procuraTag(TAD_community com,int chave,char* tag);
void buscaId (TAD_community com, char* tag, HashTableQuery11 h, int size);
int buscaTag(TAD_community com, char *s, HashTableQuery11 h, int size);
HashTableTopN transfere(TAD_community com, int N, HashTableTopN h);
void retornaTId(TAD_community com, int i, int N, HashTableQuery11 h,HashTableTopN h1,int size);
void insere_Heap_Reputation(TAD_community com);
void freeHashTableUsers  (TAD_community com, int size);
void freeHashTableTags (TAD_community com, int size);
void freeTop(TAD_community com);
void freeTopN(TAD_community com);
void freeTreeHashData (TAD_community com,int size);
#endif
