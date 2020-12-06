# FRUPAL
Frupal is a text-based adventure game that takes place on a 128 x 128 grovnick (tile) island, the Kingdom of Frupal. The player spawns in this island and is given some whiffle. The player's objective is to find the Royal Diamond in order to win the game. The player must find all of the clues in order to reveal the location of the Royal Diamond. The catch is that the player has a limited energy supply for each action made. There are obstacles that gets in the way of the player by require more energy to pass through unless they bought a tool for it. If the player spends all of their energy, they lose. Their energy can be replenished by purchasing food.

## Starting the Game
In order to start the game, the player must first compile the game. Simply enter "make" without quotation marks into the command line. Then enter "./frupal" without quotation marks once the compilation finishes.
<!--To load in a map of the kingdom. The game will prompt the user to enter the name of the map file. It's recommended to load the file called "map1.txt" (without quotation marks). The name is case sensitive so be sure to enter the exact name. By entering this into the game the map will be loaded and start the game.-->

## Map(s) for the game
* map1.txt: demonstration map

## Exiting the Game
If the player decides to stop the game, pressing the "End" key located on the right-side of the computer will end the game. Be warned that progress is not saved and the map will load its default settingsagain.

## Controls
The player will have two different controls, one is to move the player throughout the Kingdom of Frupal and the other to move their cursor. The cursor is used to inspect grovnicks on the island.

### Player Movement
* Up: 'W' key
* Down: 'S' key
* Left: 'A' key
* Right: 'D' key

### Cursor Movement
* Up: up-arrow key
* Down: down-arrow key 
* Left: left-arrow key 
* Right: right-arrow key 

## Grovnick
Each tile represents a grovnick. These grovnicks contain the terrain type and may also have objects on them, such as an obstacle, tool, and food. The player can move into most of these grovnicks and interact with the object on them.

### Terrain
A grovnick contains a type of terrain that varies in cost of energy to walk on. Some terrain are impassable and some can only be moved on unless certain conditions are met.
* Meadow: grassy, green tiles that require 1 energy to walk on
* Swamp: magenta tiles that are more difficult to traverse through, requiring 2 energy
* Water: a special blue tile that requires the player to be on a ship, which only costs 1 energy to move through
* Wall: this grey tile is an impassable grovnick, so do not try passing through or lose the energy for the tile that the player is on.

### Object
Some grovnick may have objects on them. They're represented by a character symbol. These may or may not benefit the player.
* F (food): these items recover certain amount of energy depending on the type, however they cost whiffles to purchase
* T (tool): handy devices that cost whiffle, but they allow the player to pass through certain obstacles with less energy cost
* ! (obstacle): hindrances that are passable but will cost a lot of energy to pass through unless the player uses a tool for it
* $ (treasure chest): lootable objects that may contain whiffles, tools, and food
* ? (clue): hints that, if accumulated enough, will reveal the location of the Royal Diamond
* S (ship): found on a water grovnick, allows the player the travers through a body of water
* B (binoculars): special item that expands the player's field of vision, revealing more areas around them
* $ (Royal Diamond): colored in white instead to distinguish it from treasure chests, this is your goal to win the game

## Implemented Features
All main features that defines the playability of this game has been implemented. This includes loading and display the map, player movement and interactions with objects, player menu, and a win-loss condition.

## Not finished

## Video Presentation
https://media.pdx.edu/media/Group+13+Discussion/1_19wlax3t
