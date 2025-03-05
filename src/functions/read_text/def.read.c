
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



char *Candango_read_text_by_chunck(const char *path_file){

  FILE *text_by_file = fopen(path_file, "r");
  if(!text_by_file){
    printf("Intern error: Open file recused");
    return NULL;
  }

  char chunck[CANDANGO_INITIAL_SIZE_READ];
  long total_size = 0;
  char *text = NULL;

  Candango_args_render *args = Candango_New_args_render();

  long size_text_chunk;
  while((size_text_chunk = fread(chunck, sizeof(char), CANDANGO_INITIAL_SIZE_READ - 1, text_by_file)) > 0){
    Candango_Realloc_Buffer(args, size_text_chunk);

    Candango_render_by_chunk(args, chunck, false);
  }

  fclose(text_by_file);

  const char *Candango_NULO = "\0";
  Candango_adicionar_ao_buffer(args, Candango_NULO, strlen(Candango_NULO));

  return args->strings->text_normal;
}


