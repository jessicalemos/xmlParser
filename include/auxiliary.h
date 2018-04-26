#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__
#include "date.h"
typedef struct new_pair* NEW_pair;
typedef struct query11 **HashTableQuery11;
NEW_pair create_new_pair(float fst, long snd, int trd);
void set_fst_new(NEW_pair pair, float l);
void set_snd_new(NEW_pair pair, long l);
void set_trd_new(NEW_pair pair, int l);
float get_fst_new(NEW_pair pair);
int get_trd_new(NEW_pair pair);
long get_snd_new(NEW_pair pair);
void free_new_pair(NEW_pair pair);
int max(int e,int d);
int verificaTag(char *s,char *t);
void insere (int x, long id, long *p, int *s,int N);
int contida (char* s,char* word);
int procuraArray (long* postId, long id, int N);
int compareDate (Date d1, Date d2);
int compareDateQ (Date d1, Date d2);
void insereT(Date d,long postId,Date *data,long *id,int N);
void insereTag (long tag, long* p, int* s, int N);
int existeQ7(HashTableQuery7 h,int i);
long get_id(HashTableQuery11 h,int i);
char* get_tag(HashTableQuery11 h,int i);
int get_contador(HashTableQuery11 h,int i);
void set_id(HashTableQuery11 h, long l,int i);
void set_tag(HashTableQuery11 h, char* tag,int i);
void set_contador(HashTableQuery11 h, int l,int i);
HashTableQuery11 initHashQuery11 (int N);
void insereTQuery11 (HashTableQuery11 h1, int i,char* tag,int contador, long id);
int existeQ11(HashTableQuery11 h,int i);
#endif
