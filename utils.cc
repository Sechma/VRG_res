#include "utils.hh"
#include <stdexcept>

using namespace std;

double calculateExp(double a, double b) {
    if (a == b) {
        throw invalid_argument("Cannot devide by zero");
    }
    return (a+b) / (a-b);
}