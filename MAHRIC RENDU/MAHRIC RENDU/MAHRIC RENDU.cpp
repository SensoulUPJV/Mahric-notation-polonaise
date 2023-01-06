#include <iostream>
#include <string>
#include <sstream>
#include <array>

using namespace std;

struct Stack {
    int top;
    static const int taillePile = 100;
    array<double, taillePile> data;
};

void push(Stack& stack, double value) {
    if (stack.top < stack.taillePile - 1) {
        stack.top++;
        stack.data[stack.top] = value;
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

double calcul(char operation, double operande1, double operande2) {
    switch (operation) {
    case '+':
        return operande1 + operande2;
    case '-':
        return operande1 - operande2;
    case '*':
        return operande1 * operande2;
    case '/':
        return operande1 / operande2;
    default:
        return 0;
    }
}

stringstream initialise()
{
    string entree;
    cout << "Entrez un calcul sous forme de notation polonaise : ";
    getline(std::cin, entree);
    stringstream entreeUtilisateur(entree);
    return entreeUtilisateur;
}

int main() {
    string token;
    Stack stack;
    stack.top = -1;
    stringstream entreeUtilisateur = initialise();
    while (entreeUtilisateur >> token) {
        if (isOperator(token[0])) {
            if (stack.top < 1) {
                cout << "Erreur: pas asser d'operandes pour l'operateur : " << token[0] << endl;
                return 1;
            }
            double operand2 = pop(stack);
            double operand1 = pop(stack);
            double result = calcul(token[0], operand1, operand2);
            push(stack, result);
            cout << operand1 << " " << token[0] << " " << operand2 << " = " << result << endl;
        }
        else {
            double value;
            try {
                value = stod(token);
            }
            catch (const invalid_argument& e) {
                cout << "Entree invalide " << token << endl;
                return 1;
            }
            push(stack, value);
        }
    }

    if (stack
        .top == 0) {
        cout << "Resultat : " << peek(stack) << endl;
    }
    else {
        if (stack.top > 0) {
            cout << "Error: trop d'operandes" << endl;
        }
        else {
            cout << "Erreur: pas asser d'operandes" << endl;
        }
    }
    return 0;
}
