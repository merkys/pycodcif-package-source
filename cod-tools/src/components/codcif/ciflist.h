/*-------------------------------------------------------------------------*\
* $Author: andrius $
* $Date: 2017-11-14 09:23:41 +0200 (Tue, 14 Nov 2017) $ 
* $Revision: 5795 $
* $URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/codcif/ciflist.h $
\*-------------------------------------------------------------------------*/

#ifndef __CIFLIST_H
#define __CIFLIST_H

#include <stdio.h>
#include <cexceptions.h>
#include <buffer.h>

typedef struct CIFLIST CIFLIST;

#include <cifvalue.h>

CIFLIST *new_list( cexception_t *ex );
void delete_list( CIFLIST *list );
void list_sprint( BUFFER *buffer, CIFLIST *list );
void list_dump( CIFLIST *list );

void list_push( CIFLIST *list, CIFVALUE *value, cexception_t *ex );
void list_unshift( CIFLIST *list, CIFVALUE *value, cexception_t *ex );

size_t list_length( CIFLIST *list );
CIFVALUE *list_get( CIFLIST *list, int index );
CIFVALUE **list_get_values( CIFLIST *list );

int list_contains_list_or_table( CIFLIST *list );
char *list_concat( CIFLIST *list, char separator, cexception_t *ex );

#endif
