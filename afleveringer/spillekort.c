#include <stdio.h>
#include <stdlib.h>

// Cards in deck (without jokers)
#define CARDS_IN_DECK 52

typedef struct card {
    int color;
    int value;
} card;

void makeDeck(card *deck);
void print_deck(card *deck);
void sort_cards(card *deck);
int compare_color(const void *a, const void *b);
int compare_value(const void *a, const void *b);


int main(void){

    card deck[CARDS_IN_DECK];
    makeDeck(deck);
    sort_cards(deck);
    print_deck(deck);

    return 0;
}

// Function to create cards and insert in deck
void makeDeck(card *deck){
    for (int i = 0; i < CARDS_IN_DECK; i++){
        card c;
        c.value = i % 13 + 2;
        c.color = i % 4 + 1;
        deck[i] = c; 
    }

    printf("Deck has been made:\n");
}

// Sort cards, first sort values, then for color
void sort_cards(card *deck){
    qsort(deck, CARDS_IN_DECK, sizeof(card), compare_value); 
    qsort(deck, CARDS_IN_DECK, sizeof(card), compare_color); 
}

// Print the deck by corresponding values and types
void print_deck(card *deck) {
    for (int i = 0; i < CARDS_IN_DECK; i++){
        if (deck[i].color == 1){
            printf("[ Clubs | ");
        } else if (deck[i].color == 2){
            printf("[ Diamonds | ");
        } else if (deck[i].color == 3){
            printf("[ Hearts | ");
        } else if (deck[i].color == 4){
            printf("[ Spades | ");
        } 

        if (deck[i].value == 11){
            printf("Jack ]\n");
        } else if (deck[i].value == 12){
            printf("Queen ]\n");
        } else if (deck[i].value == 13){
            printf("King ]\n");
        } else if (deck[i].value == 14){
            printf("Ace ]\n");
        } else {
            printf("%d ]\n", deck[i].value);
        }
    }

    for (int i = 0; i < 3; i++){
        printf("[ Joker ]\n");
    }
}

// Function to compare two values for the qsort()
int compare_color(const void *a, const void *b) {
    card *cardA = (card *)a;
    card *cardB = (card *)b;
  
    return (cardA->color - cardB->color);
}

// Function to compare two "colors" for the qsort()
int compare_value(const void *a, const void *b) {
    card *cardA = (card *)a;
    card *cardB = (card *)b;
  
    return (cardA->value - cardB->value);
}