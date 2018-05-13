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

/** 
 * [Cria uma NEW_pair com as informações dadas]
 * @param  fst    [Float a inserir]
 * @param  snd    [Long a inserir]
 * @param  trd    [Inteiro a inserir]
 * @return        [NEW_pair]
 */
NEW_pair create_new_pair(float fst, long snd, int trd) {
  NEW_pair p = malloc(sizeof(struct new_pair));
  p->fst = fst; 
  p->snd = snd;
  p->trd = trd;
  return p;
}

/** 
 * [Altera o float do NEW_pair]
 * @param pair    [NEW_pair]
 * @param l       [Novo float]
 */
void set_fst_new(NEW_pair pair, float l) {
  pair->fst = l;
}

/** 
 * [Altera o long do NEW_pair]
 * @param pair    [NEW_pair]
 * @param l       [Novo long]
 */
void set_snd_new(NEW_pair pair, long l) {
  pair->snd = l;
}

/** 
 * [Altera o int do NEW_pair]
 * @param pair    [NEW_pair]
 * @param l       [Novo int]
 */
void set_trd_new(NEW_pair pair, int l) {
  pair->trd = l;
}

/** 
 * [Para obter o float do NEW_pair]
 * @param pair    [NEW_pair]
 * @return        [O float do NEW_pair]
 */
float get_fst_new(NEW_pair pair) {
  return pair->fst;
}

/** 
 * [Para obter o int do NEW_pair]
 * @param pair    [NEW_pair]
 * @return        [O int do NEW_pair]
 */
int get_trd_new(NEW_pair pair) {
  return pair->trd;
}

/** 
 * [Para obter o long do NEW_pair]
 * @param pair    [NEW_pair]
 * @return        [O long do NEW_pair]
 */
long get_snd_new(NEW_pair pair) {
  return pair->snd;
}

/** 
 * [Liberta o NEW_pair]
 * @param pair    [NEW_pair]
 */
void free_new_pair(NEW_pair pair) {
    free(pair);
}

typedef struct query7{
  long id; /*id da tag*/
  int flag;
  int contador;
} Query7;

/** 
 * [Para obter o id de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Id]
 */
long get_id_Q7(HashTableQuery7 h,int i) {
  return h[i]->id;
}

/** 
 * [Para obter a flag de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Flag]
 */
int get_flag_Q7(HashTableQuery7 h,int i) {
  return h[i]->flag;
}

/** 
 * [Para obter o contador de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Contador]
 */
int get_contador_Q7(HashTableQuery7 h,int i) {
  return h[i]->contador;
}

/** 
 * [Altera o id de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  l    [Novo id]
 * @param  i    [Posição da hash]
 */
void set_id_Q7(HashTableQuery7 h, long l,int i) {
  h[i]->id = l;
}

/** 
 * [Altera a flag de uma determinada posição da hash]
 * @param  h       [Hash]
 * @param  flag    [Nova flag]
 * @param  i       [Posição da hash]
 */
void set_flag_Q7(HashTableQuery7 h, int flag,int i) {
  h[i]->flag = flag;
}

/** 
 * [Altera o contador de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  l    [Novo contador]
 * @param  i    [Posição da hash]
 */
void set_contador_Q7(HashTableQuery7 h, int l,int i) {
  h[i]->contador = l;
}

typedef struct query11{
  long id; /*id da tag*/
  char* tag;
  int contador;
} Query11;

/** 
 * [Para obter o id de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Id]
 */
long get_id(HashTableQuery11 h,int i) {
  return h[i]->id;
}

/** 
 * [Para obter a tag de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Tag]
 */
char* get_tag(HashTableQuery11 h,int i) {
       return h[i]->tag;
}

/** 
 * [Para obter o número de vezes que uma tag de uma determinada posição da hash ocorre]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Contador]
 */
int get_contador(HashTableQuery11 h,int i) {
  return h[i]->contador;
}

/** 
 * [Altera o id de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  l    [Novo id]
 * @param  i    [Posição da hash]
 */
void set_id(HashTableQuery11 h, long l,int i) {
 h[i]->id = l;
}

/** 
 * [Altera a tag de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  tag  [Nova tag]
 * @param  i    [Posição da hash]
 */
void set_tag(HashTableQuery11 h, char* tag,int i) {
  h[i]->tag = tag;
}

/** 
 * [Altera o contador de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  l    [Novo contador]
 * @param  i    [Posição da hash]
 */
void set_contador(HashTableQuery11 h, int l,int i) {
  h[i]->contador = l;
}

