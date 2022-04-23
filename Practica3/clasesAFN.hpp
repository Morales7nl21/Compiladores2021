#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class AFN
{
private:
    vector<string> estados; //Estados del AFN
    string edoInicial; //Estado inicial
    vector<string> estadosFinales; //Estados finales conjunto de
    vector<string> alfabeto; // Alfabeto a usar
    vector<vector<string>> transicion; // Transiciones del afn
    vector<string> estadosNuevos; // Estados nuevos para el AFD
    vector<vector<string>> nuevas_transiciones; // Transiciones para el AFD
    vector<pair<string,string>> estadosRenombrados; // Conjunto de estados re nombrados pair que contiene estados antes de renombrar y nuevos
    vector<string> estadosFinalesAFD; // Conjunto con estados finales para el AFD
    bool esTaVacio;

public:
    AFN(auto e, auto ed, auto edf, auto alf, auto tr) : estados(e), edoInicial(ed), estadosFinales(edf), alfabeto(alf), transicion(tr)
    {        
        estadosNuevos.push_back(edoInicial);         
        for (auto const & a: alf)
        {                        
            creaAFD(edoInicial, a);           
        }        
    };   
    void creaEstadoVacio(string estado, string calf);
    void muestraNuevosEstados();
    void muestraTransiciones(); 
    void creaAFD(string estadoActual, string calfabeto);
    string creaNuevoEstado(vector<string> &v);
    bool esNuevoEstado(string const &estadosN);
    bool esFinal(string);
    void renombraEstados();
    void muestraNuevosEstadosFinales();
    
    //Getters and Setters
    vector<vector<string>> getTransiciones();
    vector<string> getEstadosFinales();
    string getEdoInicial();
    vector<string> getAlfabeto();
    vector<string> getEstados();
};
class archivoAFN
{
private:
    string nombre_archivo;
    vector<string> alfabeto;
    vector<string> estados;
    vector<string> estadosFinales;
    string edoInicial;
    vector<vector<string>> transiciones;

public:
    archivoAFN(string nombre_archivo) : nombre_archivo(nombre_archivo) { leeArchivo(); };

    vector<string> getAlfabeto();
    vector<string> getEstados();
    vector<string> getEstadosFinales();
    string getEdoInicial();
    vector<vector<string>> getTransiciones();
    void muestraArchivoLeido();
    void leeArchivo();
    void mandarArchivoAFD(auto afd);
};

class mandaAFDaARchivo
{
};