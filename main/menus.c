/*-----------------------------------------------------------------\
| Archivo: menus.c                                                 |
| Funciones usadas: menuPrincipal() y gestionMenuPrincipal()       |
\-----------------------------------------------------------------*/
#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español

//escribimos todos los .h necesarios
#include "../Informes/informes.h"
#include "../Config/config.h"
#include "../Juego/partida.h"
#include "../main/menus.h"
#include "../main/varias.h"
#include "../Informes/ranking.h"

char menuPrincipal()
{
    int opcion; //variable opcion

    //pide que selccionemos una opcion y nos muestra las posibilidades
    printf("\nElige una de las opciones siguientes:\n");
    printf("1-Configuración\n");
    printf("2-Empezar la partida\n");
    printf("3-Mejores puntuaciones\n");
    printf("4-Ranking por niveles\n");
    printf("0-Salir\n");
    printf("-> ");
    scanf("%d",&opcion); //Introducimos la opcion deseada

    if(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4) //si opcion no es ni 0 ni 1 ni 2 ni 3
    {
        printf("Selección incorrecta\n");
        exit(1);
    }
    return opcion; //devuelve el valor que hameos seleccionado a la funcion desde donde la llama
}
void gestionMenuPrincipal()
{
    int opcion=1;
    while(opcion!=0)
    {
        opcion=(int)menuPrincipal(); //llamada a la funcion. el valor que recibe será almacenado en opcion
        switch(opcion)  //con el valor de la variable recibida se reliza  un switch que seleccionará una opcion
        {
        case 1: //si opcion es igual a 1...
            system("cls");
            gestionConfig();
            break; //en todo case hace alta un break
        case 2:
            system("cls");
            jugarPartida();
            break;
        case 3:
            system("cls");
            gestionPuntuaciones();//llamada a la funcion que le pasa los 4 argumentos
            break;
        case 4:
            system("cls");
            gestionRanking();
            break;
        case 0:
            salir(); //llamamos a la funcion salir
            break;
        default: //si no es ninguna de las anteriores, saldremos de la aplicacion, pues es erronea la opcion
            printf("Opción no posible\n");

        } //fin de switch/
        //borramos la pantalla para una mejor presentación y faciliad de uso
        system("pause");
        system("cls");
    }

    return;
}

