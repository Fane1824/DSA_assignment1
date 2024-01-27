#ifndef _COMMENT_H
#define _COMMENT_H
#include "reply.h"

typedef struct Comment {
    char* Username;
    char* Content;
    Reply* Replies;
    struct Comment* next;
    int numreply;
} Comment;

Comment* createComment(char* username, char* content);

#endif