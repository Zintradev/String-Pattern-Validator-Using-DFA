#include <stdio.h>
#include <ctype.h>
#include <string.h>

int pos_error=1;

char next_char(char texto[50], int *longitud) {
    char caracter;
    caracter = texto[*longitud]; 
    (*longitud)++;
    return caracter;
}

// Función para clasificar un carácter en una categoría
int char_class(char caracter) {
    if (caracter >= 'A' && caracter <= 'Z') return 1;  
    if (caracter >= 'a' && caracter <= 'z') return 2;  
    if (isdigit(caracter)) return 3;                    
    if (ispunct(caracter)) return 4;                     
    return 0; 
}

// Función para calcular el siguiente estado basado en el autómata
int next_state(int tipoCaracter, int old_state) {
    switch (old_state) {
        case 0: // Estado inicial
            if (tipoCaracter == 1) return 1; // (A|ϵ)
            if (tipoCaracter == 4) return 2; // Si empieza directamente con p
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 1: // Después de (A|ϵ)
            if (tipoCaracter == 4) return 2; // p
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 2: // Después de p
            if (tipoCaracter == 2 || tipoCaracter == 3) return 3; // (a|d)
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 3: // Después de (a|d)
            if (tipoCaracter == 1 || tipoCaracter == 2) return 4;// (A|a|ϵ)
            if (tipoCaracter == 4) return 5; // Si ϵ
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 4: // Después de (A|a|ϵ)
            if (tipoCaracter == 4) return 5; // p
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 5: // Después de p
            if (tipoCaracter == 2) return 6; // (a|ϵ)
            if (tipoCaracter == 2 || tipoCaracter == 1) return 7; // Si ϵ
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 6: // Después de (a|ϵ)
            if (tipoCaracter == 2 || tipoCaracter == 1) return 7; // (a|A)
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 7: // Después de (a|A)
            if (tipoCaracter == 2) return 8; // a
            if (tipoCaracter == 3) return 9; // Si la letra 5 ha sido ϵ esta a sobra porque seria d
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 8: // Después de a
            if (tipoCaracter == 3) return 9; // d
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 9: // Después de d
            if (tipoCaracter == 4) return 10; // p
            printf("Posicion de error: %i",pos_error);
            return 11; // Error
        case 10: // Estado de aceptación
            return 10; // Permanecer en el estado de aceptación
        default:
            return 11; // Error
    }
}

int main() {
    int state = 0;      // Estado inicial
    int token_type = 0; // Tipo de token: 1 = válido, 0 = error
    char input[50];     // Arreglo para la entrada del usuario
    int longitud = 0;   // Índice actual de la cadena
    char character;     // Carácter actual
    int class;          // Clase del carácter actual

    // Solicitar la entrada del usuario
    printf("Please write your string (+ENTER): ");
    scanf("%s", input); 

    // Obtener el primer carácter
    character = next_char(input, &longitud);

    // Bucle principal
    while (state != 10 && state != 11) { // Continua hasta aceptación o error
        class = char_class(character); // Clasifica el carácter actual
        state = next_state(class, state); // Calcula el siguiente estado
        character = next_char(input, &longitud); // Avanza al siguiente carácter
        pos_error++;
    }

    // Determinar el tipo de token según el estado final
    token_type = (state == 10) ? 1 : 0;

    // Resultado final
    if (token_type == 1) {
        printf("\nString IS VALID according to the expression.\n");
    } else {
        printf("\nString IS NOT VALID according to the expression.\n");
    }

    return 0;
}
