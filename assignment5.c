/*
 * assignment5.c - CPU scheduling
 *
 * Ethan Alder
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20 // Max tasks

int pid[MAX], arrival[MAX], burst[MAX], remain[MAX], start[MAX], end[MAX];
int queue[MAX], qlen = 0; // Ready queue

// Take the task at index i from the ready queue and return its index in the task arrays.
int take(int i) {
    int t = queue[i];
    for (int j = i; j < qlen - 1; j++) {
        queue[j] = queue[j + 1];
    } 
    qlen--;
    return t;
}

int main(int argc, char *argv[]) {
    // Check command line arguments.
    if (argc < 3) {
        printf("Usage: ./assignment5 input_file [FCFS|RR|SJF] [time_quantum]\n");
        return 1;
    }
    char *alg = argv[2];
    // Check algorithm and time quantum.
    int rr = strcmp(alg, "RR") == 0, sjf = strcmp(alg, "SJF") == 0;
    int quantum = (rr && argc > 3) ? atoi(argv[3]) : 0;
    if ((!rr && !sjf && strcmp(alg, "FCFS") != 0) || (rr && quantum <= 0)) {
        printf("Invalid algorithm or missing time quantum\n");
        return 1;
    }

    // Read input file.
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { printf("Cannot open %s\n", argv[1]); return 1; }
    int n;
    fscanf(fp, "%d", &n);
    // Read tasks into arrays.
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %d %d", &pid[i], &arrival[i], &burst[i]);
        remain[i] = burst[i];
    }
    fclose(fp);

    // Initialize variables for scheduling.
    int order[MAX], done = 0;
    // Arrays to store segments for RR scheduling.
    int seg_pid[1000], seg_start[1000], seg_end[1000], nseg = 0;
    // Initialize variables for the main loop.
    int cur = -1, used = 0, time = 0;

    while (done < n) {
        // 1. Check for new arrivals and add them to the ready queue.
        for (int i = 0; i < n; i++)
            if (arrival[i] == time) {
                printf("<time %d> P%d arrives\n", time, pid[i]);
                queue[qlen++] = i;
            }

        // 2. Preempt the current task if RR and quantum is used up.
        if (rr && cur != -1 && used == quantum) {
            printf("<time %d> P%d preempted\n", time, pid[cur]);
            seg_pid[nseg] = pid[cur]; seg_start[nseg] = time - used; seg_end[nseg++] = time;
            queue[qlen++] = cur;
            cur = -1;
        }

        // 3. CPU free: FCFS/RR take the head, SJF takes the shortest burst.
        if (cur == -1 && qlen > 0) {
            int best = 0;
            if (sjf)
                for (int i = 1; i < qlen; i++)
                    if (burst[queue[i]] < burst[queue[best]]) best = i;
            cur = take(best);
            if (remain[cur] == burst[cur]) start[cur] = time;
            used = 0;
        }

        // 4. Run the task for one time unit, or idle.
        if (cur == -1) {
            printf("<time %d> idle\n", time);
        } else {
            printf("<time %d> P%d running\n", time, pid[cur]);
            remain[cur]--;
            used++;
            if (remain[cur] == 0) {
                end[cur] = time + 1;
                printf("<time %d> P%d finished\n", time + 1, pid[cur]);
                seg_pid[nseg] = pid[cur]; seg_start[nseg] = time + 1 - used; seg_end[nseg++] = time + 1;
                order[done++] = cur;
                cur = -1;
            }
        }
        time++;
    }

    // Print statistics.
    double total = 0;
    printf("\n");
    if (rr) {
        printf("PID\tStart\tEnd\tRunning\n");
        for (int i = 0; i < nseg; i++)
            printf("%d\t%d\t%d\t%d\n", seg_pid[i], seg_start[i], seg_end[i],seg_end[i] - seg_start[i]);
        printf("\nPID\tArrival\tRunning\tEnd\tWaiting\n");
        for (int i = 0; i < n; i++) {
            int wait = end[i] - arrival[i] - burst[i];
            total += wait;
            printf("%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], burst[i], end[i], wait);
        }
    } else {
        printf("PID\tArrival\tStart\tEnd\tRunning\tWaiting\n");
        for (int k = 0; k < n; k++) {
            int i = order[k];
            int wait = end[i] - arrival[i] - burst[i];
            total += wait;
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], start[i], end[i], burst[i], wait);
        }
    }
    printf("\nAverage Waiting Time: %g\n", total / n);
    return 0;
}
