//
//  Functions.cpp
//  Final Project 2270
//
//  Created by DANIEL BECKMAN on 7/24/17.
//  Copyright © 2017 DANIEL BECKMAN. All rights reserved.
//  The file is the flesh out for all functions prototyped in the .hpp 
//
#include <iostream>
#include "Functions.hpp"
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

//Constructor - I kept this one pretty sparse. It covers some class pointer implementation and a few house 
//keeping variables.

Route::Route(){
    
    Price = false;

    sim = false;
    
    Root = nullptr;
    
    sum = 0;
    
    next = nullptr;
    

};

//Distructer will be called to destroy the linked lists and the BST. 

Route::~Route(){};


//Graph builder helper function - Creates Vertices and then links them with edges.

void Route::BuildG(){
    if (!sim){
        addVert();
    
        addEdge("Routes.txt");}
    else{
        addEdge("Sim.txt");}
    }


//Vertex add function - It uses a while loop to establish a Verticies for every city linked to the route.

void Route::addVert(){
    string data;
    ifstream inputFile;
    inputFile.open("City.txt");
    
    

    while(getline(inputFile, data, ',').good()){
        
        Vert v;
        v.city = data;
        v.distance = 0;
        v.visited = false;
        v.parent = nullptr;
        vertices.push_back(v);
        getline(inputFile, data);
    }}
    
 //Edge creator function - stitches the edges together using another text file.

void Route::addEdge(string data){
    string strt;
    string end;
    string mil;
    string null;
    
    
    ifstream inputFile;
    inputFile.open(data);
    
    while(getline(inputFile, strt, ',').good()){
        
        getline(inputFile, end, ',');
        getline(inputFile, mil, ',');
        getline(inputFile, null);
        //cout << strt << " " << end << " " << mil << endl;
        for(int i = 0; i < vertices.size(); i++){
            
            if(vertices[i].city == strt){


                for(int j = 0; j < vertices.size(); j++){
                    //cout << "\"" << vertices[j].city << "\" \"" << end <<"\"" << j << endl;
                    if(vertices[j].city == end && i != j){
                        //cout << "entered" << endl;
                        adjVert av;
                        av.v = &vertices[j];
                        av.miles = stoi(mil);
                        vertices[i].adj.push_back(av);}}}}}}

 //A Graph print function that is switched off. It helps understand the nature of the graph but is definately 
//a developer feature not to be included in the final program
    
void Route::PrntG(){
    //loop through all vertices and adjacent vertices
    cout<<"============================================================"<<endl;
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].city << " to:" << endl << endl;
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout << vertices[i].adj[j].v->city;
            cout<<" (Distance: "<< vertices[i].adj[j].miles << " miles)" << endl;
           // <<", visited: "<<vertices[i].adj[j].v->visited<<", parent: ";
           // if (vertices[i].adj[j].v->parent==nullptr)
                //cout<<" nullptr)"<<endl;
          //  else
                //cout<<vertices[i].adj[j].v->parent->city<<")"<<endl;
        }
        cout<<"============================================================"<<endl;
    }
}

//Dijkstra's Alg used in this case to first establish London as a hub and secondly to link people to thier New York destination
//as efficently as possible. Dijkstra grabs adjacents via BFS then jams them into a cue to be solved. The most efficent route remains while the 
//others are discontinued or overwritten

