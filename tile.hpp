#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "resource.hpp"

using namespace std;


namespace ariel{

    class Tile{
        
        private:
            Resource resource;
            vector<int> adjIntersections;
            int number;
            int id;

        public:
            Tile();
            Tile(int ID);
            string getType();
            void setType(ResourceType type);
            int getNumber();
            void setNumber(int number);
            void addAdjIntersections(int intersection1, int intersection2, int intersection3, int intersection4, int intersection5, int intersection6);
            vector<int> getAdjIntersections();
            void setId(int ID);
            int getId();
    };
}
#endif