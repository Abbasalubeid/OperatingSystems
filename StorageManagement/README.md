## Disk Scheduling Algorithms in C

This program implements and compares different disk-scheduling algorithms. The program processes 1000 random cylinder requests on a disk with 5000 cylinders (0 to 4999).

## Disk Scheduling Algorithms Included

### FCFS (First-Come, First-Served)
Processes requests in the order they arrive, straightforward but not always efficient.

### SSTF (Shortest Seek Time First)
Selects the request closest to the current head position. It can cause starvation for some requests.

### SCAN
Moves the head from one end of the disk to the other, servicing requests along the way, then reverses direction at the end.

### C-SCAN (Circular SCAN)
Similar to SCAN but moves in only one direction. Upon reaching the end, it returns to the beginning without servicing requests on the return trip.

### Look
Variation of SCAN. The arm only goes as far as the last request in each direction, then reverses immediately without reaching the disk's end.

### C-Look
Similar to C-SCAN, a variation of Look. It only services requests in one direction and quickly returns to the start after the last request.

These algorithms aim to optimize the disk's total head movement, improving overall efficiency and reducing wait times.


### Usage
1. Compile the program:
   ```bash
   gcc -o disk-scheduling disk-scheduling.c
   ```
2. Run the program with an initial disk head position within the range of 0 to 4999 (e.g., 2500):
   ```bash
   ./disk-scheduling 2500
   ```

The output reports total head movements for each algorithm. Different runs give varying results due to 1000 random cylinder requests.