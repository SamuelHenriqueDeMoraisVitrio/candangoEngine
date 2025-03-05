
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end






void Candango_render_by_chunk(Candango_args_render *args, char *chunk, bool is_recursive){

  size_t index = 0;

  if(args->key_started == CANDANGO_NOTHING){
    const char *keys[4] = {
      CANDANGO_KEY_INIT_IGNORE,
      CANDANGO_KEY_INIT_RAW_CONTEXT,
      CANDANGO_KEY_INIT_FUNCTION,
      CANDANGO_KEY_INIT_VARIABLE
    };
    const char *primary_key = Candango_find_primary_key(chunk, keys, &args->key_started);
    if(primary_key == NULL){
      Candango_adicionar_ao_buffer(args, chunk, strlen(chunk));
      return;
    }

    size_t primary_block_concatened = primary_key - chunk;
    Candango_adicionar_ao_buffer(args, chunk, primary_block_concatened);

    if(args->key_started > CANDANGO_FUNCTION){
      index = primary_block_concatened + 1;
    }
    if(args->key_started > CANDANGO_NOTHING){
      index = primary_block_concatened + 2;
    }
  }


}



