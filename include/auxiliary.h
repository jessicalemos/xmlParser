#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__
#include "date.h"
typedef struct new_pair* NEW_pair;

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
int elimRep (long v[], int N);
int contida (char* s,char* word);
int procuraArray (long* postId, long id, int N);
int compareDate (Date d1, Date d2);
int compareDateQ (Date d1, Date d2);
void insereT(Date d,long postId,Date *data,long *id,int N);
void insereTag (long tag, long* p, int* s, int N);

#endif
