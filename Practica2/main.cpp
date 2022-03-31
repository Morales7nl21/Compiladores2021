/*
    Este programa regresa un AFD en un .txt determinado como AfnToAFD.txt
*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clasesAFN.hpp"

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

void limpiar_pantalla()
{    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void menu();
void leerArchivoAFN();
void imprimeAlfabeto();
void imprimeEstados();
void imprimeTransiciones();
void generaAFD();
archivoAFN* archAFN;
int main(int argc, char const *argv[])
{
    menu();
    return 0;
}

void menu(){
     int k;          
    do
    {      
        
        cout << endl <<"0 -> Leer de archivo AFD" << endl; 
        cout << "1 -> Mostrar alfabeto" << endl;
        cout << "2 -> Mostrar estados" << endl;  
        cout << "3 -> Imprimir tabla de transiciones del Automata" << endl;
        cout << "4 -> Verificar Palabra" << endl;
        cout << "5 -> Salir del programa" << endl << endl;                    
        cin>>k;
        switch (k)
        {        
            case 0: leerArchivoAFN(); break;
            case 1: imprimeAlfabeto(); break;    
            case 2: imprimeEstados();break;
            case 3: imprimeTransiciones(); break;        
            case 4: generaAFD(); break;
            case 5: cout << "Saliendo" << endl; break;     
            default: cout << "Opcion no valida" << endl; break;
        }        
    } while (k!=5);    
    
}
void leerArchivoAFN(){ 
    
    archAFN = new archivoAFN("AfnToAFD.txt");
    archAFN->muestraArchivoLeido();
    
    
}
void imprimeAlfabeto(){};
void imprimeEstados(){};
void imprimeTransiciones(){};
void generaAFD(){};
