#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

void play_yatzi(void);
int getAmountInput(void);
int *roll_multiple_dice(int n);
int check_for_number_in_roll(int *rolls, int n, int amount);
int calculate_score(int count, int value);
void print_scoreboard(char *rounds[], int *scores);
int check_for_other_in_roll(int *scores, int *rolls, int n, int rule);
int find_pairs_in_roll(int *rolls, int n, int a, int top);
int find_straights(int *rolls, int n, int start);
int compare(const void *a, const void *b);
int get_sum(int *array, int n);

int main(void){
    char g = 'y';
    printf("Welcome to YATZI\n");
    do {
        play_yatzi();
        printf("Want to play again? y/n\n");
        scanf(" %c", &g);
    } while (g == 'y');

    return 0;
}

void play_yatzi(void){
    int N = getAmountInput();
    int *scores = malloc(16 * sizeof(int));
    int count;
    int *rolls;

    char *rounds[] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Bonus", "One pair", "Two pair", "Three of a kind", "Four of a kind", "Small straight", "Large straight", "Full house", "Chance", "Yatzy"};
    srand(time(NULL));
    int rounds_amount = sizeof(rounds) / sizeof(rounds[0]);

    printf("Printing dies:\n");
    for (int i = 0; i<rounds_amount; i++){
        if (i != 6){
            printf("%s ", rounds[i]);
            rolls = roll_multiple_dice(N);
            qsort(rolls, N, sizeof(int), compare); 
        }
    
        if (i < 6){
            count = check_for_number_in_roll(rolls, N, i+1);
            printf(" -- %d\n", calculate_score(count, i+1));
            scores[i] = calculate_score(count, i+1);
        } else {
            count = check_for_other_in_roll(scores, rolls, N, i+1);
            if (i != 6){
                printf(" -- %d\n", count);
            }
            scores[i] = count;
        }
        free(rolls);
        rolls = NULL;
    }
    print_scoreboard(rounds, scores);
    free(scores);
}

int getAmountInput(void){
    int n;
    do {
        printf("Enter number of dice (at least 5): ");
        scanf("%d", &n);
    } while (n < 5);
    
    return n;
}

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

int check_for_number_in_roll(int *rolls, int n, int amount){
    int count = 0, i = 0;

    do {
        if (rolls[i] == amount){
            count++;
        }
        i++;
    } while(i < n && count < MAX);

    return count;
}

int calculate_score(int count, int value){
    return count * value;
}

void print_scoreboard(char *rounds[], int *scores){  

    printf("Score board:\n");
    for (int i = 0; i < 16; i++){
        printf("%s : %d \n", rounds[i], scores[i]);
    }
    printf("Sum: %d\n", get_sum(scores, 16));
}

int check_for_other_in_roll(int *scores, int *rolls, int n, int rule){
    int score, eyes, three_eyes, pair_eyes;
    switch(rule){
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
            score = find_pairs_in_roll(rolls, n, 2, 7) * 2;
            break;
        // Two pairs
        case 9: 
            eyes = find_pairs_in_roll(rolls, n, 2, 7);
            if (eyes > 0){
                pair_eyes = find_pairs_in_roll(rolls, n, 2, eyes);
                score = (eyes) * 2 + (pair_eyes * 2);
            } else{
                score = 0;
            }
            break;
        // Three of a kind
        case 10: 
            score = find_pairs_in_roll(rolls, n, 3, 7) * 3;
            break;
        // Four of a kind
        case 11:
            score = find_pairs_in_roll(rolls, n, 4, 7) * 4;
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
            three_eyes = find_pairs_in_roll(rolls, n, 3, 7);
            pair_eyes = find_pairs_in_roll(rolls, n, 2, three_eyes);
            if (three_eyes == 0 || pair_eyes == 0){
                score = 0;
            } else{
                score = (three_eyes * 3) + (pair_eyes * 2);
            }
            break;
        // Chance
        case 15:
            score = get_sum(rolls, n);
            break;
        // YATZY
        case 16:
            if (find_pairs_in_roll(rolls, n, 5, 7)){
                score = 50;
            } else {
                score = 0;
            }
            break;
    }
    return score;
}

int find_pairs_in_roll(int *rolls, int n, int a, int top){
    for (int j = 6; j > 0; j--){
        if (j == top) {
            continue;
        }
        int count = 0;
        for (int i = 0; i < n; i++){  
            if (rolls[i] == j){
                count++;
            }
            if (count >= a){
                return j;
            }
        }
    }
    return 0;
}

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

int get_sum(int *array, int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += array[i];
    }
    return sum;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}