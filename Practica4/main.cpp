#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#include "LL1.hpp"

LL1 *l1 = new LL1();

int ingresarCadena(vector<string> cadena)
{
    cout << "Cadena:" << endl;
    for (auto const &c : cadena)
    {
        cout << c;
    }
    cout << endl;

    stack<string> pila{};
    pila.push("$");
    pila.push("E");

    //cout << "valores en pila INICIO " << endl;
    /*
    stack<string> tmp_q = pila; // copy the original queue to the temporary queue
    while (!tmp_q.empty())
    {
        cout << "queue:" << tmp_q.top() << endl;
        tmp_q.pop();
    }
    */
    int cont = 0;
    int prueba = 0;
    bool cadena_valida = false;

    while (cont < cadena.size())
    {

        string valor_tabla;
        int indice_cabe = 0;
        //cout << "CADENA c: " << cadena[cont] << endl;
        if (cadena_valida == true)
        {
            break;
        }
        // obtenemos id´s para obtener posicion en tabla
        for (const auto &c2 : l1->cabezera)
        {
            if (c2 == cadena[cont])
                break;
            else
            {
                indice_cabe++;
            }
        }
        int indice_primerColumna = 0;
        for (const auto &c3 : l1->primerColumna)
        {
            if (pila.top() == c3)
                break;
            indice_primerColumna++;
        }
        if (pila.empty())
        {
            cout << "NO VALIDA, pila vacia, cadena no aceptada" << endl;
            cadena_valida = true;
            break;
        }
        if (cadena[cont] == pila.top() && pila.top() == "$")
        {
            cout << "ACEPTADA" << endl;
            break;
        }
      
        
        else if (cadena[cont] == pila.top())
        {
            //cout << "Sacando ya que son iguales" << endl;
            cont++;
            if (pila.empty())
            {
                cadena_valida = true;
                break;
            }
            else
                pila.pop();
        }
        else
        {
            //IMP valor en pila
            string simbolo_mayor = ">";
            valor_tabla = l1->tablaFinal[indice_primerColumna][indice_cabe]; // Obtenemos la produccion como string

            l1->corte(valor_tabla, simbolo_mayor); // Cortamos lo que va despues del simbolo "->" ya que nos interesa el resultado de lo que
            // produce
            auto sentencias = l1->split(valor_tabla, ' '); // Dividimos el string en vector<string> con separador de ' '
            reverse(sentencias.begin(), sentencias.end()); // Volteamos el vector de string resultado para añadir a la pila
            pila.pop();
            for (const auto &vtr : sentencias)
            {
               // cout << "VTR: " << vtr << endl;
                if (vtr == "ε")
                {
                    continue;
                }
                else if (vtr == "rror" || vtr.size() < 1)
                {
                    cout << "NO VALIDA" << endl;
                    cadena_valida = true;
                    break;
                }
                else if (vtr != " ")
                {
                   // cout << "metiendo en pila : " << vtr << endl;
                    pila.push(vtr);
                }
            }
        }
        prueba++;
    }
}

int main()
{
    /*

        */
    vector<vector<string>> sentencias = {

        {"(", "id", "+", "id", ")", "$"},
        {"id", "+", "id", "$"},
        {"id", "+", "id", "*", "id", "$"},
        {"id", "*", "id", "$"},
        {"id", "+", "id", "$"},
        {"(", "id", ")", "$"},
        {"(", "id", "+", "id", ")", "*", "id", "$"},
        {"id", "+", "(", "id", "*", "id", ")", "$"},
        {")", "id", "$"},
        {"(", "id", "$"},
        {"id", "+", "id", "*", "$"}};
    for (auto const &cadena : sentencias)
    {

        ingresarCadena(cadena);
    }

    // ll1->imprimeGramatica();
    return 0;
}
