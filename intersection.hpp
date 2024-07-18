// yocheved@davidowitz.net 324460682
#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "road.hpp"
#include "resource.hpp"
#include "tile.hpp"


using namespace std;

namespace ariel{

    class Intersection{
        
        private:
            string owner;
            bool hasSettlement;
            bool hasCity;
            vector<Intersection*> adjIntersections;
            vector<Road*> adjRoads;
            vector<Tile*> adjTiles;
            int id;

        public:
            Intersection(int ID);
            void setOwner(string owner);
            bool hasOwner();
            string getOwner() const;  
            void setHasCity(bool hasCity);
            bool getHasCity() const;
            void setAdjIntersection(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3);
            vector<Intersection*> getAdjIntersections() const;
            void setAdjRoad(Road* road1, Road* road2, Road* road3);
            vector<Road*> getAdjRoads() const;
            void setAdjTile(Tile* tile1, Tile* tile2, Tile* tile3);
            vector<Tile*> getAdjTiles() const;
            void setId(int ID);
            int getId() const;
        

    };
}
#endif