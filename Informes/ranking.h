#if !defined(RANKING_H)
#define RANKING_H 1
#include "../Juego/Jugadas.h"

//Contiene las rutas de los archivos .bin
#define MP_NIVEL1 "DATOS/MP_nivel1.bin"
#define MP_NIVEL2 "DATOS/MP_nivel2.bin"
#define MP_NIVEL3 "DATOS/MP_nivel3.bin"
struct sRanking
{
    char nick[9];
    unsigned int intentos;
    time_t tiempo;
    char formato[6];
};
void gestionRanking();
int menuRanking();
void actualizaRanking(struct sJugada jugada);
void genRankingNiveles();
void muestraRankingNivel(unsigned);
#endif
