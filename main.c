#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include "shipment.h"
#include "abb.h"
#include "costos.h"
#include "lsobb.h"
#include "Libt.h"

typedef int bool;

///CONCLUSIÓN GRUPO 6. Integrantes: Morales Daniela Ariadna y Sayago Francisco.
/*
    A la hora de realizar la respectiva comparación entre las listas presentadas,
    podemos observar que los arboles son mucho más óptimos en sus costos de altas
    y bajas con respecto a las otras estructuras, pero en cambio al observar el
    evocar del ABB en general es  mas costoso a comparacion de la LSOBB.
    Si lo que buscamos es realizar multiples consultas en nuestro sistema nos conviene
    implementar la LSOBB ya que su tipo de busqueda, binaria con biseccion,
    es mucho menos costosa que las anteriores.
    La LIBT si bien al usar nodos los costos son menores, en las altas y bajas,
    considerablemente  con respecto de la LSOBB, pero aun asi no llega a ser tan optimo como con los arboles.


     _________________________________________________________________________
    |                           |              |              |              |
    |                           |     LIBT     |    LSOBB     |     ABB      |
    |___________________________|______________|______________|______________|
    | Alta                      |              |              |              |
    |    Cantidad               |     120      |     120      |     120      |
    |    Costo Acumulado        |     964.00   |     1808.00  |     60.00    |
    |    Costo Maximo           |     29.50    |     58.00    |     0.50     |
    |    Costo Promedio         |     8.03     |     15.07    |     0.50     |
    |___________________________|______________|______________|______________|
    | Baja                      |              |              |              |
    |    Cantidad               |     93       |     93       |     93       |
    |    Costo Acumulado        |     780.00   |     1560.00  |     90.50    |
    |    Costo Maximo           |     23.50    |     47.00    |     1.50     |
    |    Costo Promedio         |     8.39     |     16.77    |     0.97     |
    |___________________________|______________|______________|______________|
    | Evocar exitoso            |              |              |              |
    |    Cantidad               |     258      |     258      |     258      |
    |    Costo Acumulado        |     2426.00  |     1437.00  |     1476.00  |
    |    Costo Maximo           |     12.00    |     7.00     |     12.00    |
    |    Costo Promedio         |     9.40     |     5.57     |     5.72     |
    |___________________________|______________|______________|______________|
    | Evocar fracaso            |              |              |              |
    |    Cantidad               |     103      |     103      |     103      |
    |    Costo Acumulado        |     1048.00  |     509.00   |     575.00   |
    |    Costo Maximo           |     12.00    |     7.00     |     10.00    |
    |    Costo Promedio         |     10.17    |     4.94     |     5.58     |
    |___________________________|______________|______________|______________|
*/


//// MENU /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gotoxy(int x, int y){
    HANDLE IdentiVentana; // Identificador
    IdentiVentana = GetStdHandle(STD_OUTPUT_HANDLE); // recuperar el identificador de la consola, 1er parametro, es el tipo de control que deseamos tener
                                                    //STD_oUTPUT_HENDLE  toma el control de la salida de la consola

    COORD coordenadas;  // estructura de windows.h con atributos x e y que simulan coordenadas
    coordenadas.X = x;
    coordenadas.Y = y;
    SetConsoleCursorPosition(IdentiVentana, coordenadas); // situa el cursor con esas coordenadas, el primero es el identificador y el 2do es la posicion donde situo el cursor

}

void draw_Menu(){

    int i,x=15,y=3;
    gotoxy(x,y);
    printf("%c",201);
    x++;
    for(i=0;i<100;i++)
    {
        gotoxy(x,y);
        printf("%c",205);
        x++;
    }

    printf("%c",187);
    y=4;
    x=15;
    for(i=0;i<16;i++)
    {
        gotoxy(x,y);
        printf("%c",186);
        y++;
    }

    x=116;
    y=4;
    for(i=0;i<16;i++)
    {
        gotoxy(x,y);
        printf("%c",186);
        y++;
    }

    y=20;
    x=15;
    gotoxy(x,y);
    printf("%c",200);
    x++;
    for(i=0;i<100;i++)
    {

        gotoxy(x,y);
        printf("%c",205);
        x++;
    }

    y=28;
    x=126;
    gotoxy(x,y);
    printf("%c",188);
    gotoxy(52,5);
    printf(" \" E L   R E V O L E O \" ");

    gotoxy(16,6);
    for(i=0;i<100;i++)
    {
     printf("%c",238);
    }


    gotoxy(16,13);
    for(i=0;i<100;i++)
    {
        printf("%c",205);
        x++;
    }
    gotoxy(16,20);
    for(i=0;i<100;i++)
    {
        printf("%c",205);
        x++;
    }
    y=9;
    gotoxy(53,y);
    printf("[1] COMPARAR ESTRUCTURAS.");

    y=16;
    gotoxy(53, y);
    printf("[2] MOSTRAR ESTRUCTURAS.\n");
    gotoxy(105, 21);
    printf("[3] Salir\n");

}


