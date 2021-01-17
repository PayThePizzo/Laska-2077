# Laska 2077

This project was made for our Introduction to Programming Course. It represent the digital mini-version of the famous tablegame, Lasca.
Check out the official site of the game, here: http://www.lasca.org/

The rules for this game are to be found inside the game and many reminders are thrown whenever a player violates them.


## Credits
Gianmaria Pizzo, Aleksandra Gjorgievska & Riccardo Peresin.


### Prerequisites
Mac Os & Linux:
- Unix Terminal
- Gcc compiler

Or

Windows:
- Visual Studio
- CLion

### Installing
Simply download the source code from this page and run it through the following commands:

```
gcc laska.c 
./a.out
```

If you have Windows, after installing these two softwares you just need to run the main.c in release mode.
You can do this both in CLion or Visual Studio.


And play the game to show the machine, or your opponent, who's the best.

```
until finished
```

These are some kinds of error messages you could get while playing:

```
"The selected box doesn't exist. Please select a letter from _ to _ ."

"The Dama (promoted pawn) may capture only in the 4 diagonals if the adjacet is a foe's pawn and the next on the diagonal is free."

"The pawn may capture only in the 2 diagonals forward if the adjacet is a foe's pawn and the next on the diagonal is free."

"The Dama (promoted pawn) may move only in the 4 diagonals if it's free."

"The pawn may move only in the 2 diagonals forward if it's free."

"You can move only into free white empty bowes."

"The selected box have to contain your pawn."

"The pawn you choosed can not be moved"

"Unfortunately, you can't choose this pawn because you are forced to capture foe's pawns, so you have to choose an other pawn.You can move only the pawn inside one of this boxes:"
```


** Features **
---
1. B4st4rd Easter Eggs: Laska-bot and Narrator like to make your day worse.
    + Don't get upset
---


### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```


### And coding style tests or memory leak tests

Explain what these tests test and why

```
Give an example
```


## Built With

* CLion
* Visual Studio - Release/Debug
* WSL - Release/Debug
* Doxygen


## Contributing

We'd like to thank our professors Claudio Lucchese and Alvise Spano' for helping us during the creation of our project.


## Versioning

Version 1.0


## Authors

Esempio:
* **Gianmaria** - *Front End Designer & Feature Creator* - [PayThePizzo](https://github.com/PayThePizzo)
* **Aleksandra** - *Structure & Rules Handler* - [aleksandragjorgievska](https://github.com/aleksandragjorgievska)
* **Riccardo** - *Group Member*

## License

This project is to be taken as an example. 
Anyone can build their own little game using only basic ANSI C.
It is not to be distributed for plagiarizing purposes or sold.


## Acknowledgments

* This was our first time coding together and my colleagues were amazing.
* This project was made to respect the ANSI C 90 standards.
