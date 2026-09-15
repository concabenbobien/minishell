#include "token.h"
#include <stdlib.h>
void token_stream_init(TokenStream *stream){
    stream->items=NULL;
    stream->count= 0;
    stream->capacity=0;
}

int token_stream_push(TokenStream *stream, Token token){
    size_t new_cap=stream->capacity+1;
    Token *new_items= realloc(stream->items, 
        new_cap*sizeof(*stream->items)); /*realloc item pointer*/
    if (new_items==NULL)
    {
        return -1; /*realloc failed */
    }
    stream->items=new_items;
    stream->items[stream->count]=token;
    stream->count++;
    stream->capacity= new_cap;
    return 0;
     /* for later: when fail, have to free lexeme.
        if (token_stream_push(&stream, token) != 0) {
        free(token.lexeme);
}*/
}


void token_stream_destroy(TokenStream *stream){
    for (size_t i = 0; i < stream->count; i++)
    {
        free((stream->items[i]).lexeme);
    }
    free(stream->items);
    stream->items=NULL;
    stream->count= 0;
    stream->capacity=0;
}
    