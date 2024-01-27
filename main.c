#include "platform.h"
#include "assert.h"
extern Platform* p;

int main() {

    while (1) {
        char command[20];
        printf("What operation would you like to perform?\n");
        scanf("%s", command);
        if (strcmp(command, "create_platform") == 0) {
            p = createPlatform();
        }
        else if (strcmp(command, "add_post") == 0) {
            char username[100];
            char caption[100];
            scanf("%s", username);
            int c;
            while ((c = getchar()) != '\n' && c != EOF && c != 32);
            fgets(caption, 100, stdin);
            bool successful = addPost(username, caption);
            if (successful == false) {
                printf("The post could not be added.\n");
            }
        }
        else if (strcmp(command, "delete_post") == 0) {
            int n;
            scanf("%d", &n);
            bool successful = deletePost(n);
            if (successful == false) {
                printf("The post does not exist.\n");
            }
        }
        else if (strcmp(command, "view_post") == 0) {
            int n;
            scanf("%d", &n);
            Post* display = viewPost(n);
            if (display == NULL) {
                printf("This post does not exist. Please create more posts.\n");
            } else {
                printf("%s ", display->Username);
                printf("%s", display->Caption);
            }
        }
        else if (strcmp(command, "current_post") == 0) {
            Post* display = currPost();
            if (display == NULL) {
                printf("This post does not exist. Please create more posts.\n");
            } else {
                printf("%s ", display->Username);
                printf("%s", display->Caption);
            }
        }
        else if (strcmp(command, "previous_post") == 0) {
            Post* display = previousPost();
            if (display == NULL) {
                printf("The previous post does not exist. Please create more posts.\n");
            } else {
                printf("%s ", display->Username);
                printf("%s", display->Caption);
            }
        }
        else if (strcmp(command, "next_post") == 0) {
            Post* display = nextPost();
            if (display == NULL) {
                printf("The next post does not exist. Please create more posts.\n");
            } else {
                printf("%s ", display->Username);
                printf("%s", display->Caption);
            }
        }
        else if (strcmp(command, "add_comment") == 0) {
            char username[100];
            char content[100];
            scanf("%s", username);
            int c;
            while ((c = getchar()) != '\n' && c != EOF && c != 32);
            fgets(content, 100, stdin);
            bool successful = addComment(username, content);
            if (successful == false) {
                printf("The comment could not be added.\n");
            }
        }
        else if (strcmp(command, "delete_comment") == 0) {
            int n;
            scanf("%d", &n);
            bool successful = deleteComment(n);
            if (successful == false) {
                printf("The comment does not exist.\n");
            }
        }
        else if (strcmp(command, "add_reply") == 0) {
            char username[100];
            char content[100];
            int n;
            scanf("%s", username);
            for (int i = 0; i < 100; i++) {
                char x;
                scanf("%c", &x);
                if (x == 10 && i == 0) {
                    scanf("%c", &x); 
                }
                if (x == 10) {
                    break;
                } else {
                    content[i] = x;
                }
            }
            scanf("%d", &n);
            bool successful = addReply(username, content, n);
            if (successful == false) {
                printf("The reply could not be added.\n");
            }
        }
        else if (strcmp(command, "delete_reply") == 0) {
            int n, m;
            scanf("%d %d", &n, &m);
            bool successful = deleteReply(n, m);
            if (successful == false) {
                printf("The reply does not exist.\n");
            }
        }     
        else if (strcmp(command, "view_all_comments") == 0 || strcmp(command, "view_comments") == 0) {
            Comment* commentviewer = viewComments();
            if (commentviewer == NULL) {
                printf("There are no comments on the last viewed post.\n");
            }
            while (commentviewer != NULL) {
                printf("%s ", commentviewer->Username);
                printf("%s", commentviewer->Content);
                Reply* replyviewer = commentviewer->Replies;
                for (int i = 0; i < commentviewer->numreply; i++) {
                    printf("\t%s ", replyviewer->Username);
                    printf("%s\n", replyviewer->Content);
                    replyviewer = replyviewer->next;
                }
                commentviewer = commentviewer->next;
            }
        }             
    }
    return 0;
}