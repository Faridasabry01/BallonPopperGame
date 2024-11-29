# Balloon Popper Game

## Overview Balloon Popper is a C++ game where players pop rising
balloons and save falling ones. It features randomized gameplay, a
dynamic scoring system, and a restart function.

## Features 
1. **Randomized Balloon Behavior**: 
- Balloons are generated at random positions and rise upward.
- Red and yellow balloons offer different point values.

2. **Dynamic Scoring System**:
 - Popping red balloons adds **1 point**, yellow balloons add **2 points**.
 - Balloons hitting the
ceiling reduce the score by **1 point**.

3. **Basket Mechanism**:  - Use the basket to catch falling
balloons and earn **1 point** for each saved balloon.

4. **Time Limit**:  - Each game session lasts **20 seconds**.

5. **Restart Capability**:  - Restart the game with **F1**,
generating a new set of balloons.

6. **Graphical Elements**:  - Uses OpenGL for rendering balloons,
basket, and background.

## Installation Guide: 
1. **Clone the Repository**:
```bash
git clone https://github.com/Faridasabry01/balloon-popper-game.git
```

2. **Compile the Code**:
- Ensure you have a C++ compiler and OpenGL libraries installed.
 - Use the provided `.cbp` (Code::Blocks Project) file or compile manually:
 - ```bash
   g++ main.cpp Balloons.cpp -o BalloonPopper -lGL -lGLU -lglut
    ```

3. **Run the Game**:
 ```bash
    ./BalloonPopper
```

## How to Play: - **Pop Balloons**:  
- Left-click on balloons to pop them before they hit the ceiling.
 - Each red balloon gives **1 point**, and yellow balloons give **2 points**.
- **Catch Falling Balloons**:  - Use arrow keys to move the basket and save falling balloons for **1 point** each. - **Restart the Game**:
 - Press **F1** to reset the game and start again.

## Future Improvements: 
- Add sound effects for popping and saving balloons.
- Introduce difficulty levels with increasing speed and balloon count.
 - Add more balloon colors and unique point values.
 -Create a high-score tracking system.


