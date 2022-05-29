#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class LL1
{
private:
    vector<string> gramatica = {
        "E ⟶ T E’",
        "E’ ⟶ + T E’ | ε",
        "T ⟶ F T’",
        "T’ ⟶ * F T’ | ε",
        "F ⟶ id | ( E )"};
    vector<vector<string>> tabla;
    map<string, vector<string>> conjunto_primeros;
    vector<vector<string>> conjunto_segundos;
    vector<string> terminales;
    vector<string> noTerminales;

public:
    LL1()
    {
        asignaTermNoTermYProduc();
    }
    void asignaTermNoTermYProduc();
    vector<string> primeros(string);
    vector<string> siguientes(string);
    void ConstruirTabla();
    void ProbarCadena(string);
    void GetTerminales();
    void GetnoTerminales();
    vector<string> verificaPrimero(string);
    bool verificaSiEsTerminal(string);
    void imprimeGramatica()
    {
        for (auto const &g : gramatica)
        {
            cout << g << endl;
        }
    }
};
