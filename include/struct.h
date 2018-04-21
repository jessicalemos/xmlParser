#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "interface.h"
#include <stdlib.h>

typedef struct TCD_community* TAD_community;
int TAD_community_get_usersSize(TAD_community com);
int TAD_community_get_dataSize(TAD_community com);
int TAD_community_get_tagsSize(TAD_community com);
long get_topN(TAD_community com, int i);

#endif