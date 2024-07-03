#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "road.hpp"
#include "resource.hpp"

using namespace std;

namespace ariel{

    class Intersection{
        
        private:
            string owner;
            bool hasSettlement;
            bool hasCity;
            vector<Intersection*> adjIntersections;
            vector<Road*> adjRoads;
            int id;

        public:
            Intersection();
            Intersection(int ID);
            // ~Intersection();
            void setOwner(string owner);
            bool hasOwner();
            string getOwner();  
            void setHasSettlement(bool hasSettlement);
            bool getHasSettlement();
            void setHasCity(bool hasCity);
            bool getHasCity();
            void setAdjIntersection(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3);
            vector<Intersection*> getAdjIntersections();
            void setAdjRoad(Road* road1, Road* road2, Road* road3);
            vector<Road*> getAdjRoads();
            void setId(int ID);
            int getId();
        

    };
}
#endif