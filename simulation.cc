/*
Author: Marek Sechra
Date: 26.3.2025
File: simulation.cc
Project: VRG_RES
*/

#include "simulation.hh"

void initECS(entt::registry& registry,  const PosWrap& shooter, const PosWrap& goal, const Bullet& bullet){
    
    auto shooterEntity = registry.create();
    registry.emplace<PosWrap>(shooterEntity, shooter.pos);
    

    auto goalEntity = registry.create();
    registry.emplace<PosWrap>(goalEntity,goal.pos);

    auto bulletEntity = registry.create();
    registry.emplace<Bullet>(bulletEntity,
                            bullet.pos,
                            bullet.weight,
                            bullet.speed,
                            0.0,
                            0.0,
                            shooterEntity
                        );
}