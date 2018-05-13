#ifndef __PARSE_H_
#define __PARSE_H_

int count (xmlDocPtr doc);
int isPost (xmlNodePtr cur);
int isUser (xmlNodePtr cur);
void loadingPost (xmlNodePtr n,TAD_community com);
void loadingUsers (xmlNodePtr n, TAD_community com);
void add (TAD_community com, xmlNodePtr t);
void parse (TAD_community com, char* dump_path);
int isTag (xmlNodePtr cur);
Date creatingDate(char *s);
void loadingTags (xmlNodePtr n, TAD_community com);
void parseDoc(xmlDocPtr doc, TAD_community com);

#endif
