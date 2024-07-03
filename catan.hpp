#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "developmentCard.hpp"


using namespace std;

namespace ariel{

    class Catan{

        private:
            vector<Player*> players;
            Board *board;
            bool isFirstRound;
            Player *currentPlayer;
            Player *HasLargestArmy;


        public:
            Catan(Player &p1, Player &p2, Player &p3);
            ~Catan();
            vector<DevelopmentCard*> devDeck;

            void ChooseStartingPlayer();
            void setPlayerColors();
            void firstRound(Player *player, int intersectionID1, int road1, int intersectionID2, int road2);
            void initDevDeck();

            void nextTurn();
            void playTurn(Player *player);
            void buyDevCard(Player *player);
            void checkLargestArmy();

            void playMonopolyDevCard(Player *player, string resource);
            void playYearOfPlentyDevCard(Player *player, string resource1, string resource2);
            void playRoadBuildingDevCard(Player *player, size_t road1, size_t road2);
            void playKnightDevCard(Player *player);
            void playVictoryPointDevCard(Player *player);

            Player* getCurrentPlayer();
            Board* getBoard();
            void printWinner();
            bool isThereAWinner();




            
            


    };
    
}

#endif