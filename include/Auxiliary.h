#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
//using std::string; // NEW
//using std::vector; // NEW
//#include "Action.h" // NEW 
//class Simulation; // NEW


class Auxiliary{
    public:
        static std::vector<std::string> parseArguments(const std::string& line);  
        //static void execute(Simulation& simulation, const vector<string>& parsedInput);
};