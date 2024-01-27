#include "platform.h"
#include "post.h"

Post* createPost(char* username, char* caption) {
    Post* post = (Post*)malloc(sizeof(Post));
    post->Caption = strdup(caption);
    post->Username = strdup(username);
    post->next = NULL;
    post->Comments = NULL;
    post->numcomment = 0;
    return post;
};