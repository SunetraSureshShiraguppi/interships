#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Simulated sensors
int sensor_1() { return rand() % 50 + 10; }  // Generates a value between 10 and 59
int sensor_2() { return rand() % 50 + 10; }
int sensor_3() { return rand() % 50 + 10; }

// Define system constants
#define TEMP_THRESHOLD 100  // Max allowed temperature
#define MAX_RETRIES 3        // Max retries for fault recovery

// Fault Logging Function
void log_fault(const char *message) {
    time_t now = time(NULL);
    printf("[FAULT] %s at %s", message, ctime(&now));
}

// Watchdog Timer
void watchdog_timer(bool system_healthy) {
    if (!system_healthy) {
        log_fault("System unresponsive. Watchdog triggered reset.");
        exit(1);  // Simulate system reset
    }
}

// Majority Voting for Redundancy
int majority_vote(int val1, int val2, int val3) {
    if (val1 == val2 || val1 == val3) return val1;
    if (val2 == val3) return val2;
    return -1;  // Error: No majority
}

// Fault Recovery 
bool recover_from_fault() {
    for (int i = 0; i < MAX_RETRIES; i++) {
        printf("Attempting recovery... (%d/%d)\n", i + 1, MAX_RETRIES);
        int recovered_value = rand() % 50 + 10;  // Simulate recovery
        if (recovered_value <= TEMP_THRESHOLD) {
            printf("Recovery successful. Recovered value: %d\n", recovered_value);
            return true;
        }
    }
    return false;  // Recovery failed
}

// Main  Loop
void monitor_temperature() {
    while (1) {
        // Simulated sensor readings
        int temp1 = sensor_1();
        int temp2 = sensor_2();
        int temp3 = sensor_3();

        printf("Sensor Readings: %d, %d, %d\n", temp1, temp2, temp3);

        // Majority voting for redundancy
        int voted_temp = majority_vote(temp1, temp2, temp3);
        if (voted_temp == -1) {
            log_fault("Sensor disagreement detected. Entering recovery mode.");
            if (!recover_from_fault()) {
                log_fault("Recovery failed. System shutdown.");
                exit(1);  // Shutdown system
            }
        } else {
            printf("Voted Temperature: %d\n", voted_temp);
        }

        // Fault detection
        if (voted_temp > TEMP_THRESHOLD) {
            log_fault("Over-temperature detected. Triggering safety shutdown.");
            exit(1);  // Trigger fail-safe mechanism
        }

        // System health monitoring (Watchdog)
        watchdog_timer(true);  // System healthy

        // Delay (simulated)
        sleep(2);  // 2-second delay
    }
}

int main() {
    printf("Starting Fault-Tolerant System...\n");
    srand(time(NULL));  // Seed for random sensor data
    monitor_temperature();  // Start monitoring
    return 0;
}