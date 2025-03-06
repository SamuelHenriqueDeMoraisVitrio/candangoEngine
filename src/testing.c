
#include "imports/imports.def.h"


int main() {

  lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = newLuaCEmbedEvaluation();

  //Candango_read_text_by_chunck("big_text.txt");
  printf("%s", Candango_read_text_by_chunck("big_text.txt"));

  return 0;
}

