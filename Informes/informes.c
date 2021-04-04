/*----------------------------------------------------------------------------------------------------\
| Archivo: informes.c                                                                                  |
| Funciones usadas: mejoresPuntuaciones(), gestionPuntuaciones(),informeJugador(),menuPuntuaciones()   |
\----------------------------------------------------------------------------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español
#include <string.h> //permite que podamos escribir funciones como strlen()

//Escribimos los .h necesarios
//Como estos .h y .c se encuentran en carpetas debemos escribir los include de estas maneras
#include "../Informes/informes.h"
#include "../Informes/franjas.h"
void gestionPuntuaciones()
{
    //struct sJugada jugadas[40]; //Vector de Registros
    struct sListaJugadas ljugadas= {0}; //Registro de la estructura sListaJugadas;
    char arch_jug[]=ARCH_JUGADAS; //ruta del archivo jugadas.bin
    int opcion=0; //Variable con la que intducimos las opciones que deseamos para la muestra de los jugadores

    //Llamada a la función. Nos devuelve el numero de jugadas que tiene el archivo
    leeJugadas(arch_jug,&ljugadas);


    opcion=menuPuntuaciones();
    switch(opcion) //depende la opcion llamamos a una funcion
    {
    case 1:
        mejoresPuntuaciones(ljugadas);
        break;
    case 2:
        informeJugador(ljugadas);
        break;
    case 3:
        informeFranjas(ljugadas);
        break;
    case 0:
        break;
    default:
        printf("Has introducido una opción incorrecta\n");
        exit(1);
    }
    free(ljugadas.jugadas); //liberamos el espacio de memoria creada por el vector dinamico de leejugadas
}
int menuPuntuaciones()
{
    int opcion=0;
    printf("Seleccione una de las siguientes opciones\n");
    printf("1-Mejores Puntuaciones\n");
    printf("2-Informe de un Jugador\n");
    printf("3-Informes Horarios\n");
    printf("0-Menú Anterior\n");
    scanf("%d",&opcion);

    return opcion; //Devuelve la opcion deseada
}

void mejoresPuntuaciones(struct sListaJugadas ljugadas)
{
    int opcion=0; //Variable con la que introducimos las opciones que deseamos para la muestra de los jugadores
    int k=0; // Varaible que va aumentano para poder tener vectores paralelos
//    //un mensaje para indicarnoslo.
    int cont=0;
    //Mensaje que nos pide una de las selecciones
    printf("\n¿Qué puntuaciones quieres que se muestren?\n");
    printf("1-Todas las puntuaciones\n");
    printf("2-Modo experto\n");
    printf("3-Modo novato\n");
    printf("->");
    scanf("%d",&opcion); //introducimos la opcion...

    switch(opcion) //...que entren un switch
    {
    case 1: //Se muestran todas

        //No hay condicion de cual se mustra y cual no. TODAS son mostradas
        system("cls");
        printListaJugadas(ljugadas);
        cont++;


        break;

    case 2: //muestra las preoupaciones del niv el experto
        //nos pregunta de que nivel queremos que sean las puntuaciones
        printf("Puntuaciones que incluyan el modo experto pero, ¿De que nivel(1-2-3)?\n");
        printf("-> ");
        scanf("%d",&opcion); //introducimos la opcion
        fflush(stdin);
        system("cls");

        if(opcion==1) //modo experto nivel 1
        {
            printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");

            for(k=0; k<ljugadas.num; k++) //vamos recorriendo el bucle desde 0 hasta el numero de jugadas leidas
            {
                if(ljugadas.jugadas[k].novato== 0 && ljugadas.jugadas[k].nivel==1) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia


                }

            }

        }

        else if(opcion==2) //modo experto nivel 2
        {
            printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");

            for(k=0; k<ljugadas.num; k++) //vamos recorriendo el bucle desde 0 hasta el numero de jugadas leidas
            {
                if(ljugadas.jugadas[k].novato== 0 && ljugadas.jugadas[k].nivel==2) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia


                }
            }
        }

        else if(opcion==3) //modo experto nivel 3
        {
            printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");
            for(k=0; k<ljugadas.num; k++) //vamos recorriendo el bucle desde 0 hasta el numero de jugadas leidas
            {
                if(ljugadas.jugadas[k].novato== 0 && ljugadas.jugadas[k].nivel==3) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia


                }
            }

        }

        else
            printf("No existe ese nivel\n\n\n");


        break; //Break del case 2(modo experto)
    case 3:
        printf("Puntuaciones que incluyan el modo novato pero, ¿De que nivel(1-2-3)?\n");
        printf("->");
        scanf("%d",&opcion); //introducimos la opcion deseaada
        system("cls");

        if(opcion==1) //Modo novto nivel 1
        {
            printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");
            for(k=0; k<ljugadas.num; k++)
            {
                if(ljugadas.jugadas[k].novato== 1 && ljugadas.jugadas[k].nivel==1) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia


                }
            }

        }
        else if(opcion==2) //Modo novto nivel 2
        {
            printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");
            for(k=0; k<ljugadas.num; k++)
            {
                if(ljugadas.jugadas[k].novato== 1 && ljugadas.jugadas[k].nivel==2) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia



                }
            }
        }
        else if(opcion==3) //Modo novto nivel 3
        {

            for(k=0; k<ljugadas.num; k++)
            {
                if(ljugadas.jugadas[k].novato== 1 && ljugadas.jugadas[k].nivel==3) //Para que imprima  la letra deben cumplirse ambas condiciones
                {
                    //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
                    // y así lo mostramos todo ordenado.
                    printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",ljugadas.jugadas[k].nick,ljugadas.jugadas[k].nivel,ljugadas.jugadas[k].intent,
                           (int)ljugadas.jugadas[k].tiempo,ljugadas.jugadas[k].clave,ljugadas.jugadas[k].novato,
                           ljugadas.jugadas[k].hora.formato_hora,ljugadas.jugadas[k].fecha.formato_fecha);
                    cont++; //Aumenta en 1 cada vez que haya encontrado la coincidencia

                }
            }

        }
        else
            printf("No existe ese nivel\n\n\n");
        break;
    default:
        printf("La opcion que ha elegido es incorrecta");
        exit(1);

    } //Fin del switch principal

    if(cont==0) //si no ha encontrado ningun jugador que cumpla las condiciones...
        printf("\nNo hay jugadores que cumplan estas condiciones todavia\n");

    return;
}

void informeJugador(struct sListaJugadas ljugadas)
{
    int i=0,j=0;
    int opcion;
    struct sListaJugadas miLista; //registro de tipo sListaJugadas
    char archivo[25];
    char nick[TAM_NICK];
    miLista.num=0; //Inicializamos el contenido a 0
    miLista.jugadas=0;
    printf("Introduce tu nick: ");
    scanf("%s", nick);
    while(strlen(nick)>8) //Si el nick mayor que 8...
    {
        printf("El nick introducido tiene mas de 8 caracteres.\nVuelve a introducirlo: ");
        scanf("%s", nick);
    }
    sprintf(archivo,"info_%s.dat",nick); //Al vector archivo le asignamos el nombre del archivo con su correspondiente nick
    for(i=0; i<ljugadas.num; i++)
    {
        if(strcmp(ljugadas.jugadas[i].nick,nick)==0) //si hay coindicencia entre el nick introducido y el recibido
        {
            //vector dinamico usando realloc()
            miLista.jugadas=(struct sJugada*)realloc(miLista.jugadas, (miLista.num+1)*sizeof(struct sJugada));
            miLista.jugadas[j]=ljugadas.jugadas[i]; //pasamos a la nueva lista el contenido de esta jugada
            j++; //incrementamos en 1 j y milista.num
            miLista.num++;

        }
    }
    if(miLista.num==0) //Se produce cuando no hay ningun nick encontrado
        printf("No hay jugadorez registrados con ese nick\n");
    else
    {
        //Ahora decidimos como queremos mostrar las jugadas
        printf("Introduzca la opcion deseada:\n1.Jugadas sin ordenar\n2.Jugadas ordenadas por tiempo\n");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1: //No hay ordenacion
            break;
        case 2:
            ordenarJugadas(&miLista); //Ordenamos las jugadas en funcion del tiempo
            break;
        default:
            printf("Opcion no valida");
            exit(1);
        }
        printf("Opciones de visualizacion del informe:\n1.Salida por pantalla\n2.Salida a archivo de texto\n3.Salida por pantalla y a archivo de texto\n");
        scanf("%d",&opcion);

        switch (opcion) //Y ahora dependiendo como queramos mostrarlo llamamos a una funcion y/u otra
        {
        case 1:
            printListaJugadas(miLista);
            break;
        case 2:
            writeListaJugadas(archivo,miLista);
            break;
        case 3:
            printListaJugadas(miLista);
            writeListaJugadas(archivo,miLista);
            break;
        default:
            printf("Opcion no valida");
            exit(1);
        }
    }
    free(miLista.jugadas); //Liberamos el espacio de memoria creado por el vector dinamico

    return;
}