void Route::Dijkstra(string starting, string destination){
    
    Vert * start = nullptr;
    Vert * ending = nullptr;
    //search routine to find starting and destination
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;
        vertices[i].parent = nullptr;
        if (vertices[i].city == starting) {
            start = &vertices[i];
        }
        if (vertices[i].city == destination) {
            ending = &vertices[i];
        }
    }
    if (start != nullptr && ending != nullptr)
    { //cout << "entered" << endl;
        start->visited = true;
        start->distance = 0;
        //cout<<"pushing "<<start->city<<" into solved"<<endl;
        vector<Vert *> solved;
        vector<Vert *> path;
        solved.push_back(start);
        //path.push_back(start);
        adjVert * v;
        Vert * u;
        Vert * minVertex;
        Vert * prev;
        while (ending->visited == false) {
            int minDistance = INT_MAX;
            for (int i = 0; i < solved.size(); i++) {
                u = solved[i];
                //cout<<endl;
                //cout<<"Inspecting route from "<<u->city<<endl;
                for (int j = 0; j < u->adj.size(); j++) {
                    v = &solved[i]->adj[j];
                    //cout<<"-> to "<<v->v->city;
                    if (v->v->visited == false) {
                        //cout<<", not yet solved,";
                            int dist = u->distance + v->miles;
                            if (dist < minDistance) {
                                //cout<<" the minimum distance was "<< minDistance;
                                minDistance = dist;
                                minVertex = v->v;
                                prev = u;
                                //cout<<" but there is a new minimum distance of "<<dist<<" between "
                                //<<start->city <<" and "<<minVertex->city<<endl;
                            }else{//cout<<" the minimum distance is "<<minDistance
                                //<<" and there is not a new minimum distance "<<dist<<endl;
                            }
                    
                    }else{
                        //cout<<" already solved, moving on"<<endl;
                    }
                }
                
            }
            solved.push_back(minVertex);
            //cout<<endl;
            //cout<<"pushing "<< minVertex->city <<" into solved ";
            minVertex->distance = minDistance;
            minVertex->parent = prev;
            minVertex->visited = true;
            //cout<<minVertex->city;
            //cout<<"(distance: "<<minVertex->distance
            //<<", visited: "<<minVertex->visited
            //<<", parent: "<<minVertex->parent->city<<")"<<endl;
            //cout<<"destination "<<ending->city<<" solved? "<<ending->visited<<endl;
            //cout<<endl;
        }
        if (!sim){
            cout<<"Standard Hub Route"<<endl;}
        else{cout << "Most efficient Re-route through southern gateway cities" << endl;}
        Vert * vert = ending;
        while (vert != nullptr) {
            path.push_back(vert);
            vert = vert->parent;
        }
        for (int i = 0; i < path.size(); i++) {
            if (i == path.size()-1)
                cout<<path[path.size()-1-i]->city;
            else
                cout<<path[path.size()-1-i]->city<<" - ";
            
        }
        if(!sim){
            cout << " - New York" << endl;
            if(Price){
                for (int i = path.size()-1; i > 0; i--){
                    //cout << path[i]->city << " " << path[i-1]->city << endl;
                    Sum(path[i]->city, path[i-1]->city); }}}
    
        
            else{ cout << endl;
                if(Price){
                    for (int i = path.size()-1; i > 0; i--){
                        //cout << path[i]->city << " " << path[i-1]->city << endl;
                        Sum(path[i]->city, path[i-1]->city);}
            if (!sim){
                cout<<"Distance: "<<solved[solved.size()-1]->distance+3470<<endl;}
            else{cout<<"Minimum Distance: "<<solved[solved.size()-1]->distance<<endl;}
    }else if (ending!=nullptr){
        cout<<"start not found"<<endl;
        exit(1);
    }else{
        cout<<"ending not found"<<endl;
        exit(1);
    }
}}}

//A helper function that decides whether or not to follow simulation rules or standard rules.
    

void Route::PrntR(bool sim){
    
    string strt, end;
    
    if (!sim){
        cout << "Please enter your departure city: ";
        getline(cin, strt);
        end = "London";
        Dijkstra(strt, end);
        
    }
    
    else{
        cout << "Please enter your departure city: ";
        getline(cin, strt);
        end = "New York";
        Dijkstra(strt, end);}
    
//My eruption scenario. It toggles the simulation conditions on and provides a sub menu.     
    
}

void Route::Scenario(){
    
    char pause;
    
    int choice;
    
    sim = true;
    
    BuildG();
    
    
    
    //sleep(1);
    cout << "*****************NEWS FLASH******************" << endl << endl;
    cout << "The Icelandinc volcano Theistareykjarbunga" << endl;
    cout << "has erupted. Volcanic ash is spewing into" <<endl;
    cout << "the upper atmosphere and jet stream. London" << endl;
    cout << "Heathrow has been shut done." << endl;
    cout << "*********************************************" << endl;
    cout << "*****************Press Enter*****************" << endl;
    cin.get();
    
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "**********************************************" << endl;
    cout << "Imaginary Airlines has it's entire trans-" << endl;
    cout << "Atlantic fleet of Boeing 747s parked in London." << endl;
    cout << "Using Dijkstra's Algorhthm, new alternative " << endl;
    cout << "flight routes have been established. Use the" << endl;
    cout << "menu below to find out the new flight paths to" << endl;
    cout << "New York..." << endl;
    cout << "**********************************************" << endl;
    cout << "*****************Press Enter*****************" << endl;
    cin.get();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    

    
    while (choice != 3){
        
        cout << "**************SIM MENU****************" << endl;
        cout << "1. Find route" << endl;
        cout << "2. Find Airfare" << endl;
        cout << "3. Exit Sim" << endl;
        
        cin >> choice;
        cin.clear();
        cin.ignore();
        
        switch(choice){
            case 1: PrntR(sim);
                break;
            case 2: getFare();
                break;
            case 3: cout << "Goodbye!" << endl;
                break; }}
    
        
        
}

