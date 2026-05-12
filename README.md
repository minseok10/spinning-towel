# Spinning Towel

A small C command-line program for managing player groups and running a
"spinning towel" elimination game from a text query file.

## Build

```sh
make
```

This creates the `spinning-towel` executable.

## Run

```sh
./spinning-towel [players-file]
```

If no player file is provided, the program looks for `players.txt`.

## Commands

- `show`: print all players or a selected group
- `add`: add a player
- `remove`: remove a player by student ID
- `play [game-file]`: run the game using `game.txt` or another query file
- `quit`: save the result to `result_game.txt` and exit

## Input Format

Player files are tab-separated:

```text
Name	Gender	Dept	StudentID	Group
```

Game query files contain target group/player positions, one pair per line:

```text
2 3
4 1
```

## Clean

```sh
make clean
```
