# Warthog Holiday Work

<p align="center">
 <img src="https://github.com/Brenocq/WarthogHolidayWork/blob/master/Images/StraightLinePath.png" height="300">
 <img src="https://github.com/Brenocq/WarthogHolidayWork/blob/master/Images/PFandA*.png" height="300">
</p>

## Introduction
The objective of this work is to use object orientation to simulate the pathfinding algorithms with soccer robots. This work was developed using a QT application to facilitate the visualization of the path generated. Currently the only algorithms being tested are Potential Field and A * in conjunction with Quad-Tree. This work was proposed by the Warthog team (USP, São Carlos).

## OOP Classes

<p align="center">
 <img src="https://github.com/Brenocq/WarthogHolidayWork/blob/master/Images/UMLgraph.png" height="400">
</p>

The image above shows the relationships between classes.

## Pathfinding
For each selected robot it is possible to choose which type of pathfinding algorithm will be used to generate the path. To change the destination just change the position of the pink square. You can still change the position of the currently selected robot and other robots to see how the algorithm behaves. To change the position, just drag and drop.

After clicking the `Run` button, the robots will start moving along their paths. new paths are calculated as the robots move.

#### Potential Field

<p align="center">
 <img src="https://github.com/Brenocq/WarthogHolidayWork/blob/master/Images/PFPath.png" height="400">
</p>

#### Quad-tree with A*

<p align="center">
 <img src="https://github.com/Brenocq/WarthogHolidayWork/blob/master/Images/QuadTreeAndA*Path.png" height="400">
</p>

## How to execute

To execute this program with Qt go to `File -> Open file or project...` inside **Qt Creator** and open the project file `WarthogHolidayWork.pro`. Once you have opened the project, click the green button in the bottom right corner.
