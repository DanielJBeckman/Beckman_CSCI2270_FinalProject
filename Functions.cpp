//
//  Functions.cpp
//  Final Project 2270
//
//  Created by DANIEL BECKMAN on 7/24/17.
//  Copyright © 2017 DANIEL BECKMAN. All rights reserved.
//
#include <iostream>
#include "Functions.hpp"
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;



Route::Route(){
    
    Price = false;

    sim = false;
    
    Root = nullptr;
    
    sum = 0;
    
    next = nullptr;
    

};

Route::~Route(){};




void Route::BuildG(){
    if (!sim){
        addVert();
    
        addEdge("Routes.txt");}
    else{
        addEdge("Sim.txt");}
    }




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
    cout << "Atlantic fleet of Boeing 747s park in London." << endl;
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


void Route::BuildT(){

 
    AddT();
    AddLL();
    
    PrntT();
    
}
    
void Route::PrntT(){
    
    PrntT(Root);
    
    
    
}

void Route::PrntT(Route *snitch){
    
    if(snitch->left != nullptr){
        PrntT(snitch->left);}
        cout << "City: " << snitch->Dep <<endl;
    if(snitch->right !=nullptr){
        PrntT(snitch->right);}
    
}




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

void Route::getFare(){
    Price = true;
    PrntR(sim);
    if(!sim){
        cout << "Ticket cost " << "$" << sum + 628 << endl;}
    else{
        cout << "Ticket cost " << "$" << sum << endl;
    }
        
    
    
}


void Route::Sum(string dep, string arr){
    
    
    Route *snitch = search(dep);
    
    while(snitch->next->Arr != arr){
        snitch = snitch->next;}
    sum = sum + stoi(snitch->next->Fare);
}
    










