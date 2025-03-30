/*
Author: Marek Sechra
Date: 25.3.2025
File: utils.hh
Project: VRG_RES
*/

#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>
#include <iomanip> 

using namespace std;

double readDoubleFromStdin(const string& inputMsg);
glm::vec3 readVec3FromStdin(const string& inputMsg);
string printVe3(const glm::vec3& v);
double calculateBulletRadius(double area);
float calculateAnglePrecision(float radius, float distance);
bool parseVec3(const std::string& str, glm::vec3& vec);
#endif