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

    game.ChooseStartingPlayer();

    game.firstRound(game.getCurrentPlayer(), 29, 41, 10, 13);
    game.firstRound(game.getCurrentPlayer(), 35, 37, 19, 25);
    game.firstRound(game.getCurrentPlayer(), 40, 56, 44, 52);

    game.playTurn(game.getCurrentPlayer());

    game.getCurrentPlayer()->printResources();

    game.getCurrentPlayer()->trade(&p2, "wheat", 1, "brick", 1);

    game.buyDevCard(game.getCurrentPlayer());


    // game.getCurrentPlayer()->placeRoad(40, *board);
    // game.getCurrentPlayer()->placeSettelemnt(42, *board);
    

    game.printWinner();

    return 0;

}