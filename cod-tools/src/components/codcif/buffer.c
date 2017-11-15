/* exports: */
#include <buffer.h>

/* uses: */
#include <stdio.h>
#include <string.h>
#include <allocx.h>
#include <cexceptions.h>

struct BUFFER {
    char *s;
    size_t length;
    size_t capacity;
};

void delete_buffer( BUFFER *buffer ) {
    freex( buffer->s );
    freex( buffer );
}

BUFFER *new_buffer( cexception_t *ex ) {
    BUFFER *buffer = callocx( 1, sizeof(BUFFER), ex );
    return buffer;
}

void bprint( BUFFER *buffer, char *string, cexception_t *ex ) {
    if( buffer ) {
        if( !buffer->capacity ) {
            buffer->capacity = 1024;
            buffer->s = callocx( buffer->capacity, sizeof(char), ex );
        }
        while( buffer->capacity < buffer->length + strlen( string ) ) {
            buffer->capacity *= 2;
            buffer->s = reallocx( buffer->s, buffer->capacity, ex );
        }
        strcat( buffer->s, string );
        buffer->length += strlen( string );
    } else {
        printf( "%s", string );
    }
}

char *buffer_string( BUFFER *buffer ) {
    return buffer->s;
}

size_t buffer_length( BUFFER *buffer ) {
    return buffer->length;
}
