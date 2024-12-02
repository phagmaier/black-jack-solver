# BLACK JACK SOLVER

## DESCRIPTION
Currently this is a command line program that runs a
monte carlo simulation to determine the percentage
chance a dealer has of reaching any of the possible values.
In the game of blackjack valid valus for a dealer are 17-21 and 
if they go over they "bust" which in a win for any player 
who has not exeeded 21. Currently I run 5 million iterations.
Players must select their cards and any dead cards. 
They must also select the number of decks the casino is using 
(in a real casino i believe this number is somewhere between 6-8)
as well as the card the dealer is showing. an important NOTE is that 
since the point of this simulation is to be able to 
determine optimal play we assume the dealer doesn't have 21 since 
any hand you have where the dealer has 21 play automatically ends so
it would be pointless to consider this and players playing against the dealer
can also assume the dealer doesn't have blackjack when the hand doesn't immedietley end.

## WHAT WE CURRENTLY HAVE
1. Command line interface
2. Select number of decks
3. Select dealers cards
4. Select player's cards 
5. Select dead cards

## IMPROVMENTS
1. Add dead cards for player so you can start simulation in a given spot
2. Convert command line interface into a simple GUI 
3. Find and show optimal strategy for player 
4. Allow 'live updates' i.e. player hits they can enter card dealt and we can calculate optimal strategy
5. Allow user to select options like just showing dealers numbers just showing players strategy etc...


## File Table

| File | Descripton |
| --------- | --------------------- |
| [main.cpp](src/main.cpp) | Runs the program |
| [healperfunctions.h](src/healperfunctions.h) | Header file for all functions to run the code |
| [healperfunctions.cpp](src/healperfunctions.cpp) | Implimentation for all functions to run the code |
| [constants.h](src/constants.h) | Has some constants the program uses |



## How to run
1. Go to or create a bin directory and run: cmake .. && make && ./runme
2. Follow command line instructions



