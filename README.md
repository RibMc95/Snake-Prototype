# Snake Game

A classic Snake game implementation in C++ using SFML (Simple and Fast Multimedia Library).

## Overview

This is a traditional Snake game where the player controls a snake to eat food and grow longer while avoiding collisions with walls and its own body. The game features:

- Smooth snake movement with keyboard controls
- Food generation and collision detection
- Score tracking
- Game over detection
- SFML graphics rendering

## Prerequisites

Before compiling and running the game, you need to have the following installed:

### SFML Library

You need SFML (Simple and Fast Multimedia Library) installed on your system.

#### On Ubuntu/Debian

```bash
sudo apt update
sudo apt install libsfml-dev
```

#### On Windows (using MSYS2/MinGW)

```bash
pacman -S mingw-w64-x86_64-sfml
```

#### On macOS (using Homebrew)

```bash
brew install sfml
```

### Build Tools

- **g++** compiler with C++17 support
- **make** utility

## File Structure

```
Snake/
├── main.cpp        # Main game loop and window management
├── Snake.h         # Snake class definition and implementation
├── Food.h          # Food class for food generation
├── Grid.h          # Grid utilities (if used)
├── Queue.h         # Queue data structure utilities
├── Makefile        # Build configuration
```

## Compilation

### Using Make (Recommended)

The project includes a Makefile for easy compilation:

```bash
# Navigate to the Snake directory
cd "c:\Your-Directory\Snake"

# Compile the game
make

# Or compile and run in one command
make run
```

### Manual Compilation

If you prefer to compile manually:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o snake_game
```

## Running the Game

### After using Make

```bash
./snake_game
```

### Or use the Make run target

```bash
make run
```

## Game Controls

- **Arrow Keys** or **WASD**: Control snake direction
  - ↑ or W: Move up
  - ↓ or S: Move down
  - ← or A: Move left
  - → or D: Move right
- **ESC**: Quit the game

## Game Rules

1. **Objective**: Eat the red food to grow your snake and increase your score
2. **Movement**: The snake moves continuously in the current direction
3. **Growing**: Each time the snake eats food, it grows by one segment
4. **Game Over**: The game ends if the snake:
   - Hits the window boundaries
   - Collides with its own body
5. **Scoring**: Your score increases each time you eat food

## Game Configuration

You can modify these constants in `main.cpp` to customize the game:

- `WINDOW_WIDTH`: Game window width (default: 800)
- `WINDOW_HEIGHT`: Game window height (default: 600)
- `SEGMENT_SIZE`: Size of each snake segment in pixels (default: 20)
- Frame rate limit (default: 10 FPS for classic snake speed)

## Troubleshooting

### SFML Not Found

If you get errors about SFML not being found:

1. Make sure SFML is properly installed
2. Check that the SFML libraries are in your system's library path
3. You may need to specify the path to SFML libraries manually

### Compilation Errors

- Ensure you have C++17 support: `g++ --version`
- Check that all header files are present
- Verify SFML installation with: `pkg-config --libs sfml-all`

### Performance Issues

If the game runs too fast or too slow:

- Modify the framerate limit in `main.cpp`
- Adjust `window.setFramerateLimit(10)` to your preferred speed

### "Setting vertical sync not supported" Warning

If you see a warning about vertical sync not being supported:

- This is a harmless warning that can occur on some systems
- The code already disables vertical sync with `window.setVerticalSyncEnabled(false)`
- The game uses framerate limiting instead, which is more suitable for this type of game
- You can safely ignore this warning as it doesn't affect gameplay

## Cleanup

To remove compiled files:

```bash
make clean
```

This will remove the `snake_game` executable and any temporary files.

## Development

This project demonstrates:

- Object-oriented programming with C++
- Game loop implementation
- SFML graphics library usage
- Basic collision detection
- Data structures (deque for snake body)

## Dependencies

- **SFML 2.5+**: Graphics, window management, and input handling
- **C++17**: Modern C++ features
- **Standard Library**: STL containers and algorithms

---

Enjoy playing the Snake game! 
