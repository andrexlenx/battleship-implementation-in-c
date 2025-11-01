# Battaglia Navale / Battleship

## Description
This is an implementation of the classic board game Battleship developed in C. Originally created in 2020 as a school assignment, the project's objective was to create a static game using the Windows library for a graphical text interface. The game uses the Windows.h library for console cursor manipulation to create a text-based graphical interface with ASCII characters. Players can position their fleet on a 10x10 grid and take turns firing at the enemy board.

The game features:
- A complete fleet of 5 ships of different sizes (ranging from 2 to 5 squares)
- Interactive ship placement with rotation capabilities
- Turn-based gameplay following traditional Battleship rules

The computer opponent starts with random targeting, but once it hits a ship, it systematically attacks adjacent squares to sink the entire vessel. The game ends when either the player or the computer sinks all of the opponent's ships.

## Compilation and Execution

> **Note:** This program relies on the `windows.h` library and will only work on **Windows** systems.

1. Download the source file: `battleship.c`
2. Compile the program using **GCC**:

   ```bash
   gcc battleship.c -o battleship.exe
   ```
3. Run the program by either:

   * Double-clicking `battleship.exe`, or
   * Executing it from the terminal:

     ```bash
     battleship.exe
     ```
