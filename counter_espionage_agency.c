#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "header.h"


#define FILE_NOT_FOUND  1
#define ARG_FILE "arguments.txt"

typedef struct {
    int id;
    int active;
} AgencyMember;

typedef struct {
    int id;
    int active;
} ResistanceMember;

typedef struct {
    int num_agency_members;
    int resistance_group_interval;
    int resistance_group_min_members;
    int resistance_group_max_members;
    float military_group_spy_chance;
    float civilian_spy_chance;
    float suspicion_threshold;
    float questioning_threshold;
    int severe_injury_recovery_time;
    int light_injury_recovery_time;
    int max_killed_resistance_members;
    int max_injured_resistance_members;
    int agency_member_target_time;
} Config;

Config config;
pthread_mutex_t lock;

void read_arguments(const char *filename, Config *config) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(FILE_NOT_FOUND);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "num_agency_members=%d", &config->num_agency_members) == 1) continue;
        if (sscanf(line, "resistance_group_interval=%d", &config->resistance_group_interval) == 1) continue;
        if (sscanf(line, "resistance_group_min_members=%d", &config->resistance_group_min_members) == 1) continue;
        if (sscanf(line, "resistance_group_max_members=%d", &config->resistance_group_max_members) == 1) continue;
        if (sscanf(line, "military_group_spy_chance=%f", &config->military_group_spy_chance) == 1) continue;
        if (sscanf(line, "civilian_spy_chance=%f", &config->civilian_spy_chance) == 1) continue;
        if (sscanf(line, "suspicion_threshold=%f", &config->suspicion_threshold) == 1) continue;
        if (sscanf(line, "questioning_threshold=%f", &config->questioning_threshold) == 1) continue;
        if (sscanf(line, "severe_injury_recovery_time=%d", &config->severe_injury_recovery_time) == 1) continue;
        if (sscanf(line, "light_injury_recovery_time=%d", &config->light_injury_recovery_time) == 1) continue;
        if (sscanf(line, "max_killed_resistance_members=%d", &config->max_killed_resistance_members) == 1) continue;
        if (sscanf(line, "max_injured_resistance_members=%d", &config->max_injured_resistance_members) == 1) continue;
        if (sscanf(line, "agency_member_target_time=%d", &config->agency_member_target_time) == 1) continue;
    }

    fclose(file);
}

void* agency_member_behavior(void* arg) {
    AgencyMember* member = (AgencyMember*)arg;
    while (member->active) {
        // Simulate data analysis and spy identification
        sleep(5);
        printf("Agency member %d analyzing data...\n", member->id);
    }
    return NULL;
}

void* resistance_member_behavior(void* arg) {
    ResistanceMember* member = (ResistanceMember*)arg;
    while (member->active) {
        // Simulate resistance member activities
        sleep(5);
        printf("Resistance member %d performing activities...\n", member->id);
    }
    return NULL;
}

void handle_sigint(int sig) {
    printf("Caught signal %d (SIGINT)\n", sig);
    exit(0);
}

void initialize_agency_members(int num_members) {
    pthread_t threads[num_members];
    AgencyMember agency_members[num_members];
    for (int i = 0; i < num_members; i++) {
        agency_members[i].id = i + 1;
        agency_members[i].active = 1;
        pthread_create(&threads[i], NULL, agency_member_behavior, &agency_members[i]);
    }
    for (int i = 0; i < num_members; i++) {
        pthread_join(threads[i], NULL);
    }
}

void initialize_resistance_groups() {
    int group_id = 1;

    while (1) {
        sleep(config.resistance_group_interval);
        int num_members = rand() % (config.resistance_group_max_members - config.resistance_group_min_members + 1) + config.resistance_group_min_members;

        pthread_t threads[num_members];
        ResistanceMember resistance_members[num_members];


        for (int i = 0; i < num_members; i++) {
            resistance_members[i].id = group_id * 100 + i + 1; //
            resistance_members[i].active = 1;
            pthread_create(&threads[i], NULL, resistance_member_behavior, &resistance_members[i]);
        }
        for (int i = 0; i < num_members; i++) {
            pthread_join(threads[i], NULL);
        }
        group_id++;
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Read configuration from arguments.txt
    read_arguments(ARG_FILE, &config);

    // Initialize mutex
    pthread_mutex_init(&lock, NULL); // for race conditions

    // Create processes for civilians, resistance groups, and counter espionage agency
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Resistance groups
        initialize_resistance_groups();
        exit(0);
    } else if (pid > 0) {
        // Parent process: Counter espionage agency
        initialize_agency_members(config.num_agency_members);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Main loop
    while (1) {
        // Simulate agency operations
        sleep(10);
        printf("Counter espionage agency running...\n");
    }

    pthread_mutex_destroy(&lock);
    return 0;
}