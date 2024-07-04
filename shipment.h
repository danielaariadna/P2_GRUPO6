#ifndef SHIPMENT_H_INCLUDED
#define SHIPMENT_H_INCLUDED
#define SUCCESS 1
#define FAILURE 0
#define FAILURE_EX 2
#define MAX 250
#include "person.h"

typedef struct {
    char code[8];
    Person receiver;
    char receiverAddress[81];
    Person sender;
    char sendingDate[11];
    char receptionDate[11];
} Shipment;


void printShipment(Shipment shipment){

            printf("- CODIGO DE ENVIO: %s\n\n", shipment.code);
            printf("* DATOS DEL RECEPTOR:\n");
            printf("  - DNI: %d\n", shipment.receiver.dni);
            printf("  - NOMBRE COMPLETO:  %s\n", shipment.receiver.fullName);
            printf("  - DIRECCION: %s\n\n", shipment.receiverAddress);
            printf("* DATOS DEL EMISOR:\n");
            printf("  - DNI: %d\n", shipment.sender.dni);
            printf("  - NOMBRE COMPLETO: %s\n\n", shipment.sender.fullName);
            printf("- FECHA DE ENVIO: %s\n", shipment.sendingDate);
            printf("- FECHA DE RECEPCION: %s\n\n", shipment.receptionDate);
}


int compareShipments(Shipment s1, Shipment s2) {
    if ((strcmp(s1.code, s2.code) == 0) &&
        (cmpPersons(s1.receiver, s2.receiver) == 0) &&
        (strcmp(s1.receiverAddress, s2.receiverAddress) == 0) &&
        (cmpPersons(s1.sender, s2.sender) == 0) &&
        (strcmp(s1.sendingDate, s2.sendingDate) == 0) &&
        (strcmp(s1.receptionDate, s2.receptionDate) == 0)) {
        return 1;
    } else {
        return 0;
    }
}



#endif // SHIPMENT_H_INCLUDED
