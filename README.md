<p align="left">
    <img width="150px" src="https://github.com/thoth-tech/.github/blob/main/images/splashkit.png"/>
</p>

# DX Game (Brick Breaker / Breakout)

**DX Game** is a modern reimagining of the classic brick-breaking games **Breakout** and **DX-Ball**, developed using C++ and SplashKit. This project demonstrates key game development concepts, serves as an educational resource, and showcases the potential of the SplashKit SDK for both arcade and Raspberry Pi environments.

## Table of Contents

- [DX Game (Brick Breaker / Breakout)](#dx-game-brick-breaker--breakout)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Purpose](#purpose)
  - [Development Team](#development-team)
  - [Programming Language \& Software](#programming-language--software)
    - [Language: C++](#language-c)
    - [Software Used](#software-used)
  - [Game Description](#game-description)
  - [Game Mechanics](#game-mechanics)
    - [Controls](#controls)
      - [Gameplay Controls for PC](#gameplay-controls-for-pc)
      - [The controls on PC for the user interface elements](#the-controls-on-pc-for-the-user-interface-elements)
    - [Types of Bricks](#types-of-bricks)
    - [Scoring System](#scoring-system)
    - [Power-Ups](#power-ups)
  - [Levels](#levels)
    - [Level Design](#level-design)
  - [Environment Setup](#environment-setup)
    - [Visual Elements](#visual-elements)
  - [Sprites](#sprites)
  - [Future Improvements](#future-improvements)
  - [Notes](#notes)
- [Notes post refactor April 2024](#notes-post-refactor-april-2024)

## Introduction

The **DX Game** is inspired by the iconic **DX-Ball** and **Breakout** games, developed with the SplashKit SDK to demonstrate its capabilities in creating 2D arcade games. This game was designed not only for fun but also to help future students understand core game development concepts in C++. It has been specifically tested for compatibility on Raspberry Pi and arcade machines.

The team has decided to create a clone of the games 'DX' and 'Breakout', by using C++ and Splashkit to demonstrate the capapbilities available to splashkit. Swanny and Norman have been the coder's behind the game, while Tulsi has worked on the documentation and testing the game on rapsberry Pi, and Harney have worked on both documentation and the game sprites. The game is made to assist future students in developing games and understanding the fundamentals of C++ and the coding language with Splashkit. The game is also made to test splashkit's capabilities with Raspberry Pi and arcade style games thanks to the work of Tulsi. DXball/Breakout is one of two new products being developed, alongside the Asteroid's game done by Phil Williams, Riley Michael and Ro Wern Ong.

## Purpose

This application/game is designed to demonstrate and explore the capabilities of SplashKit, an open-source Software Development Kit (SDK) created with the purpose of reducing the overhead required for truly technical coding.

SplashKit is primarily used for coding 2D games with unrestricted creativity and have a grounded knowledge of C++. To show the efficiency and working of this software we have decided to create a DX Ball Game, also known as Breakout, which is an arcade video game designed to be played on arcade machines and raspberry pi-based units. The functionality of the game can also be later extended to other gaming platforms like mobiles, PCs and console environments and is open for interpretation of future developers.

## Development Team

| Member               | Role                                      |
|----------------------|-------------------------------------------|
| Swanny Aurellia      | Code                                      |
| Norman Spencer Harty | Code                                      |
| Tulsi Balamurali     | Documentation, Testing on Raspberry Pi    |
| Harney Halls         | Documentation, Game Sprites               |

## Programming Language & Software

### Language: C++

The programming language we have chosen is C++ and an open source like SplashKit. Main reason for the team to choose C++ because some members had more experience in the language. This language was used in SIT102 Introduction to Programming, which also made use of SplashKit.

C++ was chosen because it has imperative, object-oriented, and generic programming features and runs on various platforms like Windows, Linux, Unix, Mac, etc. C++ is an object-oriented programming language, which is a collection of commands instructing the computer with C++ ASCII text files. The language can support unions and structures that are a mix of stand-alone and put-together files. C++ programs are useful for low-level programming language and efficient for general purposes. They offer performance, memory efficiency, and high-level abstraction, within the language of the matter domain.

Two major problems in C++ is complex during a very large high-level program, C++ is employed for platform-specific application and commonly, for the actual OS or platform, the library set is typically chosen. C++ program is complex during a very large high-level program, C++ is employed for platform-specific application commonly, For the actual OS or platform, the library set is typically chosen.

Despite the disadvantages, the main reason for the team to choose C++ because some members had more experience in the language. This language was used in SIT102 Introduction to Programming, which also made use of SplashKit. Since the team had a clear language preference, C++ was chosen as the way to go.

### Software Used

- **GitHub**: Version control and collaborative coding.
- **Microsoft Teams**: Communication and document sharing.
- **MSYS2**: Provides a Unix-like environment on Windows for building and running SplashKit games.
- **Visual Studio**: Code editor for developing and debugging.

## Game Description

DX Game follows the classic brick-breaking format: players control a paddle to bounce a ball toward bricks, aiming to clear all bricks without letting the ball fall past the paddle. The game progresses through multiple levels, each introducing new gameplay elements and challenges.

![DX-Ball](https://images.sftcdn.net/images/t_app-cover-l,f_auto/p/0f5173aa-96da-11e6-9405-00163ec9f5fa/4242823519/dx-ball-2-screenshot.jpg)

The game would have an opening screen that would allow the player to begin the game, including the name of the game, Thoth Tech company, and Splashkit. The game would run by allowing the player to move the platform left or right, or the x axis. The ball bounces between the walls and the bricks, and the platform. The goal is to break all the bricks on screen without the ball falling to the floor. The player would need to ensure the ball is able to be deflected off of the platform each time it returns. Once the ball hits the floor (past the platform), the player would be met with a game over screen.

## Game Mechanics

### Controls

#### Gameplay Controls for PC

- **Left Arrow** – Move the paddle to the left.
- **Right Arrow** – Move the paddle to the right.

#### The controls on PC for the user interface elements

- **Left Arrow** – Swap between the initials being selected during high score nickname input.
- **Right Arrow** – Swap between the initials being selected during high score nickname input.
- **Up Arrow** – Swap to the next letter when inputting initials for high score nickname.
- **Down Arrow** – Swap to the previous letter when inputting initials for high score nickname.
- **Left Control** - When the user interface asks for you to press ``1``, it is waiting/checking for 'Left Control'.
- **Left Alt** - When the user interface asks for you to press ``2``, it is waiting/checking for 'Left Alt'.
- **'1' Key** - When the user interface asks for you to press ``Start``, it is waiting/checking for the number '1'.

### Types of Bricks

1. **Single Collision Bricks**: Break upon a single hit.
2. **Dual Collision Bricks**: Require two hits to break, adding moderate difficulty.
3. **Hidden Bricks**: Invisible initially, revealed upon the first hit and destroyed on the second.

### Scoring System

1. **Sensing the breakage of the brick**: The ``brick_data`` structure contains the brick's hit point. Each time the brick collides with a ball, the value of the hit point is reduced. When the value hits ``0``, the brick is broken and score is added.
2. **Calculating scores in the game**: The scoring system is ``Ax1`` point added to the score when a brick is broken, where ``A`` is the amount of the points accumulated by the player until that point in the game. Each time a block is broken, the score is increased by one unit. When the ball finally goes out of scope, the final value on ``A`` is displayed.
3. **Proceeding to the next level**: The ``remaining_blocks`` variable determines how many bricks are left in the game. It has a predefined value pertaining to that level depending on the number of blocks in the level. Once it reaches zero, the Boolean variable ``next_level`` becomes true and the function to spawn the next level is called.

### Power-Ups

1. **Multiple Balls** – Based on the score limiter, multiple balls can be generated to break the blocks much more effectively and easily.
2. **Score Multipliers** -  Temporarily multiplies all score gain by the stated value of the multiplier.

## Levels

We currently have four levels that each introduce a new gameplay mechanic, which are the different types of bricks in this case.

1. **Level 1** introduce basic gameplay with single collision bricks and making thee player familiar with the existing gameplay.
2. **Level 2** is updated with dual collision blocks to entertain the player with moderate difficulty leading to the next level.
3. **Level 3** introduces hidden blocks to show and test the player’s capabilities that has been earned so far in the game.
4. **Level 4** combines everything we had tested the player for. We will have a combination of all the different types of bricks and players will be encouraged to use the powerups in order to clear the level.

The goal of the four levels is to showcase the game we have built so far. It combines all the gameplay mechanics and items to demonstrate the work that we have been involved so far. Future teams can add more levels with increasing difficulties whilst also giving players more powerups and scoring opportunities.

Originally, the idea was decided between 10 set levels, or the ability to have infinite levels with chances of repetative levels. The idea was chosen for, at the time, 10 levels to be included. It was then changed to 4 levels, as there was nothing new to be introduced after level 4.

Future ideas for the game can include lives of the player (standard of 3 lives), with the chance to gain more lives through powerups. Different powerups, such as a larger ball, or smaller platform, or 'bombs' to explode large chunks of bricks. There can also be disadvantages to the player too, such as the smaller platform, lose a life or others.

### Level Design

The levels are designed to progressively introduce new mechanics and test the player’s skill. The levels serve as a showcase of the game’s mechanics, with each level combining existing features and gameplay elements.

## Environment Setup

The software involved are the MSYS terminal to compile and run SplashKit games and a code editor such as Visual Studio to write the code. MSYS2 is software distribution and a building platform for Windows. It provides a Unix-like environment, a command-line interface and a software repository making it easier to install, use, build and port software on Windows. It is an independent rewrite of MSYS, based on modern Cygwin (POSIX compatibility layer) and MinGW-w64 with the aim of better interoperability with native Windows software.

We have used basic shapes like circle for the ball and rectangle for the blocks and paddle for the initial development of the game. We replaced these basic structures with sprites for bettering the cosmetics and the aesthetics of the game. Sprites are created using basic software like MS Paint.

The draw_blocks function in the code was made to help drawing all the blocks to the environment. This function is mainly used to take an array of blocks and iterate it to draw each block on the scene. If a particular block has been broken, it will not be drawn to the environment.

### Visual Elements

- **draw_blocks()**: Renders the array of blocks, ensuring only intact blocks are displayed.
- **Sprite Assets**: Replaces basic shapes with custom sprites to enhance visual appeal.

## Sprites

The game uses custom sprites to improve the aesthetics:

- **Bricks**: Different colors indicate brick types and their durability.
- **Score Multiplier Gauge**: Displays active multiplier values (e.g., x2, x3).
- **Power-Up Icons**: Drop-down icons representing active power-ups.
- **Paddle and Ball**: Unique sprites for visual appeal.
- **Score and Multiplier Text**: Helps players keep track of their progress.

## Future Improvements

The game’s modular design allows for easy expansion. Potential future improvements include:

1. **Additional Levels**: Introduce new levels with different layouts and challenges.
2. **Lives System**: Add a standard 3-life system, with power-ups for gaining additional lives.
3. **Advanced Power-Ups**: Add items like larger paddles, multi-ball, and explosive “bomb” bricks.
4. **Penalties**: Introduce drawbacks like smaller paddles or faster balls to increase difficulty.
5. **High Scores**: Implement a high score system to track player performance across sessions.
6. **Sound Effects**: Add sound effects for ball collisions, brick breaks, and power-up activations.

**DX Game** is a collaborative project showcasing the SplashKit SDK’s potential in arcade-style games. With its approachable mechanics, modular design, and exciting gameplay, it provides a fun and educational platform for both players and developers.

## Notes

# Notes post refactor April 2024

The codebase has been brought in-line with modern cpp convention and is far more ogranised in terms of its file structure, declaration patterns and slioing of functionality.

There are some major areas of improvement which have been identified and should be much easier to reason about now:

- Many functions implicitly access and mutate global state, this should be rectified prior to anything else as it is generally very bad practice and makes the codebase far more difficult to reason about. Any and all mutable data scoped to a function should be done so explicitly.
- Many antipatterns currently exist where one routine refers to and mutates both the abstract state of the game AND informs / executes rendering functionality, these should be completely decoupled.

ie. `end_game()` should only be responsible for updating the game state to reflect the game ending (it should also accept the game state as an argument), and not also be responsible for rendering the game over screen (or drawing _anything_).

- Some fun stuff could be the redesign of level generation patterns to be a function of gamestate values rather than static function per level etc.

/- Oscar Harris <T1 2024>