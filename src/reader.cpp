#include <reader.h>
#include <globals.h>


reader::reader(){}

std::string reader::readAsString(std::string path){
    std::ifstream file(path);
    if (!file) {
        std::cout << "Error: Shader/Fragment file does not exist or cannot be opened.\n";
        Globals::quit = true;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    return content;
}