#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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
    void leeArchivo();
    archivoAFN(string nombre_archivo) : nombre_archivo(nombre_archivo) { leeArchivo(); };
    vector<string> getAlfabeto();
    vector<string> getEstados();    
    vector<string> getEstadosFinales();
    string getEdoInicial();
    vector<vector<string>> getTransiciones();
    void muestraArchivoLeido();    
};
class generaAFD{
    vector<string> nestados;
    string edoInicial;
    

};
class mandaAFDaARchivo{

};