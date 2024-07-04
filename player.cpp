#include <iostream>
#include <stdexcept>
#include <vector>
#include "player.hpp"

using namespace std;
using namespace ariel;

Player::Player(string name) : name(name), color(Color::NONE), points(0), knights(0), myTurn(false), playedDevCardThisTurn(false),  settelmentsOnBoard(0), citiesOnBoard(0) {
    resourceCards["wood"] = 0;
    resourceCards["brick"] = 0;
    resourceCards["wheat"] = 0;
    resourceCards["sheep"] = 0;
    resourceCards["ore"] = 0;
}

// Player::~Player(){

//     // for(DevelopmentCard* devCard : developmentCards){
//     //     delete devCard;
//     // }
//     // developmentCards.clear();

//     // for(Tile* tile : tiles){
//     //     delete tile;
//     // }
//     // tiles.clear();
// }

void Player::placeSettelemnt(int intersectionID, Board& board){
    if(settelmentsOnBoard == 5){
        cout << getName() << " doesn't have anymore settelments to put on the board" << endl;
        return;
    }
    if(board.isValidPlaceForSettlement(intersectionID, this->getName()) == false){
        cout << "Invalid place for settlement" << endl;
        return;
        }

    if(board.getIsFirstRound() == true){
        board.placeSettelemnt(intersectionID, this->getName());
        addPoints(1);
        settelmentsOnBoard++;
        for(Tile* tile : board.getTilesAdjToSettlement(intersectionID)){
            if(tile == nullptr){
                continue;
            }
            if(tile->getNumber() != 7){
                addTile(tile);
            }
        }
        return;
    }
    else{
        if(getNumOfWood() < 1 || getNumOfBrick() < 1 || getNumOfWheat() < 1 || getNumOfSheep() < 1){
            cout << getName() << " doesn't have enough resources to build a settelment" << endl;
            return;
        }
        minusResourceCard("wood", 1);
        minusResourceCard("brick", 1);
        minusResourceCard("wheat", 1);
        minusResourceCard("sheep", 1);
        board.placeSettelemnt(intersectionID, this->getName());
        addPoints(1);
        settelmentsOnBoard++;
        for(Tile* tile : board.getTilesAdjToSettlement(intersectionID)){
            if(tile->getNumber() == 7 || tile == nullptr){
                continue;
            }
            addTile(tile);
        }
    }
}

void Player::placeRoad(int roadID, Board& board){

    if(board.isValidPlaceForRoad(roadID, this->getName()) == false){
        cout << "Invalid place for road" << endl;  
        return; 
    }
    if(board.getIsFirstRound() == true){
        board.placeRoad(roadID, this->getName());
        return;
    }
    else{
        if(getNumOfWood() < 1 || getNumOfBrick() < 1){
            cout << getName() << " doesn't have enough resources to build road" << endl;
            return;
        }
        minusResourceCard("wood", 1);
        minusResourceCard("brick", 1);
        board.placeRoad(roadID, this->getName());
        cout << name << " placed a road on road number " << roadID << endl;
    }
}

void Player::buildCity(int intersectionID, Board& board){
    if(citiesOnBoard == 4){
        cout << getName() << " doesn't have anymore cities" << endl;
        return;
    }
    else{
        if(getNumOfWheat() < 2 || getNumOfOre() < 3){
            cout << getName() << " doesn't have enough resources to build a city" << endl;
            return;
        }
        else{
            minusResourceCard("wheat", 2);
            minusResourceCard("ore", 3);
            board.buildCity(intersectionID, this->getName());
            settelmentsOnBoard--;
            addPoints(1);
            citiesOnBoard++;
        }
    }
}

bool Player::buyDevelopmentCard(DevelopmentCard* card){
    if(resourceCards["ore"] < 1 || resourceCards["sheep"] < 1 || resourceCards["wheat"] < 1){
        cout << getName() << " doesn't have enough resources to buy a development card" << endl;
        return false;
    }
    minusResourceCard("ore", 1);
    minusResourceCard("sheep", 1);
    minusResourceCard("wheat", 1);
    developmentCards.push_back(card);
    card->changeStatusOfTurn(true);
    return true;
}

bool Player::canPlayDevelopmentCard(CardType type){
    if (!myTurn) {
        cout << "It's not your turn." << endl;
        return false;
    }
    if(playedDevCardThisTurn && type != CardType::VICTORY_POINT){
        cout << "You already played a development card this turn." << endl;
        return false;
    }
    for (auto devCard = developmentCards.begin(); devCard != developmentCards.end(); ++devCard) {
        if ((*devCard)->getType() == type) {
            if((*devCard)->getBoughtThisTurn() == true){
                cout << "You can't play a card you just bought." << endl;
                return false;
            }
            cout << getName() <<" played a development card: " << (*devCard)->getDescription() << endl;

            // delete *devCard;  
            developmentCards.erase(devCard);
            playedDevCardThisTurn = true;
            return true;
        }
    }
    cout << "You dont have this card." << endl;
    return false;
}

