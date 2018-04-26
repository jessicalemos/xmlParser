#include "interface.h"
#include "struct.h"
#include "auxiliary.h"


STR_pair info_from_post(TAD_community com, long id){
	char *nome = NULL, *title = NULL;
	int iP = procuraPost(com,id); 
	if (iP != -1){
		int type = post_getPostTypeId (com, iP, id); 
		if (type == 1){
			title = post_getTitle (com, iP, id);
			long ownerUserId =  post_getOwnerUserId (com,iP, id);
			int iU = procuraUser(com,ownerUserId); 
			nome =  users_getDisplayName (com, iU);
			if (iU != -1) nome = users_getDisplayName (com, iU);
		}
		else {
			long parent = post_getparentId (com,iP,id);
			int iP2 = procuraPost(com,parent);
			title = post_getTitle (com, iP2, parent);
			long ownerUserId =  post_getOwnerUserId (com,iP2,parent);
			int iU = procuraUser(com,ownerUserId);
			if (iU != -1) nome = users_getDisplayName (com, iU);
		}
	}
	STR_pair p= create_str_pair (title, nome);
	return p;
}

LONG_list top_most_active(TAD_community com, int N){
	int k;
	for(k=0;get_topN(com,k)!=-2;k++);
	int tam=N-k;
	return contaPosts(com,tam,k);
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
	int w;
	long perguntas = 0, respostas = 0;
	if(compareDateQ(begin,end)==2) return create_long_pair(perguntas,respostas);
	else{
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					perguntas += treeHash_getContadorP (com,w);
					respostas += treeHash_getContadorR (com,w);
				}
			}
		}
	}
		return create_long_pair(perguntas,respostas);
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int  w; 
	long *array;
	int *arrayS;
	if(compareDateQ(begin,end)==2) return create_list(0);
	else{
		array = malloc(N*sizeof(long));
		arrayS = malloc(N*sizeof(int));
		for(int j=0; j<N; j++) {array[j]=-2;arrayS[j]=-20;}
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaSId (com,array,arrayS,N,w); 
				}
			}
		}
	}
	LONG_list list = create_list(N); 
	for (int i=0; i<N; i++){
		set_list(list, i, array[i]); 
	}
	free(array);free(arrayS);
	return list;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	int w, size = TAD_community_get_dataSize(com)/2, tam; 
	long *array,*aId;
	int *arrayA;
	HashTableQuery7 h = initHashQ7(TAD_community_get_dataSize(com));
	if(compareDateQ(begin,end)==2) return create_list(0);
	else{
		array = malloc(N*sizeof(long));
		arrayA = malloc(N*sizeof(int));
		for(int j=0; j<N; j++) {array[j]=-2;arrayA[j]=-20;}
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaAId (com,array,arrayA,N,w); 
				}
			}
		}
	}
	for(h=0;h<N && array[h]!=-2;h++);
	LONG_list list = create_list(h); 
	for (int i=0; i<h; i++)
		set_list(list, i, array[i]); 
	free(array);free(arrayA);
	return list;
}

LONG_list contains_word(TAD_community com, char* word, int N){
	int j, i;
	long* id = malloc(N*sizeof(long));
	Date* data = malloc(N*sizeof(Date));
	for(i=0;i<N;i++){
		id[i]=-2;
		data[i]=NULL;
	}
	LONG_list l;
		procuraTitulo(com,word,data,id,N);
		for(j=0;j<N && id[j]!=-2;j++);
		l = create_list(j);
		for(int k=0;k<j;k++){
			set_list(l,k,id[k]);
		}
	free(id); free(data);
	return l;
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	int c = TAD_community_get_dataSize(com)/2,w; 
	long *array;
	Date* arrayD;
	if(compareDateQ(begin,end)==2) return create_list(0);
	else{
		arrayD = malloc(c*sizeof(Date));
		array = malloc(c*sizeof(long));
		for(int j=0; j<c; j++) {array[j]=-2;arrayD[j]=NULL;}
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaId (com, w, array, tag, c, arrayD);
				}
			}
		}
	}
	LONG_list list = carregaListaT(com,array,arrayD); 
	free(array);free(arrayD);
	return list;
}

USER get_user_info(TAD_community com, long id){
	int i = procuraUser(com,id);
	char* aboutMe = users_getAboutMe(com,i);
	long* idP = retornaTop10(com,i);
	USER u = create_user(aboutMe,idP);
	free(idP);
	return u;
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	long* id = malloc(N*sizeof(long));
	for(int i=0;i<N;i++) id[i]=-2;
	int chave1 = procuraUser(com,id1),chave2 = procuraUser(com,id2),tam; 
	if (chave1 == -1 || chave2 == -1) return create_list(0);
	else tam = extraiHeaps(com,chave1,chave2,N,id); 
	LONG_list l = create_list(tam);
	for(int j=0;j<tam;j++)
		set_list(l,j,id[j]);
	free(id);
	return l;	
}

long better_answer(TAD_community com, long id){
	return procuraRespostas(com, id);
}

LONG_list most_used_best_rep (TAD_community com, int N, Date begin, Date end){
	int w, z; 
	HashTableQuery11 h = initHashQuery11(TAD_community_get_tagsSize(com));
	for(z=0; get_topNR(com,z)!=-2; z++);
	int tam = N-z, size = 2*TAD_community_get_tagsSize(com);
	if(compareDateQ(begin,end)==2) return create_list(0);
	int ocupados = preencheTopNR(com,tam,z,N);
	if (ocupados == 0) ocupados = N;
	for(w=0;w<TAD_community_get_dataSize(com);w++){
		if(existeTree(com,w)){
			if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
				retornaTId(com,w,N,tam,z,ocupados,h); 
			}
		}
	}
	LONG_list list = carregaListaTag(com,N,h); 		
	return list;
}

TAD_community clean (TAD_community com){
    if (com!=NULL){
        if(TAD_community_get_dataSize(com)!=-1){
	        freeTreeHashData(com, TAD_community_get_dataSize(com));
   	        freeHashTableUsers(com, TAD_community_get_usersSize(com));
            freeHashTableTags(com, TAD_community_get_tagsSize(com));
	    }
        freeTopN(com);
        freeTop(com);
	    free(com);
	}
	return com;
}
