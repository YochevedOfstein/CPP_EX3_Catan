#include <iostream>
#include <stdexcept>
#include <vector>
#include "player.hpp"

using namespace std;
using namespace ariel;

Player::Player(string name) : name(name), color(Color::NONE), points(0), knights(0), myTurn(false), playedDevCardThisTurn(false),  settelmentsOnBoard(0), citiesOnBoard(0) {
    resourceCards[ResourceType::WOOD] = 0;
    resourceCards[ResourceType::BRICK] = 0;
    resourceCards[ResourceType::WHEAT] = 0;
    resourceCards[ResourceType::SHEEP] = 0;
    resourceCards[ResourceType::ORE] = 0;
}

void Player::placeSettelemnt(int intersectionID, Board& board){
    if(!myTurn){
        cout << getName() << " It's not your turn." << endl;
        return;
    }
    if(settelmentsOnBoard == 5){
        cout << getName() << " doesn't have anymore settelments to put on the board" << endl;
        return;
    }
    if(board.isValidPlaceForSettlement(intersectionID, this->getName()) == false){
        return;
        }

    if(board.getIsFirstRound() == true){
        board.placeSettlement(intersectionID, this->getName());
        addPoints(1);
        settelmentsOnBoard++;
        for(Tile* tile : board.getTilesAdjToSettlement(intersectionID)){
            if(tile == nullptr || tile->getNumber() == 7){
                break;
            }
            addTile(tile);
        }
        return;
    }
    else{
        if(getNumOfWood() < 1 || getNumOfBrick() < 1 || getNumOfWheat() < 1 || getNumOfSheep() < 1){
            cout << getName() << " doesn't have enough resources to build a settelment" << endl;
            return;
        }
        minusResourceCard(ResourceType::WOOD, 1);
        minusResourceCard(ResourceType::BRICK, 1);
        minusResourceCard(ResourceType::WHEAT, 1);
        minusResourceCard(ResourceType::SHEEP, 1);
        board.placeSettlement(intersectionID, this->getName());
        addPoints(1);
        settelmentsOnBoard++;
        cout << name << " placed a settelment on intersection number " << intersectionID << endl;
        for(Tile* tile : board.getTilesAdjToSettlement(intersectionID)){
            if(tile == nullptr || tile->getNumber() == 7){
                break;
            }
            addTile(tile);
        }
    }
}

void Player::placeRoad(int roadID, Board& board){

    if(!myTurn){
        cout << getName() << " It's not your turn." << endl;
        return;
    }
    if(board.isValidPlaceForRoad(roadID, this->getName()) == false){
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
        minusResourceCard(ResourceType::WOOD, 1);
        minusResourceCard(ResourceType::BRICK, 1);
        board.placeRoad(roadID, this->getName());
        cout << name << " placed a road on road number " << roadID << endl;
    }
}

void Player::buildCity(int intersectionID, Board& board){
    if(!myTurn){
        cout << getName() << " It's not your turn." << endl;
        return;
    }
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
            minusResourceCard(ResourceType::WHEAT, 2);
            minusResourceCard(ResourceType::ORE, 3);
            board.buildCity(intersectionID, this->getName());
            settelmentsOnBoard--;
            addPoints(1);
            citiesOnBoard++;
            cout << name << " built a city on intersection number " << intersectionID << endl;
        }
    }
}

bool Player::buyDevelopmentCard(DevelopmentCard* card){
    if(resourceCards[ResourceType::ORE] < 1 || resourceCards[ResourceType::WHEAT] < 1 || resourceCards[ResourceType::SHEEP] < 1){
        cout << getName() << " doesn't have enough resources to buy a development card" << endl;
        return false;
    }
    minusResourceCard(ResourceType::ORE, 1);
    minusResourceCard(ResourceType::SHEEP, 1);
    minusResourceCard(ResourceType::WHEAT, 1);
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

            developmentCards.erase(devCard);
            playedDevCardThisTurn = true;
            return true;
        }
    }
    cout << "You dont have this card." << endl;
    return false;
}

void Player::printNumSettelments(){
    if(settelmentsOnBoard > 0){
        cout << settelmentsOnBoard << " settelments." << endl;  
    }
}

