/*
Author: Marek Sechra
Date: 25.3.2025
File: utils.cc
Project: VRG_RES
*/

#include "utils.hh"

// Function to read a 3D vector from stdin
// will accept if all three values are valid and greater or zero.
glm::vec3 readVec3FromStdin(const string& inputMsg) {
    glm::vec3 vector;
    string line;

    // Keep prompting
    while(1) {
        cout << inputMsg ;

        // read a line from stdin
        getline(cin,line);

        // Stringstream for line to extract a values
        stringstream ss(line);
        

        // Try to read three values of the vector
        if (ss >> vector.x >> vector.y >> vector.z){
            // if they are bellow zero
            if (vector.x < 0 || vector.y < 0 || vector.z < 0) {
                cerr << "Invalid input, coordinates must be greater than 0";
            }
            else return vector;
        }
        else {
            cerr << "Invalid input, enter: (x y z)";
        }
    }
}

// Function to read a double value from stdin
// will accept a number if number is valid and greater than zero.
double readDoubleFromStdin(const string& inputMsg) {
    double val;

    // Keep prompting
    while(1) {
        cout << inputMsg;
        cin >> val;

        // Check if input stream is non-numeric input
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input please enter valid number" << endl;
        }
        // Check if entered value is positive
        else if (val <= 0) {
            cerr << "Invalid input, number must be greater than zero" << endl;
        }

        else {
            return val;
        }
    }
}