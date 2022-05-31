#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#include "LL1.hpp"

LL1 *l1 = new LL1();

int ingresarCadena()
{
    vector<string> cadena = {"("};
    int s1, s2;
    queue<string> pila{};
    pila.push("$");
    pila.push("E");
    // cin >> cadena;
    //  id+id*id
    //  Concatenar $; $id+id*id
    //  Recorremos cadena
    for (auto &c1 : cadena)
    {
        int indice_cabe = 0;
        for (const auto &c2 : l1->cabezera)
        {
            if (c2 == c1)
            {
                cout << indice_cabe;
                break;
            }
            indice_cabe++;
        }
        int indice_primerColumna = 0;
        for (const auto &c3 : l1->primerColumna)
        {
            if (pila.back() == c3)
            {
                cout << indice_primerColumna;
                break;
            }
        }
        string simbolo_mayor = ">";
        string valor_tabla = l1->tablaFinal[indice_primerColumna + 1][indice_cabe];
        cout << valor_tabla;
        l1->corte(valor_tabla, simbolo_mayor);
        cout << "\n"
             << valor_tabla;
        pila.pop();
        // string valor_tabla_rever(valor_tabla.rbegin(), valor_tabla.rend());
        auto sentencias = l1->split(valor_tabla, ' ');
        for (const auto &vtr : sentencias)
        {
            if (vtr != " ")
            {
                string valor_tabla_rever(vtr.rbegin(), vtr.rend());
                pila.push(valor_tabla_rever);
                cout << "\n\nMetiendo en pila: " << valor_tabla_rever;
            }
        }
    }
}

int main()
{

    ingresarCadena();
    // ll1->imprimeGramatica();
    return 0;
}
