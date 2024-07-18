// yocheved@davidowitz.net 324460682

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
            Player *currentPlayer;
            Player *HasLargestArmy;


        public:
            Catan(Player &p1, Player &p2, Player &p3);
            ~Catan();
            vector<DevelopmentCard*> devDeck;
            bool isFirstRound;
            bool gameOver;

            void ChooseStartingPlayer();
            void setPlayerColors();
            void firstRound(Player *player, int intersectionID1, int road1, int intersectionID2, int road2);
            void initDevDeck();

            void nextTurn();
            void playTurn(Player *player);
            void buyDevCard(Player *player);
            void checkLargestArmy();

            void playMonopolyDevCard(Player *player, ResourceType resource);
            void playYearOfPlentyDevCard(Player *player, ResourceType resource1, ResourceType resource2);
            void playRoadBuildingDevCard(Player *player, int road1, int road2);
            void playKnightDevCard(Player *player);
            void playVictoryPointDevCard(Player *player);
            int getDevDeckSize() const;

            Player* getCurrentPlayer() const;
            Board* getBoard() const;
            void printWinner();
            bool isThereAWinner();

    };
    
}

#endif