// RESET /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void resetAll(TablaCostos *tabla,abb *a,Lsobb *lsobb, Libt *libt ){

    initializeABB(a);
    initializeLSOBB(lsobb);
    initializeLIBT(libt);
    resetTabla(tabla);
}


//COMPARACION DE ESTRUCTURAS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int readFile(TablaCostos *tabla, abb *a, Lsobb *lsobb, Libt *libt) {

    FILE *fp;
    int operacion, i;
    Shipment aux, auxS;
    int statusEvocar;
    float costo;
    if ((fp = fopen("Operaciones-Envios.txt","r")) == NULL){
        return 0;
    }
    while (fscanf(fp, "%d", &operacion) == 1) {

        if (operacion == 1 || operacion == 2) {
            fscanf(fp, " %[^\n]", aux.code);
            for(i = 0; aux.code[i] != '\0'; i++){
                aux.code[i] = toupper(aux.code[i]);
            }

            fscanf(fp, "%d", &aux.receiver.dni);
            fscanf(fp, " %[^\n]", aux.receiver.fullName);
            for(i = 0; aux.receiver.fullName[i] != '\0'; i++){
                aux.receiver.fullName[i] = toupper(aux.receiver.fullName[i]);
            }
            fscanf(fp, " %[^\n]", aux.receiverAddress);
            for(i = 0; aux.receiverAddress[i] != '\0'; i++){
            aux.receiverAddress[i] = toupper(aux.receiverAddress[i]);
            }
            fscanf(fp, "%d", &aux.sender.dni);
            fscanf(fp, " %[^\n]", aux.sender.fullName);
            for(i = 0; aux.sender.fullName[i] != '\0'; i++){
            aux.sender.fullName[i] = toupper(aux.sender.fullName[i]);
            }
            fscanf(fp, " %[^\n]", aux.sendingDate);
            fscanf(fp, " %[^\n]", aux.receptionDate);

            if (operacion == 1) { ///ALTAS-------------------------------------------
                    //ABB------------------------------------------------------------
                    costo = 0.0;
                    if(altaABB(a,aux,&costo) == 1){
                        tabla->abb.acAltas = tabla->abb.acAltas + costo; //Acumulo los costos

                        tabla->abb.cantAltas++; //incremento las altas
                        if (tabla->abb.maxAltas < costo){ //actualizo el costo maximo
                            tabla->abb.maxAltas = costo;
                        }


                    }
                    //LSOBB------------------------------------------------------------
                    costo = 0.0;
                    if(altaLSOBB(lsobb,aux,&costo) == 1){
                        tabla->lsobb.acAltas = tabla->lsobb.acAltas + costo; //Acumulo los costos

                        tabla->lsobb.cantAltas++; //incremento las altas
                        if (tabla->lsobb.maxAltas < costo){ //actualizo el costo maximo
                            tabla->lsobb.maxAltas = costo;
                        }


                    }
                    //LIBT//------------------------------------------------------------
                        costo = 0.0;
                    if(altaLIBT(libt,aux,&costo)==SUCCESS){
                        tabla->libt.acAltas = tabla->libt.acAltas + costo; //Acumulo los costos
                        tabla->libt.cantAltas++; //incremento las altas
                        if (tabla->libt.maxAltas < costo){ //actualizo el costo maximo
                            tabla->libt.maxAltas = costo;
                        }


                    }
             }else if (operacion == 2 ) { ///BAJAS-------------------------------------
                    //ABB--------------------------------------------------------------
                    if (a->raiz != NULL){
                        costo = 0.0;
                        if ((bajaABB(aux,a,&costo))== 1){
                            tabla->abb.cantBajas++;
                            tabla->abb.acBajas=tabla->abb.acBajas + costo;
                                if (tabla->abb.maxBajas < costo){
                                tabla->abb.maxBajas = costo;
                            }
                        }
                    }
                    //LSOBB------------------------------------------------------------
                     if (lsobb->ultimo != -1){
                                costo = 0.0;
                                if ((bajaLSOBB(lsobb, aux, &costo))== SUCCESS){
                                    tabla->lsobb.cantBajas++;
                                    tabla->lsobb.acBajas=tabla->lsobb.acBajas + costo;
                                        if (tabla->lsobb.maxBajas < costo){
                                        tabla->lsobb.maxBajas = costo;
                                    }
                                }
                    }
                    //LIBT//------------------------------------------------------------
                    if (libt->ultimo != -1){
                        costo = 0.0;
                        if ((bajaLIBT(libt, aux, &costo)) == SUCCESS){
                            tabla->libt.cantBajas++;
                            tabla->libt.acBajas=tabla->libt.acBajas + costo;
                                if (tabla->libt.maxBajas < costo){
                                tabla->libt.maxBajas = costo;
                            }
                        }
                    }

                    }


        }else if (operacion == 3) {
            fscanf(fp, " %[^\n]", aux.code);

            for(i = 0; aux.code[i] != '\0'; i++){
                aux.code[i] = toupper(aux.code[i]);
            }

            //ABB--------------------------------------------------------------
                   if (a->raiz != NULL){
                        costo = 0.0;
                        statusEvocar = evocacionABB(a,aux.code,&aux,&costo);
                        if (statusEvocar == 1){
                            tabla->abb.cantEvocarE++;
                            tabla->abb.acEvocarE = tabla->abb.acEvocarE + costo;
                            if (tabla->abb.maxEvocarE < costo){
                                tabla->abb.maxEvocarE = costo;
                            }
                        }else{
                            tabla->abb.cantEvocarF++;
                            tabla->abb.acEvocarF =tabla->abb.acEvocarF + costo;
                            if (tabla->abb.maxEvocarF < costo){
                                tabla->abb.maxEvocarF = costo;
                            }
                        }
                    }
            //LSOBB------------------------------------------------------------
                    if (lsobb->ultimo != -1){
                        costo = 0.0;
                        statusEvocar = evocarLSOBB(*lsobb, aux.code, &auxS, &costo);
                        if (statusEvocar){
                            tabla->lsobb.cantEvocarE++;
                            tabla->lsobb.acEvocarE = tabla->lsobb.acEvocarE + costo;
                            if (tabla->lsobb.maxEvocarE < costo){
                                tabla->lsobb.maxEvocarE = costo;
                            }
                        }else{
                            tabla->lsobb.cantEvocarF++;
                            tabla->lsobb.acEvocarF =tabla->lsobb.acEvocarF + costo;
                            if (tabla->lsobb.maxEvocarF < costo){
                                tabla->lsobb.maxEvocarF = costo;
                            }
                        }
                    }
            //LIBT---------------------------------------------------------------
            if (libt->ultimo != -1){
                        costo = 0.0;
                        statusEvocar = evocarLIBT(*libt, aux.code, &auxS, &costo);
                        if (statusEvocar == SUCCESS){
                            tabla->libt.cantEvocarE++;
                            tabla->libt.acEvocarE = tabla->libt.acEvocarE + costo;
                            if (tabla->libt.maxEvocarE < costo){
                                tabla->libt.maxEvocarE = costo;
                            }
                        }else{
                            tabla->libt.cantEvocarF++;
                            tabla->libt.acEvocarF =tabla->libt.acEvocarF + costo;
                            if (tabla->libt.maxEvocarF < costo){
                                tabla->libt.maxEvocarF = costo;
                            }
                        }
                    }

    }
    }
    fclose(fp);

     //MEDIO ABB--------------------------------------------------------------
        tabla->abb.MedioAltas = tabla->abb.acAltas / tabla->abb.cantAltas;
        tabla->abb.MedioBajas = tabla->abb.acBajas / tabla->abb.cantBajas;
        tabla->abb.MedioEvocarE = tabla->abb.acEvocarE / tabla->abb.cantEvocarE;
        tabla->abb.MedioEvocarF = tabla->abb.acEvocarF / tabla->abb.cantEvocarF;
    //MEDIO LSOBB//------------------------------------------------------------
        tabla->lsobb.MedioAltas = tabla->lsobb.acAltas / tabla->lsobb.cantAltas;
        tabla->lsobb.MedioBajas = tabla->lsobb.acBajas / tabla->lsobb.cantBajas;
        tabla->lsobb.MedioEvocarE = tabla->lsobb.acEvocarE / tabla->lsobb.cantEvocarE;
        tabla->lsobb.MedioEvocarF = tabla->lsobb.acEvocarF / tabla->lsobb.cantEvocarF;
    //LIBT--------------------------------------------------------------
        tabla->libt.MedioAltas = (tabla->libt.cantAltas != 0) ? tabla->libt.acAltas / tabla->libt.cantAltas : 0;
        tabla->libt.MedioBajas = (tabla->libt.cantBajas != 0) ? tabla->libt.acBajas / tabla->libt.cantBajas : 0;
        tabla->libt.MedioEvocarE = (tabla->libt.cantEvocarE != 0) ? tabla->libt.acEvocarE / tabla->libt.cantEvocarE : 0;
        tabla->libt.MedioEvocarF = (tabla->libt.cantEvocarF != 0) ? tabla->libt.acEvocarF / tabla->libt.cantEvocarF : 0;

    return 1;
}








