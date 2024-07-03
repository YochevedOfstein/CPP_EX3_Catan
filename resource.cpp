#include "resource.hpp"

using namespace std;
using namespace ariel;

Resource::Resource() : type(ResourceType::NONE) {}

Resource::Resource(ResourceType type) : type(type) {}

ResourceType Resource::getType() const {
    return type;
}

string Resource::getTypeName() const {
    switch(type) {
        case ResourceType::WOOD: return "wood";
        case ResourceType::BRICK: return "brick";
        case ResourceType::SHEEP: return "sheep";
        case ResourceType::WHEAT: return "wheat";
        case ResourceType::ORE: return "ore";
        default: return "None";
    }
}
