#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LOG_INTERVAL 2  // Interval in seconds for logging data
#define NUM_ENTRIES 5   // Number of entries to simulate

// Simulate reading data int readData() {
    return rand() % 100;  // Simulate data between 0 and 99
}

// Function to log data
void logData(int data) {
    printf("Logging Data: %d\n", data);
}

// Real-time data logging system
int main() {
    srand(time(NULL));  // Seed the random number generator

    for (int i = 0; i < NUM_ENTRIES; i++) {
        // Simulate data collection and logging at a fixed interval
        int data = readData();
        logData(data);

        // Simulate real-time delay (logging every LOG_INTERVAL seconds)
        sleep(LOG_INTERVAL);  // Delay for the specified interval
    }

    return 0;
}