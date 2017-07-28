# DataStructures
Final_PRJ

In 2010 iceland’s Eyjafjallajokull erupted spewing volcanic ash into the upper atmosphere. Air traffic for 32 European counties where affected. I am going to recreate this problem using a graph. I will establish air routes that require connection flights in northern Europe when I build the graph. After which I will initiate the scenario and use Dijkstra’s Algorithm (And maybe another one) to recalculate the routes. Then I will pull fair costs from an established BST w/ linked lists to give airfare prices before and afterwords. 

Project Summary

This program builds threeish structures. A graph of Air Traffic routes that hub through London before heading to New York. A Binary Search Tree/Link List hybrid that stores airfare. Once built, The user can find out how much it costs to get to new york from their departure city. This is just the setup. A menu will allow the user the chance to enter a simulation. 

The simulation

A volcano erupts in iceland and the ash closes London/Heathrow. There will be a description before the sim menu intiates. From here a new adjacency list loads in which London is essentially not an option. Using Dijkstra's alg, the routes are instantly recalculated and redrawn resualting in a new route through southern gateway cities. Additionally, the new airfare price is calculated by traversing and pulling Fare information from the BST/Link List. 

Practical Use

Airlines usually Hub in a major European city. They will then transfer all incoming flights of smaller planes to larger trans oceanic aircraft like a 747. They will typically also hub in a corresponding US east coast city like new york. If Iceland has another eruption, the air line will need to rapidly redeploy thier trans-atlantic fleet. This is a quick way to determine how to do that. Additionally, sometimes a different Data structure needs to work with an existing one. For this reason I used a BST/Link List hybrid and found a way to stich them together to merge data streams.


How to Run

This program has seven files. Main.cpp (Driver), Functions.hpp (header), Functions.cpp (function library), make up the actual program. City.txt, Route.txt, Fare.txt, and Sim.txt make up the data files for the different pieces. Simply keep them together, compile the program files and run. You will be prompted for the rest.

Dependencies
This program was compiled and run on xCode. If you run on xCode make sure to define your source folder.

System Requirements
This program should run on Mac and in a Unix. 

Daniel Beckman

Open issues/bugs
Make sure warnings are off. The program has several unintialized variables waiting on the user prompt. They do not effect the program.

