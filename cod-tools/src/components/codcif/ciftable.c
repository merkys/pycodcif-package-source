/*-------------------------------------------------------------------------*\
* $Author: andrius $
* $Date: 2017-11-14 09:23:41 +0200 (Tue, 14 Nov 2017) $ 
* $Revision: 5795 $
* $URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/codcif/ciftable.c $
\*-------------------------------------------------------------------------*/

#include <string.h>
#include <assert.h>
#include <cif_grammar_y.h>
#include <allocx.h>
#include <cexceptions.h>
#include <stringx.h>
#include <ciftable.h>
#include <cifvalue.h>
#include <buffer.h>

#define DELTA_CAPACITY (100)

struct CIFTABLE {

    size_t length;
    size_t capacity;

    char **keys;
    CIFVALUE **values;
};

void delete_table( CIFTABLE *table )
{
    assert( table );

    size_t i;
    for( i = 0; i < table->length; i++ ) {
        freex( table->keys[i] );
        delete_value( table->values[i] );
    }
    freex( table->keys );
    freex( table->values );
    freex( table );
}

CIFTABLE *new_table( cexception_t *ex )
{
    CIFTABLE *table = callocx( 1, sizeof(CIFTABLE), ex );
    table->values = NULL;
    return table;
}

void table_sprint( BUFFER *buffer, CIFTABLE *table ) {
    assert( table );
    bprint( buffer, " {", NULL );
    size_t i;
    for( i = 0; i < table->length; i++ ) {
        int max_sq_in_row = 0;
        int max_dq_in_row = 0;
        size_t j = 0;
        while( table->keys[i][j] != '\0' ) {
            if(        table->keys[i][j] == '\'' ) {
                if( max_sq_in_row == 0 || j == 0 ||
                    table->keys[i][j-1] == '\'' ) {
                    max_sq_in_row++;
                }
            } else if( table->keys[i][j] == '"' ) {
                if( max_dq_in_row == 0 || j == 0 ||
                    table->keys[i][j-1] == '"' ) {
                    max_dq_in_row++;
                }
            }
            j++;
        }
        char *buf;
        size_t key_length = strlen( table->keys[i] );
        if( max_sq_in_row == 0 ) {
            // string without single quotes
            buf = callocx( key_length + 4, sizeof(char), NULL );
            sprintf( buf, " '%s':", table->keys[i] );
        } else if( max_dq_in_row == 0 ) {
            // string without double quotes
            buf = callocx( key_length + 4, sizeof(char), NULL );
            sprintf( buf, " \"%s\":", table->keys[i] );
        } else if( max_sq_in_row < 3 ) {
            // string with 1 or 2 single quotes and some double quotes
            buf = callocx( key_length + 8, sizeof(char), NULL );
            sprintf( buf, " '''%s''':", table->keys[i] );
        } else {
            // string with three single quotes and 1 or 2 double quotes
            buf = callocx( key_length + 8, sizeof(char), NULL );
            sprintf( buf, " \"\"\"%s\"\"\":", table->keys[i] );
        }
        bprint( buffer, buf, NULL );
        value_sprint( buffer, table->values[i] );
    }
    bprint( buffer, " }", NULL );
}

void table_dump( CIFTABLE *table )
{
    table_sprint( NULL, table );
}

size_t table_length( CIFTABLE *table )
{
    assert( table );
    return table->length;
}

char **table_keys( CIFTABLE *table )
{
    assert( table );
    return table->keys;
}

void table_add( CIFTABLE *table, char *key, CIFVALUE *value, cexception_t *ex )
{
    assert( table );

    cexception_t inner;
    ssize_t i;

    cexception_guard( inner ) {
        i = table->length;
        if( table->length + 1 > table->capacity ) {
            table->keys = reallocx( table->keys,
                                    sizeof( char* ) *
                                    (table->capacity + DELTA_CAPACITY),
                                    &inner );
            table->keys[i] = NULL;
            table->values = reallocx( table->values,
                                      sizeof( CIFVALUE* ) *
                                      (table->capacity + DELTA_CAPACITY),
                                      &inner );
            table->values[i] = NULL;
            table->capacity += DELTA_CAPACITY;
        }
        table->length++;

        table->keys[i] = strdupx( key, &inner );
        table->values[i] = value;
    }
    cexception_catch {
        cexception_reraise( inner, ex );
    }    
}

CIFVALUE *table_get( CIFTABLE *table, char *key )
{
    assert( table );
    size_t i;
    for( i = 0; i < table->length; i++ ) {
        if( strcmp( table->keys[i], key ) == 0 ) {
            return table->values[i];
        }
    }
    return NULL;
}
