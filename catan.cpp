
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "catan.hpp"

const int DEVELOPMENT_DECK_SIZE = 25;
const int KNIGHT_CARDS = 14;
const int VICTORY_POINT_CARDS = 5;
const int ROAD_BUILDING_CARDS = 2;
const int MONOPOLY_CARDS = 2;
const int YEAR_OF_PLENTY_CARDS = 2;

const int WINNING_POINTS = 10;
const int MIN_LARGEST_ARMY_SIZE = 3;


using namespace std;
using namespace ariel;

Catan::Catan(Player &p1, Player &p2, Player &p3): players{&p1, &p2, &p3}, currentPlayer(nullptr), HasLargestArmy(nullptr), devDeck(DEVELOPMENT_DECK_SIZE), isFirstRound(true){
    board = new Board();
    initDevDeck();

}

Catan::~Catan(){

    for (DevelopmentCard* card : devDeck) {
        delete card;
    }
    devDeck.clear();

}

void Catan::ChooseStartingPlayer(){

    // int highest = 0;
    // Player *startingPlayer = nullptr;
    // for (Player *player : players) {
    //     int roll = player->rollDice();
    //     cout << player->getName() << " rolled a " << roll << endl;
    //     if (roll > highest) {
    //         highest = roll;
    //         startingPlayer = player;
    //     }
    // }
    // currentPlayer = startingPlayer;
    // currentPlayer->myTurn = true;
    // setPlayerColors();
    // cout << startingPlayer->getName() << " goes first!" << endl;

    currentPlayer = players[0];
    currentPlayer->myTurn = true;
    setPlayerColors();
    cout << currentPlayer->getName() << " goes first!" << endl;
}

void Catan::setPlayerColors(){
    players[0]->setColor(Color::RED);
    players[1]->setColor(Color::BLUE);
    players[2]->setColor(Color::GREEN);
}

void Catan::firstRound(Player *player, int intersectionID1, int road1, int intersectionID2, int road2){

    if(player != currentPlayer){
        cout << player->getName() << " - It's not your turn." << endl;
        return;
    }
    if(player->settelmentsOnBoard == 2){
        cout << player->getName() << " already placed 2 settlements and 2 roads." << endl;
        return;
    }
    if(isFirstRound){
        if(getBoard()->isValidFirstSettlements(player->getName(),intersectionID1, road1) && getBoard()->isValidFirstSettlements(player->getName(), intersectionID2, road2)){
            player->placeSettelemnt(intersectionID1, *board);
            player->placeRoad(road1, *board);

            player->placeSettelemnt(intersectionID2, *board);
            player->placeRoad(road2, *board);

            for(Tile* tile : player->getTiles()){
                vector<int> tileAdjIntersections = tile->getAdjIntersections();
                for(int inter : tileAdjIntersections){
                    if(inter == intersectionID2){
                        player->addResourceCard(tile->getType(), 1);
                    }
                }
            }
            cout << player->getName() << " placed 2 settlement on intersections: "<< intersectionID1 << ", "<< intersectionID2 << endl;
            cout << player->getName() << " placed 2 roads on roads: "<< road1 << ", "<< road2 << endl;

            int count = 0;
            for(Player *p : players){
                if(p->settelmentsOnBoard == 2){
                    count++;
                }
            }
            if(count == 3){
                isFirstRound = false;
                board->setIsFirstRound(false);
                cout << "First round is over." << endl;
            }
            nextTurn();
        }
        else{
            cout << player->getName() << " must choose new settlements and roads for first round" << endl;
        }
    }
}

Board* Catan::getBoard() const{
    return board;
}


void Catan::printWinner(){
    
    int highest = 0;
    Player *winner = nullptr;
    for (Player *player : players) {
        if (player->getPoints() > highest) {
            highest = player->getPoints();
            winner = player;
        }
    }
    if(highest >= WINNING_POINTS){
        cout << winner->getName() << " wins!" << endl;
    }
    else{
        cout << "No winner yet." << endl;
    }
}

bool Catan::isThereAWinner(){
    int highest = 0;
    Player *winner = nullptr;
    for (Player *player : players) {
        if (player->getPoints() > highest) {
            highest = player->getPoints();
            winner = player;
        }
    }
    if (winner->getPoints() >= WINNING_POINTS) {
        return true;
    } else {
        return false;
    }
}


void Catan::nextTurn(){
    if (currentPlayer == nullptr) {
        ChooseStartingPlayer();
    } else {
        size_t index = 0;
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i] == currentPlayer) {
                index = i;
            }
        }
        if (index == players.size() - 1) {
            currentPlayer = players[0];
            players[0]->myTurn = true;
        } else {
            currentPlayer = players[index + 1];
            players[index + 1]->myTurn = true;
        }
    }
    if(!isFirstRound){
        cout << currentPlayer->getName() << " it's your turn." << endl;
    }
}


