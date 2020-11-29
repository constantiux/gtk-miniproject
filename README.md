# SEEM3460 Mini Project

_*) Disclaimer: It is not supported to be compiled and run in REPL.it as of 24 Nov 2020_

### The Game

1. A total of nine rounds for each player to guess whether the next card has higher or lower value compared to the last card of the opponent.
2. Each player will get one initial card at the start of the game.
3. The ranking of the cards are

		2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> J -> Q -> K -> A
		Club -> Diamond -> Heart -> Spade
4. User can opt-in to check for some hints. They will know
	- How many cards left (not limited to the nine rounds)
	- Number of cards left with higher value than the last issued
	- Number of cards left with lower value than the last issued

### Docs

- To compile, make sure the system (tested on UNIX) to have GTK+3 installed. Check with `pkg-config --cflags --libs gtk+-3.0` in the terminal.
- A `Makefile` is provided. Just need to execute `make` in this directory. Then run with `./main`.
- More information to setup and further development of the game in _REPL.it_ please refer to `HOWTO`.