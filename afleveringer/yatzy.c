/*
Navn: Lucas Metz Mørch
Email: lmorch24@student.aau.dk
Fag: IMPR
Gruppe: SW1
Studieretning: Software
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define AMOUNT_OF_ROUNDS 16

// Initiate prototypes
void play_yatzi(void);
int getAmountInput(void);
int *roll_multiple_dice(int n);
int check_for_lower_in_roll(int *rolls, int n, int target);
int calculate_score(int count, int value);
int check_for_upper_in_roll(int *scores, int *rolls, int n, int round);
int find_multiples_in_roll(int *rolls, int n, int amount, int ignore);
int find_straights(int *rolls, int n, int start);
int get_sum(int *array, int n);
int compare(const void *a, const void *b);
void print_scoreboard(char *rounds[], int *scores);

int main(void){
    char answer = 'y';
    printf("Welcome to YATZI!\n");
    printf("-----------------\n");

    // Runs the Yatzy game and asks to play again
    do {
        play_yatzi();
        printf("Want to play again? y/n\n");
        scanf(" %c", &answer);
    } while (answer == 'y');

    return 0;
}

// Function to play a game of Yatzy
void play_yatzi(void){
    int n = getAmountInput();
    int count;
    int *rolls;
    int *scores = malloc(AMOUNT_OF_ROUNDS * sizeof(int));
    if (scores == NULL){
        exit(EXIT_FAILURE);
    }
    // Array of round "names"
    char *rounds[] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "BONUS", "One pair", "Two pair", "Three of a kind", "Four of a kind", "Small straight", "Large straight", "Full house", "Chance", "Yatzy"};
    srand(time(NULL));

    printf("\nPrinting dice:\n");
    for (int round = 0; round < AMOUNT_OF_ROUNDS; round++){
        int target = round + 1;
        // Rolls dice if not "Bonus round"
        if (round != 6){
            printf("%s ", rounds[round]);
            rolls = roll_multiple_dice(n);
            // sort the rolls for more efficient search
            qsort(rolls, n, sizeof(int), compare); 
        }
        // Gets scores for first six rounds (Lower)
        if (round < 6){
            count = check_for_lower_in_roll(rolls, n, target);
            printf("-- %d\n", calculate_score(count, target));
            scores[round] = calculate_score(count, target);
        // Get scores for rest of rounds (Upper)
        } else {
            count = check_for_upper_in_roll(scores, rolls, n, target);
            if (round != 6){
                printf("-- %d\n", count);
            }
            scores[round] = count;
        }
        free(rolls);
        rolls = NULL;
    }
    print_scoreboard(rounds, scores);
    free(scores);
}

// Function to let user input number of dice (least 5)
int getAmountInput(void){
    int n;
    do {
        printf("Enter number of dice you want to roll each round (at least 5): ");
        scanf(" %d", &n);
    } while (n < 5);
    
    return n;
}

// Function to roll random dice
int *roll_multiple_dice(int n){
    int *rolls = malloc(n * sizeof(int));

    if (rolls == NULL){
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++){
        rolls[i] = (rand() % 6) + 1;
        printf("%d ", rolls[i]);
    } 

    return rolls;
}

// Function to check for "Lowers" (1-6) and how many (max 5)
int check_for_lower_in_roll(int *rolls, int n, int target){
    int count = 0, i = 0;

    do {
        if (rolls[i] == target){
            count++;
        }
        i++;
    } while(i < n && count < MAX);

    return count;
}

// Function to return calculated score of round
int calculate_score(int count, int value){
    return count * value;
}

// Function to check for "Uppers" 
int check_for_upper_in_roll(int *scores, int *rolls, int n, int round){
    int score = 0;
    int eyes, three_eyes, pair_eyes;
    switch(round){
        // Bonus
        case 7:
            if (get_sum(scores, 6) >= 63){
                score = 50;
            } else{
                score = 0;
            }
            break;
        // One pair
        case 8:
            score = find_multiples_in_roll(rolls, n, 2, 7) * 2;
            break;
        // Two pairs
        case 9: 
            eyes = find_multiples_in_roll(rolls, n, 2, 7);
            if (eyes > 0){
                pair_eyes = find_multiples_in_roll(rolls, n, 2, eyes);
                score = (eyes + pair_eyes) * 2;
            } else if (eyes == 0 || pair_eyes == 0){
                score = 0;
            }
            break;
        // Three of a kind
        case 10: 
            score = find_multiples_in_roll(rolls, n, 3, 7) * 3;
            break;
        // Four of a kind
        case 11:
            score = find_multiples_in_roll(rolls, n, 4, 7) * 4;
            break;
        // Small straight
        case 12:
            score = find_straights(rolls, n, 0) ? 15 : 0;
            break;
        // Large straight
        case 13:
            score = find_straights(rolls, n, 1) ? 20 : 0;
            break;
        // Full house
        case 14:
            three_eyes = find_multiples_in_roll(rolls, n, 3, 7);
            pair_eyes = find_multiples_in_roll(rolls, n, 2, three_eyes);
            if (three_eyes == 0 || pair_eyes == 0){
                score = 0;
            } else{
                score = (three_eyes * 3) + (pair_eyes * 2);
            }
            break;
        // Chance
        case 15:
            for (int i = 0; i < 5; i++){
                score += rolls[n - 1 - i];
            }
            break;
        // YATZY
        case 16:
            if (find_multiples_in_roll(rolls, n, 5, 7)){
                score = 50;
            } else {
                score = 0;
            }
            break;
    }
    return score;
}

// Function to find multiples of a given "eyes"
int find_multiples_in_roll(int *rolls, int n, int amount, int ignore){
    for (int j = 6; j > 0; j--){
        if (j == ignore) {
            continue;
        }
        int count = 0;
        for (int i = 0; i < n; i++){  
            if (rolls[i] == j){
                count++;
            }
            if (count >= amount){
                return j;
            }
        }
    }
    return 0;
}

// Function look for Small and Large straights
int find_straights(int *rolls, int n, int start){
    int count = 0;
    int target = 1 + start;
    for (int i = 0; i < n; i++){
        
        if (rolls[i] == target){
            target++;
        }
        if (target == 5 + start){
            break;
        }
    }
    if (target < 5 + start){
        return 0;
    }
    return 1;
}

// Function to calculate sum of integers in given array
int get_sum(int *array, int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += array[i];
    }
    return sum;
}

// Function to compare two numbers for the qsort()
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to print the final scoreboard
void print_scoreboard(char *rounds[], int *scores){  
    printf("\n----------------\n");
    printf("Score board:\n");
    for (int i = 0; i < AMOUNT_OF_ROUNDS; i++){
        printf("%s : %d \n", rounds[i], scores[i]);
    }
    printf("\nTOTAL SCORE: %d\n", get_sum(scores, AMOUNT_OF_ROUNDS));
    printf("----------------\n");
}