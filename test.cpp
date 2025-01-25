
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
    CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 0);
    CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 0);
    CHECK(p1.getResources()[ariel::ResourceType::WHEAT] == 0);
    CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 0);
    CHECK(p1.getResources()[ariel::ResourceType::ORE] == 0);
    CHECK(p1.getDevelopmentCards().size() == 0);
    CHECK(p1.getPoints() == 0);
    CHECK(p1.settelmentsOnBoard == 0);
    CHECK(p1.citiesOnBoard == 0);
    CHECK(p1.myTurn == false);
    CHECK(p1.playedDevCardThisTurn == false);

    p1.myTurn = true; //for the rest of the tests

    SUBCASE("Player Resource Management"){

        p1.addResourceCard(ariel::ResourceType::WOOD, 1);
        p1.addResourceCard(ariel::ResourceType::BRICK, 2);
        p1.addResourceCard(ariel::ResourceType::WHEAT, 3);
        p1.addResourceCard(ariel::ResourceType::SHEEP, 4);
        p1.addResourceCard(ariel::ResourceType::ORE, 5);

        CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 2);
        CHECK(p1.getResources()[ariel::ResourceType::WHEAT] == 3);
        CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 4);
        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 5);

        p1.minusResourceCard(ariel::ResourceType::WOOD, 1);
        p1.minusResourceCard(ariel::ResourceType::BRICK, 2);
        p1.minusResourceCard(ariel::ResourceType::WHEAT, 3);

        CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 0);
        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 0);
        CHECK(p1.getResources()[ariel::ResourceType::WHEAT] == 0);
        CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 4);
        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 5);

        CHECK_THROWS_AS(p1.minusResourceCard(ariel::ResourceType::WOOD, 1), invalid_argument);
        CHECK_THROWS_AS(p1.addResourceCard(ariel::ResourceType::WOOD, -1), invalid_argument);
        CHECK_THROWS_AS(p1.addResourceCard(ariel::ResourceType::WOOD, 0), invalid_argument);
        CHECK_THROWS_AS(p1.minusResourceCard(ariel::ResourceType::WHEAT, -3), invalid_argument);

    }

    SUBCASE("Player Development Card Management"){

        p1.addResourceCard(ariel::ResourceType::WHEAT, 1);
        p1.addResourceCard(ariel::ResourceType::SHEEP, 1);
        p1.addResourceCard(ariel::ResourceType::ORE, 1);

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

        p1.addResourceCard(ariel::ResourceType::ORE, 5);

        ariel::Player p2("Bob");

        p2.addResourceCard(ariel::ResourceType::WOOD, 1);
        p2.addResourceCard(ariel::ResourceType::BRICK, 2);
        p2.addResourceCard(ariel::ResourceType::WHEAT, 3);
        p2.addResourceCard(ariel::ResourceType::SHEEP, 4);
        p2.addResourceCard(ariel::ResourceType::ORE, 5);

        p1.trade(&p2, ariel::ResourceType::WOOD, 1, ariel::ResourceType::ORE, 1);

        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 4);
        CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 1);
        CHECK(p2.getResources()[ariel::ResourceType::ORE] == 6);
        CHECK(p2.getResources()[ariel::ResourceType::WOOD] == 0);

        CHECK_THROWS_AS(p1.trade(&p1, ariel::ResourceType::SHEEP, 1, ariel::ResourceType::ORE, 1), invalid_argument);
        CHECK_THROWS_AS(p1.trade(&p2, ariel::ResourceType::SHEEP, -2, ariel::ResourceType::ORE,1), invalid_argument);

        p1.tradeFourForOne(ariel::ResourceType::ORE, ariel::ResourceType::BRICK);

        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 0);
        CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 1);

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

        CHECK(tiles[0]->getType() == ariel::ResourceType::ORE);
        CHECK(tiles[0]->getNumber() == 10);

        CHECK(tiles[1]->getType() == ariel::ResourceType::SHEEP);
        CHECK(tiles[1]->getNumber() == 2);

        CHECK(tiles[2]->getType() == ariel::ResourceType::WOOD);
        CHECK(tiles[2]->getNumber() == 9);

        CHECK(tiles[3]->getType() == ariel::ResourceType::WHEAT);
        CHECK(tiles[3]->getNumber() == 12);

        CHECK(tiles[4]->getType() == ariel::ResourceType::BRICK);
        CHECK(tiles[4]->getNumber() == 6);

        CHECK(tiles[5]->getType() == ariel::ResourceType::SHEEP);
        CHECK(tiles[5]->getNumber() == 4);

    }

    SUBCASE("Placing settelment"){

        board.setIsFirstRound(true);


        CHECK(board.isValidPlaceForSettlement(1, "Yonatan") == true);
        board.placeSettlement(1, "Yonatan");

        CHECK(board.getIntersections()[1]->getOwner() == "Yonatan");

        CHECK_FALSE(board.isValidPlaceForSettlement(1, "Chen"));

        CHECK_FALSE(board.isValidPlaceForSettlement(2, "Chen"));

    }

    SUBCASE("Placing road"){

        board.placeSettlement(4, "Yonatan");

        CHECK(board.isValidPlaceForRoad(4, "Yonatan") == true);
        board.placeRoad(4, "Yonatan");

        CHECK(board.getRoads()[4]->getOwner() == "Yonatan");

        CHECK_FALSE(board.isValidPlaceForRoad(4, "Chen"));

        CHECK(board.isValidPlaceForRoad(3, "Yonatan") == true);

    }

    SUBCASE("Placing city"){

        
        CHECK_THROWS_AS(board.buildCity(1, "Yonatan"), invalid_argument);

        board.placeSettlement(1, "Yonatan");
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
    CHECK(t1.getType() == ariel::ResourceType::NONE);

    SUBCASE("Tile type and number"){

        ariel::Tile t2(2);

        t2.setType(ariel::ResourceType::ORE);
        t2.setNumber(10);

        CHECK(t2.getType() == ariel::ResourceType::ORE);
        CHECK(t2.getNumber() == 10);

        CHECK_THROWS_AS(t2.setNumber(1), invalid_argument);
        CHECK_THROWS_AS(t2.setType(ariel::ResourceType::BRICK), invalid_argument);

        t1.setType(ariel::ResourceType::WOOD);
        t1.setNumber(9);

        CHECK(t1.getType() == ariel::ResourceType::WOOD);
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

        newGame.firstRound(&p1, 29, 41, 10, 13);

        CHECK(newGame.getBoard()->getIntersections()[29]->getOwner() == "Charlie");
        CHECK(newGame.getBoard()->getRoads()[41]->getOwner() == "Charlie");

        CHECK(newGame.getBoard()->getIntersections()[10]->getOwner() == "Charlie");
        CHECK(newGame.getBoard()->getRoads()[13]->getOwner() == "Charlie");

        CHECK(newGame.getBoard()->getIsFirstRound() == true);

        CHECK(p1.settelmentsOnBoard == 2);
        CHECK(p1.citiesOnBoard == 0);
        CHECK(p1.getPoints() == 2);

        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 1);

        CHECK(newGame.getCurrentPlayer()->getName() == "Bob");

        newGame.firstRound(&p3, 13, 15, 42, 58);

        newGame.firstRound(&p2, 13, 15, 42, 58);

        CHECK(newGame.getBoard()->getIntersections()[13]->getOwner() == "Bob");
        CHECK(newGame.getBoard()->getRoads()[15]->getOwner() == "Bob");

        CHECK(newGame.getBoard()->getIntersections()[42]->getOwner() == "Bob");
        CHECK(newGame.getBoard()->getRoads()[58]->getOwner() == "Bob");

        CHECK(newGame.getBoard()->getIsFirstRound() == true);

        CHECK(newGame.getCurrentPlayer()->getName() == "Alice");

        CHECK(p2.getResources()[ariel::ResourceType::WHEAT] == 2);
        CHECK(p2.getResources()[ariel::ResourceType::ORE] == 1);

        CHECK_THROWS_AS(newGame.playTurn(&p3), invalid_argument);

        newGame.firstRound(&p3, 44, 60, 43, 59);

        CHECK(p3.getPoints() != 2);
        CHECK(p3.settelmentsOnBoard != 2);

        newGame.firstRound(&p3, 22, 29, 44, 52);

        CHECK(p3.getPoints() == 2);
        CHECK(p3.settelmentsOnBoard == 2);

        CHECK(p3.getResources()[ariel::ResourceType::SHEEP] == 2);
        CHECK(p3.getResources()[ariel::ResourceType::WHEAT] == 1);

        CHECK_FALSE(newGame.isFirstRound); 
    }

    SUBCASE("Adj settlements on first round"){

        newGame.firstRound(&p1, 29, 41, 10, 13);

        CHECK(p1.getResources()[ariel::ResourceType::ORE] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 1);
        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == 1);

        newGame.firstRound(&p2, 13, 15, 22, 29);

        CHECK(p2.getResources()[ariel::ResourceType::SHEEP] == 1);
        CHECK(p2.getResources()[ariel::ResourceType::WOOD] == 1);

    }

    SUBCASE("PlayTurn"){

        CHECK_THROWS_AS(newGame.playTurn(&p1), invalid_argument);

        newGame.firstRound(&p1, 29, 41, 10, 13);
        newGame.firstRound(&p2, 13, 15, 42, 58);
        newGame.firstRound(&p3, 22, 29, 44, 52);

        CHECK_FALSE(newGame.isFirstRound);

        newGame.playTurn(&p1);

        CHECK(newGame.getCurrentPlayer()->getName() != "Bob");
        CHECK(newGame.getCurrentPlayer()->getName() == "Charlie");

        p1.endTurn();

        newGame.playTurn(&p2);

        CHECK(newGame.getCurrentPlayer()->getName() == "Bob");
    }

    SUBCASE("Game progression and ending") {

        newGame.firstRound(&p1, 29, 41, 10, 13);
        newGame.firstRound(&p2, 13, 15, 42, 58);
        newGame.firstRound(&p3, 22, 29, 44, 52);

        CHECK(p1.getPoints() == 2);
        CHECK(p2.getPoints() == 2);
        CHECK(p3.getPoints() == 2);

        CHECK_FALSE(newGame.isThereAWinner());

        p1.addPoints(8);

        CHECK(newGame.isThereAWinner() == true);
        CHECK(newGame.gameOver == true);

    }
}

