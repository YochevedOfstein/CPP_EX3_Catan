#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "board.hpp"

using namespace std;
using namespace ariel;

const int TILES = 19;
const int INTERSECTIONS = 54;
const int ROADS = 72;


Board::Board(): tiles(TILES, nullptr), intersections(INTERSECTIONS, nullptr), roads(ROADS, nullptr), theFirstRound(true){
    initBoard();
}

Board::~Board(){

    for(Tile* tile : tiles){
        delete tile;
    }
    tiles.clear();

    for(Intersection* intersection : intersections){
        delete intersection;
    }
    intersections.clear();

    for(Road* road : roads){
        delete road;
    }
    roads.clear();
}

void Board::initBoard(){
    initRoads();
    initTiles();
    initIntersections();
}

void Board::initIntersections(){

    for (size_t i = 0; i < INTERSECTIONS; ++i) {
        intersections[i] = new Intersection(i);
    }

    intersections[0]->setAdjIntersection(intersections[1], intersections[8], nullptr);
    intersections[1]->setAdjIntersection(intersections[0], intersections[2], nullptr);
    intersections[2]->setAdjIntersection(intersections[1], intersections[3], nullptr);
    intersections[3]->setAdjIntersection(intersections[2], intersections[4], nullptr);
    intersections[4]->setAdjIntersection(intersections[3], intersections[5], nullptr);
    intersections[5]->setAdjIntersection(intersections[4], intersections[6], nullptr);
    intersections[6]->setAdjIntersection(intersections[5], intersections[14], nullptr);

    intersections[0]->setAdjRoad(roads[0], roads[6], nullptr);
    intersections[1]->setAdjRoad(roads[0], roads[1], nullptr);
    intersections[2]->setAdjRoad(roads[1], roads[2], nullptr);
    intersections[3]->setAdjRoad(roads[2], roads[3], nullptr);
    intersections[4]->setAdjRoad(roads[3], roads[4], nullptr);
    intersections[5]->setAdjRoad(roads[4], roads[5], nullptr);
    intersections[6]->setAdjRoad(roads[5], roads[9], nullptr);

    intersections[0]->setAdjTile(tiles[0], nullptr, nullptr);
    intersections[1]->setAdjTile(tiles[0], nullptr, nullptr);
    intersections[2]->setAdjTile(tiles[0], tiles[1], nullptr);
    intersections[3]->setAdjTile(tiles[1], nullptr, nullptr);
    intersections[4]->setAdjTile(tiles[1], tiles[2], nullptr);
    intersections[5]->setAdjTile(tiles[2], nullptr, nullptr);
    intersections[6]->setAdjTile(tiles[2], nullptr, nullptr);

    intersections[7]->setAdjIntersection(intersections[8], intersections[17], nullptr);
    intersections[8]->setAdjIntersection(intersections[0], intersections[9], intersections[7]);
    intersections[9]->setAdjIntersection(intersections[8], intersections[10], intersections[19]);
    intersections[10]->setAdjIntersection(intersections[9], intersections[11], intersections[2]);
    intersections[11]->setAdjIntersection(intersections[10], intersections[12], intersections[21]);
    intersections[12]->setAdjIntersection(intersections[11], intersections[13], intersections[4]);
    intersections[13]->setAdjIntersection(intersections[12], intersections[14], intersections[23]);
    intersections[14]->setAdjIntersection(intersections[13], intersections[6], intersections[15]);
    intersections[15]->setAdjIntersection(intersections[14], nullptr, intersections[25]);

    intersections[7]->setAdjRoad(roads[18], roads[10], nullptr);
    intersections[8]->setAdjRoad(roads[6], roads[10], roads[11]);
    intersections[9]->setAdjRoad(roads[11], roads[12], roads[19]);
    intersections[10]->setAdjRoad(roads[12], roads[13], roads[7]);
    intersections[11]->setAdjRoad(roads[13], roads[14], roads[20]);
    intersections[12]->setAdjRoad(roads[14], roads[15], roads[8]);
    intersections[13]->setAdjRoad(roads[15], roads[16], roads[21]);
    intersections[14]->setAdjRoad(roads[16], roads[9], roads[17]);
    intersections[15]->setAdjRoad(roads[17], nullptr, roads[22]);

    intersections[7]->setAdjTile(tiles[3], nullptr, nullptr);
    intersections[8]->setAdjTile(tiles[0], tiles[3], nullptr);
    intersections[9]->setAdjTile(tiles[0], tiles[3], tiles[4]);
    intersections[10]->setAdjTile(tiles[0], tiles[1], tiles[4]);
    intersections[11]->setAdjTile(tiles[1], tiles[4], tiles[5]);
    intersections[12]->setAdjTile(tiles[1], tiles[2], tiles[5]);
    intersections[13]->setAdjTile(tiles[2], tiles[5], tiles[6]);
    intersections[14]->setAdjTile(tiles[2], tiles[6], nullptr);
    intersections[15]->setAdjTile(tiles[6], nullptr, nullptr);

    intersections[16]->setAdjIntersection(intersections[17], intersections[27], nullptr);
    intersections[17]->setAdjIntersection(intersections[7], intersections[18], intersections[16]);
    intersections[18]->setAdjIntersection(intersections[17], intersections[19], intersections[29]);
    intersections[19]->setAdjIntersection(intersections[18], intersections[9], intersections[20]);
    intersections[20]->setAdjIntersection(intersections[19], intersections[21], intersections[31]);
    intersections[21]->setAdjIntersection(intersections[20], intersections[11], intersections[22]);
    intersections[22]->setAdjIntersection(intersections[21], intersections[23], intersections[33]);
    intersections[23]->setAdjIntersection(intersections[22], intersections[13], intersections[24]);
    intersections[24]->setAdjIntersection(intersections[23], intersections[25], intersections[35]);
    intersections[25]->setAdjIntersection(intersections[24], intersections[15], intersections[26]);
    intersections[26]->setAdjIntersection(intersections[25], nullptr, intersections[37]);

    intersections[16]->setAdjRoad(roads[23], roads[33], nullptr);
    intersections[17]->setAdjRoad(roads[18], roads[23], roads[24]);
    intersections[18]->setAdjRoad(roads[24], roads[25], roads[34]);
    intersections[19]->setAdjRoad(roads[25], roads[26], roads[19]);
    intersections[20]->setAdjRoad(roads[26], roads[27], roads[35]);
    intersections[21]->setAdjRoad(roads[27], roads[28], roads[20]);
    intersections[22]->setAdjRoad(roads[28], roads[29], roads[36]);
    intersections[23]->setAdjRoad(roads[29], roads[30], roads[21]);
    intersections[24]->setAdjRoad(roads[30], roads[31], roads[37]);
    intersections[25]->setAdjRoad(roads[31], roads[32], roads[22]);
    intersections[26]->setAdjRoad(roads[32], nullptr, roads[38]);

    intersections[16]->setAdjTile(tiles[7], nullptr, nullptr);
    intersections[17]->setAdjTile(tiles[3], tiles[7], nullptr);
    intersections[18]->setAdjTile(tiles[3], tiles[7], tiles[8]);
    intersections[19]->setAdjTile(tiles[3], tiles[4], tiles[8]);
    intersections[20]->setAdjTile(tiles[4], tiles[8], tiles[9]);
    intersections[21]->setAdjTile(tiles[4], tiles[5], tiles[9]);
    intersections[22]->setAdjTile(tiles[5], tiles[9], tiles[10]);
    intersections[23]->setAdjTile(tiles[5], tiles[6], tiles[10]);
    intersections[24]->setAdjTile(tiles[6], tiles[10], tiles[11]);
    intersections[25]->setAdjTile(tiles[6], nullptr, tiles[11]);
    intersections[26]->setAdjTile(tiles[11], nullptr, nullptr);

    intersections[27]->setAdjIntersection(intersections[16], intersections[28], nullptr);
    intersections[28]->setAdjIntersection(intersections[27], intersections[29], intersections[38]);
    intersections[29]->setAdjIntersection(intersections[28], intersections[18], intersections[30]);
    intersections[30]->setAdjIntersection(intersections[29], intersections[31], intersections[40]);
    intersections[31]->setAdjIntersection(intersections[30], intersections[20], intersections[32]);
    intersections[32]->setAdjIntersection(intersections[31], intersections[33], intersections[42]);
    intersections[33]->setAdjIntersection(intersections[32], intersections[22], intersections[34]);
    intersections[34]->setAdjIntersection(intersections[33], intersections[35], intersections[44]);
    intersections[35]->setAdjIntersection(intersections[34], intersections[24], intersections[36]);
    intersections[36]->setAdjIntersection(intersections[35], intersections[37], intersections[46]);
    intersections[37]->setAdjIntersection(intersections[36], intersections[26], nullptr);

    intersections[27]->setAdjRoad(roads[39], roads[33], nullptr);
    intersections[28]->setAdjRoad(roads[39], roads[40], roads[49]);
    intersections[29]->setAdjRoad(roads[40], roads[41], roads[34]);
    intersections[30]->setAdjRoad(roads[41], roads[42], roads[50]);
    intersections[31]->setAdjRoad(roads[42], roads[43], roads[35]);
    intersections[32]->setAdjRoad(roads[43], roads[44], roads[51]);
    intersections[33]->setAdjRoad(roads[44], roads[45], roads[36]); 
    intersections[34]->setAdjRoad(roads[45], roads[46], roads[52]);
    intersections[35]->setAdjRoad(roads[46], roads[47], roads[37]);
    intersections[36]->setAdjRoad(roads[47], roads[48], roads[53]);
    intersections[37]->setAdjRoad(roads[48], nullptr, roads[38]);

    intersections[27]->setAdjTile(tiles[7], nullptr, nullptr);
    intersections[28]->setAdjTile(tiles[7], tiles[12], nullptr);
    intersections[29]->setAdjTile(tiles[7], tiles[8], tiles[12]);
    intersections[30]->setAdjTile(tiles[8], tiles[12], tiles[13]);
    intersections[31]->setAdjTile(tiles[8], tiles[9], tiles[13]);
    intersections[32]->setAdjTile(tiles[9], tiles[13], tiles[14]);
    intersections[33]->setAdjTile(tiles[9], tiles[10], tiles[14]);
    intersections[34]->setAdjTile(tiles[10], tiles[14], tiles[15]);
    intersections[35]->setAdjTile(tiles[10], tiles[11], tiles[15]);
    intersections[36]->setAdjTile(tiles[11], tiles[15], nullptr);
    intersections[37]->setAdjTile(tiles[11], nullptr, nullptr);

    intersections[38]->setAdjIntersection(intersections[28], intersections[39], nullptr);
    intersections[39]->setAdjIntersection(intersections[38], intersections[40], intersections[47]);
    intersections[40]->setAdjIntersection(intersections[39], intersections[30], intersections[41]);
    intersections[41]->setAdjIntersection(intersections[40], intersections[42], intersections[49]);
    intersections[42]->setAdjIntersection(intersections[41], intersections[32], intersections[43]);
    intersections[43]->setAdjIntersection(intersections[42], intersections[44], intersections[51]);
    intersections[44]->setAdjIntersection(intersections[43], intersections[34], intersections[45]);
    intersections[45]->setAdjIntersection(intersections[44], intersections[46], intersections[53]);
    intersections[46]->setAdjIntersection(intersections[45], intersections[36], nullptr);

    intersections[38]->setAdjRoad(roads[54], roads[49], nullptr);
    intersections[39]->setAdjRoad(roads[54], roads[55], roads[62]);
    intersections[40]->setAdjRoad(roads[55], roads[56], roads[50]);
    intersections[41]->setAdjRoad(roads[56], roads[57], roads[63]);
    intersections[42]->setAdjRoad(roads[57], roads[58], roads[51]);
    intersections[43]->setAdjRoad(roads[58], roads[59], roads[64]);
    intersections[44]->setAdjRoad(roads[59], roads[60], roads[52]);
    intersections[45]->setAdjRoad(roads[60], roads[61], roads[65]);
    intersections[46]->setAdjRoad(roads[61], nullptr, roads[53]);

    intersections[38]->setAdjTile(tiles[12], nullptr, nullptr);
    intersections[39]->setAdjTile(tiles[12], tiles[16], nullptr);
    intersections[40]->setAdjTile(tiles[12], tiles[13], tiles[16]);
    intersections[41]->setAdjTile(tiles[13], tiles[16], tiles[17]);
    intersections[42]->setAdjTile(tiles[13], tiles[14], tiles[17]);
    intersections[43]->setAdjTile(tiles[14], tiles[17], tiles[18]);
    intersections[44]->setAdjTile(tiles[14], tiles[15], tiles[18]);
    intersections[45]->setAdjTile(tiles[15], tiles[18], nullptr);
    intersections[46]->setAdjTile(tiles[15], nullptr, nullptr);

    intersections[47]->setAdjIntersection(intersections[39], intersections[48], nullptr);
    intersections[48]->setAdjIntersection(intersections[47], intersections[49], nullptr);
    intersections[49]->setAdjIntersection(intersections[48], intersections[41], intersections[50]);
    intersections[50]->setAdjIntersection(intersections[49], intersections[51], nullptr);
    intersections[51]->setAdjIntersection(intersections[50], intersections[43], intersections[52]);
    intersections[52]->setAdjIntersection(intersections[51], intersections[53], nullptr);
    intersections[53]->setAdjIntersection(intersections[52], intersections[45], nullptr);

    intersections[47]->setAdjRoad(roads[62], roads[66], nullptr);
    intersections[48]->setAdjRoad(roads[66], roads[67], nullptr);
    intersections[49]->setAdjRoad(roads[67], roads[68], roads[63]);
    intersections[50]->setAdjRoad(roads[68], roads[69], nullptr);
    intersections[51]->setAdjRoad(roads[69], roads[70], roads[64]);
    intersections[52]->setAdjRoad(roads[70], roads[71], nullptr);
    intersections[53]->setAdjRoad(roads[71], nullptr, roads[65]);

    intersections[47]->setAdjTile(tiles[16], nullptr, nullptr);
    intersections[48]->setAdjTile(tiles[16], nullptr, nullptr);
    intersections[49]->setAdjTile(tiles[16], tiles[17], nullptr);
    intersections[50]->setAdjTile(tiles[17], nullptr, nullptr);
    intersections[51]->setAdjTile(tiles[17], tiles[18], nullptr);
    intersections[52]->setAdjTile(tiles[18], nullptr, nullptr);
    intersections[53]->setAdjTile(tiles[18], nullptr, nullptr);

}


