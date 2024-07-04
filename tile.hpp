#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
// #include "intersection.hpp"
#include "resource.hpp"

using namespace std;


namespace ariel{

    class Tile{
        
        private:
            Resource resource;
            // vector<Intersection*> adjIntersections;
            vector<int> adjIntersections;
            int number;
            int id;

        public:
            Tile();
            Tile(int ID);
            // ~Tile();
            string getType();
            void setType(ResourceType type);
            int getNumber();
            void setNumber(int number);
            void addAdjIntersections(int intersection1, int intersection2, int intersection3, int intersection4, int intersection5, int intersection6);
            vector<int> getAdjIntersections();
            // void setAdjIntersections(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3, Intersection* intersection4, Intersection* intersection5, Intersection* intersection6);
            // vector<Intersection*> getAdjIntersections();
            void setId(int ID);
            int getId();
    };
}
#endif