#ifndef ROAD_HPP
#define ROAD_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace ariel{

    class Road{
        
        private:
            string owner;
            vector<int> adjIntersections;
            int id;

        public:
            Road();
            Road(int ID);
            void setOwner(string owner);
            bool hasOwner();
            string getOwner();
            void addAdjIntersections(int intersection1, int intersection2);
            vector<int> getAdjIntersections();
            void setId(int ID);
            int getId();    

    };
}

#endif