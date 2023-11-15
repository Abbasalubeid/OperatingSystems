#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSGLIMIT 1024

struct message_buffer {
    long msg_type;
    char msg_text[MSGLIMIT];
};

int countWords(char *str) {
    int count = 0;
    int inWord = 0;

    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            inWord = 0; // Not in a word anymore
        } else if (inWord == 0) {
            inWord = 1; // We've started a new word
            count++;
        }
        str++;
    }

    return count;
}

int main() {
    key_t key;
    int msgid;
    struct message_buffer message;
    int totalWords = 0;

    // Generate a unique key
    key = ftok("queuekey", 65);

    // Connect to the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive messages and count words
    while (1) {
         // The fourth argument (1) is the message type we are receiving
        // The fifth argument (0) specifies that we are blocking until a message arrives
        if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // End of file
        if (strlen(message.msg_text) == 0) 
        break;  

        totalWords += countWords(message.msg_text);
    }

    printf("Total words: %d\n", totalWords);

    // Destroy the message queue to free up system resources
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
