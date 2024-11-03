# Bricks & Breakers: Dice of Power - Comp3016 Report

## Youtube Link
- 

## How to run the game
- Download the "Game.zip" file and extract into your prefered location.
- Run the "BnB-DOP.exe" file
- Enjoy!

## Game mechanics

### Class Selection
In the character selection screen, the player has the option between 3 classes and each class has its own unique change.
This allows the player to explore different playing styles to find their preffered style.

### Dice roll
After choosing their character, 2 dice are rolled on the screen, the results of the dice roll dictate the number of balls or _breakers_, that are spawned at the start of the level.


## Game controls

__A__ - Move paddle left

__D__ - Move paddle right

Other keyboard controls for navigating menus are displayed within the in-game UI

## Dependecies

SDL2: https://www.libsdl.org/ 
SDL2Image: https://www.libsdl.org/projects/SDL_image/release/

## Patterns

A game loop is used for running the game.

Within each frame, the following occurs:

- Input gathered
- The game logic executed based on inputs and game states
- The game is rendered based on game states and inputs

## Sample screens

### Character Selection Screen
![Character Select Screen](/BnB-DOP/Game/assets/ChooseCharacterScreen.png)

### Title Screen
![Title Screen](/BnB-DOP/Game/assets/StartScreen.png)

### Game Over Screen
![Game Over Screen](/BnB-DOP/Game/assets/GameOverScreen.png)

##Exeption handling

##Evaluation

I think that I have developed a great game whilst demonstrating my ability to write unmanaged code within the object-oriented paradigm.
I especially enjoyed the freedom of designing my own game while having strict deadlines, this forced me to design and develop efficiently where I have learnt of ways in which I could improve further.
Unfortunately, I did not add sound effects to this game, personally I do not care for sound in games which but I understand it is imporant to many.
I think that the visual designs are consistently beautiful and I enjoyed acquiring AI art and seeing how good it can look and how much easier it was than creating the art myself.
If I were to decide to work further on this project, I would consider adding more classes, power-ups, audio, and an improvement to the dice rolling system.