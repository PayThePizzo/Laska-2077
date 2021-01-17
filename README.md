# Laska 2077

![alt text](https://github.com/PayThePizzo/Laska-2077/blob/main/lask-2070-logo.png?raw=true)

This project was made for our Introduction to Programming course. 
It represents a digital mini-version of the famous tablegame, Lasca.
Plus, it is inspired from THAT new futuristic game featuring Keanu Reeves.

Check out the official site of the game, here: http://www.lasca.org/


### Credits
Gianmaria Pizzo & Aleksandra Gjorgievska.


## Prerequisites
---
+ Mac Os & Linux:
    - Unix-like Terminal
    - Xcode tools and gcc compiler

Or

+ Windows:
    - Any IDE like CLion or Visual Studio
    - Any gcc compiler (We recommend using Visual Studio's and WSL's)
---


## Installing

### Mac & Linux

1. Simply download the source code from this repository.

2. Unzip it on your desktop and move the "Laska-main-2077" to your desktop.

3. Run the following commands in your unix terminal to change directory and enter the main folder:
```
$cd Desktop

$cd Laska-2077-main
```
4. Run the following commands to create the object file and the executable file, and then play.
```
$make

$./laska
```
5. Play the game to show the machine, or your opponent, who's the best.

```
White player wins!

Black player wins!
```
6. Remove extra copies after the game with the following command:
```
$clean
```
---

### Windows

1. Import the unzipped windows directory (through your IDE).
    + You can also get the files from VCS: https://github.com/PayThePizzo/Laska-2077.git
    
![alt text](https://github.com/PayThePizzo/Laska-2077/blob/main/vcs.png?raw=true)

2. Run the main.c in release mode.

3. Play the game to show the machine, or your opponent, who's the best.

```
White player wins!

Black player wins!
```
---

### No clue how to play the game? We are here to help!
---

The rules for this game are to be found inside the game and many reminders are thrown whenever a player violates them.
    + Type "yes" as soon as the game starts!
    + Check the official website for more details.

* These are some kinds of error messages you could get while playing:

```
"The selected box doesn't exist. Please select a letter from _ to _ ."

"FORCING CAPTURE - Pieces must capture if in a position to do so."

"The Officer may capture only in the 4 diagonals if the adjacet is a foe's pawn and the next on the diagonal is free."

"The pawn may capture only in the 2 diagonals forward if the adjacet is a foe's pawn and the next on the diagonal is free."

"The Officer may move only in the 4 diagonals if it's free."

"The pawn may move only in the 2 diagonals forward if it's free."

"You can move only into free white empty bowes."

"The selected box have to contain your pawn."

"The pawn you choosed can not be moved"

"Unfortunately, you can't choose this pawn because you are forced to capture foe's pawns, so you have to choose an other pawn.You can move only the pawn inside one of this boxes:"

"Error move function"
```


## Features
---
1. Easter Eggs: Laska-bot and Narrator like to make your day worse. But HE is coming to help.
    + Don't get upset, haters gonna hate.
    + Meet K.R. straight from the year 2077. Who does not love him?

2. Revise the rules
    + Laska bot is here to help! Look up the rules so you can play this wonderful game.
    + Not clear yet? visit the official website.

3. 2D? No problem, you can still see what is underneath the surface!
    + As you capture players you can still see how tall your stack is.

4. Many game modes available!
    + Single Player
    + Player vs Player
    + Player vs Pc
    + Pc vs Pc

5. Extra features for lazy people
    + Toss a coin to decide who's gonna play first!
    + Moves counter
    + Whose turn is this?
    + Active monitoring of the rules
    + Quit
    + Give Up
    + Restart the game

Here's a little insight of the welcome section:

![alt text](https://github.com/PayThePizzo/Laska-2077/blob/main/Ins.png?raw=true)



### Standard & Style

We follwed ANSI C 90 Standard rules to build this project.
The code style is snake_case type.

```
int foo_aux(int sup){

 ** Variable Declaration/ Memory allocation **
 int aux_temp;
 double a = 0.0;

 ** Statements/ Body of function **
 aux = sup;

 if(aux){
    a = 0.1;
 }
 aux = (int)a;
 
 ** Return statemente/ Memory deallocation **
 return aux_temp;
}
```


### Disclaimer

Follow the instructions given or the program will fail.
Some messages may be shown multiple times, that is a "reward" for following the rules.

```
**DISCLAIMER: The input you may type is always shown, other kinds of input may make the game fail.**
```


### Built With

* CLion
* Visual Studio - Release/Debug
* WSL - Release/Debug
* Doxygen


### Contributing

We'd like to thank our professors Claudio Lucchese, Alvise Spano' and our tutors Alberto Veneri and Antonio Emanuele Cina' for helping us during the creation of our project.


### Versioning

Version 1.0


## Authors

* **Gianmaria** - *Front End Designer & Feature Creator* - [PayThePizzo](https://github.com/PayThePizzo)
* **Aleksandra** - *Structure & Rules Handler* - [aleksandragjorgievska](https://github.com/aleksandragjorgievska)


### License

This project is to be taken as an example. 
Anyone can build their own little game using only basic ANSI C.
It is not to be distributed for plagiarizing purposes or sold.


### Acknowledgments

* This was our first time coding together and my colleagues were amazing.
* This project was made to respect the ANSI C 90 standards.
---
