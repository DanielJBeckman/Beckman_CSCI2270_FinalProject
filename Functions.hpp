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


struct Tree;

struct Vert;

struct adjVert{
    
    int miles;
    
    Vert *v;
};

struct Vert{
    
    string city;
    
    int distance;
    
    bool visited;
    
    bool isSolved;
    
    Vert *parent;
    
    vector <adjVert> adj;};


class Route
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
    
    void LLDel(Route *head);
    
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
    
    void deltree(Route *target);
    
    Route *search(string Depart);
    
    bool sim;
    
    bool Price;
};








#endif /* Functions_hpp */
