
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



char *Candango_read_text_by_chunck(const char *path_file, LuaCEmbed *machine, bool *is_error){

  FILE *text_by_file = fopen(path_file, "r");
  if(!text_by_file){
    *is_error = true;
    return "Intern error: Open file recused";
  }

  char chunck[CANDANGO_INITIAL_SIZE_READ];
  long total_size = 0;
  char *text = NULL;

  Candango_args_render *args = Candango_New_args_render();
  char *error_message = NULL;

  unsigned long size_lines = 0;
  long long size_text_chunk;
  Candango_reset_buffer_lua(args);
  while((size_text_chunk = fread(chunck, sizeof(char), CANDANGO_INITIAL_SIZE_READ - 2, text_by_file)) > 0){//-2: 1 para o terminador nulo e 1 para o santo
    if(error_message){
      break;
    }

    chunck[size_text_chunk] = '\0';
    Candango_Realloc_Buffer(args, size_text_chunk);

    error_message = Candango_render_by_chunk(args, chunck, size_text_chunk, machine);
  }

  fclose(text_by_file);

  if(args->key_started != CANDANGO_NOTHING || error_message){
    printf("\n\t'%hd', '%s'\n\n", args->key_started, error_message);
    short Candango_size_max = 380;
    char *Candango_message = malloc(Candango_size_max + 1); 
    if(!Candango_message){
      printf("Internal error: allocate Candango_message with key_started != 0");
      exit(1);
    }
    const char *message_main = error_message?error_message:"There was no correct handling of the keys in the section:";
    if(args->size_buffer_lua_current > 50){
      snprintf(Candango_message, Candango_size_max, "Error:. %s\n%.30s ... %s;\n%s\n", message_main, args->strings->text_to_work, args->strings->text_to_work + (args->size_buffer_lua_current - 30), Candango_NULO);
    }else{
      snprintf(Candango_message, Candango_size_max, "Error:. %s\n%s ...\n%s\n", message_main, args->strings->text_to_work, Candango_NULO);
    }
    *is_error = true;

    free(args->strings->text_normal);
    Candango_free_args_render(args);
    
    return Candango_message;
  }

  Candango_adicionar_ao_buffer(args, Candango_NULO, strlen(Candango_NULO));

  char *response = args->strings->text_normal;
  Candango_free_args_render(args);
  return response;
}


