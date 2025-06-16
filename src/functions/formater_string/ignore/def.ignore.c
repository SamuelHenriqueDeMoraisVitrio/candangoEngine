
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end



char *Candango_ignore_text_formatter(Candango_args_render *self, const char *text_working, size_t block_finished_cod_lua, LuaCEmbed *machine){
  Candango_adicionar_ao_buffer_lua(self, text_working, block_finished_cod_lua);
  Candango_adicionar_ao_buffer(self, self->strings->text_to_work, self->size_buffer_lua_current);
  Candango_reset_buffer_lua(self);
  return NULL;
}




