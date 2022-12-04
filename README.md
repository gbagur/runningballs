# runningballs
Simple video game with running balls crashing your square spaceship

This code is a C++ program that simulates a game in which a player must
avoid bouncing balls. The program uses the SFML library for graphics, input, and sound.

The program defines several classes, including a Game class, a Ball class, 
a Player class, and a SoundEffect class. The Game class represents the game
state, with a status member variable that indicates whether the game is alive 
or dead. The Ball class represents a ball that bounces around the screen, and
the Player class represents the player, who must avoid the balls. The SoundEffect 
class represents a sound effect that can be played, stopped, and added to a list
of active sounds.

In the main() function, the program creates several instances of these classes a
nd sets up the SFML window and event loop. The program then enters a main game loop,
in which it processes input from the player, updates the game state, draws the screen,
and plays sound effects. The game loop continues until the player dies or the window
is closed.

The program uses the SFML Keyboard class to check for player input, and the RenderWindow
class to draw graphics to the screen. It also uses the Clock class to measure the
elapsed time between frames, and the RectangleShape and CircleShape classes to represent
the player and balls. The program also uses the SFML Music class to play background
music, and the Font and Text classes to draw text to the screen.
