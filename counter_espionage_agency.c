// Faris Abufarha



#include "header.h"

#define FILE_NOT_FOUND  1
#define ARG_FILE "arguments.txt"


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
int main(void) {

    Config  config;

    read_arguments(ARG_FILE, &config);

    printf("config agency_member target: %d\n", config.agency_member_target_time);



    printf("Hello, World!\n");

    return 0;
}
