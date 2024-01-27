#include "platform.h"
#include "comment.h"

Comment* createComment(char* username, char* content) {
    Comment* comment = (Comment*)malloc(sizeof(Comment));
    comment->Content = strdup(content);
    comment->Username = strdup(username);
    comment->next = NULL;
    comment->Replies = NULL;
    comment->numreply = 0;
    return comment;
}