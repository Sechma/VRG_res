/*
Author: Marek Sechra
Date: 26.3.2025
File: create_sim.hh
Project: VRG_RES
*/

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "structures.hh"
#include "constants.hh"

#ifndef SIMULATION_HH
#define SIMULATION_HH

void initECS(entt::registry& registry,  const PosWrap& shooter, const PosWrap& goal, const Bullet& bullet);

#endif