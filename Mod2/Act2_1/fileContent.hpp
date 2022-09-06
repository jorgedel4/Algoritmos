#include <fstream>

std::string fileContent(std::string fileName){
    std::ifstream file;
    file.open(fileName);

    std::string fileContent = "";
    std::string fileLine;

    if(file.is_open()) {
        while(!file.eof()) {
            std::getline(file, fileLine);
            fileContent += fileLine;
        }
    }

    file.close();

    return fileContent;
}