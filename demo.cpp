/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"


using namespace std;
using namespace ariel;

int main()
{

    Player p1("player1");
    Player p2("player2");
    Player p3("player3");

    Catan game(p1, p2, p3);
    
    game.ChooseStartingPlayer();

    game.firstRound(&p1, 29, 41, 10, 13);
    game.firstRound(&p2, 35, 37, 19, 25);
    game.firstRound(&p3, 40, 56, 44, 52);

    game.playTurn(&p1);

    p1.printResources();

    game.buyDevCard(&p1);

    p1.trade(&p2, "wheat", 1, "brick", 1);

    game.buyDevCard(&p1);

    p1.endTurn();

    game.playTurn(&p2);

    p2.printResources();

    p2.placeRoad(31, *game.getBoard());

    p2.placeSettelemnt(25, *game.getBoard());

    p2.endTurn();

    game.playTurn(&p3);

    p3.printStatus();

    p3.endTurn();

    /////////////////////////////////////////////////////next Round///////////////////////////////////////////////////////////////

    game.playTurn(&p1);

    p1.placeRoad(42, *game.getBoard());

    p1.endTurn();

    game.playTurn(&p2);

    p2.printResources();

    p2.endTurn();

    game.playTurn(&p3);

    p3.printResources();

    p3.trade(&p1, "wheat", 1, "brick", 1);

    p3.trade(&p2, "wheat", 1, "brick", 1);

    p3.endTurn();

    /////////////////////////////////////////////////////next Round///////////////////////////////////////////////////////////////

    game.playTurn(&p1);

    p1.printResources();

    p1.trade(&p2, "brick", 1, "ore", 1);

    p1.trade(&p3, "wheat", 1, "ore", 1);

    p1.printStatus();

    p1.placeSettelemnt(31, *game.getBoard());

    p1.placeRoad(42, *game.getBoard());

    p1.endTurn();

    game.playTurn(&p2);

    p2.endTurn();

    game.playTurn(&p3);

    p3.printResources();

    p3.placeRoad(57, *game.getBoard());

    p3.placeSettelemnt(42, *game.getBoard());

    game.printWinner();

    p1.placeSettelemnt(31, *game.getBoard());

    p3.endTurn();

    /////////////////////////////////////////////////////next Round///////////////////////////////////////////////////////////////

    game.playTurn(&p1);

    p1.printResources();

    p1.endTurn();

    game.playTurn(&p2);

    p2.printResources();

    p2.placeRoad(57, *game.getBoard());

    p2.trade(&p1, "wheat", 1, "ore", 1);

    p2.placeSettelemnt(25, *game.getBoard());

    p2.printStatus();

    p2.endTurn();

    game.playTurn(&p3);

    p3.printResources();

    p3.trade(&p2, "wheat", 1, "sheep", 1);

    p3.placeRoad(45, *game.getBoard());

    p3.endTurn();

    /////////////////////////////////////////////////////next Round///////////////////////////////////////////////////////////////

    game.playTurn(&p1);

    p1.printStatus();

    p1.placeRoad(14, *game.getBoard());

    p1.endTurn();

    game.playTurn(&p2);

    p2.endTurn();

    game.playTurn(&p3);

    p3.printResources();

    p3.tradeFourForOne("sheep", "wheat");

    p3.printResources();

    game.buyDevCard(&p3);

    game.playKnightDevCard(&p3);

    p3.endTurn();

    return 0;

}