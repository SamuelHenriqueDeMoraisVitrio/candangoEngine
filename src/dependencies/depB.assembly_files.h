
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.dep.h"
//silver_chain_scope_end



#define PRIVATE_FILE_TYPE 1
#define PRIVATE_FOLDER_TYPE 2
#define PRIVATE_NOT_FOUND -1

unsigned char *private_get_any_content(const char * path,long *size,bool *is_binary);

char *private_get_string_in_file_content(const char * path);

int private_file_type(const char *path);

char *private_get_string_in_file_content(const char * path){
    long size;
    bool is_binary;
    unsigned char *element = private_get_any_content(path,&size,&is_binary);
    if(element == NULL){
        return NULL;
    }

    if(is_binary){
        free(element);
        return NULL;
    }
    return (char*)element;
}

unsigned char *private_get_any_content(const char * path,long *size,bool *is_binary){

    *is_binary = false;
    *size = 0;

    int entity = private_file_type(path);
    if(entity != PRIVATE_FILE_TYPE){
        return NULL;
    }
    FILE  *file = fopen(path,"rb");

    if(file ==NULL){
        return NULL;
    }


    if(fseek(file,0,SEEK_END) == -1){
        fclose(file);
        return NULL;
    }


    *size = ftell(file);

    if(*size == -1){
        fclose(file);
        return NULL;
    }

    if(*size == 0){
        fclose(file);
        return (unsigned char*)strdup("");
    }


    if(fseek(file,0,SEEK_SET) == -1){
        fclose(file);
        return NULL;
    }

    unsigned char *content = (unsigned char*)malloc(*size +1);
    int bytes_read = fread(content,1,*size,file);
    if(bytes_read <=0 ){
        free(content);
        fclose(file);
        return NULL;
    }


    *is_binary = false;
    for(int i = 0;i < *size;i++){
        if(content[i] == 0){
            *is_binary = true;
            break;
        }
    }
    content[*size] = '\0';

    fclose(file);
    return content;
}

int private_file_type(const char *path){
    //returns 1 for file, 2 for directory, -1 for not found
    struct stat path_stat;

    if(stat(path,&path_stat) == 0){
        if(S_ISREG(path_stat.st_mode)){
            return PRIVATE_FILE_TYPE;
        }else if(S_ISDIR(path_stat.st_mode)){
            return PRIVATE_FOLDER_TYPE;
        }
    }
    return PRIVATE_NOT_FOUND;

}

