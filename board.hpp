// yocheved@davidowitz.net 324460682
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
            void placeSettlement(int intersectionId, string playerName);
            void placeRoad(int roadId, string playerName);
            void buildCity(int intersectionId, string playerName);
            bool isValidPlaceForSettlement(int intersectionId, string playerName);
            bool isValidPlaceForRoad(int roadId, string playerName);
            bool isValidFirstSettlements(string playerName, int intersection, int road);
            bool areRoadsAdj(int road1, int road2);
            vector<Tile*> getTilesAdjToSettlement(int intersectionId) const;
            vector<Road*> getRoads() const;
            vector<Intersection*> getIntersections() const;
            vector<Tile*> getTiles() const;
            bool getIsFirstRound() const;
            void setIsFirstRound(bool status);
            

    };

}

#endif