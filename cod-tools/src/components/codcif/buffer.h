#ifndef __BUFFER_H
#define __BUFFER_H

#include <cexceptions.h>

typedef struct BUFFER BUFFER;

void delete_buffer( BUFFER *buffer );
BUFFER *new_buffer( cexception_t *ex );
void bprint( BUFFER *buffer, char *string, cexception_t *ex );
char *buffer_string( BUFFER *buffer );
size_t buffer_length( BUFFER *buffer );

#endif
