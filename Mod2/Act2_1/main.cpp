// Análisis y diseño de algoritmos avanzados 
// Actividad 2.1 Implementación de "Hash String" 
// Fecha: 5/9/2022
// Miembros:
// * Karla Sanchez Olivares         (A01730545)
// * Carlos Alberto Vega Perez      (A01731416)
// * Jorge Angel Delgado Morales    (A01551955)

#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

int main() {
    std::string fileName, fileText;
    int nColumns;

    std::getline(std::cin, fileText);
    std::cin >> nColumns;

    // transformar contenido de txt a un string
    //fileText = fileContent(fileName, fileText, nColumns);

    // numero de caracteres en el string
    size_t nChars = fileText.length();
    // numero de filas que se crearán
    int nRows = ceil(nChars / (float)nColumns);
    // matriz donde se almacenarán los caracteres
    char matrix[nRows][nColumns];

    // indice actual del contenido del string
    int curChar = 0;
    for(int i = 0; i < nRows; ++i)
        for(int j = 0; j < nColumns; ++j)
            // si ya se usaron todos los chars del string, llenar con el n dado por el usuario
            matrix[i][j] = curChar < nChars ? fileText[curChar++] : nColumns;

    std::string hexString = "";
    int columnSum;

    // recorrer columnas
    for(int j = 0; j < nColumns; ++j) {
        columnSum = 0;
        // obtener suma de la columna
        for(int i = 0; i < nRows; ++i)
            columnSum += matrix[i][j];

        columnSum %= 256;

        // transformar suma a hexadecimal
        std::ostringstream ss;
        ss << std::hex << columnSum;
        std::string result = ss.str();

        // agregar 0 en caso de que solo se tenga un digito
        if(result.length() == 1)
            result = "0" + result;
        // concatenar con el string del output
        hexString += result;
    }

    // la funcion usada para transformar a hexadecimal regresa strings en lowercase
    // pasar string a mayusculas
    for(int i = 0; i < hexString.length(); ++i) 
        hexString[i] = toupper(hexString[i]);
    
    std::cout << hexString << std::endl;
    return 0;
}