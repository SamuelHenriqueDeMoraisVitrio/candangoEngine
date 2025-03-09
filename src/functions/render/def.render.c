
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end






char *Candango_render_by_chunk(Candango_args_render *args, const char *chunk, long long size_chunk, LuaCEmbed *machine){

  size_t index = 0;

  if(args->key_started == CANDANGO_NOTHING){
    int size_key;//O tamanho da chave especifica para ser ignorada no texto final
    const char *primary_key = Candango_find_primary_key(chunk, &args->key_started, size_chunk, &size_key);
    if(!primary_key){
      Candango_adicionar_ao_buffer(args, chunk, size_chunk);
      return NULL;
    }

    size_t primary_block_concatened = primary_key - chunk;
    Candango_adicionar_ao_buffer(args, chunk, primary_block_concatened);//Adiciona o bloco antes da abertura da chave

    index = primary_block_concatened + size_key;

  }

  if(args->key_started == CANDANGO_IGNORE){
    return Candango_formater_text_default(args, chunk, index, size_chunk, machine, CANDANGO_KEY_INIT_IGNORE, CANDANGO_KEY_END_IGNORE, Candango_ignore_text_formatter);
  }
  
  if(args->key_started == CANDANGO_RAW_CONTEXT){
    return Candango_formater_text_default(args, chunk, index, size_chunk, machine, CANDANGO_KEY_INIT_RAW_CONTEXT, CANDANGO_KEY_END_RAW_CONTEXT, Candango_raw_text_formatter);
  }

  if(args->key_started == CANDANGO_FUNCTION){
    return Candango_formater_text_default(args, chunk, index, size_chunk, machine, CANDANGO_KEY_INIT_FUNCTION, CANDANGO_KEY_END_FUNCTION, Candango_function_text_formatter);
  }

  return "Internal error: 'Key started' not expected.";
}



