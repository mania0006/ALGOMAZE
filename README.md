# 🎮 ALGOMAZE - Graphics Edition

A beautiful maze navigation game built with C++ and SFML 3.0, featuring multiple difficulty levels, pathfinding visualization, and an engaging gameplay experience.

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-3.0-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Building](#building)
- [Usage](#usage)
- [Gameplay](#gameplay)
- [Project Structure](#project-structure)
- [Controls](#controls)
- [Screenshots](#screenshots)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview

ALGOMAZE is a maze navigation game where players must find their way from the start position to the goal. The game features three difficulty levels, with Level 3 introducing dynamic maze generation, key collection mechanics, and obstacles like mud that slow down movement.

The game uses a Model-View-Controller (MVC) architecture pattern, making it well-organized and maintainable.

## ✨ Features

- **Three Difficulty Levels**
  - **Easy**: Simple maze layout perfect for beginners
  - **Medium**: Complex pathfinding with more challenging routes
  - **Hard**: Dynamically generated maze with keys, obstacles, and mud patches

- **Advanced Game Mechanics**
  - Key collection system (required for Level 3)
  - Mud obstacles that slow down movement
  - Real-time pathfinding visualization
  - Step counter and timer tracking

- **Beautiful Graphics**
  - Modern UI with gradient backgrounds
  - Smooth animations and visual effects
  - Professional card-based level selection
  - Glowing goal indicators

- **Pathfinding Algorithm**
  - BFS (Breadth-First Search) for shortest path calculation
  - Real-time path visualization in UI
  - Cached path calculations for performance

- **User Experience**
  - Player name personalization
  - Win screen with detailed statistics
  - Legend panel for game elements
  - Responsive controls (Arrow keys or WASD)

## 📦 Requirements

### Dependencies

- **C++ Compiler** (C++17 or later)
  - GCC 7+ / Clang 5+ / MSVC 2017+
- **SFML 3.0** library
  - Graphics, Window, and System modules
- **CMake** (optional, for easier building)

### System Requirements

- **Windows**: Windows 7 or later
- **Linux**: Most modern distributions
- **macOS**: macOS 10.12 or later

## 🔧 Installation

### Installing SFML 3.0

#### Windows
1. Download SFML 3.0 from [SFML official website](https://www.sfml-dev.org/download.php)
2. Extract to a directory (e.g., `C:\SFML`)
3. Set environment variables or configure your build system

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### macOS
```bash
brew install sfml
```

## 🏗️ Building

### Manual Compilation

#### Windows (MinGW/MSVC)
```bash
# Compile all source files
g++ -std=c++17 main.cpp GameEngine.cpp Maze.cpp NameScreen.cpp LevelScreen.cpp GameScreen.cpp -o AlgoMaze.exe -lsfml-graphics -lsfml-window -lsfml-system

# Or using MSVC
cl /EHsc /std:c++17 main.cpp GameEngine.cpp Maze.cpp NameScreen.cpp LevelScreen.cpp GameScreen.cpp /link sfml-graphics.lib sfml-window.lib sfml-system.lib
```

#### Linux
```bash
g++ -std=c++17 main.cpp GameEngine.cpp Maze.cpp NameScreen.cpp LevelScreen.cpp GameScreen.cpp -o AlgoMaze -lsfml-graphics -lsfml-window -lsfml-system
```

#### macOS
```bash
clang++ -std=c++17 main.cpp GameEngine.cpp Maze.cpp NameScreen.cpp LevelScreen.cpp GameScreen.cpp -o AlgoMaze -lsfml-graphics -lsfml-window -lsfml-system
```

### Using CMake (Recommended)

Create a `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 3.10)
project(AlgoMaze)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)

add_executable(AlgoMaze
    main.cpp
    GameEngine.cpp
    GameEngine.hpp
    Maze.cpp
    Maze.hpp
    NameScreen.cpp
    NameScreen.hpp
    LevelScreen.cpp
    LevelScreen.hpp
    GameScreen.cpp
    GameScreen.hpp
    ScreenBase.hpp
    Common.hpp
    GameState.hpp
)

target_link_libraries(AlgoMaze PRIVATE SFML::Graphics SFML::Window SFML::System)
```

Then build:
```bash
mkdir build
cd build
cmake ..
make
```

## 🎮 Usage

### Running the Game

After compilation, simply run the executable:

```bash
# Windows
./AlgoMaze.exe

# Linux/macOS
./AlgoMaze
```

### Game Flow

1. **Name Input Screen**: Enter your name (max 15 characters)
2. **Level Selection**: Choose difficulty (1-3)
3. **Gameplay**: Navigate to the goal
4. **Win Screen**: View your statistics

## 🕹️ Gameplay

### Objective

Navigate your player (green circle) from the starting position to the goal (red square) using the shortest path possible.

### Level Details

- **Level 1 (Easy)**: Simple maze with straightforward paths
- **Level 2 (Medium)**: More complex layout with multiple routes
- **Level 3 (Hard)**: 
  - Dynamically generated maze using DFS algorithm
  - Requires collecting a key before reaching the goal
  - Contains mud patches that slow movement
  - Larger maze (15x20)

### Game Elements

- **Player** 🟢: Your character (green circle)
- **Goal** 🔴: Destination (red square, requires key for Level 3)
- **Walls** ⬛: Impassable barriers
- **Paths** ⬜: Walkable areas
- **Key** 🟡: Collectible item (Level 3 only)
- **Mud** 🟤: Slows down movement (Level 3 only)

## 📁 Project Structure

```
DSA/
├── main.cpp                 # Entry point
├── GameEngine.hpp/cpp       # Main controller (MVC)
├── Maze.hpp/cpp             # Game model (maze logic)
├── NameScreen.hpp/cpp       # Name input screen
├── LevelScreen.hpp/cpp      # Level selection screen
├── GameScreen.hpp/cpp       # Gameplay rendering
├── ScreenBase.hpp           # Base class for screens
├── Common.hpp               # Shared constants and structures
├── GameState.hpp            # Game state enumeration
└── README.md                # This file
```

### Architecture

The project follows the **MVC (Model-View-Controller)** pattern:

- **Model**: `Maze` class - handles game logic, pathfinding, movement
- **View**: `NameScreen`, `LevelScreen`, `GameScreen` - handle rendering
- **Controller**: `GameEngine` - manages state transitions and input

## ⌨️ Controls

### Movement
- **Arrow Keys** or **WASD**: Move player
  - ↑ / W: Move up
  - ↓ / S: Move down
  - ← / A: Move left
  - → / D: Move right

### Navigation
- **1-3**: Select level (on level selection screen)
- **ENTER**: Confirm name input
- **ESC**: Exit game (during gameplay or win screen)

## 📸 Screenshots

> _Add screenshots of your game here!_

Example screenshots to include:
- Name input screen
- Level selection screen
- Gameplay view
- Win screen

## 🛠️ Technical Details

### Algorithms Used

- **DFS (Depth-First Search)**: Maze generation for Level 3
- **BFS (Breadth-First Search)**: Shortest path calculation
- **Recursive Backtracking**: Maze generation algorithm

### Performance Optimizations

- Cached path calculations
- Movement timing to prevent input spam
- Efficient rendering with SFML

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👨‍💻 Author

**Your Name**
- GitHub: [@yourusername](https://github.com/yourusername)
- Email: your.email@example.com

## 🙏 Acknowledgments

- SFML team for the excellent graphics library
- Inspiration from classic maze games
- Community feedback and testing

## 📞 Support

If you encounter any issues or have questions, please open an issue on GitHub.

---

**Enjoy playing ALGOMAZE! 🎮✨**


