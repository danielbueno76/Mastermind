/*Declaracion de las funciones leeconfig() salvaConfig(), menuConfig(), etc*/
#if !defined(CONFIG_H)
#define CONFIG_H 1

//Contiene las rutas de los archivos .bin
#define ARCH_CONFIG "DATOS/config.bin"
#define ARCH_DEFAULT "DATOS/defaultconfig.bin"
struct sConfig
{
    unsigned cronos:1;
    unsigned duelo:1;
    unsigned novato:1;
    unsigned nivel:2;
    unsigned disponibles:5;
    unsigned combinaciones:4;
    unsigned intentos:7;
};
union uConfig
{
   struct sConfig param;
   int int_param;
};
void leeConfig(char ArchConf[],union uConfig *param);
void gestionConfig();
int menuConfig();
void gestionNivel(struct sConfig *param);
int menuNivel();
void muestraConfig(struct sConfig param);
void salvaConfig(char ArchConf[],union uConfig param);
void defaultConfig(char ArchDef[],char ArchConf[],union uConfig* uparam);

#endif
