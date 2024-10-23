#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Initiate prototypes
double run_calculator();
void scan_data(char *operator, double *operand);
int isBinaryOperator(char operator);
void do_next_op(char operator, double operand, double *accumulator);
void print_instructions(void);

int main(void){

    print_instructions();
    // Runs calculator
    printf("Calculator is now running!\nType 'q' to exit.\n");
    run_calculator();

    return 0;
}

double run_calculator(void){
    double accumulator = 0.0, operand;
    char operator;

    // Calculator runs until user types 'q'
    while(1){
        scan_data(&operator, &operand);
        do_next_op(operator, operand, &accumulator);
    }
    return accumulator;
}
// Gets inputs from user
void scan_data(char *operator, double *operand){
    printf("Enter Operator: ");
    scanf(" %c", operator);
    // Only asks for operand if operator is binary
    if (isBinaryOperator(*operator)){
        printf("Enter Operand: ");
        scanf(" %lf", operand);
    }
}

// Function to check if operator is binary or not
int isBinaryOperator(char operator){
    return (operator == '+' || operator =='-' ||operator == '*' || operator == '/' || operator == '^');
}

// Performs the operations on the accumulator
void do_next_op(char operator, double operand, double *accumulator){
    switch(operator){
        // Binary operations
        case '+':
            *accumulator += operand;
            break; 
        case '-':
            *accumulator -= operand;
            break;
        case '*':
            *accumulator *= operand;
            break;
        case '/':
            if(operand != 0){
                *accumulator /= operand;
            }
            break;
        case '^':
            *accumulator = pow(*accumulator, operand);
            break;

        // Unary operations
        case '#':
            if(*accumulator >= 0){
                *accumulator = sqrt(*accumulator);
            }
            break;
        case '%':
            *accumulator = 0 - *accumulator;
            break;
        case '!':
            if(*accumulator != 0){
                *accumulator = 1 / *accumulator;
            }
            break;
        // User closes the program by typing 'q'
        case 'q':
            printf("Final result is: %lf\n", *accumulator);
            exit(EXIT_SUCCESS);
        // Gives error message if the operator input is not one of the cases
        default:
            printf("Invalid operator\n");
    }
    printf("Result so far: %lf.\n", *accumulator);
}

// Function to print the instructions
void print_instructions(void){
    printf("\033[0;34m      BINARY OPERATORS:\n"
        "|+    for addition of the accumulator w/ the operand\n"
        "|-    for subtraction of the accumulator w/ the operand\n"
        "|*    for multiplication of the accumulator w/ the operand\n"
        "|/    for division of the accumulator w/ the operand\n"
        "|^    for exponentiation of the accumulator w/ the operand\n\n");

    printf("      UNARY OPERATORS:\n"
        "|#    for the square root of the accumulator\n"
        "|%%    for reversing the sign of the accumulator\n"
        "|!    for dividing 1 by the accumulator\n"
        "|q    for terminating the calculator with the final result\n"
        "-----------------------------------------------------------------\n\033[0m");
}

