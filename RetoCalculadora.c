#include <stdio.h>
#include <math.h>

//Numero Pi//

#define PI 3.141592653589793

//Funciones matematicas//

double sumar(double a, double b) {
    return a + b;
}

double restar(double a, double b) {
    return a - b;
}

double multiplicar(double a, double b) {
    return a * b;
}

double dividir(double a, double b) {
    return a / b;
}

double potencia(double base, double exp) {
    return pow(base, exp);
}

double seno(double a) {
    return sin(a * PI / 180.0);
}

double coseno(double a) {
    return cos(a * PI / 180.0);
}

double tangente(double a) {
    double rad = a * PI / 180.0;

    if (fabs(cos(rad)) < 1e-10) {
        printf("Math Error\n");
        return 0.0;
    }

    return tan(rad);
}


double raiz(double a) {
    if (a < 0) {
        printf("Error: raiz de numero negativo\n");
        return a;
    }
    return sqrt(a);
}

//Funciones del stack//

void mostrarStack(double stack[], int cantidad) {
    int i;
    printf("\nStack:\n");
    for (i = 7; i >= 0; i--) {
        if (i < cantidad)
            printf("%d  %.6lf\n", i + 1, stack[i]);
        else
            printf("%d  0.000000\n", i + 1);
    }
}

void push(double stack[], int *cantidad, double num) {
    int i;
    if (*cantidad == 8) {
        printf("Stack lleno (maximo 8 valores)\n");
        return;
    }

    for (i = *cantidad; i > 0; i--) {
        stack[i] = stack[i - 1];
    }

    stack[0] = num;
    (*cantidad)++;
}

void pop(double stack[], int *cantidad) {
    int i;
    if (*cantidad == 0) {
        printf("Stack vacio\n");
        return;
    }

    for (i = 0; i < *cantidad - 1; i++) {
        stack[i] = stack[i + 1];
    }

    (*cantidad)--;
}

void limpiarTodo(int *cantidad) {
    *cantidad = 0;
}

//Logica de operaciones//

void aplicarOperacion(double stack[], int *cantidad, char op) {
    double resultado;
    double a, b;

//Operaciones binarias//

if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'p') {

    /* Obtener operandos */
    b = (*cantidad >= 1) ? stack[0] : 0.0;
    a = (*cantidad >= 2) ? stack[1] : 0.0;

    switch (op) {
        case '+': resultado = sumar(a, b); break;
        case '-': resultado = restar(a, b); break;
        case '*': resultado = multiplicar(a, b); break;
        case '/':
            if (b == 0) {
                printf("Error: division por cero\n");
                return;
            }
            resultado = dividir(a, b);
            break;
        case 'p': resultado = potencia(a, b); break;
        default: return;
    }

    /* Liberar posiciones usadas */
    if (*cantidad >= 1) pop(stack, cantidad);
    if (*cantidad >= 1) pop(stack, cantidad);

    push(stack, cantidad, resultado);
}

    // Operaciones unitarias //
    else {
        if (*cantidad < 1) {
            printf("Stack vacio\n");
            return;
        }

        switch (op) {
            case 'r': stack[0] = raiz(stack[0]); break;
            case 's': stack[0] = seno(stack[0]); break;
            case 'c': stack[0] = coseno(stack[0]); break;
            case 't': stack[0] = tangente(stack[0]); break;
            default:
                printf("Operacion invalida\n");
        }
    }
}

//Programa principal//

int main() {
    double stack[8];
    int cantidad = 0;
    int opcion;
    char operacion;
    double num;
    int i;

    for (i = 0; i < 8; i++) {
        stack[i] = 0.0;
    }

    mostrarStack(stack, cantidad);

    do {
        printf("\n--- Calculadora RPN ---\n");
        printf("1. Ingresar numero\n");
        printf("2. Operacion\n");
        printf("3. Limpiar posicion 1\n");
        printf("4. Limpiar todo el stack\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese numero: ");
                scanf("%lf", &num);
                push(stack, &cantidad, num);
                mostrarStack(stack, cantidad);
                break;

            case 2:
                printf("Operaciones: +, - , * , / , p (Potencia) , r (Raiz) , s (Seno) , c (Coseno) , t (Tangente) : ");
                scanf(" %c", &operacion);
                aplicarOperacion(stack, &cantidad, operacion);
                mostrarStack(stack, cantidad);
                break;

            case 3:
                pop(stack, &cantidad);
                mostrarStack(stack, cantidad);
                break;

            case 4:
                limpiarTodo(&cantidad);
                mostrarStack(stack, cantidad);
                break;

            case 5:
                printf("Saliendo de la calculadora\n");
                break;

            default:
                printf("Opcion invalida\n");
        }

    } while (opcion != 5);

    return 0;
}
