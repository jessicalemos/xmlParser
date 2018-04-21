#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "interface.h"
#include <stdlib.h>

typedef struct TCD_community* TAD_community;
int TAD_community_get_usersSize(TAD_community com);
int TAD_community_get_dataSize(TAD_community com);
int TAD_community_get_tagsSize(TAD_community com);
long get_topN(TAD_community com, int i);
char* post_getTag (TAD_community com, int i, long id);
int post_getScore (TAD_community com, int i, long id);
int treeHash_getNumRespostas (TAD_community com, int i);
void TAD_community_set_usersSize(TAD_community com, int usersSize);
void TAD_community_set_dataSize(TAD_community com, int dataSize);
void TAD_community_set_tagsSize(TAD_community com, int tagsSize);
TAD_community init ();
TAD_community initHashUsers (TAD_community com, int N);
TAD_community initHashData (TAD_community com, int N);
void addTags (TAD_community com,char* tagName, long id);
void retornaAId (TAD_community com,long *p, int *s, int N,int i);
void retorna (TAD_community com, int *r , long *p, int N, int i);
void addUser (TAD_community com,int reputation, long id, char *name, char *about);
int userHash (long i, TAD_community com);
int procuraPost (TAD_community com, long id);
int contaTag (TAD_community com, int i, char* tag);
void retornaSId (TAD_community com, long *p, int *s, int N, int i);
void procuraTitulo(TAD_community com, char *word, Date *data, long *id, int N);
int retiraTitulo(TAD_community com, int i,char* word);
int procuraData(TAD_community com, Date data);
void insere_Heap(TAD_community com);
int extraiHeaps(TAD_community com,int chave1,int chave2,int N,long* id);
long procuraRespostas(TAD_community com, long id);
LONG_list contaPosts(TAD_community com, int N, int nOrdenados);
LONG_pair existeData(TAD_community com, Date b, Date f, int chaveB, int chaveE);
void freeHashTableUsers  (TAD_community com, int size);
void freeHashTableTags (TAD_community com, int size);
void freeTop(TAD_community com);
void freeTopN(TAD_community com);
#endif