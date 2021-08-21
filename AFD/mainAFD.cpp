#include <bits/stdc++.h>
using namespace std;
#include "clases.hpp"

vector<char> alfabeto;    
AFD *a;
vector<Estado> edos;
Transicion *t;
Estado final, inicial;
FuncionTransicion *ft;


void menu();
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
        cout << "1 -> Ingresar Automata" << endl;
        cout << "2 -> Imprimir tabla de transiciones del Automata" << endl;
        cout << "3 -> Verificar Palabra" << endl;
        cout << "4 -> Salir del programa" << endl;    
        cout << endl;
        cin>>k;
        switch (k)
        {
        case 1: ingresarAutomata();break;
        case 2: imprimeTransiciones(); break;        
        case 3: verificarPalabra(); break;
        case 4: cout << "Saliendo" << endl; break;     
        default: cout << "Opcion no valida" << endl; break;
        }
    } while (k!=4);   
}
void ingresarAutomata(){
    
    int nalf,nedos , sin, sfin, transicionEdo, op=0;
    string sedos, sfinal, sinicial;

    char c;
    cout << "Ingrese cuantos simbolos conforman su alfabeto: "; cin >> nalf;
    cout << "Ingrese los simbolos que conforman su alfabeto: ";
    for (int i = 0; i < nalf; i++)
    {
        cin >> c;
        alfabeto.push_back(c);
    }
    cout << "Ingrese el numero de estados: "; cin  >> nedos;
    vector<pair<Estado,char>> parestados[nedos];    
    for (int i = 0; i < nedos; i++)
    {
        cout << "ingrese cada estado "<< endl; cin >> sedos;
        Estado n{sedos};        
        edos.push_back(n);        
    }
    cout << "Indique cual es el  estado inicial: q";  cin >> sin;
    inicial = edos[sin];
    cout << "Indique cual es el estado final: q";  cin >> sfin;
    final = edos[sfin];
    cout << "Indique las transiciones de cada estado " << endl;
        
    for(auto & var : edos)
    {    
        for(auto ca : alfabeto)
        {
                cout << " Ingrese la transicion  para el estado: " << var.getNombreEdo() << "  con el simbolo:   " << ca <<"  ->  q";   
                cin >> transicionEdo;                 
                parestados[op].push_back(make_pair(edos[transicionEdo], ca));
        }
        var.setSigEdos(parestados[op]);
        op++;                        
    }
    a = new AFD(alfabeto,edos,inicial,final);
    t = new Transicion(*a);    
}

void verificarPalabra(){
   
    t->llenaTransiciones();
    string palIdentificar;
    cout << "Indica la palabra a leer: " << endl;    
    cin >> palIdentificar;
    string ini = inicial.getNombreEdo();
    ft = new FuncionTransicion(*a,ini,*t);
    ft->hacerSigTransicion(palIdentificar);
}
void imprimeTransiciones(){
    for(auto &&var : t->getTransiciones())
    {
        cout << "["<<var.first.first << ","<< var.first.second << "] : " << var.second << endl; 
    }
}