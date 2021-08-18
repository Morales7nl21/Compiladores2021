#include <bits/stdc++.h>
using namespace std;

class AFD{
    private:         
        vector<string> _alfabeto;
        vector<string> _estados;
        string _edoInicial;
        string _edoFinal; 
        string _cadIdentificar; 
        map<pair<string,char>,string> _transiciones;
    public:
        AFD(vector<string> &_alfabeto, vector<string> &_estados, string _edoInicial, string edoFinal): _alfabeto(_alfabeto), _estados(_estados), _edoInicial(_edoInicial), _edoFinal(_edoFinal){
            hacerTransiciones(_estados);
        };
        void hacerTransiciones(vector<string> &);
        bool estaEnLenguaje(string &, string &, string& );
        void funcionTransicion();
        void setCadIdentificar(string &);
        void imprimeTransiciones();
        vector<string> getAlfabeto();
        vector<string> getEstados();
};
void AFD::imprimeTransiciones(){
    
    for(auto s: _transiciones){
        cout <<"( "<< s.first.first <<" , " <<s.first.second<< " )" << "= "<<  s.second << endl;
        
    }
}
void AFD::setCadIdentificar(string& _cadIdentificar){
    this->_cadIdentificar = _cadIdentificar;
}  
bool AFD::estaEnLenguaje(string &edoInicial, string &edoFinal , string &s ){
    string t;
    if(s.length()==1){
        //cout << "u"<<edoInicial<< endl;
        //cout << s[0]<< endl;
        auto ret = _transiciones.find(make_pair(edoInicial,s[0]));   
        //cout << "ret: "<< ret->second << endl;      
        if(ret->second== edoFinal){
            cout << "Si esta en el lenguaje" << endl;
        }else{
            cout << "No esta en el lenguaje" << endl;
        }
    }else{
        //Inicia en q0 y manda el primer caracter
        //cout << s << endl;
        auto ret = _transiciones.find(make_pair(edoInicial,s[0]));          
        //cout << ret->second << endl;        
        s = s.substr(1, s.size());             
        //cout << s << endl;
        estaEnLenguaje(ret->second,edoFinal,s);        
                
    }
    return true;
}  

void AFD::hacerTransiciones(vector<string> &_estados){
    
    //transiciones definidas por mí, se puede pedir datos o agilizar esto pero lo hice de la forma más rápida
    _transiciones[make_pair(_estados[0],'a')] = "q1";
    _transiciones[make_pair(_estados[0],'b')] = "q2";    
    _transiciones[make_pair(_estados[1],'a')] = "q2";
    _transiciones[make_pair(_estados[1],'b')] = "q0";
    _transiciones[make_pair(_estados[2],'a')] = "q2";
    _transiciones[make_pair(_estados[2],'b')] = "q2";

}
int main(){
    
    vector<string> alfabeto{"a", "b"},  estados{"q0", "q1", "q2"};    
    string edoInicial = "q0", edoFinal = "q0", cad_leer="ab";    
    AFD* afd = new AFD(alfabeto, estados, edoInicial, edoFinal);    
    //cout << " Indique la cadena a comprobar en la AFD "<< endl;
    //cin >> cad_leer;
    afd->setCadIdentificar(cad_leer);
    afd->imprimeTransiciones();
    afd->estaEnLenguaje(edoInicial,edoFinal,cad_leer);
    return 0;
}