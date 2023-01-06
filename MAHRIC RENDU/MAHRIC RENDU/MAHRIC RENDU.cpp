#include <iostream>
#include <string>
#include <sstream>
#include <array>

using namespace std;

struct Pile {
    int top;
    static const int taillePile = 100;
    array<double, taillePile> data;
};

void push(Pile& pile, double value) {
    if (pile.top < pile.taillePile - 1) {
        pile.top++;
        pile.data[pile.top] = value;
    }
}

double pop(Pile& pile) {
    if (pile.top >= 0) {
        return pile.data[pile.top--];
    }
    return 0;
}

double peek(const Pile& pile) {
    if (pile.top >= 0) {
        return pile.data[pile.top];
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
    Pile pile;
    pile.top = -1;
    stringstream entreeUtilisateur = initialise();
    while (entreeUtilisateur >> token) {
        if (isOperator(token[0])) {
            if (pile.top < 1) {
                cout << "Erreur: pas asser d'operandes pour l'operateur : " << token[0] << endl;
                return 1;
            }
            double operand2 = pop(pile);
            double operand1 = pop(pile);
            double result = calcul(token[0], operand1, operand2);
            push(pile, result);
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
            push(pile, value);
        }
    }

    if (pile
        .top == 0) {
        cout << "Resultat : " << peek(pile) << endl;
    }
    else {
        if (pile.top > 0) {
            cout << "Error: trop d'operandes" << endl;
        }
        else {
            cout << "Erreur: pas asser d'operandes" << endl;
        }
    }
    return 0;
}
