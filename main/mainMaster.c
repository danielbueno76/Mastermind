 /*Proyecto Global: Mastermind                                     |
  Fecha de entrega: 11/ 12 /2013    	                           |
  Versión: 6.0 + 6.1                                               |
------------------------------------------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español

//escribimos los .h necesarios
#include "../main/menus.h"
#include "../main/varias.h"
/*---------------------------------------------------------------\
| Archivo: mainMaster.c                                          |
| Funciones usadas: main()                                       |
\---------------------------------------------------------------*/
int main() //esta fuuncion main solo hace la llamda de dos  funciones.
{
    setlocale(LC_CTYPE, "Spanish"); //muestra los caracteres como la ñ y las tildes


    intro(); //llamamos a la funcion que nos muestra la bienvenida y las instrucciones del juego

    system("pause"); //para que continuemos debemos pulsar una tecla
    system("cls");   //borra el contenudo de la pantalla

    gestionMenuPrincipal(); //esta funcion llamará al resto de funciones

    return 0; //devolvemos valor 0 para indicar que todo fue bien
}
