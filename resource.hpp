// yocheved@davidowitz.net 324460682

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <iostream>
#include <string>

using namespace std;

namespace ariel {

    enum class ResourceType {
        NONE,
        DESERT,
        WOOD,
        BRICK,
        SHEEP,
        WHEAT,
        ORE
    };

    class Resource {
        private:
            ResourceType type;

        public:
            Resource(ResourceType type);

            ResourceType getType() const;
            string getTypeNameForResource();
            static string getTypeName(ResourceType retype);
    };

}

#endif