
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end




void Candango_ignore_text(char *init_key, char *end_key, char *chunk, Candango_args_render *self, size_t *index){

  bool nothing_key = self->key_started == CANDANGO_NOTHING;
  bool init_ignore = self->key_started == CANDANGO_IGNORE;

  if(!(nothing_key || init_ignore)){
    return;
  }

  if(nothing_key){
    char *index_init_key = strstr(chunk + *index, init_key);
  }

  
}




