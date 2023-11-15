#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSGLIMIT 1024

// A struct that represents the message format.
struct message_buffer {
    long msg_type;
    char msg_text[MSGLIMIT];
};

int main() {
    key_t key;  // Key for the message queue
    int msgid;  // Message queue ID
    struct message_buffer message;

    // Generate a unique key
    key = ftok("queuekey", 65);

    // Create a message queue
    // 0666 | IPC_CREAT sets the permissions and creates the queue if it doesn't exist.
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    // Open the file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    // Read the file and send messages
    while (fgets(message.msg_text, MSGLIMIT, file) != NULL) {
        // The fourth argument (0) specifies the message priority (0 in this case).
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    // Send an empty message to indicate end of file
    strcpy(message.msg_text, "");
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    fclose(file);

    return 0;
}
