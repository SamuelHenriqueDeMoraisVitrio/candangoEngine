
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.includes.h"
//silver_chain_scope_end

#define CANDANGO_1KB 1000 //1KB
#define CANDANGO_1MB 1000 * 1000 //1MB

#define CANDANGO_SIZE_CHUNK CANDANGO_1KB * 9 //9KB
#define CANDANGO_INITIAL_SIZE_READ CANDANGO_1KB * 20 //20KB
#define CANDANGO_INITIAL_SIZE_BUFFER_LUA CANDANGO_1KB * 10 //10KB
#define CANDANGO_EXPONECIAL_SIZE 2 //The current size will be multiplied by this value until it reaches the limit.
#define CANDANGO_LIMIT_EXPONENTIAL_SIZE CANDANGO_1MB * 18 //18MB
#define CANDANGO_LIMIT_EXPONENTIAL_SIZE_BUFFER_LUA CANDANGO_1MB //1MB
#define CANDANGO_LINEAR_SIZE CANDANGO_1MB * 4 //4MB
#define CANDANGO_LINEAR_SIZE_BUFFER_LUA CANDANGO_1MB //1MB


