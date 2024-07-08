

# System Programing 2 - assignmant 3

This project is an implementation of a simplified version of the board game, Catan. It includes basic game functionalities such as player turns, resource management, and building settlements and roads.

## Table of Contents
- [Classes Overview](#classes-overview)
- [Class Details](#class-details)
    - [Board](#board)
    - [Catan](#catan)
    - [Development Card](#development-card)
    - [Intersection](#intesection)
    - [Player](#player)
    - [Resource](#resource)
    - [Road](#road)
    - [Tile](#tile)
- [Tests](#tests)


## Classes Overview
This project consists of various classes that help implement the game. Some classes represent different pieces of the game, such as Board and DevelopmentCard, while others handle the game logic, like Catan and Player.

## Class Details
### Board
The class `board.cpp` represents the game board and manages the overall state of the the pieces. It includes functionalities to initialize the board, place settlements and roads, and check valid moves.

**Key Methods:**
* `initBoard()` - Sets up the initial state of the board, by calling helper functions to initialize thr roads, intersections and tiles:
* `isValidPlaceForRoad(int roadId, string playerName)` - Validates if a player can place a road.
* `placeRoad(int roadId, string playerName)` - Places a  road on board.
* `isValidPlaceForSettlement(int intersectionId, string playerName)` - Validates if a settlement can be placed at a specified intersection.
* `placeSettelemnt(int intersectionId, string playerName)` - Places a settlement at a specified intersection.
* `buildCity(int intersectionId, string playerName)` - Bulids a city where one used to have a settlement.

### Catan
The class `catan.cpp` encapsulates the game logic, including player turns, resource distribution, and win conditions.

**Key Methods:**
* `ChooseStartingPlayer()` - Initialize which player starts and calls a function that sets each players colors.
* `initDevDeck()` - Development card deck initialization.
* `firstRound(Player *player, int intersectionID1, int road1, int intersectionID2, int road2)` - Handles ecery players first turn of placing 2 settlements and 2 roads.
* `nextTurn()`- Advances the turn to the next player.
* `playTurn(Player *player)` - Manages the player's turn, including dice rolling and resource distribution.
* `buyDevCard(Player *player)` - Allows the current player to buy a development card.
* *Development Card Methods* - Each method implements the effect of playing a specific development card.
* `checkLargestArmy()` - Checks and updates the player with the largest army, adjusting points accordingly.
* `printWinner()` - Determines and announces the player with the highest points if they meet the winning criteria.

### Development Card
The class `developmentCard.cpp` represents a development card in the game, encapsulating the card type and its description, and keeping track of whether it was bought this turn.

**Card Type**
enum class CardType: Enumerates the types of development cards available in the game, such as KNIGHT, VICTORY_POINT, ROAD_BUILDING, MONOPOLY, and YEAR_OF_PLENTY.

**Key Methods:**
* `DevelopmentCard(CardType type)` - Constructor that initializes the card with a specific type and sets its description.
* `getType()` - Returns the type of the development card.
* `getDescription()` - Provides a description of the card's effect.
* `changeStatusOfTurn(bool newCard)` - Updates whether the card was bought in the current turn.
* `getBoughtThisTurn()` - Checks if the card was bought in the current turn.

### Intersection
The class `intersection.cpp` represents points on the Catan board where settlements and cities can be placed. It manages ownership, adjacency relationships with other objects (like roads and tiles), and helps enforce settlement/city placement rules. There are 54 intersections in total and each one has a unique identifier (0-53).

**Key Methods:**
* `Intersection(int ID)` - Constructor that initializes an intersection with a unique identifier.
* 

### Player
The class `player.cpp` represents participants in the Catan game, managing resources, development cards, and actions during their turns.


### Resource 
The class `resource.cpp` represents the different types of resources available in Catan that reresent every tile in the game.
* `Resource(ResourceType type)` - Constructor that initializes the resource with a specific type.
* `getType()` -
* `string getTypeName()` - 

### Road
The class `road.cpp` represents roads on the Catan board where a player can build his own road. It manages ownership, adjacency relationships with other objects (like intersections), and helps enforce road placement rules. There are 72 intersections in total and each one has a unique identifier (0-71).

### Tile
The class `tile.cpp` represents hexagonal tiles on the board that produce resources based on dice rolls.




