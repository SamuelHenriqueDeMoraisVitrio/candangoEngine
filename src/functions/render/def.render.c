
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end






void Candango_render_by_chunk(Candango_args_render *args, const char *chunk, long long size_chunk){

  size_t index = 0;

  if(args->key_started == CANDANGO_NOTHING){
    const char *keys[CANDANGO_SIZE_INIT_KEYS] = {
      CANDANGO_KEY_INIT_IGNORE,
      CANDANGO_KEY_INIT_RAW_CONTEXT,
      CANDANGO_KEY_INIT_FUNCTION,
      CANDANGO_KEY_INIT_VARIABLE
    };
    const char *primary_key = Candango_find_primary_key(chunk, keys, &args->key_started, size_chunk);
    if(!primary_key){
      Candango_adicionar_ao_buffer(args, chunk, size_chunk);
      return;
    }

    size_t primary_block_concatened = primary_key - chunk;
    Candango_adicionar_ao_buffer(args, chunk, primary_block_concatened);//Adiciona o bloco antes da abertura da chave

    if(args->key_started > CANDANGO_FUNCTION){
      index = primary_block_concatened + 1;
    }
    if(args->key_started > CANDANGO_NOTHING){
      index = primary_block_concatened + 2;
    }
  }

  if(args->key_started == CANDANGO_IGNORE){
    Candango_ignore_text(args, chunk, index, size_chunk);
    return;
  }

}



