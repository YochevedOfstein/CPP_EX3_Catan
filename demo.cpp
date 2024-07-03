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

    game.firstRound(game.getCurrentPlayer(), 29, 41, 10, 13);
    game.firstRound(game.getCurrentPlayer(), 35, 37, 19, 25);
    game.firstRound(game.getCurrentPlayer(), 40, 56, 44, 52);

    // if(game.getCurrentPlayer() == &p1){
    //     game.firstRound(&p1, 0, 0, 1, 1);
    // }
    // else if(game.getCurrentPlayer() == &p2){
    //     game.firstRound(&p2, 0, 0, 1, 1);
    // }
    // else{
    //     game.firstRound(&p3, 0, 0, 1, 1);
    // }

    // game.printWinner();

    return 0;

}