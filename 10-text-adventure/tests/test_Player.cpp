#define CATCH_CONFIG_MAIN // This tells Catch2 to generate main()
#include "catch_amalgamated.hpp"
#include "../include/Player.h"

TEST_CASE("Player starts with 100 health", "[player]")
{
    Player p("Aragorn");
    REQUIRE(p.getHealth() == 100);
}

TEST_CASE("Player can take and check for items", "[player]")
{
    Player p("Boromir");
    p.takeItem("shield");

    REQUIRE(p.hasItem("shield") == true);
    REQUIRE(p.hasItem("sword") == false);
}

TEST_CASE("Player can heal and take damage", "[player]")
{
    Player p("Gimli");
    p.takeDamage(30);
    REQUIRE(p.getHealth() == 70);

    p.heal(20);
    REQUIRE(p.getHealth() == 90);
}