
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end




Candango_string_separator *Candango_New_string_separator(Candango_args_render *args){
  Candango_string_separator *self = malloc(sizeof(Candango_string_separator) + 1);
  if(!self){
    printf("Internal error: Candango_string_separator");
    exit(1);
  }

  self->text_normal = malloc(args->size_buffer + 1);
  self->text_to_work = malloc(args->size_buffer_lua + 1);

  return self;
}

Candango_args_render *Candango_New_args_render(){
  Candango_args_render *self = malloc(sizeof(Candango_args_render) + 1);
  if(!self){
    printf("Internal error: Candango_args_render");
    exit(1);
  }

  self->key_started = CANDANGO_NOTHING;
  self->size_buffer = CANDANGO_INITIAL_SIZE_READ;
  self->size_buffer_lua = CANDANGO_INITIAL_SIZE_BUFFER_LUA;
  self->size_buffer_current = 0;
  self->size_buffer_lua_current = 0;
  self->strings = Candango_New_string_separator(self);
  
  return self;
}

void Candango_free_string_separator(Candango_string_separator *self){
  if(self){
    if(self->text_to_work){
      free(self->text_to_work);
    }
    /*
    if(self->text_normal){
      free(self->text_normal);
    }
    */
    free(self);
  }
}

void Candango_free_args_render(Candango_args_render *self){
  if(self){
    if(self->strings){
      Candango_free_string_separator(self->strings);
    }
    free(self);
  }
}


