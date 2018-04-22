#include "interface.h"
#include "struct.h"
#include "auxiliary.h"

void selectionSort(long* p, int tam){
	int i, j, max, aux;
	for (i=0; i<tam-1; i++) {
		max = i;
	for (j=i+1; j<tam; j++) {
		if (p[j] >p[max]) max = j;
	} 
	aux = p[i];
	p[i] = p[max];
	p[max] = aux;
	}
}

int contaTitulo (TAD_community com,char *word){
	int i, c = 0;
	for(i=0;i<TAD_community_get_dataSize(com);i++)
		if(existeTree(com,i))
			c += retiraTitulo(com,i,word);  
	return c;
}

int conta (TAD_community com, int localB, int localE, Date begin, Date end, char* tag){
	int i, c = 0;
	for(i=localB;i<=localE;i++){ 
		if(existeTree(com,i)){
			if(compareDateQ(post_getCreationDate (com,i), begin)!=0 && compareDateQ(post_getCreationDate (com,i), end)!=2){
					 c += contaTag(com, i, tag);  
			}
		}
	} 
	return c;
}

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
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), j, i, k,c,l,w;
	LONG_pair local=existeData(com,begin,end,chaveB,chaveE);
	long localB=get_fst_long(local),localE=get_snd_long(local);
	long perguntas = 0, respostas = 0;
	if(compareDateQ(begin,end)==2) return create_long_pair(perguntas,respostas);
	if(localB==-1 && localE==-1){
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					perguntas += treeHash_getContadorP (com,w);
					respostas += treeHash_getContadorR (com,w);
				}
			}
		}
	}
	else if(localB!=-1 && localE!=-1 && localB<=localE){
			for(i=localB;i<=localE;i++){
				if(existeTree(com,i)){
					if(compareDateQ(post_getCreationDate (com,i), begin)!=0 && compareDateQ(post_getCreationDate (com,i), end)!=2){
						perguntas += treeHash_getContadorP (com,i);
						respostas += treeHash_getContadorR (com,i);
					}
				}
			}
		}
		else if(localB==-1 && localE!=-1){
				for(l=chaveB;l!=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
							perguntas += treeHash_getContadorP (com,l);
							respostas += treeHash_getContadorR (com,l);
						}
					}
				}
				if(l!=localE){
					for(c=0;c!=localE;c++){
						if(existeTree(com,c)){
							if(compareDateQ(post_getCreationDate (com,c), begin)!=0 && compareDateQ(post_getCreationDate (com,c), end)!=2){
								perguntas += treeHash_getContadorP (com,c);
								respostas += treeHash_getContadorR (com,c);
							}
						}
					}
				}
				perguntas += treeHash_getContadorP (com,localE);
				respostas += treeHash_getContadorR (com,localE);
			}
			else{
				for(j=localB;j<TAD_community_get_dataSize(com);j++){
					if(existeTree(com,j)){
						if(compareDateQ(post_getCreationDate (com,j), begin)!=0 && compareDateQ(post_getCreationDate (com,j), end)!=2){
						perguntas += treeHash_getContadorP (com,j);
						respostas += treeHash_getContadorR (com,j);
						}
					}
				}
				if(localE==-1) localE=localB-1;
				for(k=0;k<=localE; k++){
					if(existeTree(com,k)){
						if(compareDateQ(post_getCreationDate (com,k), begin)!=0 && compareDateQ(post_getCreationDate (com,k), end)!=2) {
							perguntas += treeHash_getContadorP (com, k);
							respostas += treeHash_getContadorR (com, k);
						}
					}
				}
			}
		free_long_pair(local);
		return create_long_pair(perguntas,respostas);
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), n, l, k, j, w; 
	long *array;
	int *arrayS;
	LONG_pair local = existeData(com,begin,end,chaveB,chaveE);
	long localB = get_fst_long(local), localE = get_snd_long(local);
	if(compareDateQ(begin,end)==2) return create_list(0);
	if(localB==-1 && localE==-1){
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
	else if(localB==-1 && localE!=-1){
		 	if(localE<chaveB){
				array = malloc(N*sizeof(long));
				arrayS = malloc(N*sizeof(int));
				for(int j=0; j<N; j++) {array[j]=0;arrayS[j]=-20;}
				for(l=chaveB;l!=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       					retornaSId (com, array, arrayS, N,l);
						}
					}
				}
				for(n=0;n!=localE;n++){
					if(existeTree(com,n)){
						if(compareDateQ(post_getCreationDate (com,n), begin)!=0 && compareDateQ(post_getCreationDate (com,n), end)!=2){
							retornaSId (com, array, arrayS, N,n);
						}
					}
				}
				retornaSId (com, array, arrayS, N,n);
			}
	    	else{
				array = malloc(N*sizeof(long));
				arrayS = malloc(N*sizeof(int));
				for(int j=0; j<N; j++) {array[j]=0;arrayS[j]=-20;}
				for(l=chaveB;l<=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       					retornaSId (com, array, arrayS, N,l);
						}
					}
				}
			}
		}
		else{
			array = malloc(N*sizeof(long));
			arrayS = malloc(N*sizeof(int));
			for(int j=0; j<N; j++) {array[j]=0;arrayS[j]=-20;}
			for(j=localB;j<TAD_community_get_dataSize(com);j++){
				if(existeTree(com,j)){
					if(compareDateQ(post_getCreationDate (com,j), begin)!=0 && compareDateQ(post_getCreationDate (com,j), end)!=2){
						retornaSId (com, array, arrayS, N,j);
					}
				}
			}
			if(localE==-1) localE=localB-1;
			for(k=0;k<=localE; k++){
				if(existeTree(com,k)){
					if(compareDateQ(post_getCreationDate (com,k), begin)!=0 && compareDateQ(post_getCreationDate (com,k), end)!=2) {
						retornaSId (com, array, arrayS, N,k);
					}
				}
			}
		} 
	LONG_list list = create_list(N); 
	for (int i=0; i<N; i++)
		set_list(list, i, array[i]); 
	free(array);free(arrayS);free_long_pair(local);
	return list;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), n, l, k, j, h, w; 
	long *array;
	int *arrayA;
	LONG_pair local = existeData(com,begin,end,chaveB,chaveE);
	long localB = get_fst_long(local), localE = get_snd_long(local);
	if(compareDateQ(begin,end)==2) return create_list(0);
	if(localB==-1 && localE==-1){
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
	else if(localB==-1 && localE!=-1){
			if(localE<chaveB){
				array = malloc(N*sizeof(long));
				arrayA = malloc(N*sizeof(int));
				for(int j=0; j<N; j++) {array[j]=0;arrayA[j]=-20;}
				for(l=chaveB;l!=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       					retornaAId (com, array, arrayA, N,l);
						}
					}
				}
				for(n=0;n!=localE;n++){
					if(existeTree(com,n)){
						if(compareDateQ(post_getCreationDate (com,n), begin)!=0 && compareDateQ(post_getCreationDate (com,n), end)!=2){
							retornaAId (com, array, arrayA, N,n);
						}
					}
				}
				retornaSId (com, array, arrayA, N,n);
			}
	    	else{
				array = malloc(N*sizeof(long));
				arrayA = malloc(N*sizeof(int));
				for(int j=0; j<N; j++) {array[j]=0;arrayA[j]=-20;}
				for(l=chaveB;l<=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       					retornaAId (com, array, arrayA, N,l);
						}
					}
				}
			}
		}
		else{
			array = malloc(N*sizeof(long));
			arrayA = malloc(N*sizeof(int));
			for(int j=0; j<N; j++) {array[j]=0;arrayA[j]=-20;}
			for(j=localB;j<TAD_community_get_dataSize(com);j++){
				if(existeTree(com,j)){
					if(compareDateQ(post_getCreationDate (com,j), begin)!=0 && compareDateQ(post_getCreationDate (com,j), end)!=2){
						retornaAId (com, array, arrayA, N,j);
					}
				}
			}
			if(localE==-1) localE=localB-1;
			for(k=0;k<=localE; k++){
				if(existeTree(com,k)){
					if(compareDateQ(post_getCreationDate (com,k), begin)!=0 && compareDateQ(post_getCreationDate (com,k), end)!=2) {
						retornaAId (com, array, arrayA, N,k);
					}
				}
			}
		} 
		for(h=0;h<N && array[h]!=-2;h++);
		LONG_list list = create_list(h); 
		for (int i=0; i<h; i++)
		    set_list(list, i, array[i]); 
		free(array);free(arrayA);free_long_pair(local);
		return list;
}