typedef struct hashTopN{
  long id;
} HashTopN;

/** [Para obter o id de uma determinada posição da hash]
 * @param  h    [Hash]
 * @param  i    [Posição da hash]
 * @return      [Id]
 */
long get_id_HashTopN(HashTableTopN h,int i) {
 if(h[i]!=NULL)
   return h[i]->id;
 else return -1;
}

/**
 * [Encontra o máximo entre dois inteiros]
 * @param  e     [Inteiro a comparar]
 * @param  d     [Inteiro a comparar]
 * @return       [Máximo]
 */
int max(int e,int d){
  return e>d?e:d;
}

/**
 * [Verifica se uma determinada tag se encontra num conjunto de tags]
 * @param  s     [Conjunto de tags]
 * @param  t     [Tag a verificar]
 * @return       [Booleano de comparação]
 */
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

/**
 * [Função que insere ordenadamente uma data e um valor inteiro na mesma posição dos arrays respetivos, com fator de ordenação o inteiro]
 * @param  x     [Valor a inserir]
 * @param  id    [Id a inserir]
 * @param  p     [Array de ids]
 * @param  s     [Array de inteiros]
 * @param  N     [Tamanho dos arrays]
 */
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

/**
 * [Verifica se uma palara está contida num conjunto de palavras]
 * @param  s      [Conjunto de palavras]
 * @param  word   [Palavra a comparar]
 * @return        [Booleano de comparação]
 */
int contida (char* s,char* word){
  int i = 0, j=0;
  while(s[i]!='\0'){
    while((s[i] != '\0') && (isspace(s[i])))
      i++; 
    while((s[i] != '\0') && word[j]!='\0' && s[i]==word[j]){
      i++; j++; 
    }
    if (word[j]=='\0') return 1;
    else {j=0; if(s[i]!='\0') i++;}
  }
  return 0;
}

/**
 * [Verifica se um id se encontra num array de ids]
 * @param  postId  [Array de ids]
 * @param  id      [Id a comparar]
 * @param  N       [Tamanho do array]
 * @return         [Booleano de comparação]
 */
int procuraArray (long* postId, long id, int N){
  int i;
  for(i=0; i<N && postId[i]!=id && postId[i]!=-2; i++);
  if (i==N) return 0;
  else if(postId[i]==-2) return 0;
  return 1;
}

/**
 * [Verifica se duas datas são iguais]
 * @param  d1     [Data]
 * @param  d2     [Data]
 * @return        [Booleano de comparação]
 */
int compareDate (Date d1, Date d2){
  if (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)==get_day(d2))
    return 1;
  return 0;
}

/**
 * [Estabelece uma relação entre duas datas]
 * @param  d1     [Data]
 * @param  d2     [Data]
 * @return        [Booleano de comparação]
 */
int compareDateQ (Date d1, Date d2){
  if (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)==get_day(d2))
    return 1;
  if(get_year(d1)>get_year(d2) || (get_year(d1)==get_year(d2) && get_month(d1)>get_month(d2)) || (get_year(d1)==get_year(d2) && get_month(d1)==get_month(d2) && get_day(d1)>get_day(d2))) 
    return 2 ;
  return 0;
}

/**
 * [Função que insere ordenadamente uma data e um id na mesma posição dos arrays respetivos, com fator de ordenação a data]
 * @param  d          [Data]
 * @param  postId     [Id]
 * @param  data       [Array de datas]
 * @param  id         [Array de ids]
 * @param  N          [Tamanho do array]
 */
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

/**
 * [Insere uma tag num array de ids de tags e caso esta já exista aumenta ao número de vezes que esta ocorre no array respetivo]
 * @param  tag   [Id da tag]
 * @param  p     [Array de ids das tags]
 * @param  s     [Array do número de vezes que cada tag ocorre]
 * @param  N     [Tamanho dos arrays]
 */
void insereTag (long tag, long* p, int* s, int N){ 
  int i;
  for(i=0;i<N-1 && p[i]!=-2 && p[i]!=tag; i++);
  if (p[i]==tag) s[i]++;
  else{
    p[i]=tag; 
    s[i]=1;
  }
}

/**
 * [Inicialização da HashTableQuery7]
 * @param  N       [Tamanho da HashTableQuery7]
 * @return         [HashTableQuery7]
 */
HashTableQuery7 initHashQ7 (int N){
  HashTableQuery7 tag = malloc(N*sizeof(Query7*));
  for (int i=0; i<N; i++){
    tag[i] = NULL;
  }
  return tag;
}

