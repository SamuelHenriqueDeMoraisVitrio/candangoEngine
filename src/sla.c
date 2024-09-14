
#include "dependencies/depB.LuaCEmbed.h"

LuaCEmbedNamespace lua;

int main(int argc, char *argv[]){

  lua = newLuaCEmbedNamespace();

  LuaCEmbed *l = newLuaCEmbedEvaluation();

  lua.evaluate(l, "ss = \"\"");
  lua.evaluate(l, " if true then ss = ss .. \"Samuel\" ss = ss .. \" H\" end");
  char *ss = lua.globals.get_string(l, "ss");

  printf("\n\t%s\n\n", ss);
  
  return EXIT_SUCCESS;
}
