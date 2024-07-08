#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "developmentCard.hpp"
#include "resource.hpp"
#include "tile.hpp"
#include "road.hpp"
#include "intersection.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <string>

using namespace std;

TEST_CASE("Player class") {

    ariel::Player p1("Charlie");

    CHECK(p1.getName() == "Charlie");
    CHECK(p1.getColor() == Color::NONE);
    CHECK(p1.getResources().size() == 5);
    CHECK(p1.getResources()["wood"] == 0);
    CHECK(p1.getResources()["brick"] == 0);
    CHECK(p1.getResources()["wheat"] == 0);
    CHECK(p1.getResources()["sheep"] == 0);
    CHECK(p1.getResources()["ore"] == 0);
    CHECK(p1.getDevelopmentCards().size() == 0);
    CHECK(p1.getPoints() == 0);
    CHECK(p1.settelmentsOnBoard == 0);
    CHECK(p1.citiesOnBoard == 0);
    CHECK(p1.myTurn == false);
    CHECK(p1.playedDevCardThisTurn == false);

    p1.myTurn = true; //for the rest of the tests

    SUBCASE("Player Resource Management"){

        p1.addResourceCard("wood", 1);
        p1.addResourceCard("brick", 2);
        p1.addResourceCard("wheat", 3);
        p1.addResourceCard("sheep", 4);
        p1.addResourceCard("ore", 5);

        CHECK(p1.getResources()["wood"] == 1);
        CHECK(p1.getResources()["brick"] == 2);
        CHECK(p1.getResources()["wheat"] == 3);
        CHECK(p1.getResources()["sheep"] == 4);
        CHECK(p1.getResources()["ore"] == 5);

        p1.minusResourceCard("wood", 1);
        p1.minusResourceCard("brick", 2);
        p1.minusResourceCard("wheat", 3);

        CHECK(p1.getResources()["wood"] == 0);
        CHECK(p1.getResources()["brick"] == 0);
        CHECK(p1.getResources()["wheat"] == 0);
        CHECK(p1.getResources()["sheep"] == 4);
        CHECK(p1.getResources()["ore"] == 5);

        CHECK_THROWS_AS(p1.minusResourceCard("wood", 1), invalid_argument);
        CHECK_THROWS_AS(p1.addResourceCard("wood", -1), invalid_argument);
        CHECK_THROWS_AS(p1.addResourceCard("wood", 0), invalid_argument);
        CHECK_THROWS_AS(p1.minusResourceCard("wheat", -3), invalid_argument);
        CHECK_THROWS_AS(p1.minusResourceCard("dogs", 2), invalid_argument);

    }

    SUBCASE("Player Development Card Management"){

        p1.addResourceCard("wheat", 1);
        p1.addResourceCard("sheep", 1);
        p1.addResourceCard("ore", 1);

        ariel::DevelopmentCard dc1(CardType::KNIGHT);

        CHECK(p1.canPlayDevelopmentCard(CardType::KNIGHT) == false);
        CHECK(p1.canPlayDevelopmentCard(CardType::ROAD_BUILDING) == false);
        CHECK(p1.canPlayDevelopmentCard(CardType::MONOPOLY) == false);

        p1.buyDevelopmentCard(&dc1);

        CHECK(p1.getDevelopmentCards().size() == 1);

        CHECK(p1.canPlayDevelopmentCard(CardType::KNIGHT) == false); // can't play a knight card the same turn it was bought

        dc1.changeStatusOfTurn(false);

        CHECK(p1.canPlayDevelopmentCard(CardType::KNIGHT) == true);

        CHECK(p1.getDevelopmentCards().size() == 0);

    }

    SUBCASE("Trade resources"){

        p1.addResourceCard("ore", 5);

        ariel::Player p2("Bob");

        p2.addResourceCard("wood", 1);
        p2.addResourceCard("brick", 2);
        p2.addResourceCard("wheat", 3);
        p2.addResourceCard("sheep", 4);
        p2.addResourceCard("ore", 5);

        p1.trade(&p2, "wood", 1, "ore", 1);

        CHECK(p1.getResources()["ore"] == 4);
        CHECK(p1.getResources()["wood"] == 1);
        CHECK(p2.getResources()["ore"] == 6);
        CHECK(p2.getResources()["wood"] == 0);

        CHECK_THROWS_AS(p1.trade(&p1, "sheep", 1, "ore", 1), invalid_argument);
        CHECK_THROWS_AS(p1.trade(&p2, "sheep", -2, "ore",1), invalid_argument);

    }

    SUBCASE("Player Points Management"){

        p1.addPoints(1);
        p1.addPoints(2);

        CHECK(p1.getPoints() == 3);

        p1.minusPoint(1);

        CHECK(p1.getPoints() == 2);

        CHECK_THROWS_AS(p1.minusPoint(3), invalid_argument);
        CHECK_THROWS_AS(p1.addPoints(-1), invalid_argument);
    
    }

    SUBCASE("Player Knight Management"){

        p1.addKnight();
        p1.addKnight();
        p1.addKnight();

        CHECK(p1.getKnights() == 3);

    }

    SUBCASE("Dice"){
 
        CHECK(p1.rollDice() >= 2);
    
    }
}



