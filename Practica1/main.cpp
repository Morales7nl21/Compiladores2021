#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clases.hpp"

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
vector<char> alfabeto;
AFD *a;
vector<Estado> edos;
Transicion *t;
vector<Estado> final;
Estado inicial;
FuncionTransicion *ft;

void menu();
void verificarPalabra();
void imprimeTransiciones();
void imprimeAlfabeto();
void imprimeEstados();
int main(int argc, char const *argv[])
{   
    menu();
    return 0;
}
void imprimeTransiciones(){
    for(auto &&var : t->getTransiciones())
    {
        cout << "["<<var.first.first << ","<< var.first.second << "] |- " << var.second << endl; 
    }
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
void imprimeAlfabeto(){
    cout << "alfabeto: " << endl;
    for (auto &i : alfabeto)
    {
        cout << i << endl;
    }
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}
void imprimeEstados(){
    int nedos=0;
     cout << "Estados" << endl;       
    for (auto &i : edos)
    {
        cout << i.getNombreEdo() << endl;
        nedos++;
    }
    cout << "Estado inicial" << endl;
    cout << inicial.getNombreEdo() << endl;
    cout << "Estados finales" << endl;
    for (auto &i : final)
    {
        cout << i.getNombreEdo() << endl;
    }
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}
void leerArchivoAFD(){
    string nombre_archivoAFD = "ejemploAutomata.txt";
    ifstream archivo(nombre_archivoAFD.c_str());
    string linea, edo_inicial;
    int  it_estado = 0;  
    vector<int> finalesInt;
    int cont = 0;    
    if (archivo.is_open())
        cout << "Todo bien al abrir archivo" << endl;
    while (getline(archivo, linea))
    {
        linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
        linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
        for (auto &c : linea)
        {

            if (c != 'q')
            {
                if (cont == 0)
                    alfabeto.push_back(c);
                else if (cont == 1)
                {
                    {
                        string s(1, c);
                        Estado n{"q" + s};
                        edos.push_back(n);
                    }
                }
                else if (cont == 2)
                    inicial = edos[(int)c - 48];
                else if (cont == 3)
                    final.push_back(edos[(int)c - 48]);
                else if (cont == 4)
                    finalesInt.push_back((int)c - 48);
            }
        }        
        cont++;
    }               
    for(auto & var : edos)
    {             
        vector<pair<Estado,char>> parestados; 
        for(auto ca : alfabeto)
        {            
            parestados.push_back(make_pair(edos[finalesInt[it_estado]], ca));
            it_estado++;   
        }        
        var.setSigEdos(parestados);
        parestados.clear();                                    
    }    
    a = new AFD(alfabeto,edos,inicial,final);
    t = new Transicion(*a); 
    cout << "Se ha creado el AFD de forma correcta "<< endl;
    cout << "\nPara continuar introduzca cualquier caracter y presione enter" << endl;
    char k; cin >> k;
    limpiar_pantalla();
}
void menu(){
    

    int k;          
    do
    {      
        cout << endl;
        cout << "0 -> Leer de archivo AFD" << endl; 
        cout << "1 -> Mostrar alfabeto" << endl;
        cout << "2 -> Mostrar estados" << endl;  
        cout << "3 -> Imprimir tabla de transiciones del Automata" << endl;
        cout << "4 -> Verificar Palabra" << endl;
        cout << "5 -> Salir del programa" << endl;    
        
        cout << endl;
        cin>>k;
        switch (k)
        {        
            case 0: leerArchivoAFD(); break;
            case 1: imprimeAlfabeto(); break;    
            case 2: imprimeEstados();break;
            case 3: imprimeTransiciones(); break;        
            case 4: verificarPalabra(); break;
            case 5: cout << "Saliendo" << endl; break;     
            default: cout << "Opcion no valida" << endl; break;
        }
    } while (k!=5);   
    limpiar_pantalla();
}
