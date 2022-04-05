#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class AFN
{
private:
    vector<string> estados;
    string edoInicial;
    vector<string> estadosFinales;
    vector<string> alfabeto;
    vector<vector<string>> transicion;
    vector<string> estadosNuevos;
    vector<vector<string>> nuevas_transiciones;
    vector<pair<string,string>> estadosRenombrados;
    vector<string> estadosFinalesAFD;
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