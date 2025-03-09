
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end




char *Candango_variable_text_formatter(Candango_args_render *self, const char *text_working, size_t block_finished_cod_lua, LuaCEmbed *machine){
  Candango_adicionar_ao_buffer_lua(self, text_working, block_finished_cod_lua);
  const char *result_evaluet = Candango_lua.get_string_evaluation(machine, self->strings->text_to_work);
  if(Candango_lua.has_errors(machine)){
    return Candango_lua.get_error_message(machine);
  }
  size_t size_result = strlen(result_evaluet);
  Candango_Realloc_Buffer(self, size_result);
  Candango_adicionar_ao_buffer(self, result_evaluet, size_result);
  Candango_reset_buffer_lua(self);

  return NULL;
}





