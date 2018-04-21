#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__
typedef struct new_pair* NEW_pair;

NEW_pair create_new_pair(float fst, long snd, int trd);
void set_fst_new(NEW_pair pair, float l);
void set_snd_new(NEW_pair pair, long l);
void set_trd_new(NEW_pair pair, int l);
float get_fst_new(NEW_pair pair);
int get_trd_new(NEW_pair pair);
long get_snd_new(NEW_pair pair);
void free_new_pair(NEW_pair pair);
void insere (int x, long id, long *p, int *s,int N);
int elimRep (long v[], int N);
int contida (char* s,char* word);
int procuraArray (long* postId, long id, int N);

#endif