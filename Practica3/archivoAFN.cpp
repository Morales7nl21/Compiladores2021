#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clasesAFN.hpp"

void archivoAFN::leeArchivo()
{
    //cout << "Abriendo archivo" << nombre_archivo << endl;

    ifstream archivo(nombre_archivo); // se lee el archivo
    string linea;
    int cont = 0, contTransicion = 0; // contador de transicion sirve para saber en que transicion del estado va
    vector<int> finalesInt;
    vector<string> transicion;
    if (archivo.is_open())
        cout << "Todo bien al abrir archivo" << endl;
    while (getline(archivo, linea))
    {
        // se eliminarn los espacios
        linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
        linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());
        // Se recorre caracter a caracter
        for (auto &c : linea)
        {
            if (c != 'q')
            {
                if (cont == 0)
                {
                    string s(1, c);
                    alfabeto.push_back(s);
                }
                else if (cont == 1)
                {
                    {
                        string s(1, c);
                        estados.push_back("q" + s);
                    }
                }
                else if (cont == 2)
                {
                    string s(1, c);
                    edoInicial = "q" + s;
                }
                else if (cont == 3)
                {
                    string s(1, c);
                    estadosFinales.push_back("q" + s);
                }
                else if (cont >= 4)
                {
                    string s(1, c);
                    transicion.push_back(s);
                }
            }
        }
        if (cont >= 4)
        {
            transiciones.push_back(transicion);
            transicion.clear();
        }
        cont++;
    }
    transicion.clear();
    cout << endl
         << "El archivo se leyo correctamente" << endl;
    archivo.close();
}

void archivoAFN::muestraArchivoLeido()
{
    cout << "Alfabeto:" << endl;
    for (auto const &a : alfabeto)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Estados:" << endl;
    for (auto const &e : estados)
    {
        cout << e << " ";
    }
    cout << endl;
    cout << "Estados inicial:" << endl;
    cout << edoInicial;
    cout << endl;
    cout << "Estados finales:" << endl;
    for (auto const &ef : estadosFinales)
    {
        cout << ef << " ";
    }
    cout << endl;
    cout << "Transiciones:" << endl;
    int convEstados = 0;
    for (auto &&nt : transiciones)
    {
        for (auto &&t : nt)
        {
            if(convEstados==1)
                cout << t << " ";
            else{
                t= "q"+t;
                cout << t << " ";
            }
            convEstados++;
        }
        convEstados = 0;
        cout << endl;
    }
    cout << endl;
}
vector<string> archivoAFN::getAlfabeto()
{
    return alfabeto;
}
vector<string> archivoAFN::getEstados(){
    return estados;
}
vector<vector<string>> archivoAFN::getTransiciones(){
    return transiciones;
}
string archivoAFN::getEdoInicial(){
    return edoInicial;
}
vector<string> archivoAFN::getEstadosFinales(){
    return estadosFinales;
}