# Maze Solving Robot

## Project Overview

An autonomous robot designed to navigate through complex mazes using a right-hand wall-following algorithm. The robot utilizes ultrasonic sensors for obstacle detection and real-time decision-making, with a servo motor for directional sensing and Arduino-based control logic for movement execution.

## Key Features

- **Autonomous Navigation:** Navigates mazes without human intervention using sensor data.
- **Right-Hand Wall-Following Algorithm:** Implements a systematic approach for maze traversal.
- **Ultrasonic Sensors:** Detects and measures distances to walls and obstacles.
- **Servo Motor:** Rotates the ultrasonic sensor for multi-directional scanning.
- **Microcontroller (Arduino):** Processes sensor data and executes navigation logic.
- **Motor Driver:** Controls DC motors for precise movement and turns.

## System Components

| Component         | Functionality                                  |
|-------------------|------------------------------------------------|
| Ultrasonic Sensor | Detects walls/obstacles, measures distance     |
| Servo Motor       | Rotates sensor for front/right wall detection  |
| Arduino           | Processes data, executes control logic         |
| Motor Driver      | Drives DC motors for movement and turns        |
| Chassis & Wheels  | Provides structure and mobility                |

## Workflow

1. **Initialization:** Sensors, servo, and motors are initialized.
2. **Environment Sensing:** Ultrasonic sensor scans front and right for walls/obstacles.
3. **Decision-Making:** Applies right-hand wall-following:
   - **Move Forward:** If path is clear and right wall is present.
   - **Turn Right:** If front is blocked, space available right.
   - **Turn Left:** If right and front are blocked.
4. **Movement Execution:** Motor commands issued based on decision.
5. **Position Adjustment:** Minor corrections to maintain optimal wall distance.
6. **Continuous Operation:** Cycle repeats until maze is solved or stopped.

## Results & Challenges

- **Partial Autonomy Achieved:** Successfully navigated sections of the maze; faced difficulties with complex turns and dead ends.
- **Challenges:** Space/wire management, sensor accuracy, and algorithm refinement.
- **Future Improvements:** Multiple sensors for accuracy, optimized pathfinding, adaptation to dynamic environments.

## Team

- **Adarsh Kumar** (2023CHB1058)
- **Ankur Praveen Prasad** (2023CHB1059)
- **Anurag Pritam Sonowal** (2023CHB1060)
- **Arnav Dubey** (2023CHB1062)
- **Vishnu Roshan** (2023CHB1089)

## Applications

- **Rescue missions**
- **Automated logistics**
- **Exploration robotics**
- **Educational robotics**

---

*Note: This robot serves as a foundation for advanced and accurate autonomous navigation systems.*[1]
