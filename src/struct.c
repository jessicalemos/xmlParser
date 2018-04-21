#include "interface.h"
#include <stdlib.h>
#include "struct.h"
#include "auxiliary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct elemento{
    long id;   /*id do utilizador*/
    int count; /*número de posts */
}elem;

typedef struct heap{
    int   size; /* Tamanho alocado para a Heap */
    int   used; /* Número de elementos da Heap */
    elem *array;
}*Heap;

typedef struct elemPosts{
    long id;  /*id do post */
    Date data; /* Data de um post */
}elemP;

typedef struct heapPosts{
    int   size; /* Tamanho alocado para a Heap */
    int   used; /* Número de elementos da Heap */
    elemP *array;
}*HeapPosts;

typedef struct users{
	long ownerUserId; /* id */
	char *displayName; /*nome */
	int reputation; /* reputação */
	int nPosts; /* número de posts */
	char *aboutMe; /*short bio */
	HeapPosts top10; /* heap com os IDs dos posts do utilizador */
} Users;

typedef struct users **HashTableUsers;

typedef struct tags{
	long id; /*id da tag*/
	char* tagName; /*nome da tag*/
} Tags;

typedef struct tags **HashTableTags;

typedef struct post{
	int postTypeId; /* Tipo do post: 1-> tipo resposta e 2-> tipo pergunta */
	long parentId; /* Id do pots ao qual foi feito uma resposta */
	long id; 
    char *tag; 
	char *title; /* Titulo */
	long ownerUserId; /* Id do utilizador */
	Date creationDate; /* Data de criação do post */	
	char *question; /* Conteúdo do post */
	int answerCount; /* Número de respostas ao post */
	int commentCount; /* Número de comentários ao post */
	int score; 
    struct post *esq,*dir;
} Post;

typedef struct treeHash{
    long contadorR; /* Número de pots tipo resposta */
    long contadorP; /* Número de posts tipo pergunta */
    int numRespostas; /* Número de posts tipo resposta e tipo pergunta */
    Post* tree; /*Árvore com os posts de cada dia*/
} TreeHash;

typedef struct treeHash **TreeHashData;

typedef struct TCD_community{
	int dataSize;  /* Tamanho da tabela de hash das datas/pots */
	int usersSize; /* Tamanho da tabela de hash dos utilizadores */
	int tagsSize; /* Tamanho da tabela de hash das tags */
	TreeHashData treeHash; /* Tabela de hash com os vários dias/pots */
	HashTableUsers hashUser;  /* Tabela de hash dos utilizadores */
	HashTableTags hashTag; /* Tabela de hash das tags */
	long *topN; /* Apontador para o array com os ids do top N */
	Heap Top; /* Heap com os ids de utilizador organizada pelo número de posts*/
}TCD_community;

int TAD_community_get_usersSize(TAD_community com){
	return com->usersSize;
}

int TAD_community_get_dataSize(TAD_community com){
	return com->dataSize;
}

int TAD_community_get_tagsSize(TAD_community com){
	return com->tagsSize;
}

long get_topN(TAD_community com, int i){
	return(com->topN[i]);
}

char* post_getTag (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->tag;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return NULL;
}

