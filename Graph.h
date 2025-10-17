//********************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Meadow Kubanski
// ASU ID: 1225852019
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges
//********************************************************************

//include necessary header file here
#include "Edge.h"

using namespace std;

class Graph
{
   private:
      int V, E;         //number of vertice and edges in the graph
      City* cityArr;    //an array of City objects
      Edge* edgeArr;    //an array of Edge objects

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      ~Graph();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void sortEdges();

      void MST_Kruskal();

      //add any auxiliary functions in case you need them
      void mergeSort(Edge* edgeArr, int l, int r);
      void merge(Edge* edgeArr, int p, int q, int r);
};

//finish each function according to above definition
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray) {
   V = numOfCities;
   E = numOfEdges;
   cityArr = cityArray;
   edgeArr = edgeArray;
}

Graph::~Graph() {

}

void Graph::make_set(City* aCity) {
   if(aCity != nullptr) {
   	aCity->parent = aCity;  //set the cities parent to itself
   	aCity->rank = 0;  //rank is 0 for now
	}
}

City* Graph::find_set(City* aCity) {
   if(aCity != aCity->parent) {
      aCity->parent = find_set(aCity->parent);  //use recursion to find the set
   }
return aCity->parent;
}

void Graph::link(City* aCity, City* bCity) {
   if(aCity->rank > bCity->rank) {  //set parents based on rank
      bCity->parent = aCity;
   }
   else {
      aCity->parent = bCity;
      if(aCity->rank == bCity->rank) {
         bCity->rank = bCity->rank + 1;   //if they are equal increment one
	
      }
   }
}

void Graph::Union(City* aCity, City* bCity) {
   if(aCity == nullptr || bCity == nullptr) {  //check that neither of the cities are null
	   return;
   }
	City* aParent = find_set(aCity);
   City* bParent = find_set(bCity);
	
	link(aParent, bParent); //if they arent null, link them
}

 void Graph::sortEdges() {
   mergeSort(edgeArr, 0, E - 1); //call merge sort on the edgeArray using its size - 1

 }

 void Graph::mergeSort(Edge* edgeArr, int l, int r) {
   if(l < r) {
      int mid = l + (r - l) / 2;
      mergeSort(edgeArr, l, mid);
      mergeSort(edgeArr, mid + 1, r);
      merge(edgeArr, l, mid, r);
   }
 }

 void Graph::merge(Edge* edgeArr, int p, int q, int r) {    //mergeSort helper function
   int count1 = q - p + 1;
   int count2 = r - q;

   Edge L[count1];
   Edge M[count2];

   for (int i = 0; i < count1; i++)
      L[i] = edgeArr[p + i];
  for (int j = 0; j < count2; j++)
      M[j] = edgeArr[q + 1 + j];

   int i, j, k;
   i = 0;
   j = 0;
   k = p;

   while (i < count1 && j < count2) {
    if (L[i].getDistance() <= M[j].getDistance()) {
      edgeArr[k] = L[i];
      i++;
    } 
    else {
      edgeArr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < count1) {
    edgeArr[k] = L[i];
    i++;
    k++;
  }

   while (j < count2) {
    edgeArr[k] = M[j];
    j++;
    k++;
  }
 }

//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;

   for(int i = 0; i < V; i++) {
      make_set(&cityArr[i]);     //make a set for each vertex
   }

   sortEdges();   //call sort on the graph before doing kruskal

   for(int i = 0; i < E; i++) {
      City* city1 = edgeArr[i].getCity1();
      City* city2 = edgeArr[i].getCity2();

      if(find_set(city1) != find_set(city2)) {
         totalDistance += edgeArr[i].getDistance();   //keep track of the total distance
	      Union(city1, city2);
	      edgeArr[i].printEdge();       //instead of adding to set A, print out the edge
      }
   }
   cout << "=================================================" << endl;
   cout << "Total Distance: " << totalDistance << endl;
}