void Catan::playTurn(Player *player){
    if(isFirstRound){
        throw invalid_argument("First round is not over, every player must choose 2 settlements and 2 roads");
    }
    if(!currentPlayer->myTurn){
        nextTurn();
    }
    if(player != currentPlayer){
        cout << player->getName() << " - It's not your turn." << endl;
        return;
    }
    player->myTurn = true;
    int dice = currentPlayer->rollDice();
    cout << currentPlayer->getName() << " rolled a " << dice << endl;
    for(Player *p : players){
        for(Tile *tile : p->getTiles()){
            if(tile->getNumber() == dice){
                if(tile->getType() != "desert"){
                p->addResourceCard(tile->getType(), 1);
                }
            }
        }
    }
    checkLargestArmy();
    if(isThereAWinner()){
        printWinner();
    }
    if(!(player->myTurn)){
        nextTurn();
    }
}


void Catan::initDevDeck(){

    devDeck.clear();

    for (int i = 0; i < KNIGHT_CARDS; i++) {
        devDeck.push_back(new DevelopmentCard(CardType::KNIGHT));
    }
    for (int i = 0; i < VICTORY_POINT_CARDS; i++) {
        devDeck.push_back(new DevelopmentCard(CardType::VICTORY_POINT));
    }
    for (int i = 0; i < ROAD_BUILDING_CARDS; i++) {
        devDeck.push_back(new DevelopmentCard(CardType::ROAD_BUILDING));
    }
    for (int i = 0; i < YEAR_OF_PLENTY_CARDS; i++) {
        devDeck.push_back(new DevelopmentCard(CardType::YEAR_OF_PLENTY));
    }
    for (int i = 0; i < MONOPOLY_CARDS; i++) {
        devDeck.push_back(new DevelopmentCard(CardType::MONOPOLY));
    }


    random_shuffle(devDeck.begin(), devDeck.end());
}

void Catan::buyDevCard(Player *player){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(devDeck.size() == 0){
        cout << "No more development cards." << endl;
        return;
    }
    DevelopmentCard* card = devDeck.back();
    if(player->buyDevelopmentCard(card)){
        devDeck.pop_back();
        cout << player->getName() << " bought a development card." << endl;
    }  
    
}

void Catan::checkLargestArmy(){
    int highest = 0;
    Player *player = nullptr;
    for(Player *p : players){
        if(p->getKnights() > highest){
            highest = p->getKnights();
            player = p;
        }
    }

    if(highest == MIN_LARGEST_ARMY_SIZE || highest > MIN_LARGEST_ARMY_SIZE){
        if(HasLargestArmy == nullptr){
            player->addPoints(2);
            HasLargestArmy = player;
            return;
        }
        else{
            if(player == HasLargestArmy){
                return;
            }
            else{
                HasLargestArmy->minusPoint(2);
                player->addPoints(2);
                HasLargestArmy = player;
            }
        }
    }
}

void Catan::playMonopolyDevCard(Player *player, string resource){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(player->canPlayDevelopmentCard(CardType::MONOPOLY)){
        for(Player *p : players){
            if(p != player){
                while(p->getResources()[resource] > 0){
                    p->minusResourceCard(resource, 1);
                    player->addResourceCard(resource, 1);
                }
            }
        }
    }
    return;
}

void Catan::playYearOfPlentyDevCard(Player *player, string resource1, string resource2){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(player->canPlayDevelopmentCard(CardType::YEAR_OF_PLENTY)){
        player->addResourceCard(resource1, 1);
        player->addResourceCard(resource2, 1);
    }
    return;
}

void Catan::playRoadBuildingDevCard(Player *player, int road1, int road2){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(player->canPlayDevelopmentCard(CardType::ROAD_BUILDING)){
        player->placeRoad(road1, *board);
        player->placeRoad(road2, *board);
    }
    return;
}

void Catan::playKnightDevCard(Player *player){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(player->canPlayDevelopmentCard(CardType::KNIGHT)){
        player->addKnight();
    }
    return;
}

void Catan::playVictoryPointDevCard(Player *player){
    if(isFirstRound){
        cout << "First round is not over, every player must choose 2 settlements and 2 roads" << endl;
        return;
    }
    if(player != currentPlayer){
        cout << player->getName() << " It's not your turn." << endl;
        return;
    }
    if(player->canPlayDevelopmentCard(CardType::VICTORY_POINT)){
        player->addPoints(1);
    }
    return;
}

Player* Catan::getCurrentPlayer() const{

    return currentPlayer;
}



