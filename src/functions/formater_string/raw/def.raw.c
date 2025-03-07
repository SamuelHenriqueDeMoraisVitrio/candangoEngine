
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end






char *Candango_raw_text(Candango_args_render *self, const char *chunk, size_t index, long long size_chunk, LuaCEmbed *machine){

  const char *text_working = chunk + index;//Posição da primeira chave para frente, text: 'é {nome}' chave: '{' posição: 'nome'('n')

  const char *finded_end_key = strstr(text_working, CANDANGO_KEY_END_RAW_CONTEXT);
  if(!finded_end_key || finded_end_key >= text_working + (size_chunk - index)){
    Candango_adicionar_ao_buffer_lua(self, text_working, size_chunk - index);//Adiciona todo chunk a partir do text_working
    return NULL;
  }

  size_t block_finished_cod_lua = finded_end_key - text_working;
  Candango_adicionar_ao_buffer_lua(self, text_working, block_finished_cod_lua);
  Candango_lua.evaluate(machine, self->strings->text_to_work);
  if(Candango_lua.has_errors(machine)){
    return Candango_lua.get_error_message(machine);
  }
  Candango_reset_buffer_lua(self);

  self->key_started = CANDANGO_NOTHING;
  const char *init_block_last_end_key = finded_end_key + strlen(CANDANGO_KEY_END_IGNORE);
  long long size_new_chunk = (chunk + size_chunk) - init_block_last_end_key;
  if(finded_end_key > 0){
    Candango_render_by_chunk(self, init_block_last_end_key, size_new_chunk, machine);
  }
  return NULL;
}




