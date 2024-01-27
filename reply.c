#include "platform.h"
#include "reply.h"

Reply* createReply(char* username, char* content) {
    Reply* reply = (Reply*)malloc(sizeof(Reply));
    reply->Content = strdup(content);
    reply->Username = strdup(username);
    reply->next = NULL;
    return reply;
}