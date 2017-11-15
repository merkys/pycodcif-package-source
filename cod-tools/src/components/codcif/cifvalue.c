/*-------------------------------------------------------------------------*\
* $Author: andrius $
* $Date: 2017-11-14 09:23:41 +0200 (Tue, 14 Nov 2017) $ 
* $Revision: 5795 $
* $URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/codcif/cifvalue.c $
\*-------------------------------------------------------------------------*/

#include <cexceptions.h>
#include <assert.h>
#include <string.h>
#include <allocx.h>
#include <cifvalue.h>
#include <ciflist.h>
#include <ciftable.h>
#include <buffer.h>

struct CIFVALUE {
    union {
        char *str;
        struct CIFLIST *l;
        struct CIFTABLE *t;
    } v;
    cif_value_type_t type;
};

void delete_value( CIFVALUE *value ) {
    assert( value );

    if( value->type == CIF_LIST ) {
        delete_list( value_list( value ) );
    } else if( value->type == CIF_TABLE ) {
        delete_table( value_table( value ) );
    } else {
        freex( value->v.str );
    }
    freex( value );
}

CIFVALUE *new_value_from_scalar( char *s, cif_value_type_t type,
                              cexception_t *ex )
{
    CIFVALUE *value = callocx( 1, sizeof(CIFVALUE), ex );
    value->v.str = s;
    value->type = type;
    return value;
}

CIFVALUE *new_value_from_list( CIFLIST *list, cexception_t *ex )
{
    CIFVALUE *value = callocx( 1, sizeof(CIFVALUE), ex );
    value->v.l = list;
    value->type = CIF_LIST;
    return value;
}

CIFVALUE *new_value_from_table( CIFTABLE *table, cexception_t *ex )
{
    CIFVALUE *value = callocx( 1, sizeof(CIFVALUE), ex );
    value->v.t = table;
    value->type = CIF_TABLE;
    return value;
}

void value_sprint( BUFFER *buffer, CIFVALUE *value ) {
    assert( value );
    char *buf = NULL;
    switch( value->type ) {
        case CIF_LIST:
            list_sprint( buffer, value_list( value ) );
            break;
        case CIF_TABLE:
            table_sprint( buffer, value_table( value ) );
            break;
        case CIF_SQSTRING:
            buf = callocx( strlen(value_scalar( value ))+4, sizeof(char), NULL );
            sprintf( buf, " '%s'", value_scalar( value ) );
            bprint( buffer, buf, NULL );
            break;
        case CIF_DQSTRING:
            buf = callocx( strlen(value_scalar( value ))+4, sizeof(char), NULL );
            sprintf( buf, " \"%s\"", value_scalar( value ) );
            bprint( buffer, buf, NULL );
            break;
        case CIF_SQ3STRING:
            buf = callocx( strlen(value_scalar( value ))+8, sizeof(char), NULL );
            sprintf( buf, " '''%s'''", value_scalar( value ) );
            bprint( buffer, buf, NULL );
            break;
        case CIF_DQ3STRING:
            buf = callocx( strlen(value_scalar( value ))+8, sizeof(char), NULL );
            sprintf( buf, " \"\"\"%s\"\"\"", value_scalar( value ) );
            bprint( buffer, buf, NULL );
            break;
        case CIF_TEXT:
            buf = callocx( strlen(value_scalar( value ))+6, sizeof(char), NULL );
            sprintf( buf, "\n;%s\n;\n", value_scalar( value ) );
            bprint( buffer, buf, NULL );
            break;
        default:
            buf = callocx( strlen(value_scalar( value ))+2, sizeof(char), NULL );
            sprintf( buf, " %s", value_scalar( value ) );
            bprint( buffer, buf, NULL );
    }
    if( buf ) { freex( buf ); }
}

void value_dump( CIFVALUE *value ) {
    value_sprint( NULL, value );
}

cif_value_type_t value_type( CIFVALUE *value ) {
    return value->type;
}

char *value_scalar( CIFVALUE *value ) {
    return value->v.str;
}

CIFLIST *value_list( CIFVALUE *value ) {
    return value->v.l;
}

CIFTABLE *value_table( CIFVALUE *value ) {
    return value->v.t;
}
