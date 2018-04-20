int count (xmlDocPtr doc){
	xmlNodePtr cur, a;
	int c=0;
	if (doc==NULL){
		fprintf(stderr,"Document not parsed\n");
		return 0;
	}
	cur = xmlDocGetRootElement (doc);
	if (cur==NULL){
		fprintf(stderr,"empty document\n");
		return 0;
	}
	a = cur->xmlChildrenNode;
	while(a!=NULL){
		if((!xmlStrcmp(a->name,(const xmlChar *)"row"))) c++;
		a = a->next;
	}
	return c;
}

int isPost (xmlNodePtr cur){
	return xmlStrcmp(cur->name, (const xmlChar *) "posts");
}

int isUser (xmlNodePtr cur){
	return xmlStrcmp(cur->name, (const xmlChar *) "users");
}

void loadingPost (xmlNodePtr n,TAD_community com){
	xmlNodePtr cur = n->xmlChildrenNode;
	Date data;
	char *titulo=NULL, *tag=NULL, *body=NULL, *parentIdChar = NULL, *answerCountChar = NULL;
	xmlChar *SCORE, *ID, *POSTTYPEID, *OWNERUSERID, *COMMENTCOUNT;
	int score, postTypeId, answerCount, commentCount;
	long id, ownerUserId, parentId;
	while (cur!=NULL){
		if((!xmlStrcmp(cur->name,(const xmlChar *)"row"))){
			POSTTYPEID = xmlGetProp(cur,(xmlChar *)"PostTypeId");
		    postTypeId = atoi((char *) POSTTYPEID);
		    xmlFree(POSTTYPEID);
		    if (postTypeId==1 || postTypeId==2){
				ID = xmlGetProp(cur,(xmlChar *)"Id");
		   		id = atol((char *) ID);
		    	xmlFree(ID);
				SCORE = xmlGetProp(cur,(xmlChar *)"Score");
		    	score = atoi((char *) SCORE);
		    	xmlFree(SCORE);
				titulo = (char *) xmlGetProp(cur,(xmlChar *)"Title");
				COMMENTCOUNT = xmlGetProp(cur,(xmlChar *)"CommentCount");
		    	commentCount = atoi((char *) COMMENTCOUNT);
		    	xmlFree(COMMENTCOUNT);
		    	data = creatingDate((char *) xmlGetProp(cur,(xmlChar *)"CreationDate"));
				body = (char *) xmlGetProp(cur,(xmlChar *)"Body");
				parentIdChar = (char *) xmlGetProp(cur,(xmlChar *)"ParentId");
		    	if (parentIdChar!=NULL){
		   	 		parentId = atol(parentIdChar);
		   			free(parentIdChar);
				}
				else parentId = -2; 
				answerCountChar = (char *) xmlGetProp(cur,(xmlChar *)"AnswerCount");
				if (answerCountChar!=NULL){
			    	answerCount = atoi(answerCountChar);
			    	free(answerCountChar);
				}
				else answerCount = 0;
				tag = (char *) xmlGetProp(cur,(xmlChar *)"Tags");
				OWNERUSERID = xmlGetProp(cur,(xmlChar *)"OwnerUserId");
				ownerUserId = atol((char *) OWNERUSERID);
				xmlFree(OWNERUSERID);

	   		addPost(com, score, postTypeId, parentId, id,tag, titulo, ownerUserId, body, answerCount, data, commentCount);
			}
		}
		cur = cur->next;		
	}	
}

void loadingUsers (xmlNodePtr n, TAD_community com){
	xmlNodePtr cur = n->xmlChildrenNode;
	int reputation;
	long id;
	char *aboutMe=NULL, *name=NULL;
	xmlChar *ID, *REPUTATION;
	while (cur!=NULL){	
		if((!xmlStrcmp(cur->name,(const xmlChar *)"row"))){
			ID = xmlGetProp(cur,(xmlChar *)"Id");
		    id = atol((char *) ID);
		    xmlFree(ID);
		 	REPUTATION = xmlGetProp(cur,(xmlChar *)"Reputation");
		  	reputation = atoi((char *) REPUTATION);
            xmlFree(REPUTATION);
		    aboutMe = (char *) xmlGetProp(cur,(xmlChar *)"AboutMe");
			name = (char *) xmlGetProp(cur,(xmlChar *)"DisplayName");

		   addUser(com,reputation,id,name,aboutMe);  
		}
		cur = cur->next;
	}
}

void add (TAD_community com, xmlNodePtr t){
	xmlNodePtr a;
	int flag=0;
	a=t;
	if (!isPost(t)) {com = initHashData(com, TAD_community_get_dataSize(com));
		loadingPost(a,com); flag=1;
	}
	if (!isUser(t)){
	   com = initHashUsers (com, TAD_community_get_usersSize(com));
	   loadingUsers(a,com);
	}
	if (!isTag(t)){
	   com = initHashTags (com, TAD_community_get_tagsSize(com));
	   loadingTags(a,com);
	}
	if(flag==1) insere_Heap(com);
}

void parse (TAD_community com, char* dump_path){
	int dataSize, usersSize, tagsSize;
	if (dump_path == NULL){
		printf ("./program path\n");
			return;
	}
	xmlDocPtr doc[3];
    char* z=(char *) malloc(1+strlen(dump_path)+strlen("/Users.xml"));
    char* w=(char *) malloc(1+strlen(dump_path)+strlen("/Posts.xml"));
    char* k=(char *) malloc(1+strlen(dump_path)+strlen("/Tags.xml"));
    strcpy(z,dump_path);
    strcpy(w,dump_path);
    strcpy(k,dump_path);
    doc[0]=xmlParseFile(strcat(z,"/Users.xml"));
    doc[1]=xmlParseFile(strcat(w,"/Posts.xml"));
   	doc[2]=xmlParseFile(strcat(k,"/Tags.xml"));
	dataSize = count(doc[1])*2;
	usersSize = count(doc[0])*2;
    tagsSize = count(doc[2])*2;
	TAD_community_set_dataSize(com,dataSize);
	TAD_community_set_tagsSize(com, tagsSize);
	TAD_community_set_usersSize(com, usersSize);
	int j;
	for(j=0;j<3;j++){
		parseDoc(doc[j], com);
		xmlFreeDoc(doc[j]);
	}
	free(z);free(w);free(k);
	xmlCleanupParser();
}