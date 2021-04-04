#if !defined(TIEMPO_H)
#define TIEMPO_H 1
struct sFecha
{
    int dia;
    int mes;
    int anio;
    char formato_fecha[11];
};
struct sHora
{
    int hora;
    int minu;
    int seg;
    char formato_hora[9];
};

void getFecha (struct sFecha *hoy);
void getHora (struct sHora *ahora);
#endif
