
/*-----------------------------------------------------------------\
| Archivo: varias.c                                                |
| Funciones usadas: intro() y salir()                              |
\-----------------------------------------------------------------*/
#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español

//escribimos todos los .h necesarios
#include "../main/varias.h"
void intro()
{
    //muestra el mensaje de bienvenida a MasterMind y las instrucciones dle juego
    printf("\t\t\t*****************************\n");
    printf("\t\t\t*¡¡Bienvenido a Mastermind!!*\n");
    printf("\t\t\t*****************************\n\n");

    printf("\tINSTRUCCIONES DEL JUEGO\n\n");
    printf("El juego consiste en adivinar un número determinado de letras y su posición.\n");
    printf("El jugador A introduce una secuencia y el jugador B,en este caso el ordenador,\ndebe comparar las secuencias.\n");
    printf("En caso de que la letra sea correcta y la posición coincida, el ordenador nos\nlo indicará mediante el caracter @.\n");
    printf("En caso de que la letra sea correcta y la posición no coincida, nos mostrará\nel caracter *.\n");
    printf("Un ejemplo sería:\nABFC ---> @@* (2 letras en la misma posicion y en distinta posición)\n");
    printf("\nEl juego termina cuando se acierta la secuencia o se agotan los turnos que se\ntienen\n\n");

    return;
}

void salir()
{
    //mensaje de despedida
    printf("Esperemos que haya disfrutado con sus jugadas\n");
    printf("¡¡¡¡Gracias por jugar a MasterMind, Vuelva pronto!!!!!\n");
    return;
}

