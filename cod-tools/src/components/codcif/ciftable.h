/*-------------------------------------------------------------------------*\
* $Author: andrius $
* $Date: 2017-11-14 09:23:41 +0200 (Tue, 14 Nov 2017) $ 
* $Revision: 5795 $
* $URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/codcif/ciftable.h $
\*-------------------------------------------------------------------------*/

#ifndef __CIFTABLE_H
#define __CIFTABLE_H

#include <stdio.h>
#include <cexceptions.h>
#include <buffer.h>

typedef struct CIFTABLE CIFTABLE;

#include <cifvalue.h>

CIFTABLE *new_table( cexception_t *ex );
void delete_table( CIFTABLE *table );
void table_sprint( BUFFER *buffer, CIFTABLE *table );
void table_dump( CIFTABLE *table );

size_t table_length( CIFTABLE *table );
char **table_keys( CIFTABLE *table );

void table_add( CIFTABLE *table, char *key, CIFVALUE *value,
                cexception_t *ex );
CIFVALUE *table_get( CIFTABLE *table, char *key );

#endif
