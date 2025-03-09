
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



char *Candango_formater_text_default(
  Candango_args_render *self,
  const char *chunk, size_t index,
  long long size_chunk,
  LuaCEmbed *machine,
  char *CANDANGO_KEY_INIT_ARGUMENT,
  char *CANDANGO_KEY_END_ARGUMENT,
  char *(*Formatter)(Candango_args_render *Candango_args, const char *text_working, size_t block_size, LuaCEmbed *machine_arg))
{

  const char *text_working = chunk + index;//Posição da primeira chave para frente, text: 'é {nome}' chave: '{' posição: 'nome'('n')

  const char *finded_end_key = strstr(text_working, CANDANGO_KEY_END_ARGUMENT);
  int size_end_key = strlen(CANDANGO_KEY_END_ARGUMENT);
  int Candango_size_init_key_ignore = strlen(CANDANGO_KEY_INIT_PASS_KEY);
  int Candango_size_end_key_ignore = strlen(CANDANGO_KEY_END_PASS_KEY);

  bool condition = finded_end_key >= text_working + (size_chunk - index);

  if(!condition){

    if(!finded_end_key){
      Candango_adicionar_ao_buffer_lua(self, text_working, size_chunk - index);//Adiciona todo chunk a partir do text_working
      return NULL;
    }

    if((finded_end_key - Candango_size_init_key_ignore) >= text_working){
      if(strncmp(CANDANGO_KEY_INIT_PASS_KEY, finded_end_key - Candango_size_init_key_ignore, Candango_size_init_key_ignore) == 0){
        if(strncmp(CANDANGO_KEY_END_PASS_KEY, finded_end_key + size_end_key, Candango_size_end_key_ignore) == 0){
          Candango_adicionar_ao_buffer_lua(self, text_working, (finded_end_key - Candango_size_init_key_ignore) - text_working);
          Candango_adicionar_ao_buffer_lua(self, finded_end_key, size_end_key);
          const char *render_rest = finded_end_key + size_end_key + Candango_size_end_key_ignore;
          if(strlen(render_rest) < size_chunk - index){
            return Candango_render_by_chunk(self, render_rest, size_chunk - index, machine);
          }
          return NULL;
        }
      }
    }
  }

  size_t block_finished_cod_lua = finded_end_key - text_working;

  char *candango_result_formatter = Formatter(self, text_working, block_finished_cod_lua, machine);
  if(candango_result_formatter){
    return candango_result_formatter;
  }

  self->key_started = CANDANGO_NOTHING;
  const char *init_block_last_end_key = finded_end_key + size_end_key;
  long long size_new_chunk = (chunk + size_chunk) - init_block_last_end_key;
  if(finded_end_key > 0){
    char *response = Candango_render_by_chunk(self, init_block_last_end_key, size_new_chunk, machine);
    if(response){
      return response;
    }
  }
  return NULL;
}