int post_getScore (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->score;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

int treeHash_getNumRespostas (TAD_community com, int i){
	return com->treeHash[i]->numRespostas;
}

void TAD_community_set_usersSize(TAD_community com, int usersSize){
	com->usersSize = usersSize;
}

void TAD_community_set_dataSize(TAD_community com, int dataSize){
	com->dataSize = dataSize;
}

void TAD_community_set_tagsSize(TAD_community com, int tagsSize){
	com->tagsSize = tagsSize;
}

TAD_community init(){
    TAD_community com = malloc(sizeof(TCD_community));
    TAD_community_set_dataSize(com,-1);
    TAD_community_set_usersSize(com,-1);
    TAD_community_set_tagsSize(com,-1);
    com->topN=NULL;
    com->Top=NULL;
    return com;
}

TAD_community initHashUsers (TAD_community com, int N){
	HashTableUsers user = malloc(N*sizeof(Users*));
	for (int i=0; i<N; i++){
		user[i] = NULL;
	}
	com->hashUser=user;
	com->topN = malloc((N/2)*sizeof(long));
	for(int j=0;j<N/2;j++) com->topN[j]=-2;
	return com;
}

TAD_community initHashData (TAD_community com, int N){
	TreeHashData tree = malloc(N*sizeof(Post*));
	for (int i=0; i<N; i++){
		tree[i] = NULL;
	}
	com->treeHash=tree;
	return com;
}

void insereTableTags (HashTableTags h1, int i, long id, char* tagName){
	Tags *new = malloc(sizeof(Tags));
	new->id = id;
	new->tagName = tagName; 	
	h1[i]=new;
}

void addTags (TAD_community com,char* tagName, long id){
	int i = tagHash(id,com); 
	while (com->hashTag[i]!=NULL){
		if (i>com->tagsSize) i=0;
		else i++;
	}
	insereTableTags(com->hashTag, i, id, tagName);
}

Post* rotate_right(Post *p){
	Post *q = p->esq;
	p->esq = q->dir;
	q->dir = p;
	return q;
}

Post* insereTree(int score, int postTypeId, long parentId, long id, char *tag, char *title, long ownerUserId, char *question, int answerCount, Date data, int commentCount){
	Post *p = malloc (sizeof(Post));
	if(p!=NULL){
	    p->postTypeId = postTypeId; 
	    p->creationDate=data;
		p->answerCount = answerCount;
		p->ownerUserId = ownerUserId;
		p->id = id;
		p->score = score;
	    p->title = title;
		p->question = question;
		p->parentId = parentId;
		p->commentCount = commentCount;
		p->tag = tag;
		p->esq = NULL;
		p->dir = NULL;
	}
	return p;
}

void retornaAIdR (Post* a, long *p, int *s, int N){
	if (a!=NULL){
		if (a->postTypeId==1){
			insere(a->answerCount,a->id,p,s,N);
		}
	retornaAIdR (a->esq,p,s,N);
	retornaAIdR (a->dir,p,s,N);
	}
}


void retornaAId (TAD_community com,long *p, int *s, int N,int i){
	Post* a = com->treeHash[i]->tree;
	retornaAIdR (a, p, s, N);
}

long* insereUsersA (Post* a, long* array, int i){
	if (a){
	  array[i]=a->ownerUserId;
	  if (a->esq!=NULL) insereUsersA (a->esq, array, i++);
	  if (a->dir!=NULL) insereUsersA (a->dir, array, i++);
	}
	return array;
}

void retorna (TAD_community com, int *r , long *p, int N, int i){ 
	Post* a = com->treeHash[i]->tree;
	long *array = malloc(com->treeHash[i]->numRespostas * sizeof(long));
	int tam = elimRep (insereUsersA (a, array, 0), com->treeHash[i]->numRespostas);
	for (int i=0; i<tam; i++)
		insere(com->hashUser[procuraUser(com,array[i])]->reputation, array[i], p, r, N);
}

int retiraTituloR(Post* a,char* word){
	int c = 0;
	if(a){
	    if(a->title!=NULL && a->postTypeId!=2){
	   		if(contida(a->title,word)) c = 1 + retiraTituloR(a->esq,word) + retiraTituloR(a->dir,word);
	   		else c = retiraTituloR(a->esq,word) + retiraTituloR(a->dir,word);
		}
		else c = retiraTituloR(a->esq,word) + retiraTituloR(a->dir,word);
	}
	return c;
}

int retiraTitulo(TAD_community com,int i,char* word){
	Post* a = com->treeHash[i]->tree;
	return retiraTituloR(a,word);
}

int procuraData(TAD_community com, Date data){
	int chave = dataHash(data,com),i,c=0;
	for(i=chave;com->treeHash[i]!=NULL && c<com->dataSize && !compareDate(com->treeHash[i]->tree->creationDate,data);i++){
		if(i+1>com->dataSize) i=0;
		c++;
	}
	if(com->treeHash[i]!=NULL && compareDate(com->treeHash[i]->tree->creationDate,data)) return i;
	return -1;
}

Heap initHeap(int size){
    Heap h = malloc(sizeof(struct heap));
    if(h != NULL) {
        h->size = size;
        h->used = 0;
        h->array=malloc(size*sizeof(struct elemento));
    }
    return h;
}

void swapPosts(HeapPosts h, int a, int b){
    elemP t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

void insere_Heap(TAD_community com){
    int i,tam=com->usersSize/2;
    com->Top=initHeap(tam);
    for(i=0;i<com->usersSize;i++){
  		if(com->hashUser[i]!=NULL && com->hashUser[i]->nPosts!=0)
   		 	insertHeap((com->Top),com->hashUser[i]->nPosts,com->hashUser[i]->ownerUserId);
    }
}

int extraiHeaps(TAD_community com,int chave1,int chave2,int N,long* id){
	int a = 0;
	HeapPosts h1 = com->hashUser[chave1]->top10; 
	HeapPosts h2 = com->hashUser[chave2]->top10;
	if (h1!=NULL && h2!=NULL){
		a = extraiId(h1,h2,N,id,com,chave1,chave2);
		freeHeapPosts(h1);freeHeapPosts(h2);
	}
	return a;
}

void freeHashTableUsers  (TAD_community com, int size){
	int i;
	Users *cur;
	for (i=0; i<size; i++){
		if (com->hashUser[i]!=NULL){
		cur = com->hashUser[i];
		free(cur->displayName);
		free(cur->aboutMe);
		freeHeapPosts(cur->top10);
		free(cur);}
	}	
	free(com->hashUser);
}