
/*---------------------------------------------------------------------------------------------------\
| Archivo: partida.c                                                                                 |
| Funciones usadas: jugarPartida() generaClave() getCombiJugador() compruebaCombiJugador()           |
\---------------------------------------------------------------------------------------------------*/

#include <stdio.h> //necesario para las funciones de entrada/salida
#include <stdlib.h> //necesario para el rand,srand system...
#include <locale.h> //permite escribir caracteres del español
#include <time.h> //necesario para el srand() y la función clock()
#include <string.h> //necesario para funciones como el strlen()
#include <ctype.h> //necesario para que si se escribe una letra en minusculas la pase a mayusculas (toupper)

//escribimos todos los .h necesarios
#include "../Config/config.h"
#include "../Juego/partida.h"
#include "../Juego/jugadas.h"
#include "../Informes/ranking.h"

void jugarPartida()
{

    struct sJugada jugada; //Declaración del regiistro de la estructura SJugada
    union uConfig uparam;

    //VARIABLES
    char clave[16]= {0}; //Vectores inicializados a 0
    char combi[16]= {0};
    char arch_jug[]=ARCH_JUGADAS; //definimos la ruta de cada archivo
    char arch_conf[]=ARCH_CONFIG;

    int correcto=0; //Variable que indca si hemos o no hemos acertado la combinacion

    clock_t start,end; //Necesario para el cronometro
    jugada.intent=0;
    uparam.int_param=0;

    //Introducimos el nick
    printf("Introduzca su nick: ");
    scanf("%s",jugada.nick);

    while(strlen(jugada.nick)>8) //Si el tamaño del nick es mayor de 8 debemos ntroducir otro
    {
        printf("Debes introducir un nick con un tamaño menor de 8 caracteres\n");
        system("pause");
        system("cls"); // Borramos la pantalla
        printf("Introduzca su nick: "); // Volvemos a introducir el nick
        fflush(stdin);
        scanf("%s",jugada.nick);

    }
    //llamada a leeConfig. Le pasamos direcciones puesto que se trata de un registro tipo puntero
    leeConfig(arch_conf,&uparam);

    srand((unsigned)time(NULL)); //Necesario para generar no siempre la misma secuencia aleatoria

    muestraConfig(uparam.param); //Llamada a muestraConfig
    fflush(stdin);
    printf("La clave debe introducirla sin espacios. (ABCD-->bien),(A B C D-->mal)\n\n");
    printf("Rango de letras %c-%c\n",65,64+uparam.param.disponibles); //Mostramos el rango de letras que hay

    generaClave(clave,uparam.param); //llamamos a la funcion para generar la comb secreta.
    system("pause"); //Nos pide que pulsemos una tecla para seguir
    system("cls"); //Limpiamos la pantalla
    if(uparam.param.cronos==1)
    {
        start=time(NULL);//Empieza el cronometro a funcionar
    }
    while(jugada.intent<uparam.param.intentos && correcto==0) //mientras los intent. usados no supere al de intent maximos y no hallmos acertado...
    {
        getCombiJugador(combi, uparam.param.disponibles, uparam.param.combinaciones); //LLamada a la función para intentar advinar la clave
        jugada.intent++; //aumentamos en uno los intentos usados

        //Si el valor devuelto es 1 significa que hemos acertado y si devuleve 0 es que hemos fallado
        correcto=compruebaCombiJugador(clave,combi,uparam.param.combinaciones);
        if(correcto==1) //Hemos acertado
        {
            //Mensaje para indicar que hemos acertado
            printf("\nAcertaste!!!! Usaste %u intentos\nBien Hecho!!!!!!\n",jugada.intent);
            if(uparam.param.cronos==1)
            {
                end = time (NULL);//El cronometro se detiene y se muestra el tiempo transcurrido
                printf("\nEl tiempo empleado en adivinar la clave ha sido %d segundos\n\n", (int)difftime(end, start));
                jugada.tiempo=(int)difftime(end,start); //Asignamos a tiempo el valor entero del tiempo que hemos tardado
            }

        }
        else if(correcto==0) //hemos fallado
            printf("\nTe quedan %u intentos", uparam.param.intentos -jugada.intent); //nos muestra los intentos que ns quedan
    }
    if(jugada.intent>=uparam.param.intentos && correcto==0) //Hemos agotado los intentos marcados
    {
        printf("\nLo siento has agotado el numero de intentos\n");
        printf("La clave correcta era %s\n\n", clave); //Mostramos la clave correcta
        if(uparam.param.cronos==1)
        {
            end = time(NULL); //paramos el crono y mostramos en pantalla el tiempo transcurrido
            printf("Has tardado %.0f segundos\n\n", difftime(end, start));
            jugada.tiempo=(int)difftime(end,start); //Asignamos a tiempo el valor entero del tiempo que hemos tardado
        }
        jugada.intent=0; //Ponemos intent a 0 para que se grabe(si cumple las condicones) en el archivo
    }
    getHora(&jugada.hora); //llamamos a las funciones getHora y getFecha para obtener hora y fecha en el momento que aciertes
    getFecha(&jugada.fecha);

    //Pasamos al registro jugada los parámetros de la clave, novato y cronos
    strcpy(jugada.clave,clave);
    jugada.novato=uparam.param.novato;
    jugada.nivel=uparam.param.nivel;
    if(correcto==1)
    {
        //en el caso de que hayamos acertado, mostramos la fecha y la hora actual
        printf("Fecha de hoy: %s\n",jugada.fecha.formato_fecha);
        printf("Hora actual: %s\n",jugada.hora.formato_hora);
    }

    if(uparam.param.duelo==0 && uparam.param.cronos==1 && uparam.param.nivel!=0) //Si se cumplen estas tres condiciones...
    {
        agregaJugada(arch_jug,jugada); //...Llamamos a agregaJugada()
    }

    //llamamos a actualizaRanking() en el caso de que hallamos  acertado la partida y cronos sea igual a 1
    if(correcto==1 && uparam.param.cronos==1)
        actualizaRanking(jugada);

    return;
}

