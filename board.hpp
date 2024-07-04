#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "tile.hpp"
#include "intersection.hpp"
#include "road.hpp"

using namespace std;

namespace ariel{

    class Board{

        private:

            vector<Tile*> tiles;
            vector<Intersection*> intersections;
            vector<Road*> roads;
            void initBoard();
            void initRoads();
            void initIntersections();
            void initTiles();
            bool theFirstRound;

        public:

            Board();
            ~Board();
            void placeSettelemnt(int intersectionId, string playerName);
            void placeRoad(int roadId, string playerName);
            void buildCity(int intersectionId, string playerName);
            bool isValidPlaceForSettlement(int intersectionId, string playerName);
            bool isValidPlaceForRoad(int roadId, string playerName);
            vector<Tile*> getTilesAdjToSettlement(int intersectionId);
            vector<Road*> getRoads();
            vector<Intersection*> getIntersections();
            vector<Tile*> getTiles();
            bool getIsFirstRound();
            void setIsFirstRound(bool status);
            

    };

}

#endif