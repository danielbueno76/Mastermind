#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español
#include <string.h> //permite que podamos escribir funciones como strlen()

#include "../Informes/franjas.h"

void informeFranjas(struct sListaJugadas ljugadas)
{
    struct sFranja *jugFranja;
    int k,j=0,f=0,encontrado=0;
    int franjas=0,visual=0;
    int *limite;
    limite=0;

    jugFranja=NULL;

    printf("Introduzca las franjas horarias en las que quiere dividir el dia: ");
    scanf("%d",&franjas);

    while(franjas>12 || 24%franjas!=0)
    {
        printf("Error al introducir la franja horaria\nVuelve a introducirla: ");
        scanf("%d",&franjas);
    }

    limite=(int*)realloc(limite,(franjas+1)*sizeof(int));
    f=24/franjas;
    for(k=0; k<=franjas; k++)
    {
        limite[k]=0+f*k;
    }

    printf("¿Cual es la franja que quiere visualizar?: ");
    scanf("%d",&visual);

    while(visual>franjas && visual==0)
    {
        printf("Error al introducir la franja que quieres visualizar\nVuelve a introducirla: ");
        scanf("%d",&visual);
    }

    for(k=0; k<ljugadas.num; k++)
    {
        if(limite[visual-1]<=ljugadas.jugadas[k].hora.hora && limite[visual]>ljugadas.jugadas[k].hora.hora)
        {
            encontrado=1;
            jugFranja=(struct sFranja*)realloc(jugFranja,(j+1)*sizeof(struct sFranja));
            strcpy(jugFranja[j].nick,ljugadas.jugadas[k].nick);
            jugFranja[j].nivel=ljugadas.jugadas[k].nivel;
            jugFranja[j].tiempo=ljugadas.jugadas[k].tiempo;
            strcpy(jugFranja[j].hora.formato_hora,ljugadas.jugadas[k].hora.formato_hora);
            j++;

        }
    }
    if(encontrado==1)
    muestraFranja(jugFranja,j,visual,limite);
    else
    printf("No se ha encontrado ninguna hora de la franja indicada\n");

    return;
}

void muestraFranja(struct sFranja jugFranja1[],int num,int franja,int lim[])
{
    FILE*ptr;
    FILE*ptr1;
    char arch[20]= {0};
    char arch1[20]= {0};
    int k;
    float medio=0;
    sprintf(arch,"FRANJAS/Franja%d.txt",franja);
    sprintf(arch1,"FRANJAS/Franja%d.bin",franja);
    ptr=fopen(arch,"wt");
    ptr1=fopen(arch1,"wb");

    if(ptr==NULL)
    {
        printf("Error en la apertura del archivo 1");
        exit(1);
    }
    if(ptr1==NULL)
    {
        printf("Error en la apertura del archivo 2");
        exit(1);
    }
    printf("Mejores Puntuaciones\n\tDe %d:00:00 a %d:59:59",lim[franja-1],lim[franja]-1);
    printf("\n----------------------------------------------\n");
    printf("Nivel    Nick   Tiempo    Hora");
    printf("\n----------------------------------------------\n");
    fprintf(ptr,"Mejores Puntuaciones\n\tDe %d:00:00 a %d:59:59",lim[franja-1],lim[franja]-1);
    fprintf(ptr,"\n----------------------------------------------\n");
    fprintf(ptr,"Nivel    Nick   Tiempo    Hora");
    fprintf(ptr,"\n----------------------------------------------\n");
    for(k=0; k<num; k++)
    {
        printf("%3d %10s %5d %12s\n",(int)jugFranja1[k].nivel,jugFranja1[k].nick,(int)jugFranja1[k].tiempo,jugFranja1[k].hora.formato_hora);
        fprintf(ptr,"%3d %10s %5d %12s\n",(int)jugFranja1[k].nivel,jugFranja1[k].nick,(int)jugFranja1[k].tiempo,jugFranja1[k].hora.formato_hora);
        fwrite(&jugFranja1[k],sizeof(struct sFranja),1,ptr1);
        medio+=jugFranja1[k].tiempo;
    }
    medio=medio/num;
    printf("----------------------------------------------");
    fprintf(ptr,"----------------------------------------------");
    printf("\nTiempo medio: %.2f",medio);
    fprintf(ptr,"\nTiempo medio: %.2f",medio);
    printf("\n----------------------------------------------\n");
    fprintf(ptr,"\n----------------------------------------------\n");
    fwrite(&medio,sizeof(float),1,ptr1);

    if(fclose(ptr)!=0)
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }
    if(fclose(ptr1)!=0)
    {
        printf("Error en el cierre del archivo");
        exit(1);
    }

}

