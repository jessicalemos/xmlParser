#ifndef __PARSE_H_
#define __PARSE_H_

int isUser (xmlNodePtr cur);
void loadingUsers (xmlNodePtr n, TAD_community com);
void add (TAD_community com, xmlNodePtr t);
void parse (TAD_community com, char* dump_path);

#endif