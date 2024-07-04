#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#include "shipment.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

//ESTRUCTURA///////////////////////////////////////////////////////
typedef struct{
    Shipment shipments[MAX];
    int ultimo;

}Lsobb;

//INICIALIZA LSOBB///////////////////////////////////////////////////
void initializeLSOBB(Lsobb *lsobb){
    lsobb->ultimo = -1;
}

//LISTA LLENA/VACIA/////////////////////////////////////////////////
int isEmptyLsobb(Lsobb *lsobb) {
    return (lsobb->ultimo == -1);
}

int isFullLsobb(Lsobb *lsobb) {
    return (lsobb->ultimo == MAX - 1);

}


//LOCALIZACION LSOBB///////////////////////////////////////////////// CADA CELDA CONSULTADA TIENE C=1

int localizarLSOBB(Lsobb lsobb, char code[], int* pos, float* celdas_consultadas) {
    if (lsobb.ultimo == -1) { // Control si está vacía
        *pos = 0;
        *celdas_consultadas = 0.0;
        return FAILURE;
    }
    int m, i, costos[lsobb.ultimo+1];
    float costosAux = 0.0;
    float li = -1;
    float ls = lsobb.ultimo+1;


    for (i = 0; i < lsobb.ultimo+2; i++) {
        costos[i] = 0;
    }

    while (li+1 < ls-1) {

        m = ( (li + ls) / 2) +1;
        if (strcmp(lsobb.shipments[m].code, code) > 0) {
            ls = m;
        } else {
            li = m-1;
        }
        if (costos[m] == 0) {
            costos[m] = 1;
            costosAux++;
        }
    }


    if (costos[(int)ls-1] == 0) {
        costosAux++;
    }
    *celdas_consultadas = costosAux;
    if(strcmp(lsobb.shipments[(int) ls-1].code,code)==0){
        ls=ls-1;
        *pos=(int) ls;
        return SUCCESS;
    }else if (strcmp(lsobb.shipments[(int) ls-1].code,code)<0){
            *pos=(int) ls;
            return FAILURE;
        }else{
            ls=ls-1;
           *pos=(int) ls;
           }
        return FAILURE;
    }





//ALTA LSOBB///////////////////////////////////////////////////////// CADA CORRIMIENTO TIENE C=1
int altaLSOBB(Lsobb *lsobb, Shipment s, float* costA){
    int pos = 0, posaux = 0;
    float costoAux=0.0, celdas_consultadas=0.0;
    (*costA)=0.0;
    posaux = lsobb->ultimo;
    if (localizarLSOBB(*lsobb, s.code, &pos,&celdas_consultadas) == SUCCESS) {
        return FAILURE;
    } else {
        if ((lsobb->ultimo < MAX - 1)) { //hay lugar
            while (posaux >= pos) {
                lsobb->shipments[posaux + 1] = lsobb->shipments[posaux]; //hago desplzamiento para guardar el envio
                posaux--;
                costoAux++; //Incremento el costo de cada corrimiento
            }
            (*costA) = costoAux;
            lsobb->shipments[pos] = s; // guardo el nuevo envio
            lsobb->ultimo++;          // actualizo el ultimo
            return SUCCESS;
        } else {
            return FAILURE_EX; // Lista llena
        }
    }
}

//BAJA LSOBB///////////////////////////////////////////////////////// CADA CORRIMIENTO TIENE C=1
int bajaLSOBB(Lsobb *lsobb, Shipment s, float* costB) {
    float celdas_consultadas=0;
    int pos = 0;
     *costB=0.0;
    if (localizarLSOBB(*lsobb, s.code, &pos,&celdas_consultadas) == SUCCESS) {
        if(compareShipments(s, lsobb->shipments[pos]) == SUCCESS){

                while (pos < lsobb->ultimo) {
            lsobb->shipments[pos] = lsobb->shipments[pos + 1]; // Desplaza elementos hacia la izquierda
            pos++;
            (*costB)++;
            }
            lsobb->ultimo--; // Reduce el valor del último elemento
            return SUCCESS;
        }
        return FAILURE_EX; // El X es igual pero el Y no
    }else{
        return FAILURE;
    }
}
//EVOCAR LSOBB/////////////////////////////////////////////////////////

int evocarLSOBB(Lsobb lsobb, char code[], Shipment *shipment, float* costo){
    int status=0, pos=0;
    float costosAux=0.0;
    status = localizarLSOBB(lsobb, code, &pos, &costosAux);
    if (status == FAILURE){
        (*costo) = costosAux;
        return FAILURE;
    } else {
        strcpy(shipment->code, lsobb.shipments[pos].code);


        shipment->receiver.dni = lsobb.shipments[pos].receiver.dni;
        strcpy(shipment->receiver.fullName, lsobb.shipments[pos].receiver.fullName);
        strcpy(shipment->receiverAddress, lsobb.shipments[pos].receiverAddress);

        shipment->sender.dni = lsobb.shipments[pos].sender.dni;
        strcpy(shipment->sender.fullName, lsobb.shipments[pos].sender.fullName);
        shipment->sender.dni = lsobb.shipments[pos].sender.dni;


        strcpy(shipment->sendingDate, lsobb.shipments[pos].sendingDate);
        strcpy(shipment->receptionDate, lsobb.shipments[pos].receptionDate);

        (*costo) = costosAux;
        return SUCCESS;
    }
}

//MOSTRAR ESTRUCTURA///////////////////////////////////////////////////

void printLsobb(Lsobb lsobb){
 int i =0;
    for (i=0; i<=lsobb.ultimo; i++){
        printf("\n//////////////////////////////");
        printf(" POSICION DEL ENVIO: %d //////////////////////////////\n\n",i);

        printShipment(lsobb.shipments[i]);
        printf("\n");

    }
}



#endif // LSOBB_H_INCLUDED
