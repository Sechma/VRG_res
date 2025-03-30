/*
Author: Marek Sechra
Date: 26.3.2025
File: create_sim.hh
Project: VRG_RES
*/

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <iomanip> 

#include "structures.hh"
#include "constants.hh"
#include "utils.hh"

#include <cmath> 

#ifndef SIMULATION_HH
#define SIMULATION_HH

bool initECS(entt::registry& registry,  const Shooter& shooter, const Target& goal, const Bullet& bullet,const AngleSearchConfig& config);

TrajectoryPoint nextPosition(const TrajectoryPoint& current,double timestep,const Bullet bullet);
bool isHit(const glm::vec3& bulletPos, const glm::vec3& targetPos);
void simulateShot(entt::registry & registry, double timestep);
void setShooterAngle(entt::registry& registry, float newAngle);
void simulateFindAngle(entt::registry& registry);
#endif