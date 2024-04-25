#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a job
struct Job {
    int id;
    int deadline;
    int profit;
};

// Function to compare jobs based on their profit (used for sorting)
int compare(const void *a, const void *b) {
    struct Job *jobA = (struct Job *)a;
    struct Job *jobB = (struct Job *)b;
    return jobB->profit - jobA->profit; // Sort in descending order of profit
}

// Function to implement job sequencing with deadline using a greedy approach
void jobSequencing(struct Job jobs[], int n) {
    // Sort jobs in descending order of profit
    qsort(jobs, n, sizeof(struct Job), compare);

    // Find the maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // Create an array to keep track of available time slots
    int *timeSlots = (int *)malloc(maxDeadline * sizeof(int));
    for (int i = 0; i < maxDeadline; i++) {
        timeSlots[i] = -1; // Initialize time slots as available
    }

    // Array to store the scheduled jobs
    struct Job scheduledJobs[maxDeadline];
    int scheduledCount = 0;
    int totalProfit = 0;

    // Schedule jobs in the available time slots
    for (int i = 0; i < n; i++) {
        // Find an available time slot for the current job
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (timeSlots[j] == -1) {
                // Schedule the job
                timeSlots[j] = i;
                scheduledJobs[scheduledCount++] = jobs[i];
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print the scheduled jobs and total profit
    printf("Scheduled Jobs (Job ID, Deadline, Profit):\n");
    for (int i = 0; i < scheduledCount; i++) {
        printf("Job ID: %d, Deadline: %d, Profit: %d\n", scheduledJobs[i].id, scheduledJobs[i].deadline, scheduledJobs[i].profit);
    }
    printf("Total Profit: %d\n", totalProfit);

    // Free the allocated memory for time slots
    free(timeSlots);
}

int main() {
    int n;

    // Input the number of jobs
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    // Input the details of each job (Job ID, Deadline, Profit)
    struct Job jobs[n];
    printf("Enter the details of the jobs (Job ID, Deadline, Profit):\n");
    for (int i = 0; i < n; i++) {
        printf("Job %d: ", i + 1);
        scanf("%d %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    // Perform job sequencing using the greedy approach
    jobSequencing(jobs, n);

    return 0;
}
