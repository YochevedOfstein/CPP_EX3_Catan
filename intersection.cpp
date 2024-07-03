
#include <iostream>
#include "intersection.hpp"

using namespace std;
using namespace ariel;

Intersection::Intersection(): owner(""), hasSettlement(false), hasCity(false), id(-1){}

Intersection::Intersection(int ID): owner(""), hasSettlement(false), hasCity(false), adjIntersections(3, nullptr), adjRoads(3, nullptr), id(ID){}

// Intersection::~Intersection(){

//     for(Intersection* intersection : this->adjIntersections){
//         delete intersection;
//     }
//     adjIntersections.clear();

//     for(Road* road : this->adjRoads){
//         delete road;
//     }

//     adjRoads.clear();
// }

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

string Intersection::getOwner(){
    return this->owner;
}

void Intersection::setHasSettlement(bool hasSettlement){
    if(!hasOwner() && hasSettlement){
        throw invalid_argument("Cannot have a settlement without an owner");
    }
    this->hasSettlement = hasSettlement;
}

bool Intersection::getHasSettlement(){
    return this->hasSettlement;
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

bool Intersection::getHasCity(){
    return this->hasCity;
}

void Intersection::setAdjIntersection(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3){
    // if(this->adjIntersections.size() > 0){
    //     throw invalid_argument("Cannot change adjacent intersections");
    // }
    this->adjIntersections.push_back(intersection1);
    this->adjIntersections.push_back(intersection2);
    this->adjIntersections.push_back(intersection3);

}

vector<Intersection*> Intersection::getAdjIntersections(){
    return this->adjIntersections;
}

void Intersection::setAdjRoad(Road* road1, Road* road2, Road* road3){
    // if(this->adjRoads.size() > 0){
    //     throw invalid_argument("Cannot change adjacent roads");
    // }
    this->adjRoads.push_back(road1);
    this->adjRoads.push_back(road2);
    this->adjRoads.push_back(road3);
}

vector<Road*> Intersection::getAdjRoads(){
    return this->adjRoads;
}

// void Intersection::setAdjTile(Tile* tile1, Tile* tile2, Tile* tile3){
//     this->adjTiles.push_back(tile1);
//     this->adjTiles.push_back(tile2);
//     this->adjTiles.push_back(tile3);
// }

// vector<Tile*> Intersection::getAdjTiles(){
//     return this->adjTiles;
// }

void Intersection::setId(int ID){
    if(this->id != -1){
        throw invalid_argument("Cannot change id");
    }
    this->id = ID;
}

int Intersection::getId(){
    return this->id;
}