void Board::initRoads(){

    for (size_t i = 0; i < ROADS; ++i) {
        roads[i] = new Road(i);
    }

    roads[0]->addAdjIntersections(0, 1);
    roads[1]->addAdjIntersections(1, 2);
    roads[2]->addAdjIntersections(2, 3);
    roads[3]->addAdjIntersections(3, 4);
    roads[4]->addAdjIntersections(4, 5);
    roads[5]->addAdjIntersections(5, 6);

    roads[6]->addAdjIntersections(0, 8);
    roads[7]->addAdjIntersections(2, 10);
    roads[8]->addAdjIntersections(4, 12);
    roads[9]->addAdjIntersections(6, 14);

    roads[10]->addAdjIntersections(7, 8);
    roads[11]->addAdjIntersections(8, 9);
    roads[12]->addAdjIntersections(9, 10);
    roads[13]->addAdjIntersections(10, 11);
    roads[14]->addAdjIntersections(11, 12);
    roads[15]->addAdjIntersections(12, 13);
    roads[16]->addAdjIntersections(13, 14);
    roads[17]->addAdjIntersections(14, 15);

    roads[18]->addAdjIntersections(7, 17);
    roads[19]->addAdjIntersections(9, 19);  
    roads[20]->addAdjIntersections(11, 21);
    roads[21]->addAdjIntersections(13, 23);
    roads[22]->addAdjIntersections(15, 25);

    roads[23]->addAdjIntersections(16, 17);
    roads[24]->addAdjIntersections(17, 18);
    roads[25]->addAdjIntersections(18, 19);
    roads[26]->addAdjIntersections(19, 20);
    roads[27]->addAdjIntersections(20, 21);
    roads[28]->addAdjIntersections(21, 22);
    roads[29]->addAdjIntersections(22, 23);
    roads[30]->addAdjIntersections(23, 24);
    roads[31]->addAdjIntersections(24, 25);
    roads[32]->addAdjIntersections(25, 26);

    roads[33]->addAdjIntersections(16, 27);
    roads[34]->addAdjIntersections(18, 29);
    roads[35]->addAdjIntersections(20, 31);
    roads[36]->addAdjIntersections(22, 33);
    roads[37]->addAdjIntersections(24, 35);
    roads[38]->addAdjIntersections(26, 37);

    roads[39]->addAdjIntersections(27, 28);
    roads[40]->addAdjIntersections(28, 29);
    roads[41]->addAdjIntersections(29, 30);
    roads[42]->addAdjIntersections(30, 31);
    roads[43]->addAdjIntersections(31, 32);
    roads[44]->addAdjIntersections(32, 33);
    roads[45]->addAdjIntersections(33, 34);
    roads[46]->addAdjIntersections(34, 35);
    roads[47]->addAdjIntersections(35, 36);
    roads[48]->addAdjIntersections(36, 37);

    roads[49]->addAdjIntersections(28, 38);
    roads[50]->addAdjIntersections(30, 40);
    roads[51]->addAdjIntersections(32, 42);
    roads[52]->addAdjIntersections(34, 44);
    roads[53]->addAdjIntersections(36, 46);

    roads[54]->addAdjIntersections(38, 39);
    roads[55]->addAdjIntersections(39, 40);
    roads[56]->addAdjIntersections(40, 41);
    roads[57]->addAdjIntersections(41, 42);
    roads[58]->addAdjIntersections(42, 43);
    roads[59]->addAdjIntersections(43, 44);
    roads[60]->addAdjIntersections(44, 45);
    roads[61]->addAdjIntersections(45, 46);

    roads[62]->addAdjIntersections(39, 47);
    roads[63]->addAdjIntersections(41, 49);
    roads[64]->addAdjIntersections(43, 51);
    roads[65]->addAdjIntersections(45, 53);

    roads[66]->addAdjIntersections(47, 48);
    roads[67]->addAdjIntersections(48, 49);
    roads[68]->addAdjIntersections(49, 50);
    roads[69]->addAdjIntersections(50, 51);
    roads[70]->addAdjIntersections(51, 52);
    roads[71]->addAdjIntersections(52, 53);

}

