#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 1024    

float stack[MAXSTACK];
int stack_top = -1;

int stack_empty() {                                     // Function: Check if stack's empty  
    return stack_top == -1; 
}

int stack_full() {                                      // Function: Check if stack's full 
    return stack_top == MAXSTACK - 1;
}

void push(float value) {                                // Function: Push into stack
    if (!stack_full()) { 
        stack[++stack_top] = value;
    } else {
        printf("Overflow.\n");
    }
}

float pop() {                                           // Function: Pop from stack
    if (!stack_empty()) {
        return stack[stack_top--];
    } else {
        printf("Underflow.\n");
        return 0.0;  
    }
}

int input_digit(char operand) {                         // Function: Check if input is digit 
    return (operand >= '0' && operand <= '9');
}

void do_rpc(char input[]) {                             // Function: For calculations 
    float num1, num2;
    int i = 0;

    while (input[i] != '\0') {
        if (input_digit(input[i]) || (input[i] == '-' && input_digit(input[i + 1]))) {  //Positive and negative operands
            float number = atof(&input[i]);  
            push(number);  

            while (input[i] != ' ' && input[i] != '\0') {                               //Space and not EOF
                i++;
            }
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {      //Operators
            if (!stack_empty()) {
                num2 = pop();  
                if (!stack_empty()) {
                    num1 = pop();  
                    
                    float result;

                    switch (input[i]) {
                        case '+':
                            result = num1 + num2;
                            push(result);
                            break;
                        case '-':
                            result = num1 - num2;
                            push(result);
                            break;
                        case '*':
                            result = num1 * num2;
                            push(result);
                            break;
                        case '/':
                            if (num2 != 0) {
                                result = num1 / num2;
                                push(result);
                            } else {
                                printf("Division by zero.\n");
                            }
                            break;
                        default:                                                  
                            break;
                    }
                    while (input[i] != ' ' && input[i] != '\0') {                               //Space and not EOF
                        i++;
                    }
                }
            }
        } else {
            printf("Invalid Input.\n");                                      //Invalid Input like = or ? 
            stack_top = -1;
        }
        i++;  
    }
}

int main() {                                             // Function: Main
    char input[MAXSTACK];

    printf("Enter an expression: ");
    scanf("%[^\n]", input);  

    do_rpc(input);  

    if (!stack_empty())
        printf("Final Answer: %.2f\n", pop());
    else 
        printf("No Answer Generated.\n");

    return 0;
}
