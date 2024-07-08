
#include <iostream>
#include "tile.hpp"


using namespace std;
using namespace ariel;

Tile::Tile(int ID): resource(ResourceType::NONE), adjIntersections(6, -1), number(-1), id(ID){}

string Tile::getType() const{
    return Resource(this->resource).getTypeName();
}

void Tile::setType(ResourceType type){
    if(this->resource.getType() != ResourceType::NONE){
        throw invalid_argument("Resource already set");
    }
    this->resource = Resource(type);
}

int Tile::getNumber() const{
    return this->number;
}

void Tile::setNumber(int number){
    if(number < 2 || number > 12){
        throw invalid_argument("Invalid number");
    }
    if(this->number != -1){
        throw invalid_argument("Number already set");
    }
    this->number = number;
}

void Tile::addAdjIntersections(int intersection1, int intersection2, int intersection3, int intersection4, int intersection5, int intersection6){
    if(intersection1 < 0 || intersection2 < 0 || intersection3 < 0 || intersection4 < 0 || intersection5 < 0 || intersection6 < 0){
        throw invalid_argument("Intersection ID cannot be negative");
    }

    this->adjIntersections[0] = intersection1;
    this->adjIntersections[1] = intersection2;
    this->adjIntersections[2] = intersection3;
    this->adjIntersections[3] = intersection4;
    this->adjIntersections[4] = intersection5;
    this->adjIntersections[5] = intersection6;

}

vector<int> Tile::getAdjIntersections(){
    if(this->adjIntersections.empty()){
        throw invalid_argument("No adjacent intersections");
    }
    return this->adjIntersections;
}

void Tile::setId(int ID){
    if(this->id != -1){
        throw invalid_argument("ID already set");
    }
    this->id = ID;
}

int Tile::getId() const{
    return this->id;
}
