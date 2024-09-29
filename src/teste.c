

//silver_chain_scope_start
//mannaged by silver chain
#include "imports/imports.def.h"
//silver_chain_scope_end

char *private_render_text_by_lua_teste(LuaCEmbed *args, char *str){
    
    lua.evaluate(args, "%s = \"\"", VARABLE_GLOBAL_TEXT_BY_LUA);

    char *response;

    if (!str) {
        response = lua.globals.get_string(args, VARABLE_GLOBAL_TEXT_BY_LUA);
        return response;
    }

    char *result_str = private_process_block(args, str);

    lua.evaluate(args, " %s ", result_str);

    free(result_str);

    if(lua.has_errors(args)){
      return "error";
    }

    response = lua.globals.get_string(args, VARABLE_GLOBAL_TEXT_BY_LUA);

    return response;
}

int main() {

  lua = newLuaCEmbedNamespace();
  LuaCEmbed *l = newLuaCEmbedEvaluation();

  lua.evaluate(l, "variavel = \"Samuel\"");
  lua.evaluate(l, "outro = {}");
  lua.evaluate(l, "outro.sla = \"Samu\"");

  printf("\n\t%s\n\n", lua.get(l, "variavel"));

  return 0;
}

