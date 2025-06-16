
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end





void Candango_adicionar_ao_buffer(Candango_args_render *self, const char *text, size_t len) {
  memcpy(self->strings->text_normal + self->size_buffer_current, text, len);
  self->size_buffer_current += len;
}

void Candango_adicionar_ao_buffer_lua(Candango_args_render *self, const char *text, size_t len){
  while ((self->size_buffer_lua - self->size_buffer_lua_current) < (len + 2)) {
    if(self->size_buffer_lua < CANDANGO_LIMIT_EXPONENTIAL_SIZE_BUFFER_LUA){
      self->size_buffer_lua *= CANDANGO_EXPONECIAL_SIZE;
    }else{
      self->size_buffer_lua += CANDANGO_LINEAR_SIZE_BUFFER_LUA;
    }

    self->strings->text_to_work = realloc(self->strings->text_to_work, self->size_buffer_lua);

    if (!self->strings->text_to_work) {
      printf("Internal error: When expanding end buffer!\n");
      exit(1);
    }
  }

  memcpy(self->strings->text_to_work + self->size_buffer_lua_current, text, len);
  self->size_buffer_lua_current += len;
}

void Candango_reset_buffer_lua(Candango_args_render *self){
  memset(self->strings->text_to_work, 0, self->size_buffer_lua);

  self->strings->text_to_work = realloc(self->strings->text_to_work, CANDANGO_INITIAL_SIZE_BUFFER_LUA + 1);
  if(!self->strings->text_to_work){
    printf("Internal error: When expanding end buffer");
    exit(1);
  }
  self->size_buffer_lua_current = 0;
  self->size_buffer_lua = CANDANGO_INITIAL_SIZE_BUFFER_LUA;
}




