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
	int chaveB = dataHash(begin, com), chaveE = dataHash(end, com), c = 0, n, l, i, k, j; 
	long *array;
	LONG_pair local = existeData(com,begin,end,chaveB,chaveE);
	long localB = get_fst_long(local), localE = get_snd_long(local);
	if((localE==-1 && localB==-1) || (compareDateQ(begin,end)==2)) return create_list(0);
	if(localB!=-1 && localE!=-1 && localB<=localE){ 
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

long better_answer(TAD_community com, long id){
	return procuraRespostas(com, id);
}