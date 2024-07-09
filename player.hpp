
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "board.hpp"
#include "resource.hpp"
#include "developmentCard.hpp"
#include "resource.hpp"

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
            map<ResourceType, int> resourceCards;
            vector<DevelopmentCard*> developmentCards;
            vector<Tile*> tiles;
            int knights;

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
            int getPoints() const;
            void addPoints(int amount);
            void minusPoint(int amount);
            void printResources();
            map<ResourceType, int> getResources() const;
            void endTurn();
            void trade(Player* player, ResourceType resource1, int amount1, ResourceType resource2, int amount2); //player gives resource1 and gets resource2
            string getName() const;
            void addTile(Tile* tile);
            vector<Tile*> getTiles() const;
            void addResourceCard(ResourceType resource, int amount);
            void minusResourceCard(ResourceType resource, int amount);
            void addKnight();
            int getKnights() const;
            void printNumKnights();
            Color getColor() const;
            void setColor(Color color);
            string colorToString(Color color);
            void printStatus();
            bool buyDevelopmentCard(DevelopmentCard* card);
            bool canPlayDevelopmentCard(CardType type);
            vector<DevelopmentCard*> getDevelopmentCards() const;
            void printDevelopmentCards();
            void tradeFourForOne(ResourceType resource1, ResourceType resource2);
            int getNumOfWood();
            int getNumOfBrick();
            int getNumOfSheep();
            int getNumOfWheat();
            int getNumOfOre();


    }; 
}

#endif