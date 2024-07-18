// yocheved@davidowitz.net 324460682
#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>
#include <vector>

using namespace std;

enum class CardType {
    KNIGHT,
    VICTORY_POINT,
    ROAD_BUILDING,
    MONOPOLY,
    YEAR_OF_PLENTY
};

namespace ariel {
    class DevelopmentCard {
        private:

            CardType type;
            string description;
            bool boughtThisTurn;

        public:

            DevelopmentCard(CardType type);
            CardType getType() const;
            string getDescription() const;
            void setDescription();
            void changeStatusOfTurn(bool newCard);
            bool getBoughtThisTurn() const;

        };

};

#endif