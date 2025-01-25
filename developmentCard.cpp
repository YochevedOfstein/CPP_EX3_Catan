

#include "developmentCard.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace ariel;

DevelopmentCard::DevelopmentCard(CardType type): type(type), boughtThisTurn(false){
    setDescription();
}

CardType DevelopmentCard::getType() const {
    return type;
}

string DevelopmentCard::getDescription() const {
    return description;
}

void DevelopmentCard::setDescription() {
    switch (type) {
        case CardType::KNIGHT:
            description = "A knight has joined your army.";
            break;
        case CardType::VICTORY_POINT:
            description = "You gain 1 victory point.";
            break;
        case CardType::ROAD_BUILDING:
            description = "You may build two roads.";
            break;
        case CardType::MONOPOLY:
            description = "You get all resources of one type from all players.";
            break;
        case CardType::YEAR_OF_PLENTY:
            description = "You get any two resources of your choice.";
            break;
        default:
            description = "Unknown card type.";
    }
}

void DevelopmentCard::changeStatusOfTurn(bool newCard) {
    boughtThisTurn = newCard;
}

bool DevelopmentCard::getBoughtThisTurn() const {
    return boughtThisTurn;
}


