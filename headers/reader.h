#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class reader{
    public:
        reader();
        std::string readAsString(std::string path);
};