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