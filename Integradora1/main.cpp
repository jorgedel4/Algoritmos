/* Análisis y diseño de algoritmos avanzados 
Actividad Integradora 1
Fecha: 7/9/2022
Miembros:
* Karla Sanchez Olivares         (A01730545)
* Carlos Alberto Vega Perez      (A01731416)
* Jorge Angel Delgado Morales    (A01551955)

*/

#include <iostream>
#include <fstream>
#include "functionZ.h"
#include "commonSubstr.h"
using namespace std;

int main() {
    // Transmission files contain plaintext
    // Code files contain malware that could be in a transmission file

    ifstream trans1File, trans2File, code1File, code2File, code3File;
    trans1File.open("transmission1.txt");
    trans2File.open("transmission2.txt");
    code1File.open("mcode1.txt");
    code2File.open("mcode2.txt");
    code3File.open("mcode3.txt");

    string code1, code2, code3, trans1, trans2, fileLine;
    code1File >> code1;
    code2File >> code2;
    code3File >> code3;
    if(trans1File.is_open()) {
        while(!trans1File.eof()) {
            getline(trans1File, fileLine);
            trans1 += fileLine;
            trans1 += '\n';
        }
        trans1 = trans1.substr(0, trans1.size()-2);
    }
    if(trans2File.is_open()) {
        while(!trans2File.eof()) {
            getline(trans2File, fileLine);
            trans2 += fileLine;
            trans2 += '\n';
        }
        trans2 = trans2.substr(0, trans2.size()-2);
    }

    vector<string> trans, codes;
    trans.push_back(trans1);
    trans.push_back(trans2);
    codes.push_back(code1);
    codes.push_back(code2);
    codes.push_back(code3);
    
    /*
    PT1: 
    For each transmission file, check if there is an ocurrence and 
    its initial position if true
    */
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            checkMatch(functionZ(codes[j], trans[i]), codes[j].size());
        } 

    /*
    PT2: 
    For each transmission file, check if there is an ocurrence of the 
    reverse code of each mcodeX.txt and where
    */
    for (int i = 0; i < 3; i++) reverse(codes[i].begin(), codes[i].end());
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            getPosition(functionZ(codes[j], trans[i]), codes[j].size());
        } 


    /*
    PT3: 
    Initial and final position in file 1 of the longest commun substring
    within the two transmission files
    */
    pair<int, int> positions = commonSubstr(trans[0], trans[1]);
    cout << positions.first << " " << positions.second << " " << endl;

}