#include "string_lookup.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define STRING_LOOKUP_NODE_CHILDREN (26)

typedef struct string_lookup_node_t{
    int32_t value;
    struct string_lookup_node_t * children[STRING_LOOKUP_NODE_CHILDREN];
} string_lookup_node_t;

static uint32_t get_child_index(char character){
    if(((character >= 'A') && (character <= 'Z')) ||
       ((character >= 'a') && (character <= 'z'))){
        return (uint32_t)to_lower(character) - 'a';
    }
    else{
        return STRING_LOOKUP_NODE_CHILDREN;
    }
}

static string_lookup_node_t * create_string_lookup_node(void){
    string_lookup_node_t * node;
    uint32_t child_index;

    node = (string_lookup_node_t *)malloc(sizeof(string_lookup_node_t));
    node->value = DEFAULT_STRING_LOOKUP_VALUE;
    for(child_index = 0; child_index < STRING_LOOKUP_NODE_CHILDREN;
        ++child_index){
        (node->children)[child_index] = NULL;
    }
    return node;
}

void register_string_lookup_value(string_lookup_t * string_lookup,
                                  const char * name, int32_t value){
    string_lookup_node_t ** node = (string_lookup_node_t **)string_lookup;
    uint32_t name_index = 0;
    uint32_t name_length = (uint32_t)strlen(name);
    uint32_t child_index;

    while(name_index < name_length){
        if(*node == NULL){
            *node = create_string_lookup_node();
        }

        child_index = get_child_index(name[name_index]);
        node = &(((*node)->children)[child_index]);
        ++name_index;
    }

    if(*node == NULL){
        *node = create_string_lookup_node();
    }
    (*node)->value = value;
}

int32_t string_lookup_value(string_lookup_t * string_lookup,
                            const char * name){
    string_lookup_node_t * node = *((string_lookup_node_t **)string_lookup);
    uint32_t name_index = 0;
    uint32_t name_length = (uint32_t)strlen(name);
    uint32_t child_index;

    while(name_index < name_length){
        if(node == NULL){
            return DEFAULT_STRING_LOOKUP_VALUE;
        }

        child_index = get_child_index(name[name_index]);
        if(child_index >= STRING_LOOKUP_NODE_CHILDREN){
            return DEFAULT_STRING_LOOKUP_VALUE;
        }
        node = (node->children)[child_index];
        ++name_index;
    }

    if(node == NULL){
        return DEFAULT_STRING_LOOKUP_VALUE;
    }
    else{
        return node->value;
    }
}

static void free_string_lookup_node(string_lookup_node_t * node){
    uint32_t child_index;

    for(child_index = 0; child_index < STRING_LOOKUP_NODE_CHILDREN;
        ++child_index){
        if((node->children)[child_index] != NULL){
            free_string_lookup_node((node->children)[child_index]);
        }
    }

    free(node);
}

void free_string_lookup(string_lookup_t * string_lookup){
    if(*string_lookup != NULL){
        free_string_lookup_node(*((string_lookup_node_t **)string_lookup));
        *string_lookup = NULL;
    }
}
