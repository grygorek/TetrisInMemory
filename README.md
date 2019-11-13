# Project Tetris

Yet another implementation of Tetris.
Tetris is a popular game.

This project is an exercice to follow architecture described in [this repository](https://github.com/grygorek/TetrisArch).

## Basic Rules

- Random figures fall with a constant speed from the top of the window.
  User can rotate the fugures.
- Figures stop falling at the bottom of the window. They fill in the window
  from the bottom.
- If the full line is filled with parts of the figures, the line is removed.
  Lines above drop down.
- User has to make an effort to fit the figures to fill in the lines. 
- Game is finished when the figures cannot fall because there is no more space.

## How To Play the Game

The game is played in computer's memory during a debugging session.

1. Set a breakpoint somewhere in the main loop in the main function
2. Configure debugger memory view window (egz. Visual Studio `Ctrl+Alt+M, 1`) to see 8 bytes per line
3. In the memory view window, set address to `&tetris._screen._lines`
4. Progress the game by stepping through the instructions in the main loop (or simply press F5 in Visual Studio; breakpoint must be in the main loop)
5. Enter your command to a global variable s_cmd and progress the game
6. The memory view window should show moving figures
7. The game is over when the top line has some blocks and the new figure has not place to be put
8. Reset the debugger to start a new game

Although, the project in this repository is for Visual Studio 2019, there is no dependency on environment. The same code should work in GCC or a bare metal application.

## Requirements To This Implementation

- Code portable between bare metal system, Windows and Linux. The same code must work: 
  - on a selected hardware in a case of bare metal
  - on Linux
  - on Windows
- Written in C++
- Game happens in memory and the default ouput is a memory window in a debugger.
- Possible extension to a graphical window in the case of Windows.

Example of a game play:

```
address      ASCII
            0123456789ABCDEF

0x00        ----------------
0x10        |              |
0x20        |              |
0x30        |              |
0x40        |        XX    |
0x50        |         X    |  <-- figure
0x60        |         X    |
0x70        |              |
0x80        |XXXXXXXXX XXXX|  <-- Two lines 
0x90        |XXXXXXXXX XXXX|
0xA0        ----------------

```

In the example above the figure will drop to the empty gap. The next screen is:

```
address      ASCII
            0123456789ABCDEF

0x00        ----------------
0x10        |              |
0x20        |     XX       |  <-- new figure 
0x30        |     XX       |  
0x40        |              |
0x50        |              |
0x60        |              |
0x70        |              |
0x80        |              |
0x90        |        XX    |  <-- remaining parts of the figure
0xA0        ----------------

```

Example of the end of the game:


```
address      ASCII
            0123456789ABCDEF

0x00        ----------------
0x10        |              |  <-- no space for a new figure
0x20        |XXXXXXXXXXX XX|
0x30        |XXXXXXX XXXXXX|
0x40        | XXXX XXXX XX |
0x50        |XXXXXX  XX  X |
0x60        | XXXXXX   XXX |
0x70        |XXXXXXXXX XXXX|
0x80        |XXXXXXXXX XXXX|
0x90        |XXXXXXXXX XXXX|
0xA0        ----------------

```

## Figures

Following figures:

### Small Square

Small square is made of a single byte:

```
X
```

Rotation has no effect.

### Big Square

Big square is made of four small squares:

```
XX
XX
```

Rotation has no effect.

### Small L

Small L is made of 3 small squares:

```
XX
 X
```

Possible figures after the rotation:

```
XX    XX     X      X
 X    X      XX    XX
```


### Big L


```
XXX    XX     X       X
  X    X      XXX     X
       X             XX
```

### T

```
XXX   X     X     X
 X    XX   XXX   XX
      X           X
```


**Enjoy!**
