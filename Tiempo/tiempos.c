/*--------------------------------------------------------------------------------------------\
| Archivo: tiempos.c                                                                          |
| Funciones usadas: getHora() y getFecha()                                                    |
\----------------------------------------------------------- --------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <time.h>
#include <string.h>

//escribimos todos los .h necesarios
#include "tiempos.h"

void getHora (struct sHora *ahora) //Registro tipo puntero
{
    //Obtenemos la hora actual del sistema
    time_t tiempo=time(NULL);
    struct tm *local=localtime(&tiempo);

    //Pasamos los parametros que nos interesan(hora--minutos-segundoos)
    ahora->seg=local->tm_sec;
    ahora->minu=local->tm_min;
    ahora->hora=local->tm_hour;

    //Cogemos los parametros hora, minu y seg y se lo asignamos a un vector
    sprintf(ahora->formato_hora, "%02d:%02d:%02d", ahora->hora, ahora->minu, ahora->seg);

    return;
}
void getFecha (struct sFecha *hoy)
{
    //Obtenemos la fecha actual del sistema
    time_t tiempo=time(NULL);
    struct tm *local=localtime(&tiempo);

    //Pasamos los parametros que nos interesan(dia-mes-año)
    hoy->dia=local->tm_mday;
    hoy->mes=local->tm_mon+1; //le sumamos 1 ya que el rango empieza en 0(enero)
    hoy->anio=local->tm_year+1900; //Le sumamos 1900 porque empieza a contar desde 1900

    //Cogemos los parametros dia, mes, anio y se lo asignamos a un vector
    sprintf(hoy->formato_fecha, "%02d/%02d/%04d",hoy->dia,hoy->mes,hoy->anio);

    return;
}