void Board::initTiles(){

    for(size_t i = 0; i < TILES; i++){
        tiles[i] = new Tile(i);
    }
    
    tiles[0]->setType(ResourceType::ORE);
    tiles[1]->setType(ResourceType::SHEEP);
    tiles[2]->setType(ResourceType::WOOD);
    tiles[3]->setType(ResourceType::WHEAT);
    tiles[4]->setType(ResourceType::BRICK);
    tiles[5]->setType(ResourceType::SHEEP);
    tiles[6]->setType(ResourceType::BRICK);
    tiles[7]->setType(ResourceType::WHEAT);
    tiles[8]->setType(ResourceType::WOOD);
    tiles[9]->setType(ResourceType::DESERT);   
    tiles[10]->setType(ResourceType::WOOD);
    tiles[11]->setType(ResourceType::ORE);
    tiles[12]->setType(ResourceType::WOOD);
    tiles[13]->setType(ResourceType::ORE);
    tiles[14]->setType(ResourceType::WHEAT);
    tiles[15]->setType(ResourceType::SHEEP);
    tiles[16]->setType(ResourceType::BRICK);
    tiles[17]->setType(ResourceType::WHEAT);
    tiles[18]->setType(ResourceType::SHEEP);

    tiles[0]->setNumber(10);
    tiles[1]->setNumber(2);
    tiles[2]->setNumber(9);
    tiles[3]->setNumber(12);
    tiles[4]->setNumber(6);
    tiles[5]->setNumber(4);
    tiles[6]->setNumber(10);
    tiles[7]->setNumber(9);
    tiles[8]->setNumber(11);
    tiles[9]->setNumber(7);
    tiles[10]->setNumber(3);
    tiles[11]->setNumber(8);
    tiles[12]->setNumber(8);
    tiles[13]->setNumber(3);
    tiles[14]->setNumber(4);
    tiles[15]->setNumber(5);
    tiles[16]->setNumber(5);
    tiles[17]->setNumber(6);
    tiles[18]->setNumber(11);

    tiles[0]->addAdjIntersections(0, 1, 2, 8, 9, 10);
    tiles[1]->addAdjIntersections(2, 3, 4, 10, 11, 12);
    tiles[2]->addAdjIntersections(4, 5, 6, 12, 13, 14);
    tiles[3]->addAdjIntersections(7, 8, 9, 17, 18, 19);
    tiles[4]->addAdjIntersections(9, 10, 11, 19, 20, 21);
    tiles[5]->addAdjIntersections(11, 12, 13, 21, 22, 23);
    tiles[6]->addAdjIntersections(13, 14, 15, 23, 24, 25);
    tiles[7]->addAdjIntersections(16, 17, 18, 27, 28, 29);
    tiles[8]->addAdjIntersections(18, 19, 20, 29, 30, 31);
    tiles[9]->addAdjIntersections(20, 21, 22, 31, 32, 33);
    tiles[10]->addAdjIntersections(22, 23, 24, 33, 34, 35);
    tiles[11]->addAdjIntersections(24, 25, 26, 35, 36, 37);
    tiles[12]->addAdjIntersections(28, 29, 30, 38, 39, 40);
    tiles[13]->addAdjIntersections(30, 31, 32, 40, 41, 42);
    tiles[14]->addAdjIntersections(32, 33, 34, 42, 43, 44);
    tiles[15]->addAdjIntersections(34, 35, 36, 44, 45, 46);
    tiles[16]->addAdjIntersections(39, 40, 41, 47, 48, 49);
    tiles[17]->addAdjIntersections(41, 42, 43, 49, 50, 51);
    tiles[18]->addAdjIntersections(43, 44, 45, 51, 52, 53);


}

