
#include "../src/dependencies/doTheWorld/doTheWorld.h"

int main(){

  const char *path_html = "testes/teste_home.html";
  char *file = dtw_load_string_file_content(path_html);

  printf("\n\t%s\n\n", file);

  free(file);
  
  return 0;
}
