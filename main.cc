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
#include "constants.hh"
#include "structures.hh"
#include "simulation.hh"

using namespace std;

int main(int argc, char* argv[]) 
{
   double maxDouble = numeric_limits<double>::max();
   PosWrap shooter;
   PosWrap goal;
   Bullet bullet; 
   double step;

   if (argc == 10) {
      CLI::App app("VRG sim");

      app.add_option("-s, --shooter", shooter.pos, "Shooter position (x y z)")
         ->expected(3)
         ->check(CLI::Range(0.0,maxDouble))
         ->capture_default_str();

      app.add_option("-g, --goal", goal.pos, "Goal position (x y z)")
         ->expected(3)
         ->check(CLI::Range(0.0,maxDouble))
         ->capture_default_str();

      app.add_option("-v --speed", bullet.speed, "Speed of shot [m/s]")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      app.add_option("-w, --weight", bullet.weight, "Weight of shot")
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
      shooter.pos = readVec3FromStdin("Please enter coordinates of shooter (x y z):");
      shooter.pos = readVec3FromStdin("Please enter coordinates of goal (x y z):");
      bullet.speed = readDoubleFromStdin("Please enter speed of shot:");
      bullet.weight = readDoubleFromStdin("Please enter weight of shot:");
      step = readDoubleFromStdin("Please enter step value:");
   }
   else {
      cerr << "Wrong number of parametr" << endl;
      return 1;
   }
   
   
   // Init ECS
   entt::registry registry;
   initECS(registry,shooter,goal,bullet);

   return 0;
}