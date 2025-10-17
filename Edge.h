//******************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Meadow Kubanski
// ASU ID: 1225852019
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the distance between them
//*******************************************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
   string cityName;
   int rank;
   struct City* parent;

   //constructor
   City(string name)
   {
      cityName = name;
      rank = 0;
      parent = NULL;
   }

   //default constructor. C++ don't provide one, need it here.
   City()
   {
      cityName = "";
      rank = 0;
      parent = nullptr;
   }
};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
   private:
   struct City* city1;
   struct City* city2;
   double distance;

   public:
   Edge(City* city1, City* city2, double distance);
   Edge();  //default constructor
   ~Edge();
   City* getCity1();
   City* getCity2();
   double getDistance();
   void printEdge();
};

//finish each function according to above definition
Edge::Edge(City* City1, City* City2, double Distance) {
   city1 = City1;
   city2 = City2;
   distance = Distance;
}

Edge::Edge() {
   city1 = nullptr; //initialize all of the variables
   city2 = nullptr;
   distance = 0;
}

Edge::~Edge() {
   //no uses of 'new' that need to be deleted
}

City* Edge::getCity1() {
   return city1;
}

City* Edge::getCity2() {
   return city2;
}

double Edge::getDistance() {
   return distance;
}

void Edge::printEdge()
{
   cout << left;
   cout << setw(15) << city1->cityName
   << setw(8) << "<--->"
   << setw(15) << city2->cityName
   << setw(3) << " = "
   << setw(8) << right << fixed << setprecision(2) << getDistance()
   << endl;
}
