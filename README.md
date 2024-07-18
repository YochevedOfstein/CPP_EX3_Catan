// yocheved@davidowitz.net

# System Programing 2 - assignmant 3

This project is an implementation of a simplified version of the board game, Catan. It includes basic game functionalities such as player turns, resource management, and building settlements and roads.

## Table of Contents
- [How to Play](#how-to-play)
    - [Game Rules](#game-rules)
    - [Player Actions](#player-actions)
- [Running the Code](#running-the-code)
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

## How to Play
### Game Rules
The goal is to be the first player to reach 10 victory points. Players earn points by building settlements, cities, having the largest army and getting victory points from development cards.

1. **Setup:** Each player starts with 2 settlements and 2 roads. Players take turns to place their initial settlements and roads.
2. **Turn Sequence:**
    * *Roll Dice:* The active player rolls two dice to determine resource production for all players.
    * *Resource Collection:* Each player collects resources from their settlements and cities adjacent to the rolled number.
    * *Trade:* Players can trade resources with each other or four cards of the same resource for one.
    * *Build:* Players can build roads, settlements, cities, or buy development cards using their resources.
    * *Play Development Cards:* Players can play one development card per turn.
    * *End Turn:* The turn passes to the next player.
3. **Winning the Game:** The first player to reach 10 points wins the game.

### Player Actions
1. **Build Road:** Connects two intersections and is required for expanding your reach on the board. Requirements: 1 wood and 1 brick.
2. **Build Settlement:** Collects resources from adjacent tiles and earns 1 victory point. Requirements: 1 wood, 1 brick, 1 wheat, and 1 sheep.
3. **Build City:** Upgrades a settlement to a city, doubling resource production from adjacent tiles and earns 2 victory points. Requirements: 3 ore and 2 wheat
4. **Buy Development Card:** Provides special abilities such as building additional roads, gaining resources, or earning victory points. Requirements: 1 ore, 1 wheat, and 1 sheep.

## Running the Code
To compile the project, use the following commands in your terminal:

```sh
make
```
This command will compile all necessary files and generate the executable for the Catan game, which includes compiling the main program (`demo`) and tests (`test`).

```sh
make catan
```
This command will compile the main program (`demo`) and then runs it (`./demo`).

## Classes Overview
This project consists of various classes that help implement the game. Some classes represent different pieces of the game, such as Board and DevelopmentCard, while others handle the game logic, like Catan and Player.

## Class Details
### Board
The class `board.cpp` manages the overall game board and its components, including tiles, roads and intersections. It provides methods to initialize the board, validate and place roads and settlements and building cities.

* **Key Methods:**
    * `Board()` -  Constructor for initializing the board.
    * `initBoard()` - Sets up the initial state of the board, by calling helper functions to initialize thr roads - `initRoads()`, intersections - `initIntersections()` and tiles - `initTiles()`.
    * `isValidPlaceForRoad(int roadId, string playerName)` - Validates if a player can place a road.
    * `placeRoad(int roadId, string playerName)` - Places a  road on board.
    * `isValidPlaceForSettlement(int intersectionId, string playerName)` - Validates if a settlement can be placed at a specified intersection.
    * `placeSettelemnt(int intersectionId, string playerName)` - Places a settlement at a specified intersection.
    * `buildCity(int intersectionId, string playerName)` - Bulids a city where one used to have a settlement.
    * `isValidFirstSettlements(string playerName, int intersection, int road)` - Validates if a player can place a settlement and road on starting turn.
    * `areRoadsAdj(int road1, int road2)` - Checks if two roads are adjacent to one another.

### Catan
The class `catan.cpp` encapsulates the game logic, including player turns, resource distribution, development card management, and determining the winner.

* **Key Methods:**
    * `Catan(Player &p1, Player &p2, Player &p3)` - Constructor that initializes the game with three players.
    * `ChooseStartingPlayer()` - Initialize which player starts and calls a function that sets each players colors.
    * `initDevDeck()` - Development card deck initialization.
    * `firstRound(Player *player, int intersectionID1, int road1, int intersectionID2, int road2)` - Handles ecery players first turn of placing 2 settlements and 2 roads.
    * `nextTurn()`- Advances the turn to the next player.
    * `playTurn(Player *player)` - Manages the player's turn, including dice rolling and resource distribution.
    * `buyDevCard(Player *player)` - Allows the current player to buy a development card.
    * *Development Card Methods* - Implement methods corresponding to each development card's effect, such as `playKnightDevCard(Player *player)` for the Knight card.
    * `checkLargestArmy()` - Checks and updates the player with the largest army, adjusting points accordingly.
    * `printWinner()` - Determines and announces the player with the highest points if they meet the winning criteria.

### Development Card
The class `developmentCard.cpp` represents a development card in the game, encapsulating the card type and its description, and keeping track of whether it was bought this turn.

* **Card Type**
    * Types of development cards available in the game: `KNIGHT`, `VICTORY_POINT`, `ROAD_BUILDING`, `MONOPOLY`, and `YEAR_OF_PLENTY`.

* **Key Methods:**
    * `DevelopmentCard(CardType type)` - Constructor that initializes the card with a specific type and sets its description.
    * `getType()` - Returns the type of the development card.
    * `getDescription()` - Provides a description of the card's effect.
    * `changeStatusOfTurn(bool newCard)` - Updates whether the card was bought in the current turn.
    * `getBoughtThisTurn()` - Checks if the card was bought in the current turn.

### Intersection
The class `intersection.cpp` represents points on the Catan board where settlements and cities can be placed. It manages ownership, adjacency relationships with other objects (like roads and tiles), and helps enforce settlement/city placement rules. There are 54 intersections in total and each one has a unique identifier (0-53).

* **Key Methods:**
    * `Intersection(int ID)` - Constructor that initializes an intersection with a unique identifier.
    * `setOwner(string owner)` - Sets the owner of the intersection to the specified player.
    * `hasOwner()` - Checks if the intersection has an owner (returns true or false).
    * `getOwner()` - Returns the name of the owner of the intersection.
    * `setHasCity(bool hasCity)` - Sets whether the intersection has a city.
    * `getHasCity()` - Checks if the intersection has a city or not.
    * `setAdjIntersection(Intersection* intersection1, Intersection* intersection2, Intersection* intersection3)` - Sets adjacent intersections.
    * `getAdjIntersections()` - Retrieves adjacent intersections.
    * `setAdjRoad(Road* road1, Road* road2, Road* road3)` - Sets adjacent roads.
    * `getAdjRoads()` - Retrieves adjacent roads.
    * `setAdjTile(Tile* tile1, Tile* tile2, Tile* tile3)` - Sets adjacent tiles.
    * `getAdjTiles()` - Retrieves adjacent Tiles.

### Player
The class `player.cpp` represents participants in the Catan game, managing resources, development cards, facilitate player trades and actions during their turns.

* **Key Methods:**
    * `Player(string name)` - Constructor that initializes a player with a specific name.
    * `placeSettelemnt(int intersectionID, Board& board)` - Places a settlement on the board at the specified intersection and pays for it with resource cards if needed.
    * `placeRoad(int roadID, Board& board)` - Places a road on the board at the specified road and pays for it with resource cards if needed.
    * `buildCity(int intersectionID, Board& board)` -  Builds a city on the board at the specified intersection and pays for it with resource cards if needed.
    * `rollDice()` - Simulates the rolling of two dice and returns the sum.
    * `trade(Player* player, ResourceType resource1, int amount1, ResourceType resource2, int amount2)` - Facilitates a trade between two players.
    * `addResourceCard(ResourceType resource, int amount)` - Adds resource cards to the player's collection.
    * `minusResourceCard(ResourceType resource, int amount)` - Removes resource cards from the player's collection.
    * `buyDevelopmentCard(DevelopmentCard* card)` - Allows the player to buy a development card.
    * `canPlayDevelopmentCard(CardType type)` -  Checks if the player can play a development card of the specified type.
    * `tradeFourForOne(ResourceType resource1, ResourceType resource2)` - Facilitates a 4:1 trade of resources.

### Resource 
The class `resource.cpp` represents the different types of resources available in Catan, Resource is used to represent different tiles and reasource cards.

* **Resource Type**
    * Types of resources: `WOOD`, `BRICK`, `SHEEP`, `WHEAT`, `ORE`, and `DESERT`.

* **Key Methods:**
    * `Resource(ResourceType type)` - Constructor that initializes the resource with a specific type.
    * `getType()` - Returns the type of the resource.
    * `getTypeName(ResourceType retype)` - Returns the name of the specified resource type.
    * `getTypeNameForResource()` - Returns the name of the resource.

### Road
The class `road.cpp` represents roads on the Catan board where a player can build his own road. It manages ownership, adjacency relationships with other objects (like intersections), and helps enforce road placement rules. There are 72 intersections in total and each one has a unique identifier (0-71).

* **Key Methods:**
    * `Road(int ID)` - Constructor that initializes a road with a unique identifier.
    * `setOwner(string owner)` - Sets the owner of the road to the specified player.
    * `hasOwner()` - Checks if the road has an owner.
    * `getOwner()` -  Returns the name of the owner of the road.
    * `addAdjIntersections(int intersection1, int intersection2)` - Sets adjacent intersections.
    * `getAdjIntersections()` - Retrieves adjacent intersections.

### Tile
The class `tile.cpp` represents hexagonal tiles on the board that produce resources based on dice rolls.

* **Key Methods:**
    * `Tile(int ID)` - Constructor that initializes a tile with a unique identifier.
    * `getTypeString()` - Returns the name of the resource type as a string.
    * `getType()` - Returns the type of the resource.
    * `setType(ResourceType type)` - Sets the type of the resource for the tile.
    * `getNumber()` - Returns the dice roll number associated with the tile.
    * `setNumber(int number)` - Sets the dice roll number for the tile.
    * `addAdjIntersections(int intersection1, int intersection2, int intersection3, int intersection4, int intersection5, int intersection6)` - Sets the adjacent intersections for the tile.
    * `getAdjIntersections()` - Retrieves the IDs of adjacent intersections.


## Tests
This project includes comprehensive unit tests using the `doctest.h` framework. These tests cover initialization, game rules, player actions, resource management, and edge cases to ensure the robustness and correctness of the implementation.

To run the tests:
```sh
make test
```
```sh
./test
```
This command compiles the test program (`test`). After compiling, running `./test` will execute the test suite.








