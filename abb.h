#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "shipment.h"

typedef struct n{
    Shipment info;
    struct n *hd;
    struct n *hi;
} Nodo;

typedef struct Nodo{

       Nodo* raiz;
       Nodo* cursor;
       Nodo* anterior;
       int cant;
}abb;

void initializeABB(abb *a){
    a->raiz=NULL;
    a->anterior=NULL;
    a->cursor=NULL;
    a->cant=0;
}
void liberarABB(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }
    liberarABB(nodo->hi); // Liberar subarbol izquierdo
    liberarABB(nodo->hd); // Liberar subarbol derecho
    free(nodo); // Liberar nodo actual
}



///LOCALIZAR

int localizacionABB(abb* arbol, char code [], float *costosL){
    float costosAux = 0.0;
    (*arbol).cursor = arbol->raiz;
    (*arbol).anterior = arbol->raiz;

    while((arbol->cursor != NULL) && (strcmp(arbol->cursor->info.code, code) != 0)) {

        if(strcmpi(arbol->cursor->info.code, code)>0 ){ //*CUR>CODE
            (*arbol).anterior = arbol->cursor;
            (*arbol).cursor = arbol->cursor->hi;
        }  else { //*CUR<CODE
            (*arbol).anterior = arbol->cursor;
            (*arbol).cursor = arbol->cursor->hd;
        }
        costosAux += 1; //Costo por cada nodo consultado

    }

    if(arbol->cursor != NULL){
            costosAux += 1 ; //Localizacion exitosa, sumo un costo de la ultima consulta
            (*costosL) = costosAux;
        return 1;
    } else {
        (*costosL) = costosAux; //Localizacion fracasa, no contamos como costo el nodo null

        return 0;
    }

}

///ALTA
int altaABB(abb *arbol, Shipment nuevo, float *costosA){
    if(arbol->cant==250){ //arbol lleno
        return 0;
    }
    float costosAux = 0.0, costos = 0.0;
    Nodo *auxiliar = (Nodo*)malloc(sizeof(Nodo));
    if (auxiliar == NULL){
        return 2; //Memoria insuficiente
    }else {
        if(localizacionABB(arbol, nuevo.code, &costos) == 0){ //Localizacion fracasa, puedo dar de alta
            auxiliar->info = nuevo;
            auxiliar->hd = NULL;
            auxiliar->hi = NULL;
            if(arbol->raiz == NULL){ /// CASO 1: EL ARBOL ESTA VACIO
                arbol->raiz = auxiliar;
                costosAux +=0.5; //modificacion de puntero de la raiz
                (*costosA) = costosAux;
                return 1; //Alta exitosa
            } ///CASO 2: EL ARBOL NO ESTA VACIO
            else if(strcmpi(arbol->anterior->info.code, auxiliar->info.code) > 0 ){///INSERTO COMO HIJO IZQUIERDO
                arbol->anterior->hi = auxiliar;
            } else {///INSERTO COMO HIJO DERECHO
                arbol->anterior->hd = auxiliar;
            }
                costosAux += 0.5; //Modificacion de puntero izq o der
                (*costosA)=costosAux;
                (arbol->cant)++;
                return 1; //Alta exitosa
        } else{//Localizacion exitosa, no doy de alta
            free(auxiliar); //libero memoria
            return 0;
        }
    }

}


