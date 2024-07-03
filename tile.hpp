#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "intersection.hpp"
#include "resource.hpp"

using namespace std;


namespace ariel{

    class Tile{
        
        private:
            Resource resource;
            vector<Intersection*> adjIntersections;
            int number;
            int id;

        public:
            Tile();
            Tile(int ID);
            // Tile(ResourceType type, int number);
            // ~Tile();
            string getType();
            void setType(ResourceType type);
            int getNumber();
            void setNumber(int number);
            void setAdjIntersections(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3, Intersection* intersection4, Intersection* intersection5, Intersection* intersection6);
            vector<Intersection*> getAdjIntersections();
            void setId(int ID);
            int getId();
    };
}
#endif