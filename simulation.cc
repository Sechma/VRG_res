/*
Author: Marek Sechra
Date: 26.3.2025
File: simulation.cc
Project: VRG_RES
*/

#include "simulation.hh"

using namespace std;

bool initECS(entt::registry& registry,const Shooter& shooter,const Target& goal,const Bullet& bullet, const AngleSearchConfig& config){
    
    // Same position is not allowed
    if (shooter.pos == goal.pos) {
        throw runtime_error("Target and shooter at same position");
        
    }

    // Creation of shooter Entity and add to registry
    auto shooterEntity = registry.create();
    registry.emplace<Shooter>(shooterEntity, shooter.pos,0.0);
    
    // Creation of goal Entity and add to registry
    auto goalEntity = registry.create();
    registry.emplace<Target>(goalEntity,goal.pos);

    // Creation of the bulletEntity and add to registry
    auto bulletEntity = registry.create();
    registry.emplace<Bullet>(bulletEntity,
                            shooter.pos,
                            bullet.weight,
                            bullet.initspeed
                        );
    // Trajectory of the history Entity and add to registry                    
    auto historyEntity = registry.create();
    registry.emplace<Trajectory>(historyEntity, vector<TrajectoryPoint>());

    auto configEntity = registry.create();
    // calculation of the angle precision bassed on area bullet
    float targetDistance = glm::length(goal.pos - shooter.pos);
    float anglePrecision = calculateAnglePrecision((float)calculateBulletRadius(AREA_BULLET), targetDistance);
    
    registry.emplace<AngleSearchConfig>(configEntity, 0.0,
        90.0,
        anglePrecision,
        config.timestep
    );

    return 0;
}

TrajectoryPoint nextPosition(
    const TrajectoryPoint& current,double timestep,const Bullet bullet
){
  
    TrajectoryPoint next; //init return value
    next.time = current.time + timestep ;// append time for next steo 
    
    double speed = current.speed.length();
    glm::vec3 dragDirection = glm::normalize(current.speed) * -1.0f; // opposite to speed

    // dragForce calculation
    double dragF = 0.5 * AIR_DENSITY * speed*speed * AIR_DRAG * AREA_BULLET;
    glm::vec3 dragAcceleration = dragDirection * (float)(dragF / bullet.weight);

    // downward
    glm::vec3 gravityAcceleration = glm::vec3(0.0f, 0.0f, (float)-GRAVITY);

    // Acceleration in total
    glm::vec3 Acceleration = dragAcceleration + gravityAcceleration;
    
    // next speed of the bullet in the air
    next.speed = current.speed + Acceleration * (float)timestep;
    // next position of the bullet in the air
    next.position = current.position + (current.speed + next.speed) * 0.5f * (float)timestep;

    return next;
}
// Simulates projectile trajectory using physincs
/// source: https://www.sciencing.com/calculate-bullet-trajectory-5185428/
void simulateShot(entt::registry & registry, double timestep) {
    // Get the shooter, bullet, goal, Trajectory Entities
    auto shooterE = registry.view<Shooter>().front();
    auto bulletE = registry.view<Bullet>().front();
    auto goalE = registry.view<Target>().front();
    auto trajectoryE = registry.view<Trajectory>().front();

    // Get components
    auto& shooter = registry.get<Shooter>(shooterE); 
    auto& target = registry.get<Target>(goalE);    
    auto& bullet = registry.get<Bullet>(bulletE);
    auto& trajectory = registry.get<Trajectory>(trajectoryE);
    
    // clear for sure
    trajectory.points.clear();
    trajectory.points.reserve(51);

    // tmp variables for calculation
    glm::vec3 targetDirection = glm::normalize(target.pos - shooter.pos);
    glm::vec3 horizontalDir = targetDirection;
    horizontalDir.z = 0.0f;
    horizontalDir = glm::normalize(horizontalDir);
     // Calculate initial velocity vector (horizontal and vertical components)

    glm::vec3 initVelocity = horizontalDir * (float)(bullet.initspeed * cos(shooter.elevationAngle));
    initVelocity.z = (float)bullet.initspeed * sin(shooter.elevationAngle);
    
    // Create initial trajectory point
    TrajectoryPoint current;
    current.time = 0.0;
    current.position = shooter.pos;
    current.speed = initVelocity;
    trajectory.points.push_back(current);

    while(1) {
         // Calculate next position using physics
        current = nextPosition(current, timestep, bullet);
        
        // Manage trajectory points storage (keep last 50 points)
        if (trajectory.points.size() >= 50) {
            rotate(trajectory.points.begin(), 
                       trajectory.points.begin() + 1, 
                       trajectory.points.end());
            trajectory.points.back() = current;
        } else {
            trajectory.points.push_back(current);
        }
        // Termination 
        if (current.position.z < 0.0) break; // Hit a ground
        if (current.position.x > target.pos.x) break; // Passed target in x
        if (current.position.y > target.pos.y) break; // Passed target in y
    }
}


// Checks if bullet hit the target based on distance and bullet radius
bool isHit(const glm::vec3& bulletPos, const glm::vec3& targetPos) {
    float radius = (float)calculateBulletRadius(AREA_BULLET);
    return glm::distance(bulletPos, targetPos) <= radius;
}

// Updates the shooter's elevation angle in the ECS registry
void setShooterAngle(entt::registry& registry, float newAngle) {
    auto view = registry.view<Shooter>();
    for (auto entity : view) {
        auto& shooter = view.get<Shooter>(entity);
        shooter.elevationAngle = newAngle;
    }
}

void simulateFindAngle(entt::registry& registry) {
    auto configE = registry.view<AngleSearchConfig>().front();
    auto targetE = registry.view<Target>().front();

    // Get components
    auto& config = registry.get<AngleSearchConfig>(configE);
    auto target = registry.get<Target>(targetE);
    
    float midAngle, elevationAngle;
    // binary searching
    while(config.upBound - config.lowerBound > config.precisionAngle) {
        
        midAngle = (config.lowerBound + config.upBound) / 2.0f;
        float elevationAngle = midAngle * (M_PI / 180.0f);
        setShooterAngle(registry, elevationAngle);
        simulateShot(registry, config.timestep);

        auto trajectoryE = registry.view<Trajectory>().front();
        const auto& trajectory =registry.get<Trajectory>(trajectoryE);
        
        // Check each point in trajectory for target hit
        bool hit = false;
        for (const auto& point : trajectory.points) {
            if (isHit(point.position, target.pos)) {
                hit = true;
                 // Print detailed trajectory information (last 50 points)
                cout << "Bullet trajectory (last 50)" << endl << "-----------------" << endl;
                for (const auto& pointOut : trajectory.points) {
                    cout << fixed << setprecision(6);
                    cout << "time: " << pointOut.time << " Position: " << printVe3(pointOut.position)
                              << " Speed: " << printVe3(pointOut.speed) << endl;
                    if (isHit(pointOut.position, target.pos)) break; 
                }

                // Print successful hit results
                cout << "-----------------" << endl << "Result: " << endl;
                cout << fixed << setprecision(6);
                cout << "Target was hit at angle: " << midAngle << " degrees" << endl;
                cout << "Position: " << printVe3(point.position) << endl;
                return; // Target hit, exit the program
            }
        }
        
        // When the bullet was up to target we get smaller angle
        // Otherwise we are going to downrgade
        const auto &lastPoint = trajectory.points.back();
        if (lastPoint.position.z > target.pos.z) config.upBound = midAngle;
        else config.lowerBound = midAngle;
        
    }
    cout << "Target was not hit." << endl;
    return;
}