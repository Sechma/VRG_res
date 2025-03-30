/*
Author: Marek Sechra
Date: 30.3.2025
File: tests.cc
Project: VRG_RES
*/


#include <iostream>
#include <sstream>
#include <catch2/catch_all.hpp>
#include "structures.hh"
#include "simulation.hh"


TEST_CASE("ECS Initialization", "[ecs]") {
    entt::registry registry;
    Shooter shooter{{0, 0, 0}};
    Target goal{{100, 0, 0}};
    Bullet bullet{{0, 0, 0}, 0.01, 300};
    AngleSearchConfig config{0, 90, 0.1f, 0.0001f};

    SECTION("Correct component creation") {
        initECS(registry, shooter, goal, bullet, config);
        
        REQUIRE_FALSE(registry.view<Shooter>().empty());
        REQUIRE_FALSE(registry.view<Target>().empty());
        REQUIRE_FALSE(registry.view<Bullet>().empty());
        REQUIRE_FALSE(registry.view<Trajectory>().empty());
        REQUIRE_FALSE(registry.view<AngleSearchConfig>().empty());
    }
}

TEST_CASE("Trajectory Simulation", "[simulation]") {
    entt::registry registry;
    Shooter shooter{{1.0, 1.0, 1.0}};
    Target goal{{100.0, 1.0, 1.0}};
    Bullet bullet{{100.0, 1.0, 1.00}, 0.01, 300};
    AngleSearchConfig config{0, 90, 0.1f, 0.01f}; 
    
    initECS(registry, shooter, goal, bullet, config);
    
    SECTION("Basic trajectory generation") {
        setShooterAngle(registry, glm::radians(45.0f));
        simulateShot(registry, 0.01f);
        
        const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
        
        REQUIRE(trajectory.points.size() > 1);
        REQUIRE(trajectory.points.front().position == shooter.pos);
    }
    
    SECTION("Angle search finds valid solution") {
        simulateFindAngle(registry);
        const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
        const auto& target = registry.get<Target>(registry.view<Target>().front());
        bool hit = false;
        
        for (const auto& point : trajectory.points) {
            if (isHit(point.position, target.pos)) {
                hit = true;
                break;
            }
        }
        REQUIRE(hit);
    }
}

TEST_CASE("Trajectory Simulation - Edge Cases", "[simulation][edge]") {
    // Test case for zero distance
    SECTION("Shooter and target at same position - should throw exception") {
        entt::registry registry;
        Shooter shooter{{1.0, 1.0, 1.0}};
        Target goal{{1.0, 1.0, 1.0}};  // Same position
        Bullet bullet{{1.0, 1.0, 1.0}, 0.01, 300};
        AngleSearchConfig config{0, 90, 0.1f, 0.01f};
        
        REQUIRE_THROWS_MATCHES(
            [&]() {
                initECS(registry, shooter, goal, bullet, config);
            }(),
            std::runtime_error,
            Catch::Matchers::Message("Target and shooter at same position")
        );
    }
    
    // Extreme angle cases
    SECTION("Extreme elevation angles") {
        entt::registry registry;
        Shooter shooter{{0, 0, 0}};
        Target goal{{100, 0, 0}};
        Bullet bullet{{0, 0, 0}, 0.01, 300};
        AngleSearchConfig config{0, 90, 0.1f, 0.01f};
        initECS(registry, shooter, goal, bullet, config);

        SECTION("90 degree shot (straight up)") {
            setShooterAngle(registry, glm::radians(90.0f));
            REQUIRE_NOTHROW(simulateShot(registry, 0.01f));
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.back().position.z <= 0.0f); // Should return to ground
        }

        SECTION("0 degree shot (flat)") {
            setShooterAngle(registry, glm::radians(0.0f));
            REQUIRE_NOTHROW(simulateShot(registry, 0.01f));
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.back().position.z <= 0.0f); // Should hit ground
            REQUIRE(trajectory.points.back().position.x > shooter.pos.x); // Should move forward
        }

        SECTION("Negative angle shot") {
            setShooterAngle(registry, glm::radians(-10.0f)); // Aiming downward
            REQUIRE_NOTHROW(simulateShot(registry, 0.01f));
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.size() > 1);
            REQUIRE(trajectory.points.back().position.z <= shooter.pos.z); // Should go down
        }
    }

    // Extreme distance cases
    SECTION("Extreme distance scenarios") {
        entt::registry registry;
        Shooter shooter{{0, 0, 0}};
        Target goal{{10000, 0, 0}}; 
        Bullet bullet{{0, 0, 0}, 0.01, 300};
        AngleSearchConfig config{0, 90, 0.1f, 0.01f};
        initECS(registry, shooter, goal, bullet, config);

        SECTION("Long distance simulation") {
            setShooterAngle(registry, glm::radians(45.0f));
            REQUIRE_NOTHROW(simulateShot(registry, 0.01f));
            
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.back().position.z <= 0.0f);
            REQUIRE(trajectory.points.back().position.x > shooter.pos.x);
        }
    }

     // Extreme clsoe cases
     SECTION("Extreme distance scenarios") {
        entt::registry registry;
        Shooter shooter{{1.0, 1.0, 1.0}};
        Target goal{{1.00001, 1.0, 1.0}}; 
        Bullet bullet{{0, 0, 0}, 0.01, 300};
        AngleSearchConfig config{0, 90, 0.1f, 0.01f};
        initECS(registry, shooter, goal, bullet, config);

        SECTION("Long distance simulation") {
            setShooterAngle(registry, glm::radians(0.0f));
            REQUIRE_NOTHROW(simulateShot(registry, 0.01f));
            
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.back().position.z <= 1.0f);
            REQUIRE(trajectory.points.back().position.x > shooter.pos.x);
        }
    }

    // Memory overflow
    SECTION("Extreme small step") {
        entt::registry registry;
        Shooter shooter{{10.0, 10.0, 1.0}};
        Target goal{{11.0, 20.0, 40.0}}; 
        Bullet bullet{{0, 0, 0}, 0.01, 300};
        AngleSearchConfig config{0, 90, 0.1f, 0.0000001f};
        initECS(registry, shooter, goal, bullet, config);

        SECTION("Small step simulation") {
            setShooterAngle(registry, glm::radians(0.703125f));
            REQUIRE_NOTHROW(simulateShot(registry, 0.00000001f));
            
            const auto& trajectory = registry.get<Trajectory>(registry.view<Trajectory>().front());
            REQUIRE(trajectory.points.back().position.z <= 40.0f);
            REQUIRE(trajectory.points.back().position.x >= shooter.pos.x);
        }
    }
}