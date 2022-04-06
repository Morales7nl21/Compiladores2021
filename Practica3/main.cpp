#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#include "analizadorLexico.hpp"
vector<string> palReservadas = {"repeat", "Init", "End", "Add", "+", "-", "*",
                                "/", "notTrue", "True", "False", "declare",
                                "AsNumber", "AsFloat", "AsChar", "Array", "len",
                                "()", "End"};

vector<char> A = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
vector<char> B = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector<int> C = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
vector<char> D = {'/', '*', '+', '-', '{', '}', '(', ')', '<', '>', '.', ':'};
vector<char> E = {' ', '\n', '\t', '\r'};
char F = '_';
void analiza();
int main(int argc, char const *argv[])
{
    analiza();
    return 0;
}
