
#include <iostream>
#include "tile.hpp"


using namespace std;
using namespace ariel;

Tile::Tile(): resource(ResourceType::NONE), number(-1){}

// Tile::Tile(ResourceType type, int number): resource(type),adjIntersections(6, nullptr), number(number){}

Tile::Tile(int ID): resource(ResourceType::NONE), adjIntersections(6, nullptr), number(-1), id(ID){}

// Tile::~Tile(){

//     for(Intersection* intersection : this->adjIntersections){
//         delete intersection;
//     }
    
//     adjIntersections.clear();
// }

string Tile::getType(){
    return Resource(this->resource).getTypeName();
}

void Tile::setType(ResourceType type){
    if(this->resource.getType() != ResourceType::NONE){
        throw invalid_argument("Resource already set");
    }
    this->resource = Resource(type);
}

int Tile::getNumber(){
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

void Tile::setAdjIntersections(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3, Intersection* intersection4, Intersection* intersection5, Intersection* intersection6){
    this->adjIntersections[0] = intersection1;
    this->adjIntersections[1] = intersection2;
    this->adjIntersections[2] = intersection3;
    this->adjIntersections[3] = intersection4;
    this->adjIntersections[4] = intersection5;
    this->adjIntersections[5] = intersection6;
}


vector<Intersection*> Tile::getAdjIntersections(){
    return this->adjIntersections;
}

void Tile::setId(int ID){
    if(this->id != -1){
        throw invalid_argument("ID already set");
    }
    this->id = ID;
}

int Tile::getId(){
    return this->id;
}
