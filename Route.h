#ifndef Route_H
#define Route_H


struct Vert{

  string city;
  
  int distance
  
  bool isSolved;
  
  Vert *parent;
  
  vector <adjVert> adjacent;};
  
struct adjVert{
  
  int weight;

  Vert *v};
  

class Route
{
  Private:
  
  string StartV;
  
  string EndV;
  
  Public:
  
  Route();
  
  ~Route();
  
  void PrntR();
  
  void PrntG();
  
  void BuildG();
  
  void BuildT();
  
  void Scenario();
  
  void Dijkstra(string start, string end);
  
  };
  
  
  #endif