void generaClave(char clave[],struct sConfig param)
{
    int k=0,j=0; //Variables para saber si,en novato activado, 2 letras se repiten.
    int fallo; //variable para saber cuando se cumplen las condciones a la hora de generar la clave
    if(param.duelo==0) //si el duelo esta desactivado
    {
        if(param.novato==0) //si el novato esta desactivado
        {
            for(k=0; k<param.combinaciones; k++) //DEsde 0 hasta combinaciones -1
            {
                fflush(stdin);
                clave[k]= 65 + rand() %(param.disponibles); //65 es la A. Generacion de la secuencia aleatoria

            }
        }
        else if(param.novato==1) //Si novato esta activado
        {
            do
            {
                fallo=0; //inicializamos a 0 el fallo
                for(k=0; k<param.combinaciones; k++) //Desde 0 hasta combinaciones -1
                {
                    clave[k]= 65 + rand() %(param.disponibles); //65 es la A. Genracion de la secuencia aleatoria¡
                }
                //Bucle para comprobar si no s repiten las letras
                for(k=0; k<param.combinaciones; k++) //Desde 0 hasta combinaciones -1
                {
                    for(j=k+1; j<param.combinaciones; j++)
                    {
                        if(clave[j]==clave[k]) //si coinciden ... clave erronea
                        {
                            fallo=1; //ponemos fallo a 1 para que vuelva a entrar en el bucle
                        }
                    }//fin del for
                } //fin del for

            }
            while(fallo==1);  //fin del do while. Si salimos significa que las letras no se repten
        } //fin del else if
    }
    else if(param.duelo==1) //si por el contrario duelo es 1
    {
        if(param.novato==0)
        {
            do
            {
                fallo=0;
                printf("\nIntroduzca la combinacion de %d letras que otro usuario debe adivinar: ",param.combinaciones);
                scanf("%s",clave);
                if(strlen(clave)!=param.combinaciones) //si el tamaño de la clave no coincide con combinaciones
                    fallo=1; //hay fallo
                else
                {
                    for(k=0; k<param.combinaciones; k++)
                    {
                        clave[k]=toupper(clave[k]); //pasamos a letras mayusculas
                        if(clave[k]<65 || clave[k]>64+param.disponibles)  //si las letras estan fuera del rango...
                        {
                            fallo =1;
                        }
                    }
                }
                if(fallo==1) //si la clave no cumple las espeficicafiones
                {
                    //Nos muestra un mensaje diciendonos que la clave no cumple los requisitos.
                    printf("Clave errónea.Vuelva a introducirla\n");
                    system("pause");
                    system("cls");
                }
            }
            while(fallo==1); //Si fallo es 1 volvemos a entrar en el bucle
        }
        else if(param.novato==1)
        {
            do
            {
                fallo=0;
                printf("\nIntroduzca la combinacion de %d letras que otro usuario debe adivinar: ",param.combinaciones);
                scanf("%s",clave);
                if(strlen(clave)!=param.combinaciones) //Si el tamaño de clave no coincide con combianciones...
                    fallo=1;
                else
                {
                    for(k=0; k<param.combinaciones; k++)
                    {
                        clave[k]=toupper(clave[k]); //Pasamos a mayusculas
                        if(clave[k]<65 || clave[k]>64+param.disponibles) //Si esta fuera del rango
                        {
                            fallo =1;
                        }
                        for(j=k+1; j<param.combinaciones; j++) //Miramos a ver si las letras se repiten
                        {
                            if(clave[j]==clave[k]) //Si coinciden...
                            {
                                fallo=1;
                            }
                        }
                    }
                }
                if(fallo==1) //Si el fallo esta a 1
                {
                    printf("Clave errónea.Vuelva a introducirla\n");
                    system("pause");
                    system("cls");
                }
            }
            while(fallo==1); //Mietras no se cuplan los requisitos seguimos en el bucle
        }
    }

    return;
}

