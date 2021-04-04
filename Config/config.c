/*--------------------------------------------------------------------------------------------\
| Archivo: config.c                                                                           |
| Funciones usadas: leeCofig(),gestionConfig(),menuConfig(),salvaConfig(),defaultConfig(),    |
|                   gestionNivel(),menuNivel() y muestraConfg()                               |
\----------------------------------------------------------- --------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h>
#include <locale.h> //permite escribir caracteres del español

//escribimos todos los .h necesarios
#include "../Config/config.h"

//Función que recibe la dirección del registro de uConfig y la ruta del archivo config.bin
void leeConfig(char ArchConf[],union uConfig *param)
{
    FILE* ptr; //archivo para leer los datos
    ptr = fopen(ArchConf,"rb"); //Abrimos el archivo para lectura
    if(ptr==NULL)//si algo va mal...
    {
        printf("Error en la apertura del archivo config.bin\n");
        exit(1);
    }
    //Leemos el archvo en binario y lo almacenamos e el regstro param
    fread(param,sizeof(union uConfig),1,ptr);

    //Cerramos el archivo de lectura y comprobamos que se ha cerrado bien
    if(fclose(ptr)!=0)
    {
        printf("Error con el cierre del archivo config.bin\n");
        exit(1); //salimos directamente del programa
    }
    return; //no deculevve nada puesto que es una funcion de tipo vacio.
}
void gestionConfig()
{
    //variable inicializada a un valor distinto de 0 para que entre en el bucle
    int opcion=1;

    union uConfig uparam; //registro de tipo union
    //Le asignamos la ruta al vector correspondiente
    char arch_conf[]=ARCH_CONFIG;
    char arch_def[]=ARCH_DEFAULT;

    uparam.int_param=0; //inicializamos a 0 el valor entero de la union

    leeConfig(arch_conf,&uparam);  //llamada a la funcion leeconfig
    //en el que pasamos la ruta del archivo de config.bin y la direccion del registro de uConfig

    do
    {
        //llamamos a la funion leeconfig y realizamos la conversión

        opcion=menuConfig();//opcion toma el valor que recibe de menuConig()
        switch(opcion) // y ese valor entra en un switch
        {
        case 1: //s la opcion es 1...
            system("cls");
            muestraConfig(uparam.param); //llamamos a muestraConfig()
            system("pause"); //pide pulsar una tecla para seguir
            system("cls"); //limpia la pantalla para una mejor faclidad de uso
            break;
        case 2:
            system("cls");
            //llamada a la funcion pasando la dirección del registro de la union
            gestionNivel(&uparam.param);
            system("pause");
            system("cls");
            break;
        case 3: //Conmutamos el valor que teniamos
            system("cls");
            uparam.param.duelo+=1; //Cambiamos el modo
            if(uparam.param.duelo==1)
            {
                printf("El duelo estaba desactivado y ha sido activado (1)\n");
            }
            else
            {
                printf("El duelo estaba activado y ha sido desactivado (0)\n");
            }
            system("pause");
            system("cls");
            break;
        case 4://Conmutamos el valor que teniamos
            system("cls");
            uparam.param.cronos+=1; //Cambiamos el modo
            if(uparam.param.cronos==1)
            {
                printf("El cronómetro estaba desactivado y ha sido activado (1)\n");
            }
            else
            {
                printf("El cronómetro estaba activado y ha sido desactivado (0)\n");
            }
            system("pause");
            system("cls");
            break;
        case 5://Conmutamos el valor que teniamos
            system("cls");
            uparam.param.novato+=1;
            if(uparam.param.novato==1)
            {
                printf("El modo novato estaba desactivado y ha sido activado (1)\n");
            }
            else
            {
                printf("El modo duelo estaba activado y ha sido desactivado (0)\n");
            }
            system("pause");
            system("cls");//Borramos el contenido de la pantalla
            break;
        case 6:
            system("cls");
            salvaConfig(arch_conf,uparam); //llamada a la funcion donde pasamos la ruta del archivo y el registro de uConfig
            system("pause");
            system("cls"); //Se limpia la pantalla
            break;
        case 7:
            system("cls");
            //Llamada a la funcion defaultconfig() para establecer los parámetros predeterminados
            defaultConfig(arch_def,arch_conf,&uparam);
            system("pause");
            system("cls");
            break;
        case 0:
            system("cls"); //en este caso, no llamamos a niguna funcion
            printf("Volviendo al menu anterior...\n\n");
            break;
        default:
            printf("Opción no válida.");
            exit(1); //salimos del programa si introducimos una variable no deseada
        } //fin del switch
    }
    while(opcion!=0);   //fin del while: Acaba cuando introducimos 0

    return;
}

int menuConfig()
{
    int opcion=0; //variable para introducir la opcion deseada.
    // Inicializamos a 0 para evitar problemas

    //Nos pide que decidamos entre una de las opciones
    printf("\nElige una de las opciones siguientes:\n");
    printf("1-Configuración Actual\n");
    printf("2-Nivel de dificultad\n");
    printf("3-Modo Duelo\n");
    printf("4-Modo Cronómetro\n");
    printf("5-Modo Novato\n");
    printf("6-Salvar configuración\n");
    printf("7-Restaurar configuración predeterminada\n");
    printf("0-Menú anterior (Debe salvar la configuración antes)\n");
    printf("-> ");
    scanf("%d",&opcion); //Introducimos la opcion deseada

    return opcion; //devolvemos el valor de opcion
}
void salvaConfig(char ArchConf[],union uConfig param)
{
    FILE* ptr; //archivo para colocar los datos leidos en la funcion leeConfig()
    ptr = fopen(ArchConf,"wb"); //abrimos el archivo Config.bin para escritura
    if(ptr==NULL)
    {
        printf("Problemas con la apertura del archivo config.bin\n");
        exit(1);
    }
    printf("Guardando la nueva configuracion...\n\n");

    //escribimos en el archivo config.bin la nueva configuracion del juego
    fwrite(&param,sizeof(struct sConfig),1,ptr);

    // Cerramos el archivo config.bin y comprobamos que se ha cerrado bien
    if(fclose(ptr)!=0)
    {
        printf("Problemas con el cierre del archivo config.bin\n");
        exit(1);
    }

    return;
}

//esta funcion establece los valores predeterminados
void defaultConfig( char ArchDef[], char ArchConf[],union uConfig *uparam)
{
    leeConfig(ArchDef,uparam); //llamada a la funcion leeConfig pasando el archivo defaultconfig
    printf("Restableciendo los datos predeterminados...\n\n");
    salvaConfig(ArchConf,*uparam); //llamada a la funcion salvaConfig pasando el archivo config

    return;
}

//Función que recibe la dirección de 7 variables tipo puntero.
void gestionNivel(struct sConfig *param)
{
    int aux; //variable auxiliar necesaria para la conversion en
    int opcion;
    opcion=menuNivel(); //el valor de la variable opcion es recibido desde la funcion menuNuvel

    //dependiendo del tipo de nivel, se toma unos valores u otros
    if(opcion==1) //si el nivel es 1 ...
    {
        param->nivel=1;
        param->disponibles=6;
        param->combinaciones=4;
        param->intentos=10;
    }

    else if(opcion==2) //si el nivel es 2 ...
    {
        param->nivel=2;
        param->disponibles=8;
        param->combinaciones=5;
        param->intentos=12;
    }


    else if(opcion==3) //si el nivel es 3 ...
    {
        param->nivel=3;
        param->disponibles=10;
        param->combinaciones=6;
        param->intentos=14;
    }

    else if(opcion==4) //si es 4...
    {
        //nivel personalizado: modificamos todos los parametros de configuracion.
        param->nivel=0;
        printf("Introduce el número de letras disponibles: ");
        scanf("%d",&aux);
        param->disponibles=(unsigned)aux; //realizamos la conversion
        printf("Introduce el número de combinaciones: ");
        scanf("%d",&aux);
        param->combinaciones=(unsigned)aux;
        printf("Intoduce el número de intentos: ");
        scanf("%d",&aux);
        param->intentos=(unsigned)aux;

        do  //Si no introducimos ni 1 ni 0
        {
            //Decidimos el modo de experiencia
            printf("Elija la opción que desee: \n");
            printf("1-Modo Novato\n");
            printf("0-Modo Experto\n");
            printf("-> ");
            scanf("%d",&aux); //introducimos el valor deseado
            param->novato=(unsigned) aux; //realizamos la conversion
            if(param->novato!=0 && param->novato!=1)
                printf("Opcion no válida\n");

        }
        while(param->novato!=0 && param->novato!=1);

        do //Si no introducimos ni 1 ni 0
        {
            //Deciidimos si el modo crono esta activo o no
            printf("Elija la opción que desee: \n");
            printf("1-Modo cronómetro ON\n");
            printf("0-Modo cronómetro OFF\n");
            printf("-> ");
            scanf("%d",&aux); //introducimos el valor deseado
            param->cronos=(unsigned) aux; //realizamos la conversion
            if(param->cronos!=0 && param->cronos!=1)
                printf("Opción no valida\n");

        }
        while(param->cronos!=0 && param->cronos!=1);

        do //Si no introducimos ni 1 ni 0
        {
            //Decidimos si el jugamos contra el ordenadr o contra otra persona
            printf("Elija la opción que desee: \n");
            printf("1-Modo duelo ON\n");
            printf("0-Modo duelo OFF\n");
            printf("-> ");
            scanf("%d",&aux); //introducimos el valor deseado
            param->duelo=(unsigned) aux; //realizamos la conversion
            if(param->duelo!=0 && param->duelo!=1)
                printf("Opcion no válida\n");

        }
        while(param->duelo!=0 && param->duelo!=1);
    }

    else if(opcion==0)
    {
        printf("Volviendo al menu anterior...\n");
        return; // Ponemos un return pues no nos interesa que nos salve la configuracion.
    }
    else//si no es ni 0 ni 1 ni 2 ni 3 ni 4...
    {
        printf("Error, la opción que has marcado no existe");
        exit(1);
    }
    if(opcion!=0) //Cuando nivel es 1,2,3 ó 4...
    {
        muestraConfig(*param);
    }
    return;
}
int menuNivel()
{
    int opcion;
    //elegimos el nivel que prefiramos
    printf("Elija el nivel de dificultad:\n");
    printf("1-Nivel Fácil\n");
    printf("2-Nivel Medio\n");
    printf("3-Nivel Difícil\n");
    printf("4-Nivel Personalizado\n");
    printf("0-Menu anterior\n");
    scanf("%d",&opcion);

    return opcion; //devuelve el valor introducido
}
//Función wue muestra la conffiguración que existev en este preciso momento
void muestraConfig(struct sConfig param)
{
    //mostramos la configuracion actual del juego
    printf("La configuración actual del juego es:\n\n\n");
    printf("Nivel: %20d\n\n", param.nivel);
    printf("Letras disponibles: %7d\n\n", param.disponibles);
    printf("Combinaciones: %12d\n\n", param.combinaciones);
    printf("Intentos: %17u\n\n", param.intentos);
    printf("Novato: %19d\n\n", param.novato);
    printf("Cronometro: %15d\n\n", param.cronos);
    printf("Duelo: %20d\n\n", param.duelo);


    return; //No devuelve nada puesto que es una variable de tipo vacio.
}
