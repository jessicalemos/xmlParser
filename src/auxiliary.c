#include <stdlib.h>
#include <string.h>
#include <common.h>
#include "auxiliary.h"
#include "date.h"

struct new_pair {
  float fst;
  long snd;
  int trd;
};

NEW_pair create_new_pair(float fst, long snd, int trd) {
  NEW_pair p = malloc(sizeof(struct new_pair));
  p->fst = fst; 
  p->snd = snd;
  p->trd = trd;
  return p;
}

void set_fst_new(NEW_pair pair, float l) {
  pair->fst = l;
}

void set_snd_new(NEW_pair pair, long l) {
  pair->snd = l;
}

void set_trd_new(NEW_pair pair, int l) {
  pair->trd = l;
}

float get_fst_new(NEW_pair pair) {
  return pair->fst;
}


int get_trd_new(NEW_pair pair) {
  return pair->trd;
}

long get_snd_new(NEW_pair pair) {
  return pair->snd;
}

void free_new_pair(NEW_pair pair) {
    free(pair);
}

void insere (int x, long id, long *p, int *s,int N){
    int i,j;
  for(i=0;i<N-1 && s[i]>x;i++);
    if(i==N-1 && s[i]<x) {s[i]=x;p[i]=id;}
       else{
        for(j=N-1;j>i;j--)
          {s[j]=s[j-1];p[j]=p[j-1];}
        if(s[i]<=x){s[i]=x;p[i]=id;}
       }
}

int elimRep (long v[], int N) {
  int r,w,wc;
  for ( r = 0 , w = 0 ; r < N ; r++ ){
    for ( wc = w-1 ; wc >= 0 && v[wc] != v[r] ; wc--);
      if ( wc < 0 ) v[w++] = v[r];
  }
  return w;
}

int contida (char* s,char* word){
  int i = 0, j=0;
  while(s[i]!='\0'){
    while((s[i] != '\0') && (isspace(s[i])))
      i++; 
    while((s[i] != '\0') && word[i]!='\0' && s[i]==word[j]){
      i++; j++; 
    }
    if ((s[i]=='\0' || s[i]==' ') && word[j]=='\0') return 1;
    else j=0;
    while((s[i] != '\0') && (!isspace(s[i]))){ 
      i++; 
    }
  }
  return 0;
}

int procuraArray (long* postId, long id, int N){
  int i;
  for(i=0; i<N && postId[i]!=id; i++);
  if (i==N) return 0;
  return 1;
}