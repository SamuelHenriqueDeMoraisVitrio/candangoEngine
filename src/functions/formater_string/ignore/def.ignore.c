
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end




void Candango_ignore_text(Candango_args_render *self, char *chunk, size_t index){

  const char *text_working = chunk + index;

  const char *finded_end_key = strstr(text_working, CANDANGO_KEY_END_IGNORE);
  if(!finded_end_key){
    size_t block_text_working_to_end_chunk = text_working - chunk;
    Candango_adicionar_ao_buffer_lua(self, text_working, block_text_working_to_end_chunk);
    return;
  }

  size_t block_finished_cod_lua = finded_end_key - text_working;
  Candango_adicionar_ao_buffer_lua(self, text_working, block_finished_cod_lua);
  Candango_adicionar_ao_buffer(self, text_working, block_finished_cod_lua);
  Candango_reset_buffer_lua(self);
}




