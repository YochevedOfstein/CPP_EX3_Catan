

# System Programing 2 - assignmant 3

This project is an implementation of a simplified version of the board game, Catan. It includes basic game functionalities such as player turns, resource management, and building settlements and roads.

## Table of Contents
- [Classes Overview](#classes-overview)
- [Class Details](#class-details)
    - [Board](#board.cpp)
    - [Catan](#catan)
    - [Development Card](#development-card)
    - [Intersection](#intesection)
    - [Player](#player)
    - [Resource](#resource)
    - [Road](#road)
    - [Tile](#tile)


## Classes Overview
This project consists of various classes that help implement the game. Some classes represent different pieces of the game, such as Board and DevelopmentCard, while others handle the game logic, like Catan and Player.

## Class Details
### `board.cpp`
The Board class represents the game board and manages the overall state of the the pieces. It includes functionalities to initialize the board, place settlements and roads, and check valid moves.

**Key Methods:**
* initBoard() - Sets up the initial state of the board, by calling helper functions to initialize thr roads, intersections and tiles:
    * initRoads()
    * initIntersections()
    * initTiles()
* isValidPlaceForRoad(int roadId, string playerName) - Validates if a player can place a road.
* placeRoad(int roadId, string playerName) - Places a  road on board.
* isValidPlaceForSettlement(int intersectionId, string playerName) - Validates if a settlement can be placed at a specified intersection.
* placeSettelemnt(int intersectionId, string playerName) - Places a settlement at a specified intersection.
* buildCity(int intersectionId, string playerName) - Bulids a city where one used to have a settlement.

### `catan.cpp`
The Catan class encapsulates the game logic, including player turns, resource distribution, and win conditions.

**Key Methods:**

