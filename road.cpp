
#include <iostream>
#include "road.hpp"

using namespace std;
using namespace ariel;

Road::Road(): owner(""), id(-1){}

Road::Road(int ID): owner(""), adjIntersections(2, -1), id(ID){}

void Road::setOwner(string newowner){
    if(hasOwner()){
        throw invalid_argument("Already has an owner");
    }
    this->owner = newowner;
}

bool Road::hasOwner(){
    return !owner.empty();
}

string Road::getOwner(){
    return this->owner;
}

void Road::addAdjIntersections(int intersection1, int intersection2){
    if(intersection1 < 0 || intersection2 < 0){
        throw invalid_argument("Intersection ID cannot be negative");
    }
    if(intersection1 == intersection2){
        throw invalid_argument("Cannot have a road between the same intersection");
    }
    if(this->adjIntersections[0] != -1 && this->adjIntersections[1] != -1){
        throw invalid_argument("Road already has two adjacent intersections");
    }
        this->adjIntersections[0] = intersection1;
        this->adjIntersections[1] = intersection2;
}

vector<int> Road::getAdjIntersections(){
    return this->adjIntersections;
}

void Road::setId(int ID){
    if(this->id != -1){
        throw invalid_argument("ID already set");
    }
    this->id = ID;
}

int Road::getId(){
    return this->id;
}

