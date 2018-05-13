#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__
#include "date.h"

typedef struct new_pair* NEW_pair;
typedef struct query7 **HashTableQuery7;
typedef struct query11 **HashTableQuery11;
typedef struct hashTopN **HashTableTopN;
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
long get_id_Q7(HashTableQuery7 h,int i);
int get_flag_Q7(HashTableQuery7 h,int i);
int get_contador_Q7(HashTableQuery7 h,int i);
void set_id_Q7(HashTableQuery7 h, long l,int i);
void set_flag_Q7(HashTableQuery7 h, int flag,int i);
void set_contador_Q7(HashTableQuery7 h, int l,int i);
HashTableQuery7 initHashQ7 (int N);
void insereTQ7 (HashTableQuery7 h1, int i,int flag,int contador, long id);
int existeQ7(HashTableQuery7 h,int i);
void freeHashTableQuery7 (HashTableQuery7 h, int size);
long get_id(HashTableQuery11 h,int i);
char* get_tag(HashTableQuery11 h,int i);
int get_contador(HashTableQuery11 h,int i);
void set_id(HashTableQuery11 h, long l,int i);
void set_tag(HashTableQuery11 h, char* tag,int i);
void set_contador(HashTableQuery11 h, int l,int i);
long get_id_HashTopN(HashTableTopN h,int i);
HashTableQuery11 initHashQuery11 (int N);
void insereTQuery11 (HashTableQuery11 h1, int i,char* tag,int contador, long id);
int existeQ11(HashTableQuery11 h,int i);
void freeHashTableQuery11 (HashTableQuery11 h, int size);
HashTableTopN initHashTopN (int N);
void insereHashTopN (HashTableTopN h1, int i,long id);
int existeHashTopN(HashTableTopN h,int i);
void freeHashTableTopN (HashTableTopN h, int size);
#endif
