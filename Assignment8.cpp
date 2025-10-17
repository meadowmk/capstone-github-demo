//************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// ASU ID: 1225852019
// Name: Meadow Kubanski
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

//include necessary header file here
#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);
int searchCity(City* oneCityArray, int size, string oneCityName);

int main()
{
   int V, E;        //number of vertices and edges

   //cout << "Enter number of vertices and edges: " << endl;
   cin >> V >> E;
   cin.ignore(20, '\n');

   //a City array used to store all vertices (Cities) of the graph
   City* cityArray = new City[V];
  
   //an array used to store all edges of the graph
   Edge* edgeArray = new Edge[E];
   //----
   //----

   int i =0, j=0; //index for cityArray and edgeArray

   //local variables
   City* city1 = nullptr;  //make sure you initialize
   City* city2 = nullptr;
   Edge* aNewEdge;

   string oneLine;

   //cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line of the input, extract the first token
      //create a City object if it does not exist in cityArray,
      //insert it inside the cityArray. This will be first vertex of the 'aNewEdge'
      string delimiter = ",";
      int pos = oneLine.find(delimiter);
      string token = oneLine.substr(0,pos);
      int departureIndex = searchCity(cityArray, V, token);
	   if (departureIndex == -1) { //make sure the departure city doesn't already exist in cityArray
        cityArray[i] = City(token); //add it if not
        departureIndex = i;
        i++;   //increment the index
      }
      oneLine.erase(0, pos+delimiter.length());

      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point of the 'aNewEdge'
      string arrivalName;
      double distance;

      if (oneLine.find("(") != string::npos) {     //check to see if there are more arrival cities
	   while(!oneLine.empty()) {
         getArrCityInfo(oneLine, arrivalName, distance);
         int arrivalIndex = searchCity(cityArray, V, arrivalName);

         if(arrivalIndex == -1) {      //check to make sure arrival city doesn't already exist
		      cityArray[i] = City(arrivalName);   //add it if not
            	arrivalIndex = i;
            	i++;  //increment the index
	      }

         //by using the two cities we got above, create a new edge, add
         //it inside edgeArray
         Edge newEdge = Edge(&cityArray[departureIndex], &cityArray[arrivalIndex], distance);   //create new edge with the cities
         edgeArray[j] = newEdge;    //add it to the edge array
    	   j++;  //increment the index

	      pos = oneLine.find(delimiter);
         if (pos != string::npos) {
            oneLine.erase(0, pos + delimiter.length());
	      }
	      else {
	         break;
	      }
      }
      }
      //get next line
      getline(cin, oneLine);
      
   }  //repeat until the 'End'

   //Create a Graph object by using cityArray and edgeArray
   Graph graph = Graph(V, E, cityArray, edgeArray);

   //Run Kruskal MST algorithm on above graph
   graph.MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Dallas(1456.5)', this function
//extract the arrival city name 'Dallas' and distance '1456.5'
//Note: the delimiter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
   string delimiter = "(";    //get everything up the the first parenthesis to get the name of the city
   int pos = oneArrCityInfo.find(delimiter);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token; 
   oneArrCityInfo.erase(0, pos+delimiter.length());

   delimiter = ")";     //get everything up to the last parenthesis to get the distance for the edge
   pos = oneArrCityInfo.find(delimiter);
   token = oneArrCityInfo.substr(0,pos);
   distance = stod(token);
   oneArrCityInfo.erase(0, pos+delimiter.length());

}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
   for(int i = 0; i < arraySize; i++) {
      if(oneCityArray[i].cityName == oneCityName) {
         return i;
      }
   }
   return -1;
}
