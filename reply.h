#ifndef _REPLY_H
#define _REPLY_H

typedef struct Reply {
    char* Username;
    char* Content;
    struct Reply* next;
} Reply;

Reply* createReply(char* username, char* content);

#endif