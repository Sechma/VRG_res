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
   Shooter shooter;
   Target goal;
   Bullet bullet;
   double speed;
   TrajectoryPoint startpoint;
   string tmp_goal, tmp_start;
   AngleSearchConfig config;


   // Parsin of the arguments
   if (argc == 11) {
      CLI::App app("VRG sim");

      app.add_option("-s, --start", tmp_start, "Coordinates of start like 'x.x y.y z.z' : ")
         ->capture_default_str();

      app.add_option("-g, --goal", tmp_goal, "Coordinates of goal like 'x.x y.y z.z' :")
         ->capture_default_str();

      app.add_option("-v, --speed", bullet.initspeed, "Speed of shot [m/s]")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      app.add_option("-w, --weight", bullet.weight, "Weight of shot")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      app.add_option("-e, --step", config.timestep, "Step size")
         ->check(CLI::PositiveNumber)
         ->capture_default_str();

      try {
         app.parse(argc,argv);
         if (!parseVec3(tmp_goal, goal.pos)) {
            std::cerr << "Wrong coordinates for goal" << std::endl;
            return 1;
        }

        if (!parseVec3(tmp_start, shooter.pos)) {
            std::cerr << "Wrong coordinates for start" << std::endl;
            return 1;  
        }

      }
      catch(const CLI::ParseError &e){
         return app.exit(e);
      }

   }
   else if(argc == 1){
      shooter.pos = readVec3FromStdin("Please enter coordinates of shooter (x.x' y.y' z.z'): ");
      goal.pos = readVec3FromStdin("Please enter coordinates of goal (x.x' y.y' z.z'): ");
      bullet.weight = readDoubleFromStdin("Please enter weight of shot: [kg] ");
      bullet.initspeed = readDoubleFromStdin("Please enter init speed of the shot: [m/s] ");
      config.timestep = readDoubleFromStdin("Please enter step value:");
   }
   else {
      cerr << "Wrong number of parametr" << endl;
      return 1;
   }
   
   // Init ECS
   entt::registry registry;
   initECS(registry,shooter,goal,bullet,config);
   // run the simulation
   try {
      simulateFindAngle(registry);
   }
   catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return -1;
  }
   return 0;
}