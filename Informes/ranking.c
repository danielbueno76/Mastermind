/*------------------------------------------------------------------------------------------------------------------\
| Archivo: ranking.c                                                                                                |
| Funciones usadas:menuRanking(),gestionRanking(),genRankingNiveles(), actualizaRanking(),muestraRankingNivel()     |
\------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h> //necesario para el rand,srand system...
#include <locale.h> //permite escribir caracteres del español
#include <time.h> //necesario para el srand() y la función clock()
#include <string.h> //necesario para funciones como el strlen()
//#include <ctype.h> //necesario para que si se escribe una letra en minusculas la pase a mayusculas (toupper)

#include "../Informes/ranking.h"

void gestionRanking()
{
    int opcion;
    opcion=menuRanking(); //llamada a la función menuRanking() que recibe la opcion elegida

    switch(opcion)
    { //si introducimos un 1,2 o 3...
    case 1:
    case 2:
    case 3:
        muestraRankingNivel(opcion); //llamada a la función
        break;
    case 4:
        genRankingNiveles(); //llamada a la función que restablece el ranking
        break;
    case 0:
        break; //Salimos de este menu
    default:
        printf("Opcion no valida");
        exit(1);
    }
    return;
}
int menuRanking()
{
    int opcion;
    printf("-----—Ranking por Niveles--------—\n");
    printf("Selecciona una opcion\n");
    //Opciones posibles
    printf("1. Ranking del nivel Fácil.\n2. Ranking del nivel Intermedio.\n3. Ranking del nivel Difícil.\n4. Restaurar ranking por defecto.\n0. Menú anterior.\n");
    //Introducimos la opcion
    scanf("%d",&opcion);
    system("cls");
    return opcion; //devolvemos la opcion introducida
}

void genRankingNiveles()
{
    FILE*ptr;
    //variables que guardaran los minutos y los segundos de las jugadas para guardarlas en formato
    int minu;
    int seg;
    int i=0;
    struct sRanking ranking[10]; //vector de registros
    ptr=fopen(MP_NIVEL1,"wb"); //abrimos el archivo para escribir en binario
    if(ptr==NULL) //si no existe el archivo...
    {
        printf("Error en la apertura del archivo");
        exit(1);
    }
    printf("Restableciendo el ranking predeterminado...\n");
    for(i=0; i<10; i++)
    {
        strcpy(ranking[i].nick,"MMind_v7"); //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].intentos=0; //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].tiempo=180 +60*i; //180=3 minutos. Va incrementando cada 60 segundos
        minu=(int)ranking[i].tiempo/60; //calculamos los minutos para formato
        seg=(int)ranking[i].tiempo%60; //Calculamos los segundos para formato
        sprintf(ranking[i].formato,"%02d:%02d",minu,seg); //Los minutos y segundos los asignamos a un vector llamado formato.
        fwrite(&ranking[i],sizeof(struct sRanking),1,ptr); //Escribimos en binario en el archivo

    }

    if(fclose(ptr)!=0) //comprobamos el cierre del archivo
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }

    ptr=fopen(MP_NIVEL2,"wb"); //abrimos el archivo para escribir en binario
    if(ptr==NULL)//si no existe el archivo...
    {
        printf("Error en la apertura del archivo");
        exit(1);
    }

    for(i=0; i<10; i++)
    {
        strcpy(ranking[i].nick,"MMind_v7"); //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].intentos=0; //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].tiempo=360 +60*i; //360=6 minutos. Va incrementando cada 60 segundos
        minu=(int)ranking[i].tiempo/60; //calculamos los minutos para formato
        seg=(int)ranking[i].tiempo%60; //Calculamos los segundos para formato
        sprintf(ranking[i].formato,"%02d:%02d",minu,seg); //Los minutos y segundos los asignamos a un vector llamado formato.
        fwrite(&ranking[i],sizeof(struct sRanking),1,ptr); //Escribimos en binario en el archivo

    }

    if(fclose(ptr)!=0) //comprobamos el cierre del archivo
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }

    ptr=fopen(MP_NIVEL3,"wb"); //abrimos el archivo para escribir en binario
    if(ptr==NULL) //si no existe el archivo...
    {
        printf("Error en la apertura del archivo");
        exit(1);
    }

    for(i=0; i<10; i++)
    {
        strcpy(ranking[i].nick,"MMind_v7"); //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].intentos=0; //copiamos en ranking[i] la cadena MMind_v7
        ranking[i].tiempo=540 +60*i; //540=9 minutos. Va incrementando cada 60 segundos
        minu=(int)ranking[i].tiempo/60; //calculamos los minutos para formato
        seg=(int)ranking[i].tiempo%60; //Calculamos los segundos para formato
        sprintf(ranking[i].formato,"%02d:%02d",minu,seg); //Los minutos y segundos los asignamos a un vector llamado formato.
        fwrite(&ranking[i],sizeof(struct sRanking),1,ptr); //Escribimos en binario en el archivo
    }

    if(fclose(ptr)!=0) //comprobamos el cierre del archivo
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }

}
void actualizaRanking(struct sJugada jugada)
{
    int i=0;
    int j=0;
    int minu,seg;
    int encontrado=0; //Variable auxiliar que se activa al entrar en una de los mejores 10 puntuaciones
    FILE *ptr;
    struct sRanking ranking;

    if(jugada.nivel==1)
    {
        ptr=fopen(MP_NIVEL1,"rb+"); //abrimos el archivo en modo binario para leer y escribir
    }
    else if(jugada.nivel==2)
    {
        ptr=fopen(MP_NIVEL2,"rb+"); //abrimos el archivo en modo binario para leer y escribir
    }
    else if(jugada.nivel==3)
    {
        ptr=fopen(MP_NIVEL3,"rb+"); //abrimos el archivo en modo binario para leer y escribir
    }
    else
    {
        printf("Ese nivel no existe\n");
        exit(1);
    }

    if(ptr==NULL) //Comprobamos la apertura
    {
        printf("Error en la apertura del archivo");
        exit(1);
    }

    for(i=0; i<10; i++)
    {
        fseek(ptr,i*sizeof(struct sRanking),SEEK_SET); //Funcion que posiciona el cursor en la linea i
        fread(&ranking,sizeof(struct sRanking),1 ,ptr); //leemos la linea indicada por fseek
        if(jugada.tiempo<ranking.tiempo) //Si el tiempo de la nueva jugada es menor que el tiempo de la jugada que acabamos de leer...
        {
            encontrado=1; //activamos la variable auxiliar
            for(j=8; j>=i; j--) //Bucle que se decrementa hasta i
            {
                fseek(ptr,j*sizeof(struct sRanking),SEEK_SET); //nos situamos en la linea j
                fread(&ranking,sizeof(struct sRanking),1,ptr); //leemos la linea en la que nos acabamos de situar
                fseek(ptr,(j+1)*sizeof(struct sRanking),SEEK_SET); //nos situamos en la linea siguiente
                fwrite(&ranking,sizeof(struct sRanking),1,ptr); //escribimos en la linea nueva

            }
            fseek(ptr,i*sizeof(struct sRanking),SEEK_SET); //nos situamos en la linea i
            //copiamos todos los registros de la jugada nueva en la linea corresponidiente
            strcpy(ranking.nick,jugada.nick);
            ranking.intentos=jugada.intent;
            ranking.tiempo=jugada.tiempo;
            minu=(int)ranking.tiempo/60;
            seg=(int)ranking.tiempo%60;
            sprintf(ranking.formato,"%02d:%02d",minu,seg);
            fwrite(&ranking,sizeof(struct sRanking),1,ptr); //y lo escribimos en esa linea

            break;
        }

    }
    if(fclose(ptr)!=0) //Comprobamos el cierre del archivo
    {
        printf("Error en el cierre del archivo\n");
        exit(1);
    }
    if(encontrado==1) //si la variable auxiliar está activada ...
    {
        system("pause");
        system("cls");
        muestraRankingNivel(jugada.nivel); //llamamos a muestraRanking() para visualizar la lista ya actualizada
    }

    else //... y sino...
        printf("\nNo has entrado en las 10 mejores puntuaciones\n");

    return;
}

void muestraRankingNivel(unsigned nivel)
{
    struct sRanking ranking[10]; //Creamos un vector de registros de tamaño 10, que son el numero de jugadas que mostramos
    int i=0;
    FILE *ptr;
    if(nivel==1) //si el nivel es 1...
    {
        ptr=fopen(MP_NIVEL1,"rb"); //abrimos el archivo en modo lectura

    }
    else if(nivel==2) //si el nivel es 2...
    {
        ptr=fopen(MP_NIVEL2,"rb"); //abrimos el archivo en modo lectura

    }
    else if(nivel==3) //si el nivel es 3...
    {
        ptr=fopen(MP_NIVEL3,"rb"); //abrimos el archivo en modo lectura

    }
    if(ptr==NULL) //si se abre mal...
    {
        printf("Error en la apertura del archivo");
        exit(1);
    }

    //Mostramos las 10 mejores puntuaciones
    printf("\nLe mostramos las mejores puntuaciones del nivel %d:\n\n" ,nivel);
    printf("Ranking    Nick   Intentos Tiempo\n\n");
    while(fread(&ranking[i],sizeof(struct sRanking),1,ptr)>0 && i<10) //Leemos hasta 10 jugadadas
    {
        printf("   %02d    %-10s  %2u %8s\n",i+1,ranking[i].nick,ranking[i].intentos,ranking[i].formato); //Y lo mostramos en pantalla
        i++;
    }

    if(fclose(ptr)!=0) //Comprobamos el cierre del archivo
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }

    return;
}