LONG_list contains_word(TAD_community com, char* word, int N){
	int c = contaTitulo(com,word), j, i;
	long* id = malloc(c*sizeof(long));
	Date* data = malloc(c*sizeof(Date));
	for(i=0;i<c;i++){
		id[i]=-2;
		data[i]=NULL;
	}
	LONG_list l;
	if(c!=0){
		procuraTitulo(com,word,data,id,c);
		if(c<N) N=c;
		for(j=0;j<N;j++);
		l = create_list(j);
		for(int k=0;k<j;k++){
			set_list(l,k,id[k]);
		}
	}
	else l = create_list(0);
	free(id);
    free(data);
	return l;
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), c = 0, n, l, i, k, j,w; 
	long *array;
	LONG_pair local = existeData(com,begin,end,chaveB,chaveE);
	long localB = get_fst_long(local), localE = get_snd_long(local);
	if(compareDateQ(begin,end)==2) return create_list(0);
	if(localB==-1 && localE==-1){
		c = conta(com, 0, TAD_community_get_dataSize(com)-1, begin, end, tag); 
		array = malloc(c*sizeof(long));
		for(int j=0; j<c; j++) array[j]=-2;
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaId (com, w, array, tag, c);
				}
			}
		}
	}
	else if(localB!=-1 && localE!=-1 && localB<=localE){ 
		c = conta(com, localB, localE, begin, end, tag); 
		array = malloc(c*sizeof(long));
		for(int j=0; j<c; j++) array[j]=-2; 
		for(i=localB;i<=localE;i++){
			if(existeTree(com,i)){
				if(compareDateQ(post_getCreationDate (com,i), begin)!=0 && compareDateQ(post_getCreationDate (com,i), end)!=2){
					{retornaId (com, i, array, tag, c); }
				}	
			}
		}
	}
	else if(localB==-1 && localE!=-1){
		 if(localE<chaveB){
			c = conta(com, chaveB, localE, begin, end, tag);
			array = malloc(c*sizeof(long));
			for(int j=0; j<c; j++) array[j]=-2;
			for(l=chaveB;l!=localE && l<TAD_community_get_dataSize(com);l++){
				if(existeTree(com,l)){
					if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       				retornaId (com, l, array, tag, c);
					}
				}
			}
				for(n=0;n!=localE;n++){
					if(existeTree(com,n)){
						if(compareDateQ(post_getCreationDate (com,n), begin)!=0 && compareDateQ(post_getCreationDate (com,n), end)!=2){
							retornaId (com, n, array, tag, c);
						}
					}
				}
			retornaId (com, localE, array, tag, c);
		}
	    else{
			c = conta(com, chaveB, localE, begin, end, tag);
			array = malloc(c*sizeof(long));
			for(int j=0; j<c; j++) array[j]=-2;
			for(l=chaveB;l<=localE && l<TAD_community_get_dataSize(com);l++){
				if(existeTree(com,l)){
					if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       				retornaId (com, l, array, tag, c);
					}
				}
			}
		}
	}
	else{
		c = conta(com,0,TAD_community_get_dataSize(com)-1, begin, end, tag);
		array = malloc(c*sizeof(long));
		for(int j=0; j<c; j++) array[j]=-2;
		for(j=localB;j<TAD_community_get_dataSize(com);j++){
			if(existeTree(com,j)){
				if(compareDateQ(post_getCreationDate (com,j), begin)!=0 && compareDateQ(post_getCreationDate (com,j), end)!=2){
					retornaId (com, j, array, tag, c);
				}
			}
		}
		if(localE==-1) localE=localB-1;
			for(k=0;k<=localE; k++){
				if(existeTree(com,k)){
					if(compareDateQ(post_getCreationDate (com,k), begin)!=0 && compareDateQ(post_getCreationDate (com,k), end)!=2) {
						retornaId (com, k, array, tag, c);
					}
				}
			}
		} 
	LONG_list list = create_list(c);
	selectionSort(array,c); 
	for (int i=0; i<c; i++){
		set_list(list, i, array[i]); 
	}
	free_long_pair(local);
	free(array);
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
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), n, l, i, k, j, w, z; 
	long *arrayT; int* nTags;
	LONG_pair local = existeData(com,begin,end,chaveB,chaveE);
	long localB = get_fst_long(local), localE = get_snd_long(local);
	for(z=0; get_topNR(com,z)!=-2; z++);
	int tam = N-z, size = 2*TAD_community_get_tagsSize(com);
	if(compareDateQ(begin,end)==2) return create_list(0);
	int ocupados = preencheTopNR(com,tam,z,N);
	if (ocupados == 0) ocupados = N;
	if(localB==-1 && localE==-1){
		arrayT = malloc(size*sizeof(long));
		for(int j=0; j<size; j++) arrayT[j]=-2;
		nTags = malloc(size*sizeof(int));
		for (int k=0; k<size; k++) nTags[k] = 0;
		for(w=0;w<TAD_community_get_dataSize(com);w++){
			if(existeTree(com,w)){
				if(compareDateQ(post_getCreationDate (com,w), begin)!=0 && compareDateQ(post_getCreationDate (com,w), end)!=2){
					retornaTId(com,w,nTags,arrayT,N,tam,z,size, ocupados); //printf("%s\n", "AQI");
				}
			}
		}
	}
	else if(localB!=-1 && localE!=-1 && localB<=localE){  
		 	arrayT = malloc(size*sizeof(long));
		 	for(int j=0; j<size; j++) arrayT[j]=-2;
		 	nTags = malloc(size*sizeof(int));
		 	for (int k=0; k<size; k++) nTags[k] = 0;
		 	for(i=localB;i<=localE;i++){
				if(existeTree(com,i)){
					if(compareDateQ(post_getCreationDate (com,i), begin)!=0 && compareDateQ(post_getCreationDate (com,i), end)!=2){
						retornaTId(com,i,nTags,arrayT,N,tam,z,size, ocupados);
					}	
				}
			}
		}
		else if(localB==-1 && localE!=-1){
			if(localE<chaveB){
				arrayT = malloc(size*sizeof(long));
				for(int j=0; j<size; j++) arrayT[j]=-2;
				nTags = malloc(size*sizeof(int));
				for (int k=0; k<size; k++) nTags[k] = 0;
				for(l=chaveB;l!=localE && l<TAD_community_get_dataSize(com);l++){
					if(existeTree(com,l)){
						if(compareDateQ(post_getCreationDate (com,l), begin)!=0 && compareDateQ(post_getCreationDate (com,l), end)!=2){
	       					retornaTId(com,l,nTags,arrayT,N,tam,z,size,ocupados);
						}
					}
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
