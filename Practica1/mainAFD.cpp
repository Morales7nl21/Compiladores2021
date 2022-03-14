#include <bits/stdc++.h>
#include <iostream>
#include "clases.hpp"
using namespace std;


#ifdef _WIN32
  #include<windows.h>
#endif  

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

vector<char> alfabeto;    
AFD *a;
vector<Estado> edos;
Transicion *t;
vector<Estado> final;
Estado inicial;
FuncionTransicion *ft;


void menu();
void mostrarUso();
void ingresarAutomata();
void verificarPalabra();
void imprimeTransiciones();

int main(int argc, const char** argv) {
    menu();   
    return 0;
}


void menu(){
    
    int k;          
    do
    {      
        cout << endl;          
        cout << "0 -> Modo de uso" << endl;
        cout << "1 -> Ingresar Automata" << endl;
        cout << "2 -> Imprimir tabla de transiciones del Automata" << endl;
        cout << "3 -> Verificar Palabra" << endl;
        cout << "4 -> Salir del programa" << endl;    
        cout << endl;
        cin>>k;
        switch (k)
        {
            case 0: mostrarUso(); break;
            case 1: ingresarAutomata();break;
            case 2: imprimeTransiciones(); break;        
            case 3: verificarPalabra(); break;
            case 4: cout << "Saliendo" << endl; break;     
            default: cout << "Opcion no valida" << endl; break;
        }
    } while (k!=4);   
}
void mostrarUso(){
        limpiar_pantalla();
        cout << "1.- Para hacer uso del programa primero ingrese un automata finito determinista antes de buscar o imprimir la tabla de transiciones" << endl;
        cout << "2.- Este automata no acepta como entradas numeros en el alfabeto o nombre de los estados" << endl;
        cout << "3.- De ser que quiera meter un numero representativo en su  alfabeto o como nombre de estado escribalo de la forma: " << endl;
        cout << " \t\t n0, n1, n2, ..., etc. " << endl;
        cout << "4.- Se recomienda que para el nombre de los estados estos inicien con 'q', seguido del numero del estado iniciando en el 0. " << endl;
        cout << "De la forma: \n\t\t q0, q1, q2, ...... , qn " << endl;
        cout << "5.- Al seleccionar el estado inicial o final ingrese solo el numero al que corresponde su estado" << endl; 
        cout << "\n\tsi es el primero use el 0 para denotarlo o si es el ultimo use el valor del total de estados menos 1 " << endl;
        cout << "6.- Para verificar la palabra utilize solo letras o cadenas, no use solo numeros, de ser asi concatenelos con algun char como se menciona en el punto 2 y 3" << endl;            
        cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
        char k; cin >> k;
        limpiar_pantalla();
}
void ingresarAutomata(){
    
    int nalf, sin, sfin, transicionEdo, op=0, numEdosFin;
    string sedos, sfinal, sinicial;

    char c;
    cout << "Ingrese cuantos simbolos conforman su alfabeto: "; cin >> nalf;
    cout << "Ingrese los simbolos que conforman su alfabeto: ";
    for (int i = 0; i < nalf; i++)
    {
        cin >> c;
        alfabeto.push_back(c);
    }
    int nedos ;    
    cout << "Ingrese el numero de estados: "; cin >> nedos;
    
    
    
    for (int i = 0; i < nedos; i++)
    {
        cout << "ingrese cada estado "<< endl; cin >> sedos;
        Estado n{sedos};        
        edos.push_back(n);        
    }
    cout << "Indique cual es el  estado inicial: q";  cin >> sin;
    inicial = edos[sin];
    cout << "Indique el numero de estados finales:";  cin >> numEdosFin;
    for (int i = 0; i < numEdosFin; i++)
    {
        cout << "Indique cual son los  estados finales:  q";  cin >> sfin;
        final.push_back(edos[sfin]);    
    }
        
    cout << "Indique las transiciones de cada estado " << endl;
        
    for(auto & var : edos)
    {    
        vector<pair<Estado,char>> parestados;   
        for(auto ca : alfabeto)
        {
                cout << " Ingrese la transicion  para el estado: " << var.getNombreEdo() << "  con el simbolo:   " << ca <<"  ->  q";   
                cin >> transicionEdo;                 
                parestados.push_back(make_pair(edos[transicionEdo], ca));
        }
        var.setSigEdos(parestados);
        parestados.clear();
        op++;                        
    }
    a = new AFD(alfabeto,edos,inicial,final);
    t = new Transicion(*a);   
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}

void verificarPalabra(){
   
    t->llenaTransiciones();
    string palIdentificar;
    cout << "Indica la palabra a leer: " << endl;    
    cin >> palIdentificar;
    string ini = inicial.getNombreEdo();
    ft = new FuncionTransicion(*a,ini,*t);
    ft->hacerSigTransicion(palIdentificar);
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}
void imprimeTransiciones(){
    for(auto &&var : t->getTransiciones())
    {
        cout << "["<<var.first.first << ","<< var.first.second << "] : " << var.second << endl; 
    }
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}