TEST_CASE("Board") {

    ariel::Board board = ariel::Board();

    CHECK(board.getTiles().size() == 19);
    CHECK(board.getRoads().size() == 72);
    CHECK(board.getIntersections().size() == 54);

    SUBCASE("Board initialization"){

        auto tiles = board.getTiles();

        CHECK(tiles[0]->getType() == "ore");
        CHECK(tiles[0]->getNumber() == 10);

        CHECK(tiles[1]->getType() == "sheep");
        CHECK(tiles[1]->getNumber() == 2);

        CHECK(tiles[2]->getType() == "wood");
        CHECK(tiles[2]->getNumber() == 9);

        CHECK(tiles[3]->getType() == "wheat");
        CHECK(tiles[3]->getNumber() == 12);

        CHECK(tiles[4]->getType() == "brick");
        CHECK(tiles[4]->getNumber() == 6);

        CHECK(tiles[5]->getType() == "sheep");
        CHECK(tiles[5]->getNumber() == 4);

    }

    SUBCASE("Placing settelment"){

        board.setIsFirstRound(true);


        CHECK(board.isValidPlaceForSettlement(1, "Yonatan") == true);
        board.placeSettelemnt(1, "Yonatan");
        
        CHECK(board.getIntersections()[1]->getOwner() == "Yonatan");

        CHECK_FALSE(board.isValidPlaceForSettlement(1, "Chen"));

        CHECK_FALSE(board.isValidPlaceForSettlement(2, "Chen"));

    }

    SUBCASE("Placing road"){

        board.placeSettelemnt(4, "Yonatan");

        CHECK(board.isValidPlaceForRoad(4, "Yonatan") == true);
        board.placeRoad(4, "Yonatan");

        CHECK(board.getRoads()[4]->getOwner() == "Yonatan");

        CHECK_FALSE(board.isValidPlaceForRoad(4, "Chen"));

        CHECK(board.isValidPlaceForRoad(3, "Yonatan") == true);

    }

    SUBCASE("Placing city"){

        
        CHECK_THROWS_AS(board.buildCity(1, "Yonatan"), invalid_argument);

        board.placeSettelemnt(1, "Yonatan");
        board.buildCity(1, "Yonatan");

        CHECK(board.getIntersections()[1]->getHasCity() == true);
    } 


}

TEST_CASE("Intersection class"){

    ariel::Intersection i1(1);

    CHECK(i1.getId() == 1);
    CHECK_FALSE(i1.hasOwner());
    CHECK_FALSE(i1.getHasCity());

    SUBCASE("Intesection id"){

        ariel::Intersection i2(2);

        CHECK(i2.getId() == 2);
        CHECK_THROWS_AS(i2.setId(1), invalid_argument);
    }

    SUBCASE("Intersection owner of settlement/city"){

        ariel::Player p1("Charlie");

        i1.setOwner(p1.getName());

        CHECK(i1.hasOwner() == true);

        CHECK_THROWS_AS(i1.setOwner("Chanan"), invalid_argument);

        CHECK_FALSE(i1.getHasCity());

        ariel::Intersection i2(2);

        CHECK_THROWS_AS(i2.setHasCity(true), invalid_argument);

        i2.setOwner(p1.getName());

        i2.setHasCity(true);

        CHECK(i2.getHasCity() == true);

    }

    SUBCASE("Adjacent Intersections"){

        ariel::Intersection i2(2);
        ariel::Intersection i3(3);
        ariel::Intersection i4(4);

        i1.setAdjIntersection(&i2, &i3, &i4);

        CHECK(i1.getAdjIntersections()[0]->getId() == i2.getId());
        CHECK(i1.getAdjIntersections()[1]->getId() == i3.getId());
        CHECK(i1.getAdjIntersections()[2]->getId() == i4.getId());

    }

    SUBCASE("Adjacent Roads"){

        ariel::Road r1(1);
        ariel::Road r2(2);
        ariel::Road r3(3);

        i1.setAdjRoad(&r1, &r2, &r3);

        auto adjRoads = i1.getAdjRoads();

        CHECK(adjRoads[0]->getId() == r1.getId());
        CHECK(adjRoads[1]->getId() == r2.getId());
        CHECK(adjRoads[2]->getId() == r3.getId());
    }

    SUBCASE("Adjacent Tiles"){

        ariel::Tile t1(1);
        ariel::Tile t2(2);
        ariel::Tile t3(3);

        i1.setAdjTile(&t1, &t2, &t3);

        auto adjTiles = i1.getAdjTiles();

        CHECK(adjTiles[0]->getId() == t1.getId());
        CHECK(adjTiles[1]->getId() == t2.getId());
        CHECK(adjTiles[2]->getId() == t3.getId());

    }

}

