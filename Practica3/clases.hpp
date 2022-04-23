#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Estado{    
    private:
        string _nombreEdo;
        vector<pair<Estado,char>> _sigEdos;
    public:       
        Estado(); 
        Estado(string);
        vector<pair<Estado,char>>  getSigEdos();
        void  setSigEdos(vector<pair<Estado,char>> &);
        string getNombreEdo();
   
};

class AFD{
    private:
        vector<char> _alfabeto;
        vector<Estado> _estados, _edoFinal;
        Estado _edoInicial;
    public:
        AFD();
        AFD(vector<char> , vector<Estado> &, Estado &, vector<Estado> &);
        vector<char> getAlfabeto();
        vector<Estado> getEstados();
        Estado getEdoInicial();
        vector<Estado> getEdosFinales();
        void setAlfabeto(vector<string>);
        void setEstados(vector<string>, vector<vector<string>>);
        void setEstadoInicial(string);
        void setEstadosFinales(vector<string>);

};
class Transicion{
    private:
        map<pair<string,char>,string> _transiciones;
        AFD _afd;
    public:
        Transicion();
        Transicion(AFD &);
        map<pair<string,char>,string> getTransiciones();
        void setTransiciones(map<pair<string,char>,string> &);
        void llenaTransiciones();

};

class FuncionTransicion{
    private:
        AFD _afd; 
        string _edoActual;    
        Transicion _transiciones;           
        
    public:
        FuncionTransicion();
        FuncionTransicion(AFD &, string &, Transicion &);        
        
        bool esPosible(string &);
        void hacerSigTransicion(string &);     

        void setEstadoActual(string &);   
        string  getEstadoActual();
};
