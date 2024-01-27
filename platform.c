#include "platform.h"

Platform* p;
int chflag = 0;

Platform* createPlatform() {
    Platform* platform = (Platform*)malloc(sizeof(Platform));
    platform->Posts = NULL;
    platform->lastViewedPost = NULL;
    platform->numposts = 0;
    return platform;
}

bool addPost(char* username, char* caption) {
    bool posted = false;
    if (p->Posts == NULL) {
        p->Posts = createPost(username, caption);
        posted = true;
        p->lastViewedPost = p->Posts;
    } else {
        Post* newnode = createPost(username, caption);
        newnode->next = p->Posts;
        p->Posts = newnode;
        posted = true;
        if (chflag == 0) {
            p->lastViewedPost = newnode;
        }
    }
    p->numposts++;
    return posted;
}

Post* viewPost(int n) {
    Post* temp = p->Posts;
    chflag = 1;
    int c = 1; 
    while (c != n && temp != NULL) {
        temp = temp->next;
        c++;
    }
    if (temp != NULL) {
        p->lastViewedPost = temp;
    }
    return temp;
}

Post* currPost() {
    if (p->lastViewedPost != NULL) {
        chflag = 1;
        return p->lastViewedPost;
    } 
    return NULL;
}

Post* nextPost() {
    if (p->lastViewedPost == NULL) {
        return NULL;
    }
    chflag = 1;
    if (p->lastViewedPost->next == NULL) {
        return p->lastViewedPost;
    } else {
        p->lastViewedPost = p->lastViewedPost->next;
        return p->lastViewedPost;
    }
    return NULL;
}

Post* previousPost() {
    if (p->lastViewedPost == NULL) {
        return NULL;
    }
    chflag = 1;
    if (p->lastViewedPost == p->Posts) {
        return p->lastViewedPost;
    } 
    if (p->Posts->next == p->lastViewedPost) {
        p->lastViewedPost = p->Posts;
        return p->Posts;
    } else {
        Post* temp = p->Posts;
        while (temp->next != p->lastViewedPost) {
            temp = temp->next;
        }
        p->lastViewedPost = temp;
        return temp;
    }
    return NULL;
}

bool addComment(char* username, char* content) {
    bool commented = false;
    Comment* newComment = createComment(username, content);
    if (p->lastViewedPost->Comments == NULL) {
        p->lastViewedPost->Comments = newComment;
        p->lastViewedPost->numcomment++;
        commented = true;
    } else {
        Comment* temp = p->lastViewedPost->Comments;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newComment;
        p->lastViewedPost->numcomment++;
        commented = true;
    }
    return commented;
}

bool deleteReply(int n, int m) {
    bool deleted = false;
    if (p->lastViewedPost != NULL) {
        if (p->lastViewedPost->Comments != NULL) {
            n = p->lastViewedPost->numcomment - n + 1;
            Comment* comtemp = p->lastViewedPost->Comments;
            int c = 1; 
            while (c != n && comtemp != NULL) {
                comtemp = comtemp->next;
                c++;
            }
            m = comtemp->numreply - m + 1;
            if (comtemp != NULL && c == n && m <= comtemp->numreply) {
                Reply* delbuffer;
                if (m == 1 || m == 2) {
                    if (m == 1) {
                        delbuffer = comtemp->Replies;
                        comtemp->Replies = comtemp->Replies->next;
                    } else {
                        delbuffer = comtemp->Replies->next;
                        comtemp->Replies->next = comtemp->Replies->next->next;
                    }
                }
                else {
                    int c2 = 1;
                    while (c2 != m-1) {
                        comtemp->Replies = comtemp->Replies->next;
                        c2++;
                    }
                    delbuffer = comtemp->Replies->next;
                    comtemp->next = comtemp->next->next;
                }
                comtemp->numreply--;
                free(delbuffer);
                deleted = true;
            }
        }
    }
    return deleted;
}

bool deleteComment(int n) {
    bool deleted = false;
    if (p->lastViewedPost != NULL) {
        if (p->lastViewedPost->Comments != NULL && n <= p->lastViewedPost->numcomment) {
            n = p->lastViewedPost->numcomment - n + 1;
            Comment* delbuffer;
            if (n == 1 || n == 2) {
                if (n == 1) {
                    delbuffer = p->lastViewedPost->Comments;
                    p->lastViewedPost->Comments = p->lastViewedPost->Comments->next;
                } else {
                    delbuffer = p->lastViewedPost->Comments->next;
                    p->lastViewedPost->Comments->next = p->lastViewedPost->Comments->next->next;
                }
            } else {
                Comment* comtemp = p->lastViewedPost->Comments;
                int c2 = 1;
                while (c2 != n-1) {
                    comtemp = comtemp->next;
                    c2++;
                }
                delbuffer = comtemp->next;
                comtemp->next = comtemp->next->next;
            }
            while (delbuffer->Replies != NULL) {
                Reply* tempd = delbuffer->Replies;
                delbuffer->Replies = delbuffer->Replies->next;
                free(tempd);
            }
            deleted = true;
            free(delbuffer);
            if (p->lastViewedPost->numcomment != 0) {
                p->lastViewedPost->numcomment--;
            }
        }
    } 
    return deleted;
}

bool deletePost(int n) {
    bool deleted = false;
    Post* temp = p->Posts;
    int flag = 0;
    Post* delpost;
    if (n <= p->numposts) {
        int c = 1;
        if (n == 1) {
            if (n == p->numposts) {
                p->lastViewedPost = NULL;
                chflag = 0;
            } else {
                if (temp == p->lastViewedPost) {
                    p->lastViewedPost = temp->next;
                } 
            }
            delpost = p->Posts;
            p->Posts = p->Posts->next;
        } else {
            while (c != n-1 && temp != NULL) {
                temp = temp->next;
                c++;
            }
            if (temp->next == p->lastViewedPost) {
                p->lastViewedPost = p->Posts;
            }     
            delpost = temp->next;
            temp->next = temp->next->next;
        }
        flag = 1;
    }
    Post* delpost2 = delpost;
    if (flag == 1) {
        Comment* commentbuffer = delpost2->Comments;
        while (commentbuffer != NULL) {
            Reply* replybuffer = commentbuffer->Replies;
            while (replybuffer != NULL) {
                Reply* tempr = replybuffer;
                replybuffer = replybuffer->next;
                free(tempr);
            }
            Comment* tempc = commentbuffer;
            commentbuffer = commentbuffer->next;
            free(tempc);
        }
        free(delpost2);
        deleted = true;
        p->numposts--;
    }
    return deleted;
}

bool addReply(char* username, char* content, int n) {
    bool replied = false;
    if (p->lastViewedPost != NULL) {
        if (p->lastViewedPost->Comments != NULL) {
            n = p->lastViewedPost->numcomment - n + 1;
            Comment* comtemp = p->lastViewedPost->Comments;
            int c = 1; 
            while (c != n && comtemp != NULL) {
                comtemp = comtemp->next;
                c++;
            }
            if (comtemp != NULL && c == n) {
                if (comtemp->Replies == NULL) {
                    comtemp->Replies = createReply(username, content);
                } else {
                    while (comtemp->Replies->next!= NULL) {
                        comtemp->Replies = comtemp->Replies->next;
                    }
                    comtemp->Replies->next = createReply(username, content);
                }
                comtemp->numreply++;
                replied = true;
            }
        }
    }
    return replied;
}

Comment* viewComments() {
    Comment* comments = p->lastViewedPost->Comments;
    return comments;
}

