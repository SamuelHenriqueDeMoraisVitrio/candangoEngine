
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end



char *Candango_formater_text_default(
    Candango_args_render *self,
    const char *chunk,
    size_t index,
    long long size_chunk,
    LuaCEmbed *machine,
    char *CANDANGO_KEY_INIT_ARGUMENT,
    char *CANDANGO_KEY_END_ARGUMENT,
    char *(*Formatter)(Candango_args_render *Candango_args, const char *text_working, size_t block_size, LuaCEmbed *machine_arg));