//A BST/linklist hybid creator function that stitches together a slightly modified BST builder and a Linked list
//build algorthm of my own devising.

void Route::BuildT(){

 
    AddT();
    AddLL();
    
    PrntT();
    
}
    
//Print helper function

void Route::PrntT(){
    
    PrntT(Root);
    
//Finds first the Leaf containing the city name. Set the leaf to head. Then creates a nodes with the Arrival city name and
//an airfare pointer 
    
}

void Route::PrntT(Route *snitch){
    
    if(snitch->left != nullptr){
        PrntT(snitch->left);}
        cout << "City: " << snitch->Dep <<endl;
    if(snitch->right !=nullptr){
        PrntT(snitch->right);}
    
}


//BST building algorthm. "newLeaf->next = nullptr" was added to setup the link list additions 

void Route::AddT(){
    
string data;
ifstream inputFile;
inputFile.open("City.txt");
    
    
while (getline(inputFile, data, ',').good()){
            
            Route *newLeaf = new Route;
            //Build Algo
    
            //load up the leaf with values
            
            newLeaf->Dep = data;
        
            
            
    
            newLeaf->left = nullptr;
            newLeaf->right = nullptr;
            newLeaf->parent = nullptr;
            newLeaf->next = nullptr;
            bool inserted = false;
            current = Root;
            while(!inserted){
                
                
                if (Root != nullptr){
                    
                    if(newLeaf->Dep < current->Dep)
                        if(current->left != nullptr){
                            current = current->left;
                        }
                        else{
                            current->left = newLeaf;
                            newLeaf->parent = current;
                            inserted = true;}
                        else{
                            if(current->right != nullptr){
                                current = current->right;}
                            else{
                                current->right = newLeaf;
                                newLeaf->parent = current;
                                inserted = true;}}}
                else{Root = newLeaf; inserted = true;}}
    getline(inputFile, data);
    }
        
}


//My custom Linked List script. It stitches a linked list to the proper leaf in the BST.

void Route::AddLL(){
    string data;
    ifstream inputFile;
    inputFile.open("Fare.txt");
    
    
    Route *current = nullptr;
    
    while(getline(inputFile, data, ',').good()){
    
    current = search(data);
    
    if (current->next == nullptr){
        
    
        Route *newNode = new Route;
        newNode->next = nullptr;
        getline(inputFile, data, ',');
        newNode->Arr = data;
        getline(inputFile, data, ',');
        newNode->Fare = data;
        
        current->next = newNode;}
    else{
        while(current->next != nullptr){
            current = current->next;}
        Route *newNode = new Route;
        newNode->next = nullptr;
        getline(inputFile, data, ',');
        newNode->Arr = data;
        getline(inputFile, data, ',');
        newNode->Fare = data;
        
        current->next = newNode;}
    getline(inputFile, data);}
    }
    






Route * Route::search(string Depart){
    
    
    current = Root;
    
    
    while(current != nullptr){
        
        if(current->Dep > Depart){
            current= current->left;}
        
        else if(current->Dep < Depart){
            current = current->right;}
        
        else{return current;}}
    
    return nullptr;}



//Toggles on Price sub-routines in Dijksta and prints the fare price.

void Route::getFare(){
    Price = true;
    PrntR(sim);
    if(!sim){
        cout << "Ticket cost " << "$" << sum + 628 << endl;}
    else{
        cout << "Ticket cost " << "$" << sum << endl;
    }
        
    
    
}

//A summation algorthm that works intandem with a subroutine I wrote into Dijkstra's alg. It pulls the edge between cities as
//Dijkstra solves the path. Then it sums these to be printed later.

void Route::Sum(string dep, string arr){
    
    
    Route *snitch = search(dep);
    
    while(snitch->next->Arr != arr){
        snitch = snitch->next;}
    sum = sum + stoi(snitch->next->Fare);
}
    










