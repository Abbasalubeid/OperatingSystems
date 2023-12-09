#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define MAX_CYLINDER 4999
#define NUM_REQUESTS 1000


int fcfs(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_head_position = head_start;

    for(int i = 0; i < num_requests; i++) {
        // Calculate the distance the head moves to service the request
        total_head_movement += abs(request_queue[i] - current_head_position);
        // Move the head to the request's position
        current_head_position = request_queue[i];
    }

    return total_head_movement;
}

int sstf(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_head_position = head_start;
    int shortest_seek;
    int index;
    int request_serviced[1000] = {0};

    for (int i = 0; i < num_requests; i++) {
        shortest_seek = INT_MAX;

        for (int j = 0; j < num_requests; j++) {
            if (!request_serviced[j]) {
                int seek_time = abs(request_queue[j] - current_head_position);
                if (seek_time < shortest_seek) {
                    shortest_seek = seek_time;
                    index = j;
                }
            }
        }

        request_serviced[index] = 1; // Mark this request as serviced
        total_head_movement += shortest_seek;
        current_head_position = request_queue[index];
    }

    return total_head_movement;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int scan(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_position = head_start;
    int right_requests[1000], left_requests[1000];
    int right_size = 0, left_size = 0;

    qsort(request_queue, num_requests, sizeof(int), compare);

    // Split the queue into requests to the right and left of the head start
    for (int i = 0; i < num_requests; i++) {
        if (request_queue[i] < head_start) {
            left_requests[left_size++] = request_queue[i];
        } else {
            right_requests[right_size++] = request_queue[i];
        }
    }

    // Service the requests to the right
    for (int i = 0; i < right_size; i++) {
        total_head_movement += abs(right_requests[i] - current_position);
        current_position = right_requests[i];
    }

    if (current_position != MAX_CYLINDER) {
        total_head_movement += MAX_CYLINDER - current_position;
        current_position = MAX_CYLINDER;
    }

    // Service the requests to the left
    for (int i = left_size - 1; i >= 0; i--) {
        total_head_movement += abs(left_requests[i] - current_position);
        current_position = left_requests[i];
    }

    return total_head_movement;
}

int cscan(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_position = head_start;
    int i, right_size = 0;
    int right_requests[1000];

    qsort(request_queue, num_requests, sizeof(int), compare);

    // Split the queue into requests to the right of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] >= head_start) {
            right_requests[right_size++] = request_queue[i];
        }
    }

    // Service the requests to the right
    for (i = 0; i < right_size; i++) {
        total_head_movement += abs(right_requests[i] - current_position);
        current_position = right_requests[i];
    }
    
    if (current_position != MAX_CYLINDER) {
        total_head_movement += abs(current_position - MAX_CYLINDER);
        current_position = 0;
    }

    // Service the requests to the left of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] < head_start) {
            total_head_movement += abs(request_queue[i] - current_position);
            current_position = request_queue[i];
        }
    }

    return total_head_movement;
}

int look(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_position = head_start;
    int i, right_size = 0;
    int right_requests[1000];

    qsort(request_queue, num_requests, sizeof(int), compare);

    // Split the queue into requests to the right of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] >= head_start) {
            right_requests[right_size++] = request_queue[i];
        }
    }

    // Service the requests to the right
    for (i = 0; i < right_size; i++) {
        total_head_movement += abs(right_requests[i] - current_position);
        current_position = right_requests[i];
    }

    // Service the requests to the left of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] < head_start) {
            total_head_movement += abs(request_queue[i] - current_position);
            current_position = request_queue[i];
        }
    }

    return total_head_movement;
}

int clook(int request_queue[], int num_requests, int head_start) {
    int total_head_movement = 0;
    int current_position = head_start;
    int i, right_size = 0;
    int right_requests[1000];

    qsort(request_queue, num_requests, sizeof(int), compare);

    // Split the queue into requests to the right of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] >= head_start) {
            right_requests[right_size++] = request_queue[i];
        }
    }

    // Service the requests to the right
    for (i = 0; i < right_size; i++) {
        total_head_movement += abs(right_requests[i] - current_position);
        current_position = right_requests[i];
    }

    current_position = request_queue[0];
    
    // Service the requests to the left of the head start
    for (i = 0; i < num_requests; i++) {
        if (request_queue[i] < head_start) {
            total_head_movement += abs(request_queue[i] - current_position);
            current_position = request_queue[i];
        }
    }

    return total_head_movement;
}

// int main() {
//     int request_queue[] = {98, 183, 37, 122, 14, 124, 65, 67};
//     int head_start = 53;
//     int num_requests = sizeof(request_queue) / sizeof(request_queue[0]);

//     // Calculate total head movement
//     int total_head_movement_fcfs = fcfs(request_queue, num_requests, head_start);
//     int total_head_movement_sstf = sstf(request_queue, num_requests, head_start);
//     int total_head_movement_scan = scan(request_queue, num_requests, head_start);
//     int total_head_movement_cscan = cscan(request_queue, num_requests, head_start);
//     int total_head_movement_look = look(request_queue, num_requests, head_start);
//     int total_head_movement_clook = clook(request_queue, num_requests, head_start);

//     printf("Total head movement for FCFS: %d cylinders\n", total_head_movement_fcfs);
//     printf("Total head movement for SSTF: %d cylinders\n", total_head_movement_sstf);
//     printf("Total head movement for SCAN: %d cylinders\n", total_head_movement_scan);
//     printf("Total head movement for CSCAN: %d cylinders\n", total_head_movement_cscan);
//     printf("Total head movement for LOOK: %d cylinders\n", total_head_movement_look);
//     printf("Total head movement for CLOOK: %d cylinders\n", total_head_movement_clook);


//     return 0;
// }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <initial disk head position>\n", argv[0]);
        return 1;
    }

    int head_start = atoi(argv[1]);
    if (head_start < 0 || head_start > MAX_CYLINDER) {
        printf("Invalid initial head position. It must be between 0 and %d.\n", MAX_CYLINDER);
        return 1;
    }

    srand(time(NULL));
    int request_queue[NUM_REQUESTS];

    // Generate random requests
    for (int i = 0; i < NUM_REQUESTS; i++) {
        request_queue[i] = rand() % (MAX_CYLINDER + 1);
    }

    // Calculate total head movement for each scheduling algorithm
    int total_head_movement_fcfs = fcfs(request_queue, NUM_REQUESTS, head_start);
    int total_head_movement_sstf = sstf(request_queue, NUM_REQUESTS, head_start);
    int total_head_movement_scan = scan(request_queue, NUM_REQUESTS, head_start);
    int total_head_movement_cscan = cscan(request_queue, NUM_REQUESTS, head_start);
    int total_head_movement_look = look(request_queue, NUM_REQUESTS, head_start);
    int total_head_movement_clook = clook(request_queue, NUM_REQUESTS, head_start);

    printf("Total head movement for FCFS: %d cylinders\n", total_head_movement_fcfs);
    printf("Total head movement for SSTF: %d cylinders\n", total_head_movement_sstf);
    printf("Total head movement for SCAN: %d cylinders\n", total_head_movement_scan);
    printf("Total head movement for CSCAN: %d cylinders\n", total_head_movement_cscan);
    printf("Total head movement for LOOK: %d cylinders\n", total_head_movement_look);
    printf("Total head movement for CLOOK: %d cylinders\n", total_head_movement_clook);

    return 0;
}