TEST_CASE("Catan Development Card Tests") {
    ariel::Player p1("Chen");
    ariel::Player p2("Yoav");
    ariel::Player p3("Yoni");

    ariel::Catan game(p1, p2, p3);
    game.ChooseStartingPlayer();

    game.firstRound(&p1, 10, 13, 22, 29);
    game.firstRound(&p2, 31, 43, 43, 59);
    game.firstRound(&p3, 18, 25, 35, 37);

    CHECK(p1.getResources()[ariel::ResourceType::WOOD] == 1);
    CHECK(p1.getResources()[ariel::ResourceType::SHEEP] == 1);  

    CHECK(!game.isFirstRound); 

    p1.addResourceCard(ariel::ResourceType::SHEEP, 1);
    p1.addResourceCard(ariel::ResourceType::WHEAT, 1);
    p1.addResourceCard(ariel::ResourceType::ORE, 1);

    SUBCASE("Buy Development Card") {

        game.buyDevCard(&p1);

        CHECK(p1.getDevelopmentCards().size() == 1);
        CHECK(game.getDevDeckSize() == 24);
    }

    SUBCASE("Play Knight Development Card") {

        p1.buyDevelopmentCard(new ariel::DevelopmentCard(CardType::KNIGHT));

        game.playKnightDevCard(&p1);

        CHECK(p1.getDevelopmentCards().size() == 1);

        CHECK(p1.getKnights() == 0); //can't play card when it was just boaught
        game.checkLargestArmy();

        p1.endTurn();
        game.playTurn(&p2);
        p2.endTurn();
        game.playTurn(&p3);
        p3.endTurn();
        game.playTurn(&p1);
        game.playKnightDevCard(&p1);

        CHECK(p1.getKnights() == 1);
    }

    SUBCASE("Play Victory Point Development Card") {

        p1.buyDevelopmentCard(new ariel::DevelopmentCard(CardType::VICTORY_POINT));

        CHECK(p1.getDevelopmentCards().size() == 1);

        game.playVictoryPointDevCard(&p1);

        CHECK(p1.getPoints() == 3); // 2 from initial settlements + 1 from VP card
    }

    SUBCASE("Play Road Building Development Card") {

        p1.buyDevelopmentCard(new ariel::DevelopmentCard(CardType::ROAD_BUILDING));

        CHECK(p1.getDevelopmentCards().size() == 1);

        p1.endTurn();
        game.playTurn(&p2);
        p2.endTurn();
        game.playTurn(&p3);
        p3.endTurn();
        game.playTurn(&p1);

        game.playRoadBuildingDevCard(&p1, 20, 28);

        CHECK(game.getBoard()->getRoads()[20]->getOwner() == "Chen");
        CHECK(game.getBoard()->getRoads()[28]->getOwner() == "Chen");
    }

    SUBCASE("Play Monopoly Development Card") {

        p1.buyDevelopmentCard(new ariel::DevelopmentCard(CardType::MONOPOLY));

        CHECK(p1.getDevelopmentCards().size() == 1);

        p2.addResourceCard(ariel::ResourceType::WOOD, 2);
        p3.addResourceCard(ariel::ResourceType::WOOD, 3);

        p1.endTurn();
        game.playTurn(&p2);
        p2.endTurn();
        game.playTurn(&p3);
        p3.endTurn();
        game.playTurn(&p1);

        int numwood = p1.getNumOfWood();

        int p2num = p2.getNumOfWood();
        int p3num = p3.getNumOfWood();

        game.playMonopolyDevCard(&p1, ariel::ResourceType::WOOD);

        CHECK(p1.getResources()[ariel::ResourceType::WOOD] == numwood+p2num+p3num); // from p2 + from p3 + from p1
        CHECK(p2.getResources()[ariel::ResourceType::WOOD] == 0);
        CHECK(p3.getResources()[ariel::ResourceType::WOOD] == 0);
    }

    SUBCASE("Play Year of Plenty Development Card") {

        p1.buyDevelopmentCard(new ariel::DevelopmentCard(CardType::YEAR_OF_PLENTY));

        p1.endTurn();
        game.playTurn(&p2);
        p2.endTurn();
        game.playTurn(&p3);
        p3.endTurn();
        game.playTurn(&p1);

        int numwheat = p1.getNumOfWheat();
        int numbrick = p1.getNumOfBrick();

        game.playYearOfPlentyDevCard(&p1, ariel::ResourceType::BRICK, ariel::ResourceType::WHEAT);

        CHECK(p1.getResources()[ariel::ResourceType::BRICK] == numbrick+1);
        CHECK(p1.getResources()[ariel::ResourceType::WHEAT] == numwheat+1);
    }
}

    


