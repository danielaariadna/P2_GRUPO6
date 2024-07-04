#ifndef COSTOS_H_INCLUDED
#define COSTOS_H_INCLUDED
typedef struct{
    float maxAltas;      //Costo maximo
    float acAltas;      //Costo acumulado
    float MedioAltas;  //Costo medio
    int cantAltas;    //Cantidad de altas

    float maxBajas;
    float acBajas;
    float MedioBajas;
    int cantBajas;

    float maxEvocarE; //E= exitoso
    float acEvocarE;
    float MedioEvocarE;
    int cantEvocarE;

    float maxEvocarF; //F = Fracaso
    float acEvocarF;
    float MedioEvocarF;
    int cantEvocarF;
}costos;

typedef struct {
    costos libt;
    costos lsobb;
    costos abb;
}TablaCostos;


void resetTabla(TablaCostos *tabla){

    //LIBT
    tabla->libt.maxAltas = 0.0;
    tabla->libt.acAltas = 0.0;
    tabla->libt.MedioAltas = 0.0;
    tabla->libt.cantAltas = 0;

    tabla->libt.maxBajas = 0.0;
    tabla->libt.acBajas = 0.0;
    tabla->libt.MedioBajas = 0.0;
    tabla->libt.cantBajas = 0;

    tabla->libt.maxEvocarE = 0.0;
    tabla->libt.acEvocarE = 0.0;
    tabla->libt.MedioEvocarE = 0.0;
    tabla->libt.cantEvocarE = 0;

    tabla->libt.maxEvocarF = 0.0;
    tabla->libt.acEvocarF = 0.0;
    tabla->libt.MedioEvocarF = 0.0;
    tabla->libt.cantEvocarF = 0;

    //LSOBB
    tabla->lsobb.maxAltas = 0.0;
    tabla->lsobb.acAltas = 0.0;
    tabla->lsobb.MedioAltas = 0.0;
    tabla->lsobb.cantAltas = 0;

    tabla->lsobb.maxBajas = 0.0;
    tabla->lsobb.acBajas = 0.0;
    tabla->lsobb.MedioBajas = 0.0;
    tabla->lsobb.cantBajas = 0;

    tabla->lsobb.maxEvocarE = 0.0;
    tabla->lsobb.acEvocarE = 0.0;
    tabla->lsobb.MedioEvocarE = 0.0;
    tabla->lsobb.cantEvocarE = 0;

    tabla->lsobb.maxEvocarF = 0.0;
    tabla->lsobb.acEvocarF = 0.0;
    tabla->lsobb.MedioEvocarF = 0.0;
    tabla->lsobb.cantEvocarF = 0;

    //ABB
    tabla->abb.maxAltas = 0.0;
    tabla->abb.acAltas = 0.0;
    tabla->abb.MedioAltas = 0.0;
    tabla->abb.cantAltas = 0;

    tabla->abb.maxBajas = 0.0;
    tabla->abb.acBajas = 0.0;
    tabla->abb.MedioBajas = 0.0;
    tabla->abb.cantBajas = 0;

    tabla->abb.maxEvocarE = 0.0;
    tabla->abb.acEvocarE = 0.0;
    tabla->abb.MedioEvocarE = 0.0;
    tabla->abb.cantEvocarE = 0;

    tabla->abb.maxEvocarF = 0.0;
    tabla->abb.acEvocarF = 0.0;
    tabla->abb.MedioEvocarF = 0.0;
    tabla->abb.cantEvocarF = 0;
}
void printTabla(TablaCostos tabla) {
     printf("\n\n\t\t\t  _________________________________________________________________________\n"
                "\t\t\t |                           |              |              |              |\n"
                "\t\t\t |                           |     LIBT     |    LSOBB     |     ABB      |\n"
                "\t\t\t |___________________________|______________|______________|______________|\n"
                "\t\t\t | Alta                      |              |              |              |\n"
                "\t\t\t |    Cantidad               |     %d      |     %d      |     %d      |\n"
                "\t\t\t |    Costo Acumulado        |     %.2f   |     %.2f  |     %.2f    |\n"
                "\t\t\t |    Costo Maximo           |     %.2f    |     %.2f    |     %.2f     |\n"
                "\t\t\t |    Costo Promedio         |     %.2f     |     %.2f    |     %.2f     |\n"
                "\t\t\t |___________________________|______________|______________|______________|\n"
                "\t\t\t | Baja                      |              |              |              |\n"
                "\t\t\t |    Cantidad               |     %d       |     %d       |     %d       |\n"
                "\t\t\t |    Costo Acumulado        |     %.2f   |     %.2f  |     %.2f    |\n"
                "\t\t\t |    Costo Maximo           |     %.2f    |     %.2f    |     %.2f     |\n"
                "\t\t\t |    Costo Promedio         |     %.2f     |     %.2f    |     %.2f     |\n"
                "\t\t\t |___________________________|______________|______________|______________|\n"
                "\t\t\t | Evocar exitoso            |              |              |              |\n"
                "\t\t\t |    Cantidad               |     %d      |     %d      |     %d      |\n"
                "\t\t\t |    Costo Acumulado        |     %.2f  |     %.2f  |     %.2f  |\n"
                "\t\t\t |    Costo Maximo           |     %.2f    |     %.2f     |     %.2f    |\n"
                "\t\t\t |    Costo Promedio         |     %.2f     |     %.2f     |     %.2f     |\n"
                "\t\t\t |___________________________|______________|______________|______________|\n"
                "\t\t\t | Evocar fracaso            |              |              |              |\n"
                "\t\t\t |    Cantidad               |     %d      |     %d      |     %d      |\n"
                "\t\t\t |    Costo Acumulado        |     %.2f  |     %.2f   |     %.2f   |\n"
                "\t\t\t |    Costo Maximo           |     %.2f    |     %.2f     |     %.2f    |\n"
                "\t\t\t |    Costo Promedio         |     %.2f    |     %.2f     |     %.2f     |\n"
                "\t\t\t |___________________________|______________|______________|______________|\n\n",
        tabla.libt.cantAltas, tabla.lsobb.cantAltas, tabla.abb.cantAltas,
        tabla.libt.acAltas, tabla.lsobb.acAltas, tabla.abb.acAltas,
        tabla.libt.maxAltas, tabla.lsobb.maxAltas, tabla.abb.maxAltas,
        tabla.libt.MedioAltas, tabla.lsobb.MedioAltas, tabla.abb.MedioAltas,
        tabla.libt.cantBajas, tabla.lsobb.cantBajas, tabla.abb.cantBajas,
        tabla.libt.acBajas, tabla.lsobb.acBajas, tabla.abb.acBajas,
        tabla.libt.maxBajas, tabla.lsobb.maxBajas, tabla.abb.maxBajas,
        tabla.libt.MedioBajas, tabla.lsobb.MedioBajas, tabla.abb.MedioBajas,
        tabla.libt.cantEvocarE, tabla.lsobb.cantEvocarE, tabla.abb.cantEvocarE,
        tabla.libt.acEvocarE, tabla.lsobb.acEvocarE, tabla.abb.acEvocarE,
        tabla.libt.maxEvocarE, tabla.lsobb.maxEvocarE, tabla.abb.maxEvocarE,
        tabla.libt.MedioEvocarE, tabla.lsobb.MedioEvocarE, tabla.abb.MedioEvocarE,
        tabla.libt.cantEvocarF, tabla.lsobb.cantEvocarF, tabla.abb.cantEvocarF,
        tabla.libt.acEvocarF, tabla.lsobb.acEvocarF, tabla.abb.acEvocarF,
        tabla.libt.maxEvocarF, tabla.lsobb.maxEvocarF, tabla.abb.maxEvocarF,
        tabla.libt.MedioEvocarF, tabla.lsobb.MedioEvocarF, tabla.abb.MedioEvocarF);
}



#endif // COSTOS_H_INCLUDED
