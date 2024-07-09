#include "resource.hpp"

using namespace std;
using namespace ariel;

Resource::Resource(ResourceType type) : type(type) {}

ResourceType Resource::getType() const {
    return type;
}

string Resource::getTypeNameForResource() {
    switch(type) {
        case ResourceType::WOOD: return "wood";
        case ResourceType::BRICK: return "brick";
        case ResourceType::SHEEP: return "sheep";
        case ResourceType::WHEAT: return "wheat";
        case ResourceType::ORE: return "ore";
        default: return "None";
    }
}

string Resource::getTypeName(ResourceType retype) {
    switch(retype) {
        case ResourceType::WOOD: return "wood";
        case ResourceType::BRICK: return "brick";
        case ResourceType::SHEEP: return "sheep";
        case ResourceType::WHEAT: return "wheat";
        case ResourceType::ORE: return "ore";
        default: return "None";
    }
}
