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

struct PosWrap {
    glm::vec3 pos;
 };

 struct Bullet {
    glm::vec3 pos;
    double weight;
    double speed;
    double timeStart;
    double timeEnd;
    entt::entity shooter;
 };

 #endif