void Player::printNumSettelments(){
    cout << settelmentsOnBoard << " settelments." << endl;
}

void Player::printNumCities(){
    cout <<  citiesOnBoard << " cities." << endl;
}

int Player::rollDice(){

    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int sum = dice1 + dice2;

    return sum;
}

void Player::printPoints(){
    cout << points << " points." << endl;
}

int Player::getPoints(){
    return points;
}

void Player::addPoints(int amount){
    if(amount < 0){
        throw invalid_argument("Invalid amount");
    }
    points += amount;
}

void Player::minusPoint(int amount){
    if(amount < 0){
        throw invalid_argument("Invalid amount");
    }
    if(points - amount < 0){
        throw invalid_argument("Not enough points");
    }
    points -= amount;
}

void Player::printResources() { // iterator usage - the iterator is used to iterate over the map to print the resource cards a player has
    cout << getName() << " has the following resources:" << endl;
    for (auto it = resourceCards.begin(); it != resourceCards.end(); ++it) {
        const string& resource = it->first; // resource name
        int number = it->second; // number of resources
        if (number > 0) {
            cout << number << " " << resource << endl;
        }
    }
}

void Player::endTurn(){
    playedDevCardThisTurn = false;
    for(DevelopmentCard* devCard : developmentCards){
        devCard->changeStatusOfTurn(false);
    }
    myTurn = false;
}

void Player::trade(Player* player, string resource1,  int amount1, string resource2, int amount2){
    if(!myTurn){
        throw invalid_argument("It's not your turn.");
    }
    if(player == nullptr){
        throw invalid_argument("Invalid player.");
    }
    if(player == this){
        throw invalid_argument("You can't trade with yourself.");
    }
    if(amount1 < 0 || amount2 < 0){
        cout << "Invalid amount." << endl;
        return;
    }

    if(player->resourceCards[resource1] >= amount1 && this->resourceCards[resource2] >= amount2){
        player->minusResourceCard(resource1, amount1);
        player->addResourceCard(resource2, amount2);
        minusResourceCard(resource2, amount2);
        addResourceCard(resource1, amount1);
        cout << name << " trades " << amount2 << " " << resource2 << " for "<< amount1 << " " << resource1 << " with " <<player->getName() << "." << endl;
    } else {
        cout << "Not enough resources to trade." << endl;
        return;
    }
}



string Player::getName(){
    return name;
}


void Player::addTile(Tile* tile){
    tiles.push_back(tile);
}

vector<Tile*> Player::getTiles(){
    return tiles;
}

void Player::addResourceCard(string resource, int amount){
    if(resource != "wood" && resource != "brick" && resource != "wheat" && resource != "sheep" && resource != "ore"){
        throw invalid_argument("Invalid resource");
    }
    if(resourceCards.find(resource) == resourceCards.end()){
        throw invalid_argument("Invalid resource");
    }
    if(amount <= 0){
        throw invalid_argument("Invalid amount");
    }
    resourceCards[resource] += amount;
}

void Player::minusResourceCard(string resource, int amount){
    if(resource != "wood" && resource != "brick" && resource != "wheat" && resource != "sheep" && resource != "ore"){
        throw invalid_argument("Invalid resource");
    }
    if(resourceCards.find(resource) == resourceCards.end()){
        throw invalid_argument("Invalid resource");
    }
    if(amount <= 0){
        throw invalid_argument("Invalid amount");
    }
    if(resourceCards[resource] < amount){
        throw invalid_argument("Not enough resources");
    }
    resourceCards[resource] -= amount;
}

void Player::addKnight(){
    knights++;
}

int Player::getKnights(){
    return knights;
}

void Player::printNumKnights(){
    cout << knights << " knights." << endl;
}

Color Player::getColor(){
    return color;
}

void Player::setColor(Color color){
    this->color = color;
}

string Player::colorToString(Color color){
    switch(color){
        case Color::RED:
            return "Red";
        case Color::BLUE:
            return "Blue";
        case Color::GREEN:
            return "Green";
        default:
            return "None";
    }
}

void Player::printStatus(){
    cout << getName() <<  " status:" << endl;
    printPoints();
    printNumSettelments();
    printNumCities();
    printNumKnights();
    printResources();
}

int Player::getNumOfWood(){
    return resourceCards["wood"];
}

int Player::getNumOfBrick(){
    return resourceCards["brick"];
}

int Player::getNumOfSheep(){
    return resourceCards["sheep"];
}

int Player::getNumOfWheat(){
    return resourceCards["wheat"];
}

int Player::getNumOfOre(){
    return resourceCards["ore"];
}

map<string, int> Player::getResources(){
    return resourceCards;
}

vector<DevelopmentCard*> Player::getDevelopmentCards(){
    return developmentCards;
}



