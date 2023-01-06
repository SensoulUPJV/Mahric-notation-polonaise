#include <iostream>
#include <string>
#include <sstream>
#include <array>
using namespace std;
const int taillePile = 100;

struct Stack {
    array<double, taillePile> data;
    int top;
};

void push(Stack& stack, double value) {
    if (stack.top < taillePile - 1) {
        stack.data[++stack.top] = value;
    }
}

double pop(Stack& stack) {
    if (stack.top >= 0) {
        return stack.data[stack.top--];
    }
    return 0;
}

double peek(const Stack& stack) {
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
            cout << operand1 << " " << token[0] << " " << operand2 << " = " << result <<endl;
        }
        else {
            double value;
            try {
                value = stod(token);
            }
            catch (const invalid_argument& e) {
                cout << "Entrée invalide " << token <<endl;
                return 1;
            }
            push(stack, value);
        }
    }

    if (stack.top == 0) {
        cout << "Resultat : " << peek(stack) << endl;
    }
    else {
        cout <<
            "Calcul impossible." << endl;
    }
    return 0;
}

