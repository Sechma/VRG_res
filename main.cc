/*
Author: Marek Sechra
Date: 25.3.2025
File: main.cc
Project: VRG_RES
*/


#include <iostream>
#include <cstdlib>
#include <limits>

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <CLI/CLI.hpp>

#include "utils.hh"

using namespace std;

int main(int argc, char* argv[]) 
{

   // Init
   glm::vec3 shooter;
   glm::vec3 goal;
   double speed_of_shot;
   double weight_of_shot;
   double step;

   // Help variables
   double maxDouble = numeric_limits<double>::max();

   if (argc == 10) {
      /*shooter = glm::vec3(atof(argv[1]),atof(argv[2]),atof(argv[3]));
      goal = glm::vec3(atof(argv[4]),atof(argv[5]),atof(argv[6]));
      speed_of_shot = atof(argv[7]);
      weight_of_shot = atof(argv[8]);
      step = atof(argv[9]);*/

      CLI::App app("VRG sim");

      app.add_option("-s, --shooter", shooter, "Shooter position (x y z)")
         ->expected(3)
         ->check(CLI::Range(0.0,maxDouble))
         ->capture_default_str();

      app.add_option("-g, --goal", goal, "Goal position (x y z)")
         ->expected(3)
         ->check(CLI::Range(0.0,maxDouble))
         ->capture_default_str();

      app.add_option("-v --speed", speed_of_shot, "Speed of shot [m/s]")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      app.add_option("-w, --weight", weight_of_shot, "Weight of shot")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      app.add_option("-e, --step", step, "Step size")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      try {
         app.parse(argc,argv);

      }
      catch(const CLI::ParseError &e){
         return app.exit(e);
      }
   }
   else if(argc == 1){
      shooter = readVec3FromStdin("Please enter coordinates of shooter (x y z):");
      goal = readVec3FromStdin("Please enter coordinates of goal (x y z):");
      speed_of_shot = readDoubleFromStdin("Please enter speed of shot:");
      weight_of_shot = readDoubleFromStdin("Please enter weight of shot:");
      step = readDoubleFromStdin("Please enter step value:");
   }
   else {
      cerr << "Wrong number of parametr" << endl;
      return 1;
   }

   return 0;
}