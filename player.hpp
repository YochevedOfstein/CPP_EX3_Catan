
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "board.hpp"
#include "resource.hpp"
#include "developmentCard.hpp"

using namespace std;

enum class Color{
    NONE,
    RED,
    BLUE,
    GREEN
};

namespace ariel{

    class Player{

        private:

            string name;
            Color color;
            int points;
            map<string, int> resourceCards;
            vector<DevelopmentCard*> developmentCards;
            vector<Tile*> tiles;
            int knights;
            int getNumOfWood();
            int getNumOfBrick();
            int getNumOfSheep();
            int getNumOfWheat();
            int getNumOfOre();


        public:
            Player(const string name);
            bool myTurn;
            bool playedDevCardThisTurn;
            int settelmentsOnBoard;
            int citiesOnBoard;
            void placeSettelemnt(int intersectionID, Board& board);
            void placeRoad(int roadID, Board& board);
            void buildCity(int intersectionID, Board& board);
            void printNumSettelments();
            void printNumCities();
            int rollDice();
            void printPoints();
            int getPoints();
            void addPoints(int amount);
            void minusPoint(int amount);
            void printResources();
            map<string, int> getResources();
            void endTurn();
            void trade(Player* player, string resource1, int amount1, string resource2, int amount2); //player gives resource1 and gets resource2
            string getName();
            void addTile(Tile* tile);
            vector<Tile*> getTiles();
            void addResourceCard(string resource, int amount);
            void minusResourceCard(string resource, int amount);
            void addKnight();
            int getKnights();
            void printNumKnights();
            Color getColor();
            void setColor(Color color);
            string colorToString(Color color);
            void printStatus();
            bool buyDevelopmentCard(DevelopmentCard* card);
            bool canPlayDevelopmentCard(CardType type);
            vector<DevelopmentCard*> getDevelopmentCards();
            void printDevelopmentCards();
            void tradeFourForOne(string resource1, string resource2);


    }; 
}

#endif