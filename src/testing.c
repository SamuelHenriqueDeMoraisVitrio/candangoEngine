
#include "imports/imports.def.h"


int main() {

  lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = newLuaCEmbedEvaluation();

  printf("\n\t%s\n\n", Candango_read_text_by_chunck("small_text.txt"));

  return 0;
}