TEST_CASE("Road class"){
        
        ariel::Road r1(1);
    
        CHECK(r1.getId() == 1);
        CHECK_FALSE(r1.hasOwner());

        SUBCASE("Road id"){
    
            ariel::Road r2(2);
    
            CHECK(r2.getId() == 2);
    
            CHECK_THROWS_AS(r2.setId(1), invalid_argument);
    
        }
    
        SUBCASE("Road owner"){
    
            ariel::Player p1("Charlie");
    
            r1.setOwner(p1.getName());
    
            CHECK(r1.hasOwner() == true);
    
            CHECK_THROWS_AS(r1.setOwner("Chanan"), invalid_argument);
    
        }
    
        SUBCASE("Adjacent Intersections"){

            CHECK_THROWS_AS(r1.addAdjIntersections(-2, 7), invalid_argument);
    
            ariel::Intersection i1(1);
            ariel::Intersection i2(2);

            int ID1 = i1.getId();
            int ID2 = i2.getId();
    
            r1.addAdjIntersections(ID1, ID2);
    
            CHECK(r1.getAdjIntersections()[0] == ID1);
            CHECK(r1.getAdjIntersections()[1] == ID2);
    
            ariel::Intersection i3(3);
            ariel::Intersection i4(4);
    
            CHECK_THROWS_AS(r1.addAdjIntersections(i3.getId(), i4.getId()), invalid_argument);
    
        }
}

TEST_CASE("Tile class"){

    ariel::Tile t1(1);

    CHECK(t1.getId() == 1);
    CHECK(t1.getType() == "None");

    SUBCASE("Tile type and number"){

        ariel::Tile t2(2);

        t2.setType(ariel::ResourceType::ORE);
        t2.setNumber(10);

        CHECK(t2.getType() == "ore");
        CHECK(t2.getNumber() == 10);

        CHECK_THROWS_AS(t2.setNumber(1), invalid_argument);
        CHECK_THROWS_AS(t2.setType(ariel::ResourceType::NONE), invalid_argument);

        t1.setType(ariel::ResourceType::WOOD);
        t1.setNumber(9);

        CHECK(t1.getType() == "wood");
        CHECK(t1.getNumber() == 9);
    }

    SUBCASE("Tile adjacent Intersections"){

        ariel::Intersection i1(1);
        ariel::Intersection i2(2);
        ariel::Intersection i3(3);
        ariel::Intersection i4(4);
        ariel::Intersection i5(5);
        ariel::Intersection i6(6);

        t1.addAdjIntersections(1, 2, 3, 4, 5, 6);

        vector<int> testadjIntersections = {1, 2, 3, 4, 5, 6};

        auto adjIntersections = t1.getAdjIntersections();

        CHECK(testadjIntersections.size() == adjIntersections.size());
        CHECK(testadjIntersections == adjIntersections);

        CHECK(adjIntersections[0] == i1.getId());
        CHECK(adjIntersections[1] == i2.getId());
        CHECK(adjIntersections[2] == i3.getId());
        CHECK(adjIntersections[3] == i4.getId());
        CHECK(adjIntersections[4] == i5.getId());
        CHECK(adjIntersections[5] == i6.getId());
    }
}

TEST_CASE("Development Card class"){

    ariel::DevelopmentCard dc1(CardType::KNIGHT);

    CHECK(dc1.getType() == CardType::KNIGHT);
    CHECK_FALSE(dc1.getBoughtThisTurn());


    SUBCASE("Development Card bought this turn"){

        dc1.changeStatusOfTurn(true);

        CHECK(dc1.getBoughtThisTurn() == true);

        dc1.changeStatusOfTurn(false);

        CHECK(dc1.getBoughtThisTurn() == false);

    }

}

TEST_CASE("Catan class"){

    ariel::Player p1("Charlie");
    ariel::Player p2("Bob");
    ariel::Player p3("Alice");
        
    ariel::Catan newGame(p1, p2, p3);

    CHECK(newGame.getBoard() != nullptr);
    CHECK(newGame.getBoard()->getTiles().size() == 19);
    CHECK(newGame.getBoard()->getRoads().size() == 72);
    CHECK(newGame.getBoard()->getIntersections().size() == 54);

    CHECK(newGame.getBoard()->getIsFirstRound() == true);
    CHECK(newGame.isFirstRound == true);

    newGame.ChooseStartingPlayer();

    CHECK(newGame.getCurrentPlayer()->getName() == "Charlie");

    SUBCASE("First round"){

        newGame.firstRound(&p1, 13, 13, 42, 48);

        // CHECK(p1.settelmentsOnBoard == 2);
        // CHECK(p1.getPoints() == 2);

        // CHECK(p1.getResources()["wood"] == 0);
        // CHECK(p1.getResources()["brick"] == 0);
        // CHECK(p1.getResources()["wheat"] == 2);
        // CHECK(p1.getResources()["sheep"] == 0);
        // CHECK(p1.getResources()["ore"] == 1);

        // CHECK(newGame.getCurrentPlayer()->getName() == "Bob");

        // newGame.firstRound(&p2, 14, 14, 49, 34);

        
    }
    
}

    


