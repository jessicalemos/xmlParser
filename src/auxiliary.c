#include <stdlib.h>
#include <string.h>
#include <common.h>
#include "auxiliary.h"
#include <ctype.h>

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

typedef struct query7{
  long id; /*id da tag*/
  int flag;
  int contador;
} Query7;

long get_id_Q7(HashTableQuery7 h,int i) {
  return h[i]->id;
}

int get_flag_Q7(HashTableQuery7 h,int i) {
  return h[i]->flag;
}

int get_contador_Q7(HashTableQuery7 h,int i) {
  return h[i]->contador;
}

void set_id_Q7(HashTableQuery7 h, long l,int i) {
  h[i]->id = l;
}

void set_flag_Q7(HashTableQuery7 h, int flag,int i) {
  h[i]->flag = flag;
}

void set_contador_Q7(HashTableQuery7 h, int l,int i) {
  h[i]->contador = l;
}

typedef struct query11{
  long id; /*id da tag*/
  char* tag;
  int contador;
} Query11;

long get_id(HashTableQuery11 h,int i) {
  return h[i]->id;
}

char* get_tag(HashTableQuery11 h,int i) {
       return h[i]->tag;
}

int get_contador(HashTableQuery11 h,int i) {
  return h[i]->contador;
}

void set_id(HashTableQuery11 h, long l,int i) {
 h[i]->id = l;
}

void set_tag(HashTableQuery11 h, char* tag,int i) {
  h[i]->tag = tag;
}

void set_contador(HashTableQuery11 h, int l,int i) {
  h[i]->contador = l;
}

int max(int e,int d){
  return e>d?e:d;
}

int verificaTag(char *s,char *t){
  int a=0,i=0,k=0,j;
  char *tag=malloc(strlen(s)*sizeof(char));
  while(s[k]){
    i=k;
    while(s[i] && s[i]=='<') i++;
    for(j=i,a=0;s[j] && s[j]!='>';j++,a++){
        tag[a]=s[j];
    }
    tag[a]=0;
      if(!strcmp(tag,t)) {free(tag);return 1;}
      if(s[j] && s[j]=='>') {j++;}
      k=j;
  }
  free(tag);
  return 0;
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

int contida (char* s,char* word){
  int i = 0, j=0;
  while(s[i]!='\0'){
    while((s[i] != '\0') && (isspace(s[i])))
      i++; 
    while((s[i] != '\0') && word[j]!='\0' && s[i]==word[j]){
      i++; j++; 
    }
    if (word[j]=='\0') return 1;
    else {j=0; i++;}
  }
  return 0;
}

int procuraArray (long* postId, long id, int N){
  int i;
  for(i=0; i<N && postId[i]!=id && postId[i]!=-2; i++);
  if(postId[i]==-2) return 0;
  if (i==N) return 0;
  return 1;
}

int compareDate (Date d1, Date d2){
  if (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)==get_day(d2))
    return 1;
  return 0;
}

int compareDateQ (Date d1, Date d2){
  if (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)==get_day(d2))
    return 1;
  if(get_year(d1)>get_year(d2) || (get_year(d1)==get_year(d2) && get_month(d1)>get_month(d2)) || (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)>get_day(d2))) 
    return 2 ;
  return 0;
}

void insereT(Date d,long postId,Date *data,long *id,int N){
  int i,j;
  for(i=0;i<N-1 && data[i]!=NULL && compareDateQ(data[i],d)==2;i++);
  if(data[i]==NULL){
    data[i] = d;
    id[i] = postId;
  }
  else{
    if(i==N-1 && compareDateQ(data[i],d)==0) {
      data[i] = d;
      id[i] = postId;
    } 
    else{
      for(j=N-1;j>i;j--){
        data[j] = data[j-1];
        id[j] = id[j-1];
      }
      if(compareDateQ(data[i],d)!=2){
        data[i] = d;
        id[i] = postId;
      }
    }
  }
}

void insereTag (long tag, long* p, int* s, int N){ 
  int i;
  for(i=0;i<N-1 && p[i]!=-2 && p[i]!=tag; i++);
  if (p[i]==tag) s[i]++;
  else{
    p[i]=tag; 
    s[i]=1;
  }
}

HashTableQuery7 initHashQ7 (int N){
  HashTableQuery7 tag = malloc(N*sizeof(Query7*));
  for (int i=0; i<N; i++){
    tag[i] = NULL;
  }
  return tag;
}

void insereTQ7 (HashTableQuery7 h1, int i,int flag,int contador, long id){
  Query7 *new= malloc(sizeof(Query7));
  new->id = id;  
  new->contador=contador;  
    new->flag = flag;  
  h1[i]=new;
}

int existeQ7(HashTableQuery7 h,int i){
  if(h[i]!=NULL) return 1;
  return 0;
}

HashTableQuery11 initHashQuery11 (int N){
  HashTableQuery11 tag = malloc(N*sizeof(Query11*));
  for (int i=0; i<N; i++){
    tag[i] = NULL;
  }
  return tag;
}

void insereTQuery11 (HashTableQuery11 h1, int i,char* tag,int contador, long id){
  Query11 *new= malloc(sizeof(Query11));
  new->id = id;  
  new->contador=contador;  
  new->tag = mystrdup(tag);  
  h1[i]=new;
}

int existeQ11(HashTableQuery11 h,int i){
  if(h[i]!=NULL) return 1;
  return 0;
}
