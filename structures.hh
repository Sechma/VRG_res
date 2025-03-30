/*
Author: Marek Sechra
Date: 26.3.2025
File: create_sim.hh
Project: VRG_RES
*/

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#ifndef structures_HH
#define structures_HH

 struct Target {
    glm::vec3 pos;
 };

 struct Shooter {
   glm::vec3 pos;
   float elevationAngle;
 };

 struct Bullet {
    glm::vec3 pos;
    double weight;
    double initspeed;
 };

 struct TrajectoryPoint {
   double time;
   glm::vec3 position;
   glm::vec3 speed;
 };

 struct Trajectory {
   std::vector<TrajectoryPoint> points;
};

  struct AngleSearchConfig {
    float lowerBound;
    float upBound;
    float precisionAngle;
    float timestep;
  };
  

 #endif