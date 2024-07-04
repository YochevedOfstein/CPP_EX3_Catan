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

    // Board *board = game.getBoard();

    // game.ChooseStartingPlayer();

    // game.firstRound(game.getCurrentPlayer(), 29, 41, 10, 13);
    // game.firstRound(game.getCurrentPlayer(), 35, 37, 19, 25);
    // game.firstRound(game.getCurrentPlayer(), 40, 56, 44, 52);

    // game.playTurn(game.getCurrentPlayer());

    // game.getCurrentPlayer()->printResources();

    // game.getCurrentPlayer()->trade(&p2, "wheat", 1, "brick", 1);

    // game.buyDevCard(game.getCurrentPlayer());

    // game.getCurrentPlayer()->endTurn();

    // game.playTurn(game.getCurrentPlayer());

    // game.getCurrentPlayer()->printResources();


    // game.getCurrentPlayer()->placeRoad(40, *board);
    // game.getCurrentPlayer()->placeSettelemnt(42, *board);
    
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

    p1.trade(&p3, "brick", 1, "wheat", 1);


  




    game.printWinner();

    return 0;

}