///BAJA
int bajaABB(Shipment v, abb* arbol, float *costosB){
    int resp;
    float costosAux =0.0, costos = 0.0;
    if(localizacionABB(arbol, v.code, &costos) == 1){ //Localizacion exitosa
            resp = compareShipments(arbol->cursor->info, v);
            (arbol->cant)--;
        }
        if (resp == 1){///CASO 1: NODO SIN HIJOS
        if ((arbol->cursor->hi == NULL) && (arbol->cursor->hd == NULL)){
            if (arbol->cursor == arbol->raiz){ ///SI EL NODO ES RAIZ
                free((void*)arbol->raiz);
                arbol->raiz = NULL;

            }else if(strcmpi(arbol->cursor->info.code, arbol->anterior->info.code)>0){ ///SI EL NODO ES UN HIJO DERECHO
                arbol->anterior->hd = NULL ;
                free((void*)arbol->cursor);
                }
                else{ ///EL NODO ES UN HIJO IZQUIERDO
                    arbol->anterior->hi = NULL ;
                    free((void*)arbol->cursor);
                }
            costosAux += 0.5;//Modificacion del puntero
        }else if ((arbol->cursor->hi == NULL) && (arbol->cursor->hd != NULL) ){///CASO 2: TIENE UN HIJO DERECHO
            if(arbol->cursor == arbol->raiz){ /// SI EL NODO ES RAIZ
                arbol->raiz = arbol->cursor->hd;
                free(arbol->cursor);
            }
            else if(strcmpi(arbol->cursor->info.code, arbol->anterior->info.code)>0){ ///EL NODO ES UN HIJO DERECHO
                arbol->anterior->hd = arbol->cursor->hd; ///Asigno el HD del nodo como HD del anterior
                free(arbol->cursor);
                }
            else {  ///EL NODO ES UN HIJO IZQUIERDO
                arbol->anterior->hi = arbol->cursor->hd; ///asigno el HD del nodo como HI del anterior
                free(arbol->cursor);
                }
            //en este caso tambien hay una sola modificacion de punteros
            costosAux += 0.5;
        }else if ((arbol->cursor->hi!= NULL) && (arbol->cursor->hd == NULL)) {///CASO 3: TIENE UN HIJO IZQUIERDO
            if(arbol->cursor == arbol->raiz){ ///SI EL NODO ES RAIZ
                arbol->raiz = arbol->cursor->hi;
                free(arbol->cursor);
            } else if(strcmpi(arbol->cursor->info.code, arbol->anterior->info.code)>0){ ///EL NODO ES UN HIJO DERECHO
                arbol->anterior->hd = arbol->cursor->hi;
                free(arbol->cursor);
            }
            else { ///EL NODO ES UN HIJO IZQUIERDO
                    arbol->anterior->hi = arbol->cursor->hi;
                    free(arbol->cursor);
                }
            costosAux += 0.5;
        }else if ((arbol->cursor->hi != NULL) && (arbol->cursor->hd != NULL)){ ///CASO 4: TIENE HIJO IZQUIERDO Y DERECHO
            ///metodo de reemplazo el mayor de los menores

            Nodo* aux = arbol->cursor;
            Nodo* aux_ant = aux;
            aux = aux->hi;
            while (aux->hd !=NULL){//recorre hasta encontrar el mayor de los menores
                aux_ant = aux;
                aux = aux->hd;
            }
            //asigna los hijos
            if (aux_ant != arbol->cursor){
                aux_ant->hd = aux->hi;
            }else{
                aux_ant->hi = aux->hi;
            }

            if (arbol->cursor == arbol->raiz){
                arbol->raiz->info = aux->info; //reemplazo
            }
            else {
                    arbol->cursor->info = aux->info;
            }

            costosAux +=1.5 ;
            free(aux);
            aux = NULL;
        }
            (*costosB) = costosAux;
            return 1; //lo encontro
        }else{
            return 0;
            }  //no lo encontro
    }

///EVOCACION
int evocacionABB(abb* arbol,char code[], Shipment *s, float* costos){
    float costosAux=0.0;
    if(localizacionABB(arbol, s, &costosAux) == 1){
        strcpy(s->code,arbol->cursor->info.code);
        strcpy(s->receiver.fullName,arbol->cursor->info.receiver.fullName);
        s->receiver.dni = arbol->cursor->info.receiver.dni;
        strcpy(s->receiverAddress,arbol->cursor->info.receiverAddress);
        strcpy(s->receptionDate,arbol->cursor->info.receptionDate);
        strcpy(s->sender.fullName,arbol->cursor->info.sender.fullName);
        s->sender.dni = arbol->cursor->info.sender.dni;
        strcpy(s->sendingDate,arbol->cursor->info.sendingDate);

         (*costos) = costosAux;
         return 1;
    } else {
        (*costos)=costosAux;
        return 0;
        }
}

///IMPRIMIR NODO Y SUS HIJOS
void printShipmentN(Nodo* node){

            printf("- CODIGO DE ENVIO: %s\n\n", node->info.code);
            printf("* DATOS DEL RECEPTOR:\n");
            printf("  - DNI: %d\n", node->info.receiver.dni);
            printf("  - NOMBRE COMPLETO:  %s\n", node->info.receiver.fullName);
            printf("  - DIRECCION: %s\n\n", node->info.receiverAddress);
            printf("* DATOS DEL EMISOR:\n");
            printf("  - DNI: %d\n", node->info.sender.dni);
            printf("  - NOMBRE COMPLETO: %s\n\n", node->info.sender.fullName);
            printf("- FECHA DE ENVIO: %s\n", node->info.sendingDate);
            printf("- FECHA DE RECEPCION: %s\n\n", node->info.receptionDate);
            printf("-HIJO IZQUIERDO: %s\n\n", node->hi->info.code);
            printf("-HIJO DERECHO: %s\n\n", node->hd->info.code);
}

///BARRIDO INRODER
void printInorder(Nodo* node, int *cont) {
    if (node == NULL) {
        return;
    }
    (*cont)++;
    printf("//////////////////////////////\n");
    printInorder(node->hi, cont);
    printShipmentN(node);
    printInorder(node->hd, cont);
}


#endif // ABB_H_INCLUDED