int main()
{
    int contador=0;
    int resp=0;
    int opt,optE=0;
    Shipment s, auxS;
    //DECLARACION DE ESTRUCTURAS
    TablaCostos tabla;
    abb a;
    Lsobb lsobb;
    Libt libt;
    resetAll(&tabla,&a,&lsobb,&libt);

    system ("color 0B");
    do{
            system("cls");
            draw_Menu();
            gotoxy(0,22);
            printf("\n- OPCION (Luego presione enter): ");
            scanf("%d",&opt);
            getchar();

            switch(opt){
            case 1: // COMPARAR ESTRUCTURAS
                system("cls");
                liberarLIBT(&libt); //Libera la memoria usada en la lista invertida
                liberarABB(a.raiz); //Libera la memoria usada en el arbol
                resetAll(&tabla,&a,&lsobb,&libt);
                readFile(&tabla,&a,&lsobb,&libt);
                printTabla(tabla);
                system("pause");

                break;
            case 2: // MOSTRAR ESTRUCTURAS
                do{
                        system("cls");
                        printf("\n\t\t\t\t     \n\n"
                       "\t___________________________________________________________________________________\n\n"
                       "\t\t\tMostrar Estructuras:  \n\n"
                       "\t\t\t< 1 > Lista Invertida con Busqueda por Triseccion (LIBT)\n\n"
                        "\t\t\t< 2 > Lista Secuencial Ordenada con Busqueda por Biseccion (LSOBB)\n\n"
                       "\t\t\t< 3 > Arbol Binario de Busqueda (ABB)\n\n"
                       "\t\t\t< 4 > Volver al menu principal \n\n"
                       "\t___________________________________________________________________________________\n");

                 printf("\n- OPCION (Luego presione enter): ");
                scanf("%d", &optE);
                getchar();
              switch(optE){
                    case 1: //MOSTRAR LSOBB
                        system("cls");
                        if(libt.ultimo==-1){
                        printf("\n                    * * * *  E S T R U C T U R A  V A C I A  * * * *\n\n\n");
                        }else{
                        printf("\n                    * * * *   E N V I O S   C A R G A D O S  E N  L A  E S T R U C T U R A   * * * *\n\n\n");
                        printLibt(libt);
                        }
                        system("pause");

                        break;
                    case 2: //MOSTRAR LIBT
                        system("cls");
                            if(lsobb.ultimo == -1){
                        printf("\n                    * * * *  E S T R U C T U R A  V A C I A  * * * *\n\n\n");
                        }else{
                        printf("\n                    * * * *   E N V I O S   C A R G A D O S  E N  L A  E S T R U C T U R A   * * * *\n\n\n");
                        printLsobb(lsobb);
                        }
                     system("pause");
                        break;
                    case 3: //MOSTRAR ABB
                        system("cls");
                        if(a.raiz==NULL){
                            printf("\n                    * * * *  E S T R U C T U R A  V A C I A  * * * *\n\n\n");
                            system("pause");
                        } else{
                       printInorder(a.raiz,&contador);
                       printf("CANTIDAD DE ENVIOS MOSTRADOS: %d\n", contador);
                       system("pause");}
                        break;
                    case 4: //SALIR
                        break;
                    }
                }while(optE!=4);

                break;
            case 3: //SALIR
                system("cls");
                exit(0);
                break;

            }

    }
    while(opt!=3);
    system("cls");
    return 0;
}
