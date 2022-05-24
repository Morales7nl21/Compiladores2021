#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class LL1{    
    private:        
        vector<string> gramatica;
        vector<vector<string>> tabla;
        map<string,vector<string>> primeros;
        vector<vector<string>> segundos;
        vector<string> terminales;
        vector<string> noTerminales;
    public:       
        vector<string> Primero(string); 
        vector<string> Siguiente(string);
        void ConstruirTabla();
        void  ProbarCadena(string);      
        void GetTerminales();
        void GetnoTerminales();  
        vector<string> verificaPrimero(string);
        bool verificaSiEsTerminal(string);
};
