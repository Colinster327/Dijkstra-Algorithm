/*
  Colin Murphy
  CS 3610 Data Structures
  Purpose: implement Dijkstra's Algorithm for shortest path HEAP VERSION
  main.cpp
*/

#include <iostream>
#include <vector>
#include "GraphMinHeap.h"

using std::cin;
using std::cout;
using std::getline;
using std::string;
using std::swap;
using std::vector;

// structure used to hold city information on graph
struct City
{
  // constructor
  City(int cityID = 0, int distance = 0) : cityID(cityID), distance(distance) {}
  int cityID;
  int distance;
  vector<int> predecessors;
};

// Format weights matrix values to be ~infinity if 0
// precondition: vector<vector<int> > &weights (matrix by reference)
// postcondition: no return, just alters weights matrix to satisfy
//                conditions needed for Dijkstra's Algorithm
void formatWeights(vector<vector<int> > &weights);

// Finds the shortest path from first city to last city
// precondition: const vector<vector<int> > &weights (current distances between vertices)
//               vector<int> &citiesInOrder (used to set cities visited in shortest path)
//               int numCities (NEEDS TO BE AT LEAST 1)
// postcondition: returns the shortest distance from first to last city and sets citiesInOrder
//                to be the cities visited in the shortest path
int shortestPath(const vector<vector<int> > &weights, vector<int> &citiesInOrder, int numCities);

int main()
{
  // get number of testcases from input
  int numCases;
  cin >> numCases;

  for (int x = 0; x < numCases; x++)
  {
    // get number of cites from input
    int numCities;
    cin >> numCities;
    cin.ignore();

    // store all of the city names from input
    string cities[numCities];
    for (int i = 0; i < numCities; i++)
      getline(cin, cities[i]);

    // store the weight values from input
    vector<vector<int> > weights(numCities, vector<int>(numCities));
    for (int i = 0; i < numCities; i++)
      for (int j = 0; j < numCities; j++)
        cin >> weights[i][j];

    formatWeights(weights);
    vector<int> citiesInOrder;                                              // used to store list of cities taken in shortest path
    int shortestDistance = shortestPath(weights, citiesInOrder, numCities); // find shortest path

    for (int i = 0; i < citiesInOrder.size(); i++)
      cout << cities[citiesInOrder[i]] << " ";
    cout << shortestDistance << "\n";
  }

  return 0;
}

void formatWeights(vector<vector<int> > &weights)
{
  for (int i = 0; i < weights.size(); i++)      // loop through all vertices
    for (int j = 0; j < weights[i].size(); j++) // loop through all adjancencies of vertex
      if (i != j && weights[i][j] == 0)
        weights[i][j] = 10001; // set zeros to just above max range value if not itself
}

int shortestPath(const vector<vector<int> > &weights, vector<int> &citiesInOrder, int numCities)
{
  citiesInOrder.clear();                              // ensure vector is empty
  GraphMinHeap<City> smallestWeights;                 // min_heap
  vector<GraphMinHeap<City>::HeapNode *> lookupTable; // table manage all vertices

  City temp[numCities]; // used to hold cities and keys to turn into min heap
  int tempKeys[numCities];
  for (int i = 0; i < numCities; i++) // insert vertices into temps
  {
    temp[i] = City(i, weights[0][i]);
    tempKeys[i] = weights[0][i];
  }
  lookupTable = smallestWeights.heapify(temp, tempKeys, numCities); // make min heap and set lookup table

  smallestWeights.extract_min(); // take first city out of heap
  lookupTable[0] = NULL;         // set first city to found

  for (int i = 0; i < numCities - 1; i++)
  {
    City minCity = smallestWeights.extract_min();   // get smallest distance
    lookupTable[minCity.cityID] = NULL;             // set vertex to be determined
    minCity.predecessors.push_back(minCity.cityID); // add itself to predecessor list

    if (minCity.cityID == numCities - 1) // exit case -> found min distance to last city
    {
      citiesInOrder.push_back(0);                                                                          // add first city to predecessor list
      citiesInOrder.insert(citiesInOrder.end(), minCity.predecessors.begin(), minCity.predecessors.end()); // set rest of predecessors
      return minCity.distance;
    }

    for (int j = 0; j < numCities; j++) // check adjancencies of min city
    {
      if (lookupTable[j] != NULL) // vertex is undetermined
      {
        if (minCity.distance + weights[minCity.cityID][j] < lookupTable[j]->data.distance)
        {
          lookupTable[j]->data.distance = minCity.distance + weights[minCity.cityID][j];                     // change smallest weights value
          lookupTable[j]->data.predecessors = minCity.predecessors;                                          // set predecessors of neighbor to that of min city
          smallestWeights.decreaseKey(lookupTable[j]->index, minCity.distance + weights[minCity.cityID][j]); // bubble up
        }
      }
    }
  }

  // default case when only 1 city is inputted
  citiesInOrder.push_back(0);
  return 0;
}