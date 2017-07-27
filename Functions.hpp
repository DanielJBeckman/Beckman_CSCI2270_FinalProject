//
//  Functions.hpp
//  Final Project 2270
//
//  Created by DANIEL BECKMAN on 7/24/17.
//  Copyright © 2017 DANIEL BECKMAN. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp


#include <string>
#include <vector>

using namespace std;


struct Vert;  //Vertex structure prototype.

struct adjVert{ //Adjacent builder struct for adding edges
    
    int miles;
    
    Vert *v;
};

struct Vert{    //Vert is my vertex building struct. Used in the creation of my city graph and dijkstra alg.
    
    string city;
    
    int distance;
    
    bool visited;
    
    bool isSolved;
    
    Vert *parent;
    
    vector <adjVert> adj;};


class Route  //Route class. Stores my fuctions and BST/Linked List pointers and variables. Functions are described in detail 
    //in Functions.cpp
{

private:
    
   // string StartV;
    
    void addVert();
    
    void addEdge(string data);
    
    void AddLL();
    
    void AddT();
    
   // string EndV;
    
    vector <Vert> vertices;
    
    void Dijkstra(string starting, string destination);
    
    void PrntT(Route *snitch);
    
    int sum;
    
    string Dep;
    
    string Arr;
    
    string Fare;
    
    Route *Root;
    
    Route *current;
    
    Route *left;
    
    Route *right;
    
    Route *parent;
    
    Route *next;

    
public:
    
    Route();
    
    ~Route();
    
    void PrntR(bool sim);
    
    void PrntG();
    
    void PrntT();
    
    void BuildG();
    
    void BuildT();
    
    void Scenario();
    
    void getFare();
    
    void Sum(string dep, string arr);
    
    
    
    Route *search(string Depart);
    
    bool sim;
    
    bool Price;
};








#endif /* Functions_hpp */
