
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



const char *Candango_find_primary_key(const char *chunk, const char **keys, short *key_started){
  const char *menor = NULL;

  for (short i = 0; i < CANDANGO_SIZE_INIT_KEYS; i++) {
    const char *pos = strstr(chunk, keys[i]);
    if (pos && (!menor || pos < menor)) {
      if(key_started){
        *key_started = i + 1;
      }
      menor = pos;
    }
  }

  return menor;
}



