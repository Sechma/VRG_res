/*
Author: Marek Sechra
Date: 25.3.2025
File: main.cc
Project: VRG_RES
*/


#include <iostream>
#include <cstdlib>
#include <entt/entt.hpp>

#include "utils.hh"

using namespace std;

int main(int argc, char* argv[]) 
{

    double a = 10.2;
    double b = 5.3;
    try {
        double res = calculateExp(a,b);
        cout << "Res:" << res << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}