/**
 * [Insere numa determinada posição da hash um novo id, uma nova flag e um novo id]
 * @param  h1            [HashTableQuery7]
 * @param  i             [Posição da hash]
 * @param  flag          [Flag]
 * @param  contador      [Contador]
 * @param  id            [Id]
 */
void insereTQ7 (HashTableQuery7 h1, int i,int flag,int contador, long id){
  Query7 *new= malloc(sizeof(Query7));
  new->id = id;  
  new->contador=contador;  
    new->flag = flag;  
  h1[i]=new;
}

/**
 * [Verifica se uma determinada posição da hash é nula]
 * @param  h       [HashTableQuery7]
 * @param  i       [Posição da hash]
 * @return         [Booleano de comparação]
 */
int existeQ7(HashTableQuery7 h,int i){
  if(h[i]!=NULL) return 1;
  return 0;
}

/**
 * [Liberta a HashTableQuery7]
 * @param  h          [HashTableQuery7]
 * @param  size       [Tamanho da HashTableQuery7]
 */
void freeHashTableQuery7 (HashTableQuery7 h, int size){
  int i;
  Query7 *cur;
  for (i=0; i<size; i++){
    if (h[i]!=NULL){
      cur = h[i];
      free(cur);
    }
  } 
  free(h);
}

/**
 * [Inicialização da HashTableQuery11]
 * @param  N       [Tamanho da HashTableQuery11]
 * @return         [HashTableQuery11]
 */
HashTableQuery11 initHashQuery11 (int N){
  HashTableQuery11 tag = malloc(N*sizeof(Query11*));
  for (int i=0; i<N; i++){
    tag[i] = NULL;
  }
  return tag;
}

/**
 * [Insere numa detreminada posição da hash um novo elemento]
 * @param  h1           [HashTableQuery11]
 * @param  i            [Posição da hash]
 * @param  tag          [Tag]
 * @param  contador     [Contador]
 * @param  id           [Id]
 */
void insereTQuery11 (HashTableQuery11 h1, int i,char* tag,int contador, long id){
  Query11 *new= malloc(sizeof(Query11));
  new->id = id;  
  new->contador=contador;  
  new->tag = mystrdup(tag);  
  h1[i]=new;
}

/**
 * [Verifica se uma determinada posição da hash é nula]
 * @param  h      [HashTableQuery11]
 * @param  i      [Posição da hash]
 * @return        [Booleano de comparação]
 */
int existeQ11(HashTableQuery11 h,int i){
  if(h[i]!=NULL) return 1;
  return 0;
}

/**
 * [Liberta a HashTableQuery11]
 * @param  h          [HashTableQuery11]
 * @param  size       [Tamanho da HashTableQuery11]
 */
void freeHashTableQuery11 (HashTableQuery11 h, int size){
  int i;
  Query11 *cur;
  for (i=0; i<size; i++){
    if (h[i]!=NULL){
      cur = h[i];
      free(cur->tag);
      free(cur);
    }
  } 
  free(h);
}

/**
 * [Inicialização da hashTopN]
 * @param  N       [Tamanho da hashTopN]
 * @return         [HashTableTopN]
 */
HashTableTopN initHashTopN (int N){
  HashTableTopN t = malloc(N*sizeof(HashTopN*));
  for (int i=0; i<N; i++){
    t[i] = NULL;
  }
  return t;
}

/**
 * [Insere numa determinada posição da hash um novo id]
 * @param  h1      [HashTableTopN]
 * @param  i       [Posição da hash]
 * @param  id      [Id]
 */
void insereHashTopN (HashTableTopN h1, int i,long id){
  HashTopN *new= malloc(sizeof(HashTopN));
  new->id = id;     
  h1[i]=new;
}

/**
 * [Verifica se uma determinada posição da hash é nula]
 * @param  h       [HashTableTopN]
 * @param  i       [Posição da hash]
 * @return         [Booleano de comparação]
 */
int existeHashTopN(HashTableTopN h,int i){
  if(h[i]!=NULL) return 1;
  return 0;
}

/**
 * [Liberta a HashTableTopN]
 * @param  h          [HashTableTopN]
 * @param  size       [Tamanho da HashTableTopN]
 */
void freeHashTableTopN (HashTableTopN h, int size){
  int i;
  HashTopN *cur;
  for (i=0; i<size; i++){
    if (h[i]!=NULL){
      cur = h[i];
      free(cur);
    }
  } 
  free(h);
}
