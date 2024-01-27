#ifndef _POST_H
#define _POST_H
#include "comment.h"

typedef struct Post {
    char* Username;
    char* Caption;
    Comment* Comments;
    struct Post* next;
    int numcomment;
} Post;

Post* createPost(char* username, char* caption);

#endif
