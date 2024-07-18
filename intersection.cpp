// yocheved@davidowitz.net 324460682
#include <iostream>
#include "intersection.hpp"

using namespace std;
using namespace ariel;

Intersection::Intersection(int ID): owner(""), hasSettlement(false), hasCity(false), adjIntersections(3, nullptr), adjRoads(3, nullptr), adjTiles(3, nullptr), id(ID){}

void Intersection::setOwner(string owner){
    if(hasOwner()){
        throw invalid_argument("Already has an owner");
    }
    this->owner = owner;
    this->hasSettlement = true;
}

bool Intersection::hasOwner(){
    if(this->owner == ""){
        return false;
    }
    return true;
}

string Intersection::getOwner() const{
    return this->owner;
}


void Intersection::setHasCity(bool hasCity){
    if(!hasOwner() && hasCity){
        throw invalid_argument("Cannot have a city without an owner");
    }
    if(!hasSettlement && hasCity){
        throw invalid_argument("Cannot have a city without a settlement first");
    }
    this->hasCity = hasCity;
    this->hasSettlement = false;
}

bool Intersection::getHasCity() const{
    return this->hasCity;
}

void Intersection::setAdjIntersection(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3){

    this->adjIntersections[0] = intersection1;
    this->adjIntersections[1] = intersection2;
    this->adjIntersections[2] = intersection3;

}

vector<Intersection*> Intersection::getAdjIntersections() const{
    return this->adjIntersections;
}

void Intersection::setAdjRoad(Road* road1, Road* road2, Road* road3){
    // if(this->adjRoads.size() > 0){
    //     throw invalid_argument("Cannot change adjacent roads");
    // }
    this->adjRoads[0] = road1;
    this->adjRoads[1] = road2;
    this->adjRoads[2] = road3;
}

vector<Road*> Intersection::getAdjRoads() const{
    return this->adjRoads;
}

void Intersection::setAdjTile(Tile* tile1, Tile* tile2, Tile* tile3){
    this->adjTiles[0] = tile1;
    this->adjTiles[1] = tile2;
    this->adjTiles[2] = tile3;
}

vector<Tile*> Intersection::getAdjTiles() const{
    return this->adjTiles;
}

void Intersection::setId(int ID){
    if(this->id != -1){
        throw invalid_argument("Cannot change id");
    }
    this->id = ID;
}

int Intersection::getId() const{
    return this->id;
}

