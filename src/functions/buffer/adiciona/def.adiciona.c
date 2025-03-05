
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end





void Candango_adicionar_ao_buffer(Candango_args_render *self, const char *text) {
  size_t len = strlen(text);
  memcpy(self->strings->text_normal + self->size_buffer_current, text, len);
  self->size_buffer_current += len;
}




