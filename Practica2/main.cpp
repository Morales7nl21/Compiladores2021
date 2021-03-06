/*
    Este programa regresa un AFD en un .txt determinado como AfnToAFD.txt
*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clasesAFN.hpp"
#include "../Practica1/clases.hpp"

using namespace std;

void menu();
void leerArchivoAFN();
void imprimeEstados();
void imprimeTransiciones();
void generaAFD();
void renombraEstados();
void mostrarEstadosFinales();
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
        cout << "3 -> Renombra estados" << endl;
        cout << "4 -> Muestra nuevos estados AFD" << endl;  
        cout << "5 -> Muestra archivos finales de AFD" << endl;
        cout << "6 -> Salir" << endl;        
        cin>>k;
        switch (k)
        {        
            case 0: leerArchivoAFN(); break;
            case 1: generaAFD(); break;    
            case 2: imprimeTransiciones();break;
            case 3: renombraEstados();break;                    
            case 4: imprimeEstados();break;                 
            case 5: mostrarEstadosFinales();break;   
            case 6: cout << "Saliendo" << endl; break;     
            default: cout << "Opcion no valida" << endl; break;
        }        
    } while (k!=6);    
    
}
void leerArchivoAFN(){ 
    
    archAFN = new archivoAFN("AnalizadorLexicoAFN.txt");
    //archAFN = new archivoAFN("AnalizadorLexicoAFN.txt");
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
void renombraEstados(){
    afn->renombraEstados();
    cout << "Se han renombrado los estados del AFD, vealo en las nuevas transiciones" << endl;
}
void mostrarEstadosFinales(){
    cout << "Mostrando los nuevos estados finales" << endl;
    afn->muestraNuevosEstadosFinales();
};