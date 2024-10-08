# DXBallGame

1. Requires a [SplashKit installation](https://splashkit.io/installation/).
2. Build using `skm clang++ *.cpp -o dxballgame` while in the project folder.
3. Run using `./dxballgame` while in the project folder.

_See also: usage documentation for [skm](https://github.com/splashkit/skm/blob/master/README.MD) and [SplashKit](https://splashkit.io/guides/using-splashkit/0-overview/)._

## Technical overview

- **Language:** C++
- **Current scope:** Medium
- **Code quality:** Good
- **Gameplay implementation:** Complete

## Gameplay overview

A hectic brick-breaker (Breakout clone) supporting one player. The player controls a paddle at the bottom of the screen, which is used to bounce one or more balls up to hit and destroy bricks. Levels are cleared by destroying all bricks.

### Player 1 Controls

| Action        | Key             |
|---------------|-----------------|
| Rotate Left   | Left arrow      |
| Rotate Right  | Right arrow     |
| START         | SPACE           |
| 1             | Z               |
| 2             | X               |
| Cycle initial | Up / Down arrow |

## Other notes

- An old readme by the original authors and the refactorer is available in `/docs/`.

## Screenshots

![](/docs/screenshot-01.png)

![](/docs/screenshot-02.png)

## Credits

Originally created by 2023-T1 team:

- Swanny Aurellia
- Norman Spencer Harty
- Tulsi Balamurali
- Harney Halls

Refactored in 2024-T1 by Oscar Harris.
