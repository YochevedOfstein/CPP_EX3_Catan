// yocheved@davidowitz.net 324460682

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
            Road(int ID);
            void setOwner(string owner);
            bool hasOwner() const;
            string getOwner() const;
            void addAdjIntersections(int intersection1, int intersection2);
            vector<int> getAdjIntersections() const;
            void setId(int ID);
            int getId() const;    

    };
}

#endif