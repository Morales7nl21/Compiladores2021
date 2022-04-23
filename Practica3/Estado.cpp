#include <bits/stdc++.h>
#include <iostream>
#include "clases.hpp"
using namespace std;


Estado::Estado(){};
Estado::Estado(string _nombreEdo){
    this->_nombreEdo = _nombreEdo;
};
string Estado::getNombreEdo(){
    return _nombreEdo;
}
vector<pair<Estado,char>> Estado::getSigEdos(){
    return _sigEdos;
}
void Estado::setSigEdos(vector<pair<Estado,char>> & _sigEdos){
    this->_sigEdos = _sigEdos;
}