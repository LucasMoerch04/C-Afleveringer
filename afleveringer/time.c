#include <stdio.h>
#define SECONDS_PR_WEEK 604800
#define SECONDS_PR_DAY 86400
#define SECONDS_PR_HOUR 3600
#define SECONDS_PR_MINUTE 60

int main(void){
    // Initialize variables
    
    int chosenSec, seconds, minutes, hours, days, weeks;

    // Prompts user for input of seconds
    printf("Insert amount of seconds: ");
    scanf("%d", &chosenSec);

    // Converts data
    seconds = chosenSec % 60;
    minutes = (chosenSec / SECONDS_PR_MINUTE) % 60;
    hours = (chosenSec / SECONDS_PR_HOUR) % 24;
    days = (chosenSec / SECONDS_PR_DAY) % 7;
    weeks = (chosenSec / SECONDS_PR_WEEK);

    // Outputs the result
    printf("\n%d seconds amount to: \n" 
            "%d weeks, \n"
            "%d days, \n"
            "%d hours, \n"
            "%d minutes, \n"
            "%d seconds \n",
            chosenSec, weeks, days, hours, minutes, seconds);

    return 0;
}
