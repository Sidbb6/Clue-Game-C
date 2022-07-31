
Welcome to this version of the game Clue. 

Instructions on how to run: 
In order to get started you must compile the code in the "adventure.c" file.
This is done with the "gcc adventure.c" command inputted into the terminal.

After a successful compilation, this will be characterized by no messages/errors in the terminal, 
simply input "./a.out" to run the project. 

Description of structure of game board: 
The game board is constructed through the use of pointers and custom "Room" structures. Through the use of "malloc", 
first the size of the Room struct is calculated in the form of bytes of memory then allocated 9 times to form the space for 
the gameboard. Then these pointers are specified (casted) as room struct pointers and the board has been generated. 

User input:
After running the game, type commands in uppercase (for example, "GO NORTH") in order to interact with the game.

Have fun!  
