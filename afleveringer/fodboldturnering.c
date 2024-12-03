/*
Navn: Lucas Metz Mørch
Email: lmorch24@student.aau.dk
Fag: IMPR
Gruppe: SW1
Studieretning: Software
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT_OF_MATCHES 90
#define AMOUNT_OF_TEAMS 12

typedef struct Match {
    char day[4]; // Chars has 1 additional space for null-terminator
    char date[6];
    char time[6];
    char team1[4];
    char team2[4];
    int team1_goals;
    int team2_goals;
    int attendance;
} Match;

typedef struct Team {
    char *name;
    int points;
    int goals_scored;
    int goals_against;
} Team;

Match *load_file(void);
void initialize_team_array(Team *team_array);
void assign_team_data(Match *match_array, Team *team_array);
int assign_points(int teamA_goals, int teamB_goals);
int compare_teams(const void *a, const void *b);
void print_scoreboard(Team *team_array);


int main(void) {
    Match *match_array = load_file();
    Team team_array[AMOUNT_OF_TEAMS];

    initialize_team_array(team_array);
    assign_team_data(match_array, team_array); 
    qsort(team_array, 12, sizeof(Team), compare_teams);
    print_scoreboard(team_array);
   
    // Free allocated memory
    free(match_array);

    return 0;
}

Match *load_file(void) {
    // Allocate memory to array of Match structs
    Match *match_array = malloc(sizeof(Match) * AMOUNT_OF_MATCHES);
    if (!match_array) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen("kampe-2024-2025.txt", "r"); // Opens file in read-mode

    if (!file) {
        printf("Failed to open file\n");
        free(match_array); // Free allocated memory before exiting
        exit(EXIT_FAILURE);
    }

    // Parse data from each match into match array
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++) {
        if (fscanf(file, " %3s %5s %5s %3s - %3s %d - %d %d", 
                        match_array[i].day, match_array[i].date, match_array[i].time,
                        match_array[i].team1, match_array[i].team2, 
                        &match_array[i].team1_goals, &match_array[i].team2_goals, 
                        &match_array[i].attendance) != 8) {
            printf("Error reading match data at index %d\n", i);
            free(match_array);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return match_array;
}

// Searches for teams in every match and updates data
void assign_team_data(Match *match_array, Team *team_array){
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++){
        for (int j = 0; j < AMOUNT_OF_TEAMS; j++){
            if (strcmp(match_array[i].team1, team_array[j].name) == 0){
                team_array[j].points += assign_points(match_array[i].team1_goals, match_array[i].team2_goals);
                team_array[j].goals_scored += match_array[i].team1_goals;
                team_array[j].goals_against += match_array[i].team2_goals;

            } if (strcmp(match_array[i].team2, team_array[j].name) == 0){
                team_array[j].points += assign_points(match_array[i].team2_goals, match_array[i].team1_goals);
                team_array[j].goals_scored += match_array[i].team2_goals;
                team_array[j].goals_against += match_array[i].team1_goals;
            }
        }
    }
}

// Returns 3 points for win, 1 for draw, 0 for loss
int assign_points(int teamA_goals, int teamB_goals){
    if (teamA_goals > teamB_goals){
        return 3;
    } else if (teamB_goals == teamA_goals){
        return 1;
    } else {
        return 0;
    }
}

// Inserts every team into array and gives default values
void initialize_team_array(Team *team_array){
    char *team_names[AMOUNT_OF_TEAMS] = {"AaB", "AGF", "BIF", "FCK", "FCM", "FCN", "LBK", "RFC", "SIF", "SJF", "VB", "VFF"};
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++){
        team_array[i].name = team_names[i];
        team_array[i].points = 0;
        team_array[i].goals_scored = 0;
        team_array[i].goals_against = 0;
    }
}

// Function to compare values for the qsort()
int compare_teams(const void *a, const void *b) {
    Team *teamA = (Team *)a;
    Team *teamB = (Team *)b;

    // Compare points first
    if (teamB->points != teamA->points) {
        return teamB->points - teamA->points;
    }

    // If points are equal, compare goal difference
    int goal_diffA = teamA->goals_scored - teamA->goals_against;
    int goal_diffB = teamB->goals_scored - teamB->goals_against;
    return goal_diffB - goal_diffA;
}

void print_scoreboard(Team *team_array){
    printf("\n%s\n", "Superligaen 2024-2025");
    printf("-------------------------------\n");
    printf("| %-7s %-7s %-7s %-3s |\n", "Team", "Points", "GS", "GA");
    printf("-------------------------------\n");

    for (int i = 0; i < AMOUNT_OF_TEAMS; i++){
        printf("| %-7s %-7d %-7d %-3d |\n",
            team_array[i].name, team_array[i].points, team_array[i].goals_scored, team_array[i].goals_against);
    }
    printf("-------------------------------\n");

}