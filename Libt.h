#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Shipment.h"

//TRISECCION: Limite inferior inclusivo, limite superior exclusivo, segmento mas grande a la izquierda.

//ESTRUCTURA///////////////////////////////////////////////////////

typedef struct{
    Shipment *shipments[MAX];
    int ultimo;
}Libt;

//INICIALIZA LIBT///////////////////////////////////////////////////
void initializeLIBT(Libt *libt){
    libt->ultimo = -1;
}

//LIBERAR MEMORIA LIBT///////////////////////////////////////////////////
void liberarLIBT(Libt *libt) {
    int i;
    for(i = 0;i<=libt->ultimo;i++){
        free(libt->shipments[i]); // Liberar nodo actual
    }
    libt->ultimo = -1;
}

//LOCALIZACION LIBT///////////////////////////////////////////////// CADA CELDA CONSULTADA TIENE C=1

int localizarLIBT(Libt libt, char code [], int *pos, float *cost){
    int li=0;
    int ls=libt.ultimo +1;
    int m= (int)ceil((li+ls)/2);

    while ((li<ls) && (strcmp(libt.shipments[m]->code,code)!= 0)){
        (*cost)+=2; //Incremento el costo por cada celda y nodo consultado
        if(strcmp(libt.shipments[m]->code, code) < 0){
            li=m+1;
        }else{
            ls=m;
        }
        m = (int)ceil((li+ls)/2);
    }

    if(li<ls)(*cost)+=2; //costo cuando se cumple la primer condicion y la segunda no
    *pos=m; //Guardo la posicion de la lista en la que se detuvo
    if (li < ls){
        return SUCCESS;//encontro el elemento
    }
    else{
        return FAILURE; //lista vacia no encontro el elemento
    }
}

//ALTA LIBT///////////////////////////////////////////////////////// CADA CORRIMIENTO TIENE C=0,5 y MODIFICACION DE PUNTERO TIENE C=0,5
int altaLIBT(Libt *libt, Shipment s, float *costA) {
    int posaux = libt->ultimo, pos;
    float costoAux = 0.0, celdas_consultadas=0.0;

    if(libt->ultimo < MAX-1){ //Hay lugar
        Shipment *aux = (Shipment*)malloc(sizeof(Shipment));
        if(aux==NULL) {
            return FAILURE; //Hay lugar pero no tiene memoria para un nuevo nodo
            }
        else {
                if(SUCCESS == localizarLIBT(*libt,s.code,&pos,&celdas_consultadas)){
                free(aux);
                return FAILURE; //Ya existe, no se puede dar de alta
            }else{
                while(posaux >= pos){
                    libt->shipments[posaux+1]=libt->shipments[posaux]; //hago desplzamiento de direcciones para guardar el envio
                    posaux--;
                    costoAux += 0.5; //Incremento el costo en 0,5 de cada corrimiento de direcciones de puntero
                }

                *aux = s;//Guardo los datos en aux
                libt->shipments[pos]=aux; //guardo aux en la posicion
                costoAux += 0.5; //Incremento el costo en 0,5 por la asignacion del arreglo al nodo
                libt->ultimo++; //Incremento el ultimo
                (*costA)=costoAux;

                return SUCCESS;
            }
        }
    }
    else {
        return FAILURE; //Arreglo lleno
        }
}

//BAJA LIBT///////////////////////////////////////////////////////// CADA CORRIMIENTO TIENE C=0,5 Y MODIFICACION DE PUNTERO TIENE C=0,5
int bajaLIBT(Libt *libt, Shipment s, float *costB) {
    float celdas_consultadas=0;
    int pos= 0;
     (*costB)=0.0;
    if (localizarLIBT(*libt, s.code, &pos,&celdas_consultadas) == SUCCESS) {
        if(compareShipments(s, *libt->shipments[pos]) == SUCCESS){
            free(libt->shipments[pos]);
                while (pos < libt->ultimo) {
            libt->shipments[pos] = libt->shipments[pos + 1]; // Desplaza elementos hacia la izquierda
            pos++;
            (*costB)+=0.5;//Decremento el costo en 0,5 de cada corrimiento de direcciones de puntero
            }
            libt->ultimo--; // Reduce el valor del ultimo elemento
            return SUCCESS;
        }
        return FAILURE;
    }else{
        return FAILURE;
    }
}



//EVOCAR LIBT/////////////////////////////////////////////////////////

int evocarLIBT(Libt libt, char code[], Shipment *shipment, float* costo){
    int status=0, pos=0;
    float costosAux=0.0;
    status = localizarLIBT(libt, code, &pos, &costosAux);
    if (status == FAILURE){
        (*costo) = costosAux;
        return FAILURE;
    } else {
        strcpy(shipment->code, libt.shipments[pos]->code);
        shipment->receiver.dni = libt.shipments[pos]->receiver.dni;
        strcpy(shipment->receiver.fullName, libt.shipments[pos]->receiver.fullName);
        strcpy(shipment->receiverAddress, libt.shipments[pos]->receiverAddress);
        shipment->sender.dni = libt.shipments[pos]->sender.dni;
        strcpy(shipment->sender.fullName, libt.shipments[pos]->sender.fullName);
        shipment->sender.dni = libt.shipments[pos]->sender.dni;
        strcpy(shipment->sendingDate, libt.shipments[pos]->sendingDate);
        strcpy(shipment->receptionDate, libt.shipments[pos]->receptionDate);
        (*costo) = costosAux;
        return SUCCESS;
    }
}



//MOSTRAR ESTRUCTURA////////////////////////////////////////////////////

void printLibt(Libt libt){
 int i =0;
    for (i=0; i<=libt.ultimo; i++){
        printf("\n//////////////////////////////");
        printf(" POSICION DEL ENVIO: %d //////////////////////////////\n\n",i);
        printShipment(*libt.shipments[i]);
        printf("\n");
    }
}


#endif // LIBT_H_INCLUDED


