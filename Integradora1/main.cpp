/* Análisis y diseño de algoritmos avanzados 
Actividad Integradora 1
Fecha: 7/9/2022
Miembros:
* Karla Sanchez Olivares         (A01730545)
* Carlos Alberto Vega Perez      (A01731416)
* Jorge Angel Delgado Morales    (A01551955)

PREGUNTAS:
PT1: 
Mostrar todas las coincidencias o 1 sola?
Los archivos code solo tienen una secuencia de caracteres?
Qué tan largos son los archivos transmission? Para evaluar cómo guardarlos.
Para la parte dos: Solo reversear string y repetir el proceso?

*/

#include <iostream>
#include <fstream>
#include "functionZ.cpp"
using namespace std;

// Complexity: O(N), where N is the size of the arrayZ
void checkMatch(vector<int> arrayZ, int patternSize) {
    bool isFound = false;
    for (int i = 0; i < arrayZ.size(); i++) {
        if (arrayZ[i] == patternSize) {
            if (!isFound) {
                cout << "true ";
                isFound = true;
            }
            cout << i << " ";
        }
    }
    if (!isFound) cout << "false" << endl;
    else cout << endl;
    return;
}

int main() {
    // Transmission files contain plaintext
    // Code files contain malware that could be in a transmission file

    /* YO SE QUE SE VE DLVG LOS INPUTS, NO ME CRITIQUEN :(*/

    ifstream trans1File, trans2File, code1File, code2File, code3File;
    trans1File.open("transmission1.txt");
    trans2File.open("transmission2.txt");
    code1File.open("mcode1.txt");
    code2File.open("mcode2.txt");
    code3File.open("mcode3.txt");

    string code1, code2, code3, trans1, trans2;
    code1File >> code1;
    code2File >> code2;
    code3File >> code3;
    trans1File >> trans1;
    trans2File >> trans2;
    // TODO: Check initialization. Seems like my compiler doesn't support it
    // https://stackoverflow.com/questions/26270691/initializing-vectors-with-variables-c
    // vector<string> trans{trans1, trans2};
    // vector<string> codes{code1, code2, code3};
    vector<string> trans, codes;
    trans.push_back(trans1);
    trans.push_back(trans2);
    codes.push_back(code1);
    codes.push_back(code2);
    codes.push_back(code3);

    // [DEBUGGING] Printing values for files and codes
    // cout << "---> FILES: " << endl;
    // cout << trans1 << endl << trans2 << endl;
    // cout << "---> CODES" << endl;
    // cout << code1 << endl << code2 << endl << code3 << endl;
    
    /*
    PT1: 
    For each transmission file, check if there is an ocurrence and 
    its initial position if true
    */
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++){
            // [DEBUGGING] Printing marker for each file and code
            cout << "=== Checking file " << i << " for match on code " << j << "===" << endl;
            cout << "file: " << trans[i] << endl;
            cout << "code: " << codes[j] << endl;
            checkMatch(functionZ(codes[j], trans[i]), codes[j].size());
        } 

    /*
    PT2: 
    For each transmission file, check if there is an ocurrence and where
    */


    /*
    PT3: 
    Initial and final position of the longest commun substring 
    within the two transmission files
    */
}