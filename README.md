<img width="748" height="411" alt="FaulkensTerminal" src="https://github.com/user-attachments/assets/28f98821-b78a-43ab-bcc8-2f4a0656307a" />

# Project Faulken - C++ Version

This is a C++ port of the Python text-based adventure game Project Faulken.

## Project Structure

```
cpp_version/
├── CMakeLists.txt          # Build configuration
├── include/                # Header files
│   ├── Game.h
│   ├── Player.h
│   ├── Console.h
│   ├── GameOver.h
│   ├── MapBase.h
│   └── nlohmann/json.hpp   # (download and place here)
└── src/                    # Implementation files
   ├── main.cpp
   ├── Game.cpp
   ├── Player.cpp
   ├── Console.cpp
   ├── GameOver.cpp
   └── MapBase.cpp
```

## Dependencies

- **CMake** 3.10 or higher
- **C++17 compiler** (g++, clang, or MSVC)
- **nlohmann/json** (header-only library)

## Setup Instructions

### 1. Download nlohmann/json

The project uses the header-only `nlohmann/json` library. Download it here:
https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp

Then place it in the `include/nlohmann/` directory:
```bash
mkdir -p include/nlohmann
# Download json.hpp to include/nlohmann/json.hpp
```

Or, if you have `curl`:
```bash
mkdir -p include/nlohmann
curl -o include/nlohmann/json.hpp https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
```

### 2. Build the Project

```bash
cd cpp_version
mkdir -p build
cd build
cmake ..
make  # or 'cmake --build .' on Windows
```

### 3. Run the Game

```bash
./faulken    # Linux/macOS
# or
faulken.exe  # Windows
```

## Game Commands

- `<look>` - Look around your current location
- `<take>` - Pick up items
- `<inv>` - Check your inventory
- `<map>` - Display the game map
- `<nav>` - Show available exits for current room
- `<save>` - Save your progress
- `<load>` - Load a saved game
- `<help>` - Show available commands
- `<scan_id>` - Scan your ID badge
- `<north>`, `<south>`, `<east>`, `<west>` - Navigate between rooms
- `<use term>` - Use terminal (in terminal rooms)
- `<quit>` - Exit the game

## Features

-  **Animated title screen** - Full ASCII art with animated text (from titleScreen.py)
-  **Core game loop** - Room navigation, player actions, inventory
-  **Fixed navigation system** - Proper directional movement (north/south/east/west) with switch-based routing
-  **Inventory system** - Take items, display inventory, item management
-  **Save/Load functionality** - Basic game state persistence
-  **Terminal/Console interface** - In-game terminal with credential checking and decryption
-  **Navigation help** - Use `<nav>` command to see available exits
-  **Game Over screen** - Animated farewell text
-  **ANSI color support** - Red text styling throughout
-  **Cross-platform support** - Builds on Linux, macOS, and Windows
-  **Animated title screen** - Full ASCII art with animated text (from titleScreen.py)
-  **Core game loop** - Room navigation, player actions, inventory
-  **Fixed navigation system** - Proper directional movement (north/south/east/west) with switch-based routing
-  **Inventory system** - Take items, display inventory, item management
-  **Save/Load functionality** - Basic game state persistence
-  **Terminal/Console interface** - In-game terminal with credential checking and decryption
-  **Navigation help** - Use `<nav>` command to see available exits
-  **Game Over screen** - Animated farewell text
-  **ANSI color support** - Red text styling throughout
-  **Cross-platform support** - Builds on Linux, macOS, and Windows

## Architecture and State Management

This version is moving toward a cleaner game model with structured room state.

Key design goals:
- Use `enum class Room { ZeroCentral, ZeroWest, ZeroEast, ... }` instead of raw integers
- Store room data in a centralized structure containing:
  - `description`
  - `exits`
  - `items`
  - `map function`
  - `special actions`
- Replace nested `switch`/`case` navigation with a data-driven table of room exits
- Serialize game state using a proper struct/class for save/load instead of ad hoc file parsing

Benefits:
- Easier to add and modify rooms
- Clearer and more maintainable navigation logic
- Lower risk of inconsistent state
- Better separation between game logic and rendering
- Cleaner save/load behavior for future expansion

## TODO / Future Improvements

- [ ] Complete all room descriptions and interactions
- [ ] Full JSON serialization for game saves (inventory)
- [ ] Sound effects support
- [ ] Complete terminal decryption mini-game
- [ ] Additional advanced game features
