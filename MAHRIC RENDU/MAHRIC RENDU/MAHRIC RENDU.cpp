#include <iostream>
#include <string>
#include <sstream>
using namespace std;
const int STACK_SIZE = 100;

struct Stack {
    double data[STACK_SIZE];
    int top;
};

void push(Stack& stack, double value) {
    if (stack.top < STACK_SIZE - 1) {
        stack.data[++stack.top] = value;
    }
}

double pop(Stack& stack) {
    if (stack.top >= 0) {
        return stack.data[stack.top--];
    }
    return 0;
}

double peek(Stack& stack) {
    if (stack.top >= 0) {
        return stack.data[stack.top];
    }
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double calcul(char operation, double operand1, double operand2) {
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        return 0;
    }
}

int main() {
    string input;
    cout << "Entrez un calcul sous forme de notation polonaise : ";
    getline(std::cin, input);

    stringstream inputStream(input);
    string token;
    Stack stack;
    stack.top = -1;

    while (inputStream >> token) {
        if (isOperator(token[0])) {
            double operand2 = pop(stack);
            double operand1 = pop(stack);
            double result = calcul(token[0], operand1, operand2);
            push(stack, result);
            cout << operand1 << " " << token[0] << " " << operand2 << " = " << result << std::endl;
        }
        else {
            double value;
            try {
                value = std::stod(token);
            }
            catch (const std::invalid_argument& e) {
                cout << "Entrée invalide " << token << std::endl;
                return 1;
            }
            push(stack, value);
        }
    }

    if (stack.top == 0) {
        cout << "Resultat : " << peek(stack) << std::endl;
    }
    else {
        cout <<
            "Calcul impossible." << std::endl;
    }
    return 0;
}

