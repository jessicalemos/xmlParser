#include "interface.h"
#include "struct.h"
#include "auxiliary.h"

/**
 * [Query 1 - Devolve o tı́tulo do post e o nome de utilizador do autor]
 * @param  com      [Estrutura]
 * @param  id       [Id de um post]
 * @return          [Par com o tı́tulo do post e o nome do autor]
 */
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

/**
 * [Query 2 - Devolve o top N utilizadores com maior número de posts de sempre]
 * @param  com     [Estrutura]
 * @param  N       [N pedido no top N]
 * @return         [Lista com os ids dos utilizadores com maior número de posts]
 */
LONG_list top_most_active(TAD_community com, int N){
	int k;
	if(N>0){
		for(k=0;get_topN(com,k)!=-2;k++);
		int tam=N-k;
		return contaPosts(com,tam,k);
	}
	return create_list(0);
}

/**
 * [Query 3 - Devolve o número total de posts, perguntas e respostas separadamente, num dado intervalo de tempo]
 * @param  com         [Estrutura]
 * @param  begin       [Data inicial]
 * @param  end         [Data final] 
 * @return             [Par com o número de perguntas e número de respostas]
 */
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

/**
 * [Query 6 - Devolve os ids das N respostas com mais votos num dado intervalo de tempo]
 * @param  com         [Estrutura]
 * @param  N           [N pedido no top N] 
 * @param  begin       [Data inicial]
 * @param  end         [Data final] 
 * @return             [Lista com os ids das N respostas com mais votos]
 */
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int  w; 
	long *array;
	int *arrayS;
	if(compareDateQ(begin,end)==2 || N<=0) return create_list(0);
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

/**
 * [Query 7 - Devolve os ids das N perguntas com mais respostas num dado intervalo de tempo]
 * @param  com         [Estrutura]
 * @param  N           [N pedido no top N] 
 * @param  begin       [Data inicial]
 * @param  end         [Data final] 
 * @return             [Lista com os ids das N perguntas com mais respostas]
 */
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	int w, c = 0;HashTableQuery7 h; 
	if(compareDateQ(begin,end)==2 || N<=0) return create_list(0);
	else{
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					c += treeHash_getNumRespostas(com,w);
				}
			}
		}
		c *= 2;
		h = initHashQ7(c);
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaAId (com,w,h,c); 
				}
			}
		}
	}
	LONG_list list = carregaListaQ(com,N,h,c); 
	freeHashTableQuery7(h,c); 
	return list;
}

/**
 * [Query 8 - Devolve uma lista com os ids de N perguntas cujos tı́tulos contenham uma dada palavra]
 * @param  com         [Estrutura]
 * @param  word        [Palavra a comparar] 
 * @param  N           [N pedido no top N]  
 * @return             [Lista com os ids de N perguntas cujos tı́tulos contenham a palavra]
 */
LONG_list contains_word(TAD_community com, char* word, int N){
	int j, i;
	if(N<=0) return create_list(0);
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

/**
 * [Query 4 - Devolve todas as perguntas que contenham uma determinada tag num dado intervalo de tempo]
 * @param  com         [Estrutura]
 * @param  tag         [Tag a comparar] 
 * @param  begin       [Data inicial]
 * @param  end         [Data final] 
 * @return             [Lista com os ids das perguntas]
 */
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

/**
 * [Query 5 - Devolve a informação do seu perfil e os ids dos seus 10 últimos posts]
 * @param  com         [Estrutura]
 * @param  id          [Id de um utilizador] 
 * @return             [USER que contém a short bio e os ids dos posts]
 */
USER get_user_info(TAD_community com, long id){
	int i = procuraUser(com,id);
	USER u;
	if(i!=-1){
		char* aboutMe = users_getAboutMe(com,i);
		long* idP = retornaTop10(com,i);
		u = create_user(aboutMe,idP);free(idP);
	}
	else {
		long* idP = malloc(10*sizeof(long));
		for(int j=0;j<10;j++) idP[j] = -2;
		u = create_user(NULL,idP); free(idP);
	}
	return u;
}

/**
 * [Query 9 - Devolve as últimas N perguntas em que participaram dois utilizadores especı́ficos]
 * @param  com          [Estrutura]
 * @param  id1          [Id de um utilizador] 
 * @param  id2          [Id de um utilizador]  
 * @param  N            [N pedido no top N]  
 * @return              [Lista com os ids das N perguntas em que participaram os dois utilizadores]
 */
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	if(N<=0) return create_list(0);
	long* id = malloc(N*sizeof(long));
	for(int i=0;i<N;i++) id[i]=-2;
	int chave1 = procuraUser(com,id1),chave2 = procuraUser(com,id2),tam; 
	if (chave1 == -1 || chave2 == -1) {free(id); return create_list(0);}
	else tam = extraiHeaps(com,chave1,chave2,N,id); 
	LONG_list l = create_list(tam);
	for(int j=0;j<tam;j++)
		set_list(l,j,id[j]);
	free(id);
	return l;	
}

/**
 * [Query 10 - obter a melhor resposta, ou seja, com melhor média ponderada]
 * @param  com         [Estrutura]
 * @param  id          [Id de uma pergunta] 
 * @return             [Id da pergunta com melhor média ponderada]
 */
long better_answer(TAD_community com, long id){
	return procuraRespostas(com, id);
}

/**
 * [Query 11 - Devolve os identificadores das N tags mais usadas pelos N utilizadores com melhor reputação num dado intervalo de tempo]
 * @param  com         [Estrutura]
 * @param  N           [N pedido no top N]  
 * @param  begin       [Data inicial]
 * @param  end         [Data final] 
 * @return             [Lista com os ids das N tags mais usadas pelos N utilizadores com melhor reputação]
 */
LONG_list most_used_best_rep (TAD_community com, int N, Date begin, Date end){
	int w, z, c = 0;
	for(z=0; get_topNR(com,z)!=-2; z++);
	int tam = N-z;
	if(compareDateQ(begin,end)==2 || N<=0) return create_list(0);
	preencheTopNR(com,tam,z,N);
	HashTableTopN h1 = initHashTopN(N*2);
	h1 = transfere(com,N,h1);
	for(w=0;w<TAD_community_get_dataSize(com);w++){
		if(existeTree(com,w)){
			if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
				c += treeHash_getNumRespostas(com,w); 
			}
		}
	}
	c *= 5;
	HashTableQuery11 h = initHashQuery11(c);
	for(w=0;w<TAD_community_get_dataSize(com);w++){
		if(existeTree(com,w)){
			if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
				retornaTId(com,w,N,h,h1,c); 
			}
		}
	}
	LONG_list list = carregaListaTag(com,N,h,c); 
	freeHashTableQuery11(h,c);freeHashTableTopN(h1,N*2); 		
	return list;
}

/**
 * [Liberta todas as estruturas associadas à estrutura TAD_community]
 * @param  com         [Estrutura]
 * @return             [A estrutura sem nada guardado em memória]
 */
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
