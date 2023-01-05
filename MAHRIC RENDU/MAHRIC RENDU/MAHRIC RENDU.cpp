#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

// Structure de pile
struct Stack {
    int top;
    int capacity;
    double* array;
};

// Création de pile
Stack* createStack(int capacity) {
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = new double[(stack->capacity * sizeof(double))];
    return stack;
}

// Vérifier si la pile est vide
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Vérifier si la pile est pleine
bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Ajouter un élément à la pile
void push(Stack* stack, double item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Supprimer un élément de la pile
double pop(Stack* stack) {
    if (isEmpty(stack))
        return 0;
    return stack->array[stack->top--];
}

// Fonction principale
int main() {
    Stack* stack = createStack(100);

    // Lire l'expression à réduire
    string expression;
    int expression_length = expression.length();
    cout << "Entrez l'expression à réduire : ";
    getline(cin, expression);

    // Réduire l'expression
    for (int i = 0; i < expression_length; i++) {
        // Si c'est un opérande, ajouter à la pile
        if (expression[i] >= '0' && expression[i] <= '9')
            push(stack, expression[i] - '0');

        // Si c'est un opérateur
        else {
            // Extraire les opérandes
            double op1 = pop(stack);
            double op2 = pop(stack);

            // Effectuer l'opération
            switch (expression[i]) {
            case '+':
                push(stack, op2 + op1);
                break;
            case '-':
                push(stack, op2 - op1);
                break;
            case '*':
                push(stack, op2 * op1);
                break;
            case '/':
                push(stack, op2 / op1);
                break;
            }
        }
    }

    // Afficher le résultat
    cout << "Résultat : " << pop(stack) << endl;

    return 0;
}
