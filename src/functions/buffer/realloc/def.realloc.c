
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end





void Candango_Realloc_Buffer(Candango_args_render *args, size_t size_text_chunk) {
  while ((args->size_buffer - args->size_buffer_current) < (size_text_chunk + 1)) {
    if(args->size_buffer < CANDANGO_LIMIT_EXPONENTIAL_SIZE){
      args->size_buffer *= CANDANGO_EXPONECIAL_SIZE;
    }else{
      args->size_buffer += CANDANGO_LINEAR_SIZE;
    }

    args->strings->text_normal = realloc(args->strings->text_normal, args->size_buffer);

    if (!args->strings->text_normal) {
      printf("Internal error: When expanding end buffer!\n");
      exit(1);
    }
  }
}




