#include <stdio.h>
#include <math.h>

// Initiate prototypes

double run_calculator();
void scan_data(char *operator, double *operand);
int isBinaryOperator(char operator);
void do_next_op(char operator, double operand, double *accumulator);

int main(void){
    // Runs calculator
    printf("Calculator is now running!\nType 'q' to exit.\n");
    double final_result = run_calculator();
    printf("Final result is: %lf\n", final_result);

    return 0;
}

double run_calculator(){
    double accumulator = 0.0, operand;
    char operator;

    // Calculator runs until user types 'q'
    while(1){
        scan_data(&operator, &operand);
        if (operator == 'q'){
            break;
        }
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
        // Gives error message if the operator input is not one of the cases
        default:
            printf("Invalid operator\n");
    }
    printf("Result so far: %lf.\n", *accumulator);
}

