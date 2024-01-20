## Inter-Process Communication in C Using Message Queues

This lab is about inter-process communication using message queues in Unix-like systems with a sender and a receiver process.

### Implementation Details

1. **Message Queue Creation**: Both processes access a common message queue.
2. **File Reading and Sending**: Sender reads a file and sends content.
3. **Receiving and Word Counting**: Receiver processes and counts words.

### Usage

1. Write a free number of words separated by space in **input.txt** and save the file.
2. Compile both the receiver and sender:
   ```bash
   gcc -o receiver receiver.c
   gcc -o sender sender.c
   ```
3. In one terminal window/tab, run the receiver to wait for the sender:
   ```bash
   ./receiver
   ```
4. In another terminal window/tab, run the sender to send the contents of **input.txt** to the receiver:
   ```bash
   ./sender
   ```
   The receiver will then display the word count, e.g., "Total words: 5".

Ensure that the receiver and sender are run concurrently for the process to work correctly.