void Player::printNumCities(){
    if(citiesOnBoard > 0){
    cout <<  citiesOnBoard << " cities." << endl;
    }
}

int Player::rollDice(){

    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int sum = dice1 + dice2;

    return sum;
}

void Player::printPoints(){
    if(points > 0){
    cout << points << " points." << endl;
    }
}

int Player::getPoints() const{
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
        const ResourceType& resource = it->first; // resource name
        int number = it->second; // number of resources
        cout << number << " " << Resource::getTypeName(resource) << endl;
    }
}

void Player::endTurn(){
    playedDevCardThisTurn = false;
    for(DevelopmentCard* devCard : developmentCards){
        devCard->changeStatusOfTurn(false);
    }
    myTurn = false;
}

void Player::trade(Player* player, ResourceType resource1,  int amount1, ResourceType resource2, int amount2){
    if(!myTurn){
        cout << getName() << " It's not your turn." << endl;
    }
    if(player == nullptr){
        throw invalid_argument("Invalid player.");
    }
    if(player == this){
        throw invalid_argument("You can't trade with yourself.");
    }
    if(amount1 < 0 || amount2 < 0){
        throw invalid_argument("Invalid amount.");
    }

    if(player->resourceCards[resource1] >= amount1 && this->resourceCards[resource2] >= amount2){
        player->minusResourceCard(resource1, amount1);
        player->addResourceCard(resource2, amount2);
        minusResourceCard(resource2, amount2);
        addResourceCard(resource1, amount1);
        cout << name << " trades " << amount2 << " " << Resource::getTypeName(resource2)  << " for "<< amount1 << " " << Resource::getTypeName(resource1) << " with " <<player->getName() << "." << endl;
    } else {
        cout << "Not enough resources to trade." << endl;
        return;
    }
}

void Player::tradeFourForOne(ResourceType resource1, ResourceType resource2){
    
    if(!myTurn){
        cout << getName() << " It's not your turn." << endl;
        return;
    }
    if(resourceCards[resource1] < 4){
        cout << getName() << " doesn't have enough resources to trade." << endl;
        return;
    }
    minusResourceCard(resource1, 4);
    addResourceCard(resource2, 1);
    cout << name << " trades 4 " << Resource::getTypeName(resource1) << " for 1 " << Resource::getTypeName(resource2) << endl;
}

string Player::getName() const{
    return name;
}


void Player::addTile(Tile* tile){
    tiles.push_back(tile);
}

vector<Tile*> Player::getTiles()const{
    return tiles;
}

void Player::addResourceCard(ResourceType resource, int amount){
    if(resourceCards.find(resource) == resourceCards.end()){
        throw invalid_argument("Invalid resource");
    }
    if(amount <= 0){
        throw invalid_argument("Invalid amount");
    }
    resourceCards[resource] += amount;
}

void Player::minusResourceCard(ResourceType resource, int amount){
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

int Player::getKnights() const{
    return knights;
}

void Player::printNumKnights(){
    if(knights > 0){
    cout << knights << " knights." << endl;
    }
}

Color Player::getColor() const{
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
    cout << "Color: " << colorToString(color) << endl;
    printPoints();
    printNumSettelments();
    printNumCities();
    printNumKnights();
    printDevelopmentCards();
    printResources();
}

int Player::getNumOfWood(){
    return resourceCards[ResourceType::WOOD];
}

int Player::getNumOfBrick(){
    return resourceCards[ResourceType::BRICK];
}

int Player::getNumOfSheep(){
    return resourceCards[ResourceType::SHEEP];
}

int Player::getNumOfWheat(){
    return resourceCards[ResourceType::WHEAT];
}

int Player::getNumOfOre(){
    return resourceCards[ResourceType::ORE];
}

map<ResourceType, int> Player::getResources() const{
    return resourceCards;
}

vector<DevelopmentCard*> Player::getDevelopmentCards() const{
    return developmentCards;
}

void Player::printDevelopmentCards(){
    if(!developmentCards.empty()){
        cout << getName() << " has " << developmentCards.size() << " development cards" << endl;
    }
}



