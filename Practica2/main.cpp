/*
    Este programa regresa un AFD en un .txt determinado como AfnToAFD.txt
*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clasesAFN.hpp"

using namespace std;

void menu();
void leerArchivoAFN();
void imprimeEstados();
void imprimeTransiciones();
void generaAFD();
archivoAFN* archAFN;
AFN *afn;
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
        cout << "1 -> genera AFD" << endl;
        cout << "2 -> Muestra Transiciones AFD" << endl;  
        cout << "2 -> Muestra nuevos estados AFD" << endl;  
        cout << "3 -> Manda Archivo Transiciones AFD" << endl;
        cout << "4 -> Salir" << endl;        
        cin>>k;
        switch (k)
        {        
            case 0: leerArchivoAFN(); break;
            case 1: generaAFD(); break;    
            case 2: imprimeTransiciones();break;
            case 3: imprimeEstados();break;                    
            case 4: cout << "Saliendo" << endl; break;     
            default: cout << "Opcion no valida" << endl; break;
        }        
    } while (k!=4);    
    
}
void leerArchivoAFN(){ 
    
    archAFN = new archivoAFN("AfnToAFD.txt");
    archAFN->muestraArchivoLeido();    
    
}
void imprimeEstados(){
    
    cout << "Mostrando nuevos estados : " << endl;
    afn->muestraNuevosEstados();

};
void imprimeTransiciones(){
    
    cout << "Mostrando las nuevas transiciones" << endl;
    afn->muestraTransiciones();

};
void generaAFD(){
    
     afn = new AFN(archAFN->getEstados(),archAFN->getEdoInicial(), archAFN->getEstadosFinales(),archAFN->getAlfabeto(),archAFN->getTransiciones());     
     cout << "Se ha generado el nuevo AFD" << endl;
};
