#include "interface.h"
#include <stdlib.h>
#include "struct.h"
#include "auxiliary.h"
#include <stdio.h>
#include <string.h>
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
	long *topNR; /* Apontador para o array com os ids do top N dos utilizadore com melhor reputação */
	Heap Top; /* Heap com os ids de utilizador organizada pelo número de posts*/
	Heap TopR; /* Heap com os ids de utilizador organizada pela reputação*/
	
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

long get_topNR(TAD_community com, int i){
	return(com->topNR[i]);
}

char* users_getDisplayName (TAD_community com, int i){
	return com->hashUser[i]->displayName;
}

char* users_getAboutMe (TAD_community com, int i){
	return com->hashUser[i]->aboutMe;
}

Date post_getCreationDate (TAD_community com, int i){
	return com->treeHash[i]->tree->creationDate;
}

int post_getPostTypeId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->postTypeId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

char* post_getTitle (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->title;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return NULL;
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

long post_getOwnerUserId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->ownerUserId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

long post_getparentId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->parentId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

int treeHash_getNumRespostas (TAD_community com, int i){
	return com->treeHash[i]->numRespostas;
}

long treeHash_getContadorR (TAD_community com, int i){
	return com->treeHash[i]->contadorR;
}

long treeHash_getContadorP (TAD_community com, int i){
	return com->treeHash[i]->contadorP;
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
    com->topNR=NULL;
    com->TopR=NULL;
    return com;
}

TAD_community initHashUsers (TAD_community com, int N){
	HashTableUsers user = malloc(N*sizeof(Users*));
	for (int i=0; i<N; i++){
		user[i] = NULL;
	}
	com->hashUser=user;
	com->topNR = malloc((N/2)*sizeof(long));
	com->topN = malloc((N/2)*sizeof(long));
	for(int j=0;j<N/2;j++){
        com->topN[j]=-2;
		com->topNR[j]=-2;
	return com;
}

TAD_community initHashTags (TAD_community com, int N){
	HashTableTags tag = malloc(N*sizeof(Tags*));
	for (int i=0; i<N; i++){
		tag[i] = NULL;
	}
	com->hashTag=tag;
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

HeapPosts initHeapPosts(int size){
    HeapPosts h = malloc(sizeof(struct heapPosts));
    if(h != NULL) {
        h->size = size;
        h->used = 0;
        h->array=malloc(size*sizeof(struct elemPosts));
    }
    return h;
}

int userHash (long i, TAD_community com){
	if (i < 0) return (-(i % com->usersSize));
	else return (i % (com->usersSize));
}

void insereTableUsers (HashTableUsers h1, int i, int reputation, long id, char *name, char *about){
	int tam=10;
	Users *new= malloc(sizeof(Users));
	new->ownerUserId = id;  
	new->reputation = reputation; 
	new->displayName = name;
	new->nPosts = 0;
	new->aboutMe = about;
	new->top10=initHeapPosts(tam);
	h1[i]=new;
}

void addUser (TAD_community com,int reputation, long id,char *name,char *about){
	int i = userHash(id,com);
	while (com->hashUser[i]!=NULL && !(com->hashUser[i]->ownerUserId == id)){
		if (i>com->usersSize) i=0;
		else i++;
	}
	insereTableUsers(com->hashUser,i,reputation, id, name, about);
}

int procuraUser (TAD_community com, long id){
	int i, chave = userHash(id,com),c=0;
	for (i=chave; com->hashUser[i]!=NULL && c<com->usersSize && com->hashUser[i]->ownerUserId!=id; i++){
		if (i+1>com->usersSize) i=0;
		c++;
	}
	if (com->hashUser[i]!=NULL && com->hashUser[i]->ownerUserId==id) return i;
	else return -1;
}

void incrementaPost(TAD_community com, long id){
	int i = procuraUser(com, id);
	com->hashUser[i]->nPosts++;
}

int tagHash (char* s, TAD_community com){
	int l = strlen(s),soma = 0;
    for(int i=0; i<l; i++)
        soma += s[i];
	return (soma % com->tagsSize);
}

void insereTableTags (HashTableTags h1, int i, long id, char* tagName){
	Tags *new = malloc(sizeof(Tags));
	new->id = id;
	new->tagName = tagName; 	
	h1[i]=new;
}

void addTags (TAD_community com,char* tagName, long id){
	int i = tagHash(tagName,com); 
	while (com->hashTag[i]!=NULL){
		if (i>com->tagsSize) i=0;
		else i++;
	}
	insereTableTags(com->hashTag, i, id, tagName);
}

int dataHash (Date data, TAD_community com){
	int i = get_day(data) + get_month(data) + get_year(data);
	return ((i) % com->dataSize); 
}

int height(Post *p){
	int altura = 0;
	if(p!=NULL){
		altura = 1 + max(height(p->esq),height(p->dir));
	}
	return altura;
}

Post* rotate_right(Post *p){
	Post *q = p->esq;
	p->esq = q->dir;
	q->dir = p;
	return q;
}

Post* rotate_left(Post *p){
	Post *q = p->dir;
	p->dir = q->esq;
	q->esq = p;
	return q;
}

Post* balancaTree (Post *p){
	Post *p1 = p->esq;	
	Post *p2 = p->dir;
	if ( height(p->esq) - height(p->dir) == 2 ){
		if ( height(p1->dir) > height(p1->esq) )
			p->esq = rotate_left(p->esq);
		return rotate_right(p);
	}
	else if ( height(p->dir) - height(p->esq) == 2 ){
		if ( height(p2->esq) > height(p2->dir) )
			p->dir = rotate_right(p->dir);
		return rotate_left(p);
	}
	return p;
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

Post* rec(Post* c,int score, int postTypeId,long parentId, long id, char *tag, char *title, long ownUserId, char *question, int answerCount, Date data, int commentCount){
	if(c==NULL){
	    return insereTree(score, postTypeId,parentId,id,tag,title,ownUserId,question,answerCount,data,commentCount);
	}
    else{
    	if(c->id>id) c->esq=rec(c->esq,score,postTypeId,parentId,id,tag,title,ownUserId,question,answerCount,data,commentCount);
        else c->dir=rec(c->dir,score,postTypeId,parentId,id,tag,title,ownUserId,question,answerCount,data,commentCount);
    }
    return balancaTree(c);
}
 
void addPost (TAD_community com,int score,int postTypeId,long parentId, long id, char *tag, char *title, long ownerUserId, char *question, int answerCount, Date data,int commentCount){
	int i=dataHash(data,com); 
	while (com->treeHash[i]!=NULL && !compareDate(com->treeHash[i]->tree->creationDate,data)){
		if (i>com->dataSize) i=0;
		else i++;
	}
	if(com->treeHash[i]==NULL){
			TreeHash *new= malloc(sizeof(TreeHash));
			new->tree=NULL;
			com->treeHash[i]=new;
		    com->treeHash[i]->contadorR = 0;
        	com->treeHash[i]->contadorP = 0;
        	com->treeHash[i]->numRespostas = 0;
	}
    com->treeHash[i]->tree=rec(com->treeHash[i]->tree,score,postTypeId,parentId,id,tag,title,ownerUserId,question,answerCount,data,commentCount);
    incrementaPost(com,ownerUserId);
    if (postTypeId ==1 || postTypeId == 2) insere_Heap_Posts(com,ownerUserId,id,data);
    if (postTypeId == 2) com->treeHash[i]->contadorR++;
    if (postTypeId == 1) com->treeHash[i]->contadorP++;
    com->treeHash[i]->numRespostas++;
}

int procuraPost (TAD_community com, long id){
	for(int i=0; i< com->dataSize; i++){
		if (com->treeHash[i]!=NULL){
			Post* a= com->treeHash[i]->tree;
			while (a){
				if (a->id == id) return i;
				else if (a->id > id && a->esq!=NULL ) a=a->esq;
				else a=a->dir;
			}
		}
	}
	return -1;
}

int contaTagR (Post* a, char* tag){
	int c=0;
	if (a!=NULL){
		if (a->tag!=NULL && a->postTypeId!=2){ 
			if (verificaTag(a->tag,tag)==1){   
				c = 1 + contaTagR(a->esq, tag) + contaTagR(a->esq, tag);
			}
			else {c = contaTagR(a->esq, tag) + contaTagR(a->dir, tag);}
		}
		else {c = contaTagR(a->esq, tag) + contaTagR(a->dir, tag);}
	}
	return c;
}

int contaTag (TAD_community com, int i, char* tag){
	Post* a = com->treeHash[i]->tree;
	return contaTagR (a,tag);
}

int existeTree (TAD_community com, int i){
    if(com->treeHash[i]!=NULL) return 1;
    return 0;
}

void retornaIdR (Post* a, char* tag, long* p, int c){
	int i;
	if (a!=NULL){
		if (a->tag!=NULL && a->postTypeId!=2){
			if (verificaTag(a->tag,tag)==1){
				for (i=0; i<c && p[i]!=-2; i++);
				p[i] = a->id;
			}
		}
	retornaIdR (a->esq,tag,p,c);
	retornaIdR (a->dir,tag,p,c);
	}
}

void retornaId (TAD_community com, int i, long* p, char* tag, int c){
	Post* a = com->treeHash[i]->tree;
	retornaIdR (a, tag, p, c);
}

void retornaSIdR (Post* a, long *p, int *s, int N){
	if (a!=NULL){
		if (a->postTypeId!=1){
      		insere(a->score,a->id,p,s,N);
		}
	retornaSIdR (a->esq,p,s,N);
	retornaSIdR (a->dir,p,s,N);}
}

void retornaSId (TAD_community com,long *p, int *s, int N,int i){
	Post* a = com->treeHash[i]->tree;
	retornaSIdR (a, p, s, N);
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

void procuraTituloR(Post *a,char *word,Date *data,long *id,int N){
	if(a){
		if(a->title!=NULL && a->postTypeId!=2)
			if(contida(a->title,word)) insereT(a->creationDate,a->id,data,id,N);
		procuraTituloR(a->esq,word,data,id,N);
		procuraTituloR(a->dir,word,data,id,N);
	}
}

void procuraTitulo(TAD_community com,char *word,Date *data,long *id,int N){
	int i;
	for(i=0;i<com->dataSize;i++){
		if(com->treeHash[i]!=NULL){
			Post *a=com->treeHash[i]->tree;
			procuraTituloR(a,word,data,id,N);
		}
	}
}

int contaTR (Post* a, char* word){
	int c=0;
	if (a!=NULL){
		if (a->title!=NULL && a->postTypeId!=2){ 
			if (contida(a->title,word)==1){   
				c = 1 + contaTR(a->esq, word) + contaTR(a->esq, word);
			}
			else c = contaTR(a->esq, word) + contaTR(a->dir, word);
		}
		else c = contaTR(a->esq, word) + contaTR(a->dir, word);
	}
	return c;
}

int contaT (TAD_community com, int i, char* word){
	Post* a = com->treeHash[i]->tree;
	return contaTR (a,word);
}

void guardaRespostas(TAD_community com, Post* a, long id, float max, int flag, NEW_pair p){
	float c = 0;
	if(a!=NULL && get_trd_new(p)!=0){
		if(a->postTypeId==2 && a->parentId == id){
			set_trd_new(p,get_trd_new(p)-1);
			c = (com->hashUser[procuraUser(com,a->ownerUserId)]->reputation)*0.25 + (a->score)*0.65 + (a->commentCount)*0.1;
			if(flag==0) {
				set_snd_new(p,a->id);
				set_fst_new(p,c);
				flag = 1;
			}
			else if(c>max) {
				set_snd_new(p,a->id);
				set_fst_new(p,c);
			}
		}
		guardaRespostas(com,a->esq, id, max, flag,p);
		guardaRespostas(com,a->dir, id, max, flag,p);
	}
}

long procuraRespostas(TAD_community com, long id){
	int i,j,flag = 0,local = procuraPost(com,id),nRespostas=0;
	float max = 0,maximo = 0;
	NEW_pair p= create_new_pair(0,-2,nRespostas);
	long idM=-2;
	if(local!=-1){
		Post *b = com->treeHash[local]->tree;
		while(b){
			if(b->id==id){
				if(b->postTypeId==1) {nRespostas = b->answerCount;break;}
		    	else return -2;
			}
			else if(b->id>id && b->esq!=NULL) b = b->esq;
				 else b = b->dir;
		}
		set_trd_new(p,nRespostas);
		for(i=local;i<com->dataSize && nRespostas!=0;i++){
			if(com->treeHash[i]!=NULL){
				Post* a = com->treeHash[i]->tree;
				guardaRespostas(com,a,id,max,0,p);
				nRespostas = get_trd_new(p);
				if(get_snd_new(p)!=-2 && flag==0) {
					maximo = get_fst_new(p);
					idM = get_snd_new(p);
					flag = 1;
				}
				if(get_fst_new(p)>maximo && flag==1) {
					maximo = get_fst_new(p);
					idM = get_snd_new(p);
				}
			}
		}
		if(nRespostas!=0){
			for(j=0;j<i && nRespostas!=0;j++){
				if(com->treeHash[j]!=NULL){
					Post* a = com->treeHash[j]->tree;
					guardaRespostas(com,a,id,max,0,p);
					nRespostas = get_trd_new(p);
					if(get_snd_new(p)!=-2 && flag==0) {
						maximo = get_fst_new(p);
						idM = get_snd_new(p);
	     				flag = 1;				
					}
					if(get_fst_new(p)>maximo && flag==1) {
						maximo = get_fst_new(p);
						idM = get_snd_new(p);	
					}
				}
			}
		}
	}
	free_new_pair(p);
	return idM;
}

LONG_pair existeData(TAD_community com, Date b, Date f, int chaveB, int chaveE){
	long fst=-1,snd=-1;
	if(chaveE>=chaveB){
		for(int i=chaveE;i<com->dataSize && (fst==-1 || snd==-1);i++){
			if(com->treeHash[i]!=NULL){
				if(compareDate(com->treeHash[i]->tree->creationDate,b)==1) fst=i;
				if(compareDate(com->treeHash[i]->tree->creationDate,f)==1) snd=i;
			}
		}
		if(fst==-1){
			for(int i=0;i<chaveE && (fst==-1 || snd==-1);i++){
				if(com->treeHash[i]!=NULL){
					if(compareDate(com->treeHash[i]->tree->creationDate,b)==1) fst=i;
					if(compareDate(com->treeHash[i]->tree->creationDate,f)==1) snd=i;
				}
			}
		}
		else if(snd==-1){
			for(int i=0;i<chaveE &&  snd==-1;i++)
				if(com->treeHash[i]!=NULL){
					if(compareDate(com->treeHash[i]->tree->creationDate,f)==1) snd=i;
				}
			}
	}
	else{
		for(int j=chaveE;j<com->dataSize && fst==-1;j++){
			if(com->treeHash[j]!=NULL){
				if(compareDate(com->treeHash[j]->tree->creationDate,b)==1) fst=j;
				if(compareDate(com->treeHash[j]->tree->creationDate,f)==1) snd=j;
			}
		}
		for(int j=0;j<chaveE && snd==-1;j++){
			if(com->treeHash[j]!=NULL){
				if(compareDate(com->treeHash[j]->tree->creationDate,f)==1) snd=j;
			}
		}
	}
	return create_long_pair(fst,snd);
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

void swapPosts(HeapPosts h, int a, int b){
    elemP t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

void bubbleUpPosts(HeapPosts h, int i){                
    while (i!=0 && compareDateQ(h->array[i].data,h->array[PARENT(i)].data)==2) {
        swapPosts(h, i, PARENT(i));
        i = PARENT(i);
    }
}

void bubbleDownPosts(HeapPosts h, int N){    
    int i = 0, max ;
    while (RIGHT(i) < N && compareDateQ(h->array[max=(compareDateQ(h->array[LEFT(i)].data,h->array[RIGHT(i)].data)==2) ? LEFT(i) : RIGHT(i)].data, h->array[i].data)==2) {
        swapPosts(h, i, max);
        i = max;
    }
    if (LEFT(i) < N && compareDateQ(h->array[LEFT(i)].data,h->array[i].data)==2)
        swapPosts(h, i, LEFT(i));
}

int insertHeapPosts(HeapPosts h,Date data,long id){
    if (h->used == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(struct elemPosts));
        h->size *= 2;
    }
    assert( h!= NULL);
    h->array[h->used].data= data;
    h->array[h->used].id= id;
    (h->used)++;
    bubbleUpPosts(h, h->used-1);
    return 1;
}

long extractMaxPosts2(HeapPosts h,HeapPosts h2){
    if (h->used > 0) {
        elemP novo= h->array[0];
        long res=novo.id;
        insertHeapPosts(h2,novo.data,res);
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDownPosts(h, h->used);
        return res;
    } else return -1;
}

void procuraId(HeapPosts h, TAD_community com, long* postId, HeapPosts h3){
	int c = h->used, j; 
	long idP;
	for(j=0;j<c;j++){
		Date data = h->array[0].data;
		idP = extractMaxPosts2(h,h3);
		int chave = procuraData(com,data);
		if(post_getPostTypeId(com,chave,idP)==1){
			postId[j]=idP; 
		}
		else if (post_getPostTypeId(com,chave,idP)==2){
			long id = post_getparentId(com,chave,idP); 
			postId[j] = id; 
		}
	}
}

int extraiId(HeapPosts h1,HeapPosts h2,int N,long* id,TAD_community com,int chave1,int chave2){
	int k=0; 
	if(h1->used<h2->used) {
		int c = h2->used,j;
		int a = h1->used;
		HeapPosts h3 = initHeapPosts(c);
		HeapPosts h4 = initHeapPosts(a);
		long* ID = malloc(c*sizeof(long));
		procuraId(h2,com,ID,h3);
		for(j=0;j<a && k<N;j++){
			Date data = h1->array[0].data;
			long postId;
			postId = extractMaxPosts2(h1,h4);
			if(post_getPostTypeId(com,procuraData(com,data),postId)==1 && procuraArray(ID,postId,c)){
				id[k] = postId; k++;
			}
			else {
				long idP = post_getparentId(com,procuraData(com,data),postId);
				if(procuraArray(ID,idP,c)!=0){
					id[k] = idP ;
					k++;
				 }
			}
		}
		com->hashUser[chave2]->top10=h3;com->hashUser[chave1]->top10=h4;free(ID);
	}
	else{
		int c = h1->used,j;
		int a = h2->used;
		HeapPosts h3 = initHeapPosts(c);
		HeapPosts h4 = initHeapPosts(a);
		long* ID = malloc(c*sizeof(long));
		procuraId(h1,com,ID,h3);
		for(j=0;j<a && k<N;j++){
			Date data = h2->array[0].data;
			long postId = extractMaxPosts2(h2,h4);
			if(post_getPostTypeId(com,procuraData(com,data),postId)==1 && procuraArray(ID,postId,c)!=0){
				id[k] = postId; 
			}
			else {
				long idP = post_getparentId(com,procuraData(com,data),postId);
				if(procuraArray(ID,idP,c)!=0){
					id[k] = idP ;
					k++;
				 }
			}
		}
		com->hashUser[chave1]->top10=h3;
	    com->hashUser[chave2]->top10=h4;free(ID);
	}
	return k;
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

void swap(Heap h, int a, int b){
    elem t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

void bubbleUp(Heap h, int i){
    while (i!=0 && h->array[i].count > h->array[PARENT(i)].count) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}

void bubbleDown(Heap h, int N){
    int i = 0, max ;
    while (RIGHT(i) < N && h->array[max = h->array[LEFT(i)].count > h->array[RIGHT(i)].count ? LEFT(i) : RIGHT(i)].count > h->array[i].count) {
        swap(h, i, max);
        i = max;
    }
    if (LEFT(i) < N && h->array[LEFT(i)].count > h->array[i].count)
        swap(h, i, LEFT(i));
}

int insertHeap(Heap h,int count,long id){
    if (h->used == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(struct elemento));
        h->size *= 2;
    }
    assert( h!= NULL);
    h->array[h->used].count= count;
    h->array[h->used].id= id;
    (h->used)++;
    bubbleUp(h, h->used-1);
    return 1;
}

long extractMax(Heap h){
    if (h->used > 0) {
        elem novo= h->array[0];
        long res=novo.id;
       
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDown(h, h->used);
        return res;
    } 
    else return -1;
}

void insere_Heap(TAD_community com){
    int i,tam=com->usersSize/2;
    com->Top=initHeap(tam);
    for(i=0;i<com->usersSize;i++){
  		if(com->hashUser[i]!=NULL && com->hashUser[i]->nPosts!=0)
   		 	insertHeap((com->Top),com->hashUser[i]->nPosts,com->hashUser[i]->ownerUserId);
    }
}

void insere_Heap_Posts(TAD_community com,long ownerUserId, long id, Date data){
	int i = procuraUser(com, ownerUserId);
	insertHeapPosts(com->hashUser[i]->top10,data,id);
}

void freeHeapPosts(HeapPosts r){
    if(r != NULL) {
        free(r->array);
        free(r);
    }
}

long* retornaTop10(TAD_community com, int i){
	long* id = malloc(10*sizeof(long));
	int c=com->hashUser[i]->top10->used,j;
	HeapPosts b = com->hashUser[i]->top10;
	HeapPosts h=initHeapPosts(c);
	for(j=0;j<10 && j<c;j++){
		id[j] = extractMaxPosts2(com->hashUser[i]->top10,h);
	}
	for(int k=j;k<c;k++)
		extractMaxPosts2(com->hashUser[i]->top10,h);
	com->hashUser[i]->top10=h;
	freeHeapPosts(b);
	return id;
}

LONG_list contaPosts(TAD_community com, int N, int nOrdenados){
	int b = com->Top->used;
	if(N>0){
		int a=nOrdenados;
		for(int h=0; h<N && h<b; h++){
	    	com->topN[a] = extractMax(com->Top);
	    	a++;
		}
	}
	LONG_list list = create_list(N+nOrdenados);
	if(N>b) N = b;
	for (int i=0; i<N+nOrdenados; i++){
		set_list(list, i, com->topN[i]); 
	}
	return list;
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

void freeTopN(TAD_community com){
	free(com->topN);
	free(com->topNR);
}

void freeHeap(Heap r){
	if(r!=NULL){
		free(r->array);
		free(r);
	}
}

int pertenceU (TAD_community com, long ownerUserId, int N, int n){
	for(int i=0; i<N && i<n && i<com->usersSize/2; i++){ 
		if (ownerUserId==com->topNR[i]) return 1;
	}
	return 0;
}

void buscaId (TAD_community com, char* tag, long* p, int* n, int size){
	int chave = tagHash(tag, com), c=0, i;
	for(i=chave; com->hashTag[i]!=NULL && c>com->tagsSize && strcmp(com->hashTag[i]->tagName,tag); i++){
		if (i+1>com->tagsSize) i=0;
		c++;
	}
	if (com->hashTag[i]!=NULL && !strcmp(com->hashTag[i]->tagName,tag))
		insereTag(com->hashTag[i]->id,p,n,size);
}

int buscaTag(TAD_community com, char *s, long* p, int* n, int size){
  int a=0,i=0,k=0,j; 
  char *tag=malloc(strlen(s)*sizeof(char));
  while(s[k]){
    i=k;
    while(s[i] && s[i]=='<') i++;
    for(j=i,a=0;s[j] && s[j]!='>';j++,a++){
        tag[a]=s[j];
    }
    tag[a]=0; 
      buscaId(com,tag,p,n,size);
      if(s[j] && s[j]=='>') {j++;}
      k=j;
  }
  free(tag);
  return 0;
}

void retornaTIdR (TAD_community com, Post* a, long* p, int* n, int N, int z, int size, int ocupados){
	if (a!=NULL){
		if (pertenceU(com,a->ownerUserId,N,ocupados))
			if (a->tag!=NULL) buscaTag(com,a->tag,p,n,size);
		retornaTIdR (com,a->esq,p,n,N,z,size,ocupados);
		retornaTIdR (com,a->dir,p,n,N,z,size,ocupados);
	}
}

int preencheTopNR (TAD_community com, int tam, int z, int N){
	int b = com->TopR->used;
	if (tam>0){
		for (int k=0; k<tam && k<b; k++){
			com->topNR[z] = extractMax(com->TopR);
			z++;
		}
	}
	else{
		for (int k=0; k<N && k<b; k++){
			com->topNR[z] = extractMax(com->TopR);
			z++;
		}
	}
	return b;
}

void retornaTId(TAD_community com, int i, int* nTags, long* arrayT, int N, int tam, int z, int size, int ocupados){
	Post* a = com->treeHash[i]->tree;
	retornaTIdR (com,a,arrayT,nTags,N,z,size,ocupados);
}

void extrai(long* arrayT, int* nTags, int size, int N){
	Heap tag;
	tag = NULL;
	tag = initHeap(size);
	for(int i=0; i<size && arrayT[i]!=-2; i++)
		insertHeap(tag,nTags[i],arrayT[i]);
	int c = tag->used;
	for(int j=0; j<N && j<c; j++){
		arrayT[j] = extractMax(tag);
	}
	freeHeap(tag);
}

void insere_Heap_Reputation(TAD_community com){
    int i,tam=com->usersSize/2;
    com->TopR=initHeap(tam);
    for(i=0;i<com->usersSize;i++){
  		if(com->hashUser[i]!=NULL && com->hashUser[i]->nPosts!=0)
   		 	insertHeap((com->TopR),com->hashUser[i]->reputation,com->hashUser[i]->ownerUserId);
    }
}

void freeTop(TAD_community com){
	freeHeap(com->Top);
	freeHeap(com->TopR);
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

void freeHashTableTags (TAD_community com, int size){
	int i;
	Tags *cur;
	for (i=0; i<size; i++){
		if (com->hashTag[i]!=NULL){
			cur = com->hashTag[i];
			free(cur->tagName);
			free(cur);
		}
	}	
	free(com->hashTag);
}

void freeP(Post* p2){
	if(p2!=NULL){
		free(p2->title);
		free(p2->tag);
		free(p2->question);
		free_date(p2->creationDate);
		freeP((p2->esq));
		freeP((p2->dir));
		free(p2);
	}
}

void freeTreeHashData (TAD_community com,int size){
	int i;
	TreeHash *cur, *prev;
	for(i=0;i<size;i++){
		if(com->treeHash[i]!=NULL){
			cur = com->treeHash[i];
			prev = cur;
			Post *a = prev->tree;
			if(a!=NULL){
				Post* a2 = a;
				freeP(a2);		
			}
			free(prev);
		}
	}
	free(com->treeHash);
}