void Board::placeSettelemnt(int interId, string playerName){
    intersections[interId]->setOwner(playerName);
    intersections[interId]->setHasSettlement(true);

}

vector<Tile*> Board::getTilesAdjToSettlement(int interId){
    if(interId < 0 || interId >= INTERSECTIONS){
        throw invalid_argument("Invalid intersection id.");
    }
    
    vector<Tile*> theAdjtiles = intersections[interId]->getAdjTiles();
    return theAdjtiles;
}

bool Board::isValidPlaceForSettlement(int interId, string playerName){
    if(interId < 0 || interId >= INTERSECTIONS){
        cout<< "Invalid intersection id." << endl;
        return false;
    }
    if(intersections[interId]->hasOwner()){
        cout << "Can't build - This intersection already has a settlement." << endl;
        return false;
    }

    for(Intersection* neighbor : intersections[interId]->getAdjIntersections()){
        if(neighbor != nullptr && neighbor->hasOwner()){
            cout << "Can't build - Settlements cannot be placed adjacent to each other." << endl;
            return false;
        }
    }
    if(!getIsFirstRound()){
        bool hasAdjacentRoad = false;
        for (Road* road : intersections[interId]->getAdjRoads()) {
            if (road->getOwner() == playerName) {
                hasAdjacentRoad = true;
                break;
            }
        }
        if (!hasAdjacentRoad) {
            cout << "Can't build - Settlement must be connected to one of your roads." << endl;
            return false;
        }
        return true;
    }
    return true;
}

