//utils
#ifndef UTILS_H
#define UTILS_H

#include "kernel/types.h"
#include "user/user.h"

static inline void die(char *msg){
    printf("%ss\n", msg);
    exit(1);
}

static inline int streq(char *a, char *b){
    return strcmp(a, b)==0;
}

#endif