//Función en la que introducimos una combinacion.
void getCombiJugador(char combi[], unsigned letrasD, unsigned letrasC)
{

    //Variables
    int k;
    int fallo;
    do
    {
        fflush(stdin);
        printf("\nIntroduzca la combinacion secreta: ");
        gets(combi); //Introducimos la combinacion

        fallo=0;
        if(strlen(combi)!=letrasC) //si no coinciden el tamaño de combi con el de letrasC...
            fallo=1; //Fallo
        for(k=0; k<letrasC; k++)
        {
            combi[k]=toupper(combi[k]); //Transformamos a mayusculas
            if(combi[k]<65 || combi[k]>64+letrasD) //Si estan fuera del rango...
            {
                fallo =1;
            }
        }
        if(fallo==1) //si se ha producido una irregularidad...
            printf("La combinación no cumple los parámetros. Vuelva a introducirla\n");

    }
    while(fallo==1);

    return;
}

//Función en la que comprobamos si la combinacion coincide con la clave
int compruebaCombiJugador(char clave[], char combi[],unsigned numC)
{
    //Variables
    int k;
    int j;
    int cont=0;  //Variable que guarda el numero de letras correctas en la misma posicion
    int contD=0; //Variable que guarda el numero de letras correctas pero en distinta posicion

    /*Para que no volvamos a comparar una letra que ya ha encontrado una coincidencia, vamos a crear dos vectores auxiliares,
    de tal manera que una vez que se encuentre una coincidencia, se bloquee el vector auxiliar y no se vuelve a comparar la
    letra con otras.*/
    char aux[20]= {0}; //inicializamos los vectores a 0 para que cuando llegue al \0 no nos imprima caracteres de más.
    char aux2[20]= {0}; //aux: vector auxiliar para bloquear as letras de clave. Aux2 vector auxiliar para bloquear las de combi

    for(k=0; k<numC; k++)
    {
        if(clave[k]==combi[k]) //Si la letra k de clave coincide con la letra k de combi...
        {
            //bloqueamos tanto el vector aux de clave como el aux2 de combi
            aux[k]=1;
            aux2[k]=1;
            cont++; //Aumentamos en 1 el numero de coincidencias en la misma posicion
        }

    }
    //Vamos a ver si coinciden las letras pero en distinta posicion.
    for(k=0; k<numC; k++)
    {
        if(aux[k]==0) //Si no está bloqueado el vctor aux
        {
            for(j=0; j<numC; j++)
            {
                //Si no está bloqueado ninguno de los vecotres auxiliares y la letra k de clave coincide con la letra j de combi
                if(clave[k]==combi[j]&& aux[k]==0 && aux2[j]==0)
                {
                    contD++; //Aumenta el numero de letras de distinta posición
                    aux[k]=1; //bloqueamos el vector de clave
                    aux2[j]=1; //Bloqueamos el vector de combi
                }
            }
        }
    }
    for(k=0; k<cont; k++)
    {
        printf("@ "); //La letra coincide en posicion
    }
    for(k=0; k<contD; k++)
    {
        printf("* "); //La letra coincide pero en distinta posición
    }
    if(cont==numC) //Dependiendo de si hemos acertado o no la combinación,devolvemos 1(acierto) o 0(fallamos)
        return 1; //Acierto
    else
        return 0; //Fallo
}
