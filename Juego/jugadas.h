#if !defined(JUEGO_H)
#define JUEGO_H 1
#define TAM_NICK 9 //8 caracteres + el \0
#define MAX_CLAVE 16
#define ARCH_JUGADAS "DATOS/jugadas.bin" //Contiene las rutas de los archivos .bin
#include "../Tiempo/tiempos.h"
struct sJugada
{
    char nick[TAM_NICK];
    unsigned char nivel;
    unsigned int intent;
    time_t tiempo;
    char clave[MAX_CLAVE];
    char novato;
    struct sHora hora;
    struct sFecha fecha;
};

struct sListaJugadas
{
    int num;
    struct sJugada *jugadas;
};
void leeJugadas(char nomArch[],struct sListaJugadas *lista);
void agregaJugada(char nomArch[],struct sJugada jugada);
void printListaJugadas(struct sListaJugadas lista);
void writeListaJugadas(char archivo[], struct sListaJugadas lista);
void ordenarJugadas(struct sListaJugadas *lista);
void intercambia(struct sJugada *a,struct sJugada *b);
#endif
