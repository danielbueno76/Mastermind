/*---------------------------------------------------------------------------------------------------------------------------\
| Archivo: jugadas.c                                                                                                         |
| Funciones usadas:  leeJugadas(), agregaJugada(),intercambia(),ordenarJugadas(),printListaJugadas(),writeListJugadas()      |
\---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español
#include <string.h> //permite que podamos escribir funciones como strlen()

//escribimos todos los .h ncesarios
#include "../Juego/jugadas.h"

//Funcion que lee las jugadas del archivo. Devuelve el numero de jugadas leidas
void leeJugadas(char nomArch[],struct sListaJugadas *lista)
{
    int tam; //variable que creamos para saber el tamaño del archivo jugadas.bin
    int i=0; //Variable que va aumentando cada vez que leamos una jugada nueva
    FILE*ptr;
    ptr=fopen(nomArch, "rb"); //abrimos el archivo para lectura
    if(ptr==NULL) //si no existe o algo va mal ...
    {
        printf("Error al abrir jugadas.bin\n");
        exit(1);
    }
    fseek(ptr,0,SEEK_END); //Nos posicionamos al final del archivo
    tam=ftell(ptr); //Calculamos el tamaño del archivo
    lista->jugadas=(struct sJugada*)realloc(lista->jugadas,tam); //Creamos un vector dinamico del tamaño del archivo
    fseek(ptr,0,SEEK_SET); //Y ahora nos situamos al principio del archivo para poder leer
    //Bucle que te lee el archivo en binario y lo almacena en un vector de regstros

    while(fread(&lista->jugadas[i],sizeof(struct sJugada),1,ptr)>0) //Mientras leamos algo...
    {
        lista->num++;
        i++;//aumenta el numero de jugadas en 1
    }

    if(fclose(ptr)!=0) //comprobamos el cierre que el archivo es correcto
    {
        printf("Error al cerrar jugadas.bin\n");
        exit(1);
    }

    return;
}
//Esta funcion cuando es llamada agregará la jugada al archivo jugadas.bin
void agregaJugada(char nomArch[],struct sJugada jugada)
{
    FILE*ptr;
    ptr=fopen(nomArch, "ab"); //abrimos el archivo jugadas.bin para añadir.
    if(ptr==NULL) //si algo va mal...
    {
        printf("Error al abrir jugadas.bin\n");
        exit(1);   //salimos del programa inmediatamente.
    }
    //escribimos en el archivo las características de la jugada
    fwrite(&jugada,sizeof(struct sJugada), 1, ptr);

    if(fclose(ptr)!=0) //si se cierra el archivo mal...
    {
        printf("Error al cerrar jugadas.bin\n");
        exit(1);
    }

    return; //No devuelve nada puesto que es una funcion de tipo vacio.
}

void printListaJugadas(struct sListaJugadas lista)
{
    int k=0;
    //Mostramos las jugadas que hemos recibido
    printf("Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");
    for(k=0; k<lista.num; k++) //bucle que va recorriendo desde 0 hasta el numero de jugadas que han sido leidas
    {

        //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
        // y así lo mostramos todo ordenado.

        printf("%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",lista.jugadas[k].nick,lista.jugadas[k].nivel,lista.jugadas[k].intent,
               (int)lista.jugadas[k].tiempo,lista.jugadas[k].clave,lista.jugadas[k].novato,
               lista.jugadas[k].hora.formato_hora,lista.jugadas[k].fecha.formato_fecha);

    }
    printf("\n\n");
    return;
}
void writeListaJugadas(char archivo[], struct sListaJugadas lista)
{
    FILE*ptr;
    int k=0;
    char arch[]= {0};
    sprintf(arch,"DATOS/%s",archivo);
    ptr=fopen(arch,"wt"); //abrimos el archivo para escribir
    if(ptr==NULL) //comprobamos la apertura del archivo
    {
        printf("Error en la apertura del archivo %s\n",archivo);
        exit(1);
    }
    printf("\nSe ha creado el archivo %s en la carpeta DATOS",archivo);
    fprintf(ptr,"Nick   Nivel Intentos  Tiempo  Clave   Novato    Hora        Fecha\n\n");
    for(k=0; k<lista.num; k++) //bucle que va recorriendo desde 0 hasta el numero de jugadas que han sido leidas
    {
        //Hemos puesto %-8s, %-2u, %-4d ... para indicar cual debe ser el campo de esa variable en todos los vetores
        // y así lo mostramos todo ordenado.

        fprintf(ptr,"%-8s %-3d %5u %8d  %7s %5d %12s %13s\n",lista.jugadas[k].nick,lista.jugadas[k].nivel,lista.jugadas[k].intent,
                (int)lista.jugadas[k].tiempo,lista.jugadas[k].clave,lista.jugadas[k].novato,
                lista.jugadas[k].hora.formato_hora,lista.jugadas[k].fecha.formato_fecha);
    }
    printf("\n\n");
    if(fclose(ptr)!=0) //comprobamos el cierre del archivo
    {
        printf("Error con el cierre del archivo %s\n",archivo);
        exit(1); //salimos directamente del programa
    }
    return;
}

//funcion que nos permite ordenadar las jugadas en funcion del tiempo
void ordenarJugadas(struct sListaJugadas *lista)
{
    int i, j, aux;
    for(i=0; i<lista->num; i++)
    {
        aux = i;

        for(j = i+1; j<lista->num; j++)
            if(lista->jugadas[j].tiempo < lista->jugadas[aux].tiempo)
                aux = j;

        intercambia(&lista->jugadas[aux], &lista->jugadas[i]); //llamamos a esta función para intercambiar dos jugadas
    }

    return;
}

// funcion que intercambia de posición dos jugadas.
void intercambia(struct sJugada *a,struct sJugada *b)
{
    struct sJugada aux;
    aux= *a;
    *a = *b;

    *b = aux;

    return;
}
