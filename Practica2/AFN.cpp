#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "clasesAFN.hpp"

void AFN::creaAFD(string estadoActual, string calf)
{
    string edLeer;
    stringstream input_stringstream(estadoActual); // convierte cad en stream
    vector<string> posibleNuevoEstado{};
    while (getline(input_stringstream, edLeer, ','))
    {
        for (auto const &t : transicion)
        {
            vector<string> linea_separada_transicion;
            for (auto const &vt : t)
            {
                string trans_leidas;
                stringstream input_stringstream2(vt);

                while (getline(input_stringstream2, trans_leidas, ' '))
                {
                    linea_separada_transicion.push_back(trans_leidas);
                    trans_leidas = "";
                }
            }
            if (linea_separada_transicion[0] == edLeer && linea_separada_transicion[1] == calf)
            {
                int cont = 0;
                for (auto const &lst : linea_separada_transicion)
                {
                    if (cont > 1)
                        posibleNuevoEstado.push_back(lst);
                    cont++;
                }
            }
        }
    }

    // eliminan repetidos

    std::sort(posibleNuevoEstado.begin(), posibleNuevoEstado.end()); // el algo unique funciona solo con val ordenados
    auto last = unique(posibleNuevoEstado.begin(), posibleNuevoEstado.end());
    posibleNuevoEstado.erase(last, posibleNuevoEstado.end());
    if (posibleNuevoEstado.size() > 0)
    {
        string nuevoEdoString = creaNuevoEstado(posibleNuevoEstado);
        vector<string> nuevaTransicionAcrear{};
        if (esNuevoEstado(nuevoEdoString))
        {

            nuevaTransicionAcrear.push_back(estadoActual);
            nuevaTransicionAcrear.push_back(calf);
            nuevaTransicionAcrear.push_back(nuevoEdoString);
            nuevas_transiciones.push_back(nuevaTransicionAcrear);
            nuevaTransicionAcrear.clear();
            estadosNuevos.push_back(nuevoEdoString);
            for (auto const &ca : alfabeto)
            {
                creaAFD(nuevoEdoString, ca);
            }
        }
        else
        {
            nuevaTransicionAcrear.push_back(estadoActual);
            nuevaTransicionAcrear.push_back(calf);
            nuevaTransicionAcrear.push_back(nuevoEdoString);
            nuevas_transiciones.push_back(nuevaTransicionAcrear);
            nuevaTransicionAcrear.clear();
        }
        nuevaTransicionAcrear.clear();
    }
    else
    {

        creaEstadoVacio(estadoActual, calf);
    }
}
void AFN::creaEstadoVacio(string estado, string calf)
{

    estadosNuevos.push_back("{}");
    vector<string> vectEdoVacio{};
    vectEdoVacio.push_back(estado);
    vectEdoVacio.push_back(calf);
    vectEdoVacio.push_back("{}");
    nuevas_transiciones.push_back(vectEdoVacio);
    vectEdoVacio.clear();
    if (esTaVacio)
    {
        for (auto const &a : alfabeto)
        {
            vectEdoVacio.push_back("{}");
            vectEdoVacio.push_back(a);
            vectEdoVacio.push_back("{}");
            nuevas_transiciones.push_back(vectEdoVacio);
            vectEdoVacio.clear();
        }
        esTaVacio = false;
    }
}
void AFN::muestraTransiciones()
{
    for (auto const &it : nuevas_transiciones)
    {
        for (auto const &s : it)
        {
            cout << "Transicion: " << s << endl;
        }
    }
}
void AFN::muestraNuevosEstados()
{
    for (auto const &eN : estadosNuevos)
    {

        cout << "Estado nuevo : " << eN << endl;
    }
}
string AFN::creaNuevoEstado(vector<string> &estadosN)
{
    string nE = "";
    sort(estadosN.begin(), estadosN.end(),
         [](const auto &a, const auto &b) -> bool
         {
             return a[1] - '0' < b[1] - '0';
         });
    for (auto const &eN : estadosN)
    {
        nE.append(eN);
        nE.push_back(',');
    }
    nE.pop_back();
    return nE;
}
bool AFN::esNuevoEstado(string const &estadosN)
{

    for (auto const &eN : estadosNuevos)
    {
        if (eN == estadosN)
            return false;
    }
    return true;
}