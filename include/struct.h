#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "interface.h"
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
void retornaAId (TAD_community com,long *p, int *s, int N,int i);
void retorna (TAD_community com, int *r , long *p, int N, int i);
void addUser (TAD_community com,int reputation, long id, char *name, char *about);
int procuraUser (TAD_community com, long id);
void incrementaPost(TAD_community com, long id);
int tagHash (char* s, TAD_community com);
int userHash (long i, TAD_community com);
void addPost (TAD_community com,int score,int postTypeId,long parentId, long id, char *tag, char *title, long ownerUserId, char *question, int answerCount, Date data,int commentCount);
int procuraPost (TAD_community com, long id);
int contaTag (TAD_community com, int i, char* tag);
int existeTree (TAD_community com, int i);
void retornaId (TAD_community com, int i, long* p, char* tag, int c);
void retornaSId (TAD_community com, long *p, int *s, int N, int i);
void procuraTitulo(TAD_community com, char *word, Date *data, long *id, int N);
int retiraTitulo(TAD_community com, int i,char* word);
int procuraData(TAD_community com, Date data);
void insere_Heap(TAD_community com);
void insere_Heap_Posts(TAD_community com,long ownerUserId, long id, Date data);
long* retornaTop10(TAD_community com, int i);
int extraiHeaps(TAD_community com,int chave1,int chave2,int N,long* id);
int contaT (TAD_community com, int i, char* word);
long procuraRespostas(TAD_community com, long id);
LONG_list contaPosts(TAD_community com, int N, int nOrdenados);
int pertenceU (TAD_community com, long ownerUserId, int N, int n);
int preencheTopNR (TAD_community com, int tam, int z, int N);
void buscaId (TAD_community com, char* tag, long* p, int* n, int size);
int buscaTag(TAD_community com, char *s, long* p, int* n, int size);
void retornaTId(TAD_community com, int i, int* nTags, long* arrayT, int N, int tam, int z, int size, int ocupados);
void extrai(long* arrayT, int* nTags, int size, int N);
void insere_Heap_Reputation(TAD_community com);
void freeHashTableUsers  (TAD_community com, int size);
void freeHashTableTags (TAD_community com, int size);
void freeTop(TAD_community com);
void freeTopN(TAD_community com);
void freeTreeHashData (TAD_community com,int size);
#endif
