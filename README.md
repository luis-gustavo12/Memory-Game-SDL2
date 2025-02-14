# Memory Game SDL 2

## Description

This project was intended to be a game where you need to hit the squares in order, and remember the ones you hit before


## Requirements

- SDL2 library
- CMake
- C Compiler


## Installation

1. Download it on your machine. Since it's built using SDL, it is multi plataform

``` git clone https://github.com/luis-gustavo12/Memory-Game-SDL2 ```

2.

On Linux, go to build folder

``` cd build```

3. Then run CMake command

```cmake ..```


4. Now use build command

``` make ```

5. Now run the binary

```./MEMORY_GAME```


# Change Log

## [1.10] -> 11 / Jan / 2025

### New
- Added CMake configuration, and adapted paths to recognize paths through different OSs


## [1.11] -> 18 / Jan / 2025

## Fix

- Fixed exit button display

### New

- Added attribute background to buttons

## [1.12] -> 22 / Jan / 2025

## Fix

- Fixed circular inclusion prone design
- Added refactoring for game main module

## [1.13] -> 25 / Jan / 2025

### New

- Improved exit button appearance and made it functional

## [1.14] -> 27 / Jan / 2025

## Fix

- Fixed a game state bug that didn't make player start on the right game logic state

## [1.15] -> 28 / Jan / 2025

## Fix

- Gave different background to guessing and hitting states

## [1.16] -> 30 / Jan / 2025

## Fix

- Fixed Guessing Queue Bug when pressed play again button

## [1.17] -> 13 / Feb / 2025

## Fix

- Fixed a bugging count on the order of the squares
- Added logging module


## [1.17] -> 14 / Feb / 2025

- Fixed some compiler warning issues, and added specific compiler warnings