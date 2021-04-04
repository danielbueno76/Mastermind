#if !defined(FRANJAS_H)
#define FRANJAS_H 1
#include "../Tiempo/Tiempos.h"
#include "../Juego/Jugadas.h"
struct sFranja
{
    char nick[9];
    unsigned char nivel;
    time_t tiempo;
    struct sHora hora;

};

void informeFranjas(struct sListaJugadas jugadas);
void muestraFranja(struct sFranja franja[],int,int,int[]);
#endif
