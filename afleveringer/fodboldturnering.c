#include <stdio.h>
#include <stdlib.h>

#define AMOUNT_OF_MATCHES 90

// Struct containing members of data about a match
typedef struct Match {
    char day[4];
    char date[6];
    char time[6];
    char team1[4];
    char team2[4];
    int team1_goals;
    int team2_goals;
    int attendance;
} Match;

Match *load_file(void);

int main(void) {
    Match *match_array = load_file();

    printf("Day: %s, Date: %s, Time: %s, Teams: %s vs %s, Goals: %d-%d, Attendance: %d\n",
           match_array[0].day, match_array[0].date, match_array[0].time,
           match_array[0].team1, match_array[0].team2,
           match_array[0].team1_goals, match_array[0].team2_goals,
           match_array[0].attendance);

    // Free allocated memory
    free(match_array);

    return 0;
}

Match *load_file(void) {
    Match *match_array = malloc(sizeof(Match) * AMOUNT_OF_MATCHES);
    if (!match_array) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen("kampe-2024-2025.txt", "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        free(match_array); // Free allocated memory before exiting
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < AMOUNT_OF_MATCHES; i++) {
        if (fscanf(file, " %3s %5s %5s %3s - %3s %d - %d %d", 
                   match_array[i].day, match_array[i].date, match_array[i].time,
                   match_array[i].team1, match_array[i].team2, 
                   &match_array[i].team1_goals, &match_array[i].team2_goals, 
                   &match_array[i].attendance) != 8) {
            fprintf(stderr, "Error reading match data at index %d\n", i);
            free(match_array);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return match_array;
}
