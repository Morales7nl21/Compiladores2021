#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class LL1
{
private:
    int cont_s=0;
    /*
    vector<string> gramatica = { //Al ordenar la gramatica así se ejecuta más rápido
        "E -> T E’",
        "T’ -> * F T’ | ε",
        "F -> id | ( E )",
        "T -> F T’",                
        "E’ -> + T E’ | T ε"
        };
    */
    vector<string> gramatica = {
        "E -> T E’",
        "E’ -> + T E’ | ε",
        "T -> F T’",
        "T’ -> * F T’ | ε",
        "F -> id | ( E )"};
     
    vector<vector<string>> tabla;
    map<string, vector<string>> conjunto_primeros; //Aqui se almacenan los primeros donde la llave es el terminal al que se le busca el primero
    map<string, vector<string>> conjunto_siguientes;
    vector<string> terminales;
    vector<string> noTerminales;
    vector<vector<string>> v_gramatica{};
    vector<pair<string, vector<string>>> primerosNoConjunto;
    map<string, vector<pair<string,string>>> sigNoConjunto;

public:
    LL1()
    {
        asignaTermNoTermYProduc();
        obtienePrimeros();
        obtieneSiguientes();
    }
    void obtienePrimeros();
    void obtieneSiguientes();
    void asignaTermNoTermYProduc();
    /*
        El primer parametro hace referencia al simbolo del cual se busca su primero
        el segundo parametro hace referencia al primer elemento despues del simbolo '->'
        el tercer parametro hace referencia al conjunto que guardará sus primeros
    */
    void primeros( const vector<string> &, vector<string> &);
    void siguientes(const string &, vector<string> &);
    void ConstruirTabla();
    void ProbarCadena(string);
    void GetTerminales();
    void GetnoTerminales();
    vector<string> verificaPrimero(string);
    bool verificaSiEsNoTerminal(string);
    
    void imprimeGramatica()
    {
        for (auto const &g : gramatica)
        {
            cout << g << endl;
        }
    }
    string &leftTrim(string &str, string const &chars)
    {
        str.erase(0, str.find_first_of(chars) + 3); // Cortamos el elemento '-' '>' y space por eso '3'
        return str;
    }
    string &rightTrim(string &str, string const &chars)
    {
        str.erase(str.find_first_of(chars)+1);
        return str;
    }
    vector<string> split(const string &s, char seperator)
    {
        vector<std::string> output;
        string::size_type prev_pos = 0, pos = 0;

        while ((pos = s.find(seperator, pos)) != string::npos)
        {
            string substring(s.substr(prev_pos, pos - prev_pos));
            output.push_back(substring);
            prev_pos = ++pos;
        }
        output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
        return output;
    }
};