void Board::placeRoad(int roadId, string playerName){

    roads[roadId]->setOwner(playerName);
}

bool Board::isValidPlaceForRoad(int roadId, string playerName){

    if(roadId < 0 || roadId >= ROADS){
        cout<< "Invalid road id." << endl;
        return false;
    }

    if(roads[roadId]->hasOwner()){
        cout << "Can't build road- Road already has an owner." << endl;
        return false;
    }

    bool hasAdjacentSettlement = false;
    bool hasAdjacentRoad = false;

    for (int intersectionid : roads[roadId]->getAdjIntersections()) { 
        if(intersections[intersectionid] == nullptr){
            break;
        }
        if (intersections[intersectionid]->getOwner() == playerName) {
            hasAdjacentSettlement = true;
            break;
        }
        for(Road* road : intersections[intersectionid]->getAdjRoads()){
            if(road == nullptr){
                break;
            }
            if(road->getOwner() == playerName){
                hasAdjacentRoad = true;
                break;
            }
        }
       
    }
    
    if (hasAdjacentRoad == false && hasAdjacentSettlement == false) {
        cout <<"hasAdjacentRoad: " << hasAdjacentRoad << " hasAdjacentSettlement: " << hasAdjacentSettlement << endl;
        cout << "problem here" << endl;
        cout << "Can't build - road must be adjacent to another road/settlement" << endl;
        return false;
    }
    return true;
}

void Board::buildCity(int intersectionId, string playerName){
    if(intersections[intersectionId]->getOwner() != playerName){
        cout << playerName << " You don't own this intersection - can't build city." << endl;
        throw invalid_argument("You don't own this intersection.");
    }
    intersections[intersectionId]->setHasCity(true);
    intersections[intersectionId]->setHasSettlement(false);

}

vector<Road*> Board::getRoads(){
    return roads;
}

vector<Intersection*> Board::getIntersections(){
    return intersections;
}

vector<Tile*> Board::getTiles(){
    return tiles;
}

bool Board::getIsFirstRound(){
    return theFirstRound;
}

void Board::setIsFirstRound(bool status){
    theFirstRound = status;
}


