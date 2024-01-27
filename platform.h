#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "post.h"

typedef struct Platform {
    Post* Posts;
    Post* lastViewedPost; 
    int numposts;
} Platform;

Platform* createPlatform();
bool addPost(char* username, char* caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();
bool addComment(char* username, char* content);
bool deleteComment(int n);
Comment* viewComments();
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);

#endif
