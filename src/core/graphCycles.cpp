#include <iostream>
#include <list>
#include <climits>

using namespace std;

// This function is a variation of DFSUytil() in https://www.geeksforgeeks.org/archives/18212
bool recContainsCycle(list<int> *connections, int v, bool visited[], bool *recStack)
{
  if(!visited[v])
  {
    // Mark the current node as visited and part of recursion stack
    visited[v] = true;
    recStack[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = connections[v].begin(); i != connections[v].end(); ++i)
    {
      if ( !visited[*i] && recContainsCycle(connections ,*i, visited, recStack) )
        return true;
      else if (recStack[*i])
        return true;
    }

  }
  recStack[v] = false;  // remove the vertex from recursion stack
  return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in https://www.geeksforgeeks.org/archives/18212
bool containsCycle(list<int> *connections, int allNodes)
{
  // Mark all the vertices as not visited and not part of recursion
  // stack
  bool *visited = new bool[allNodes];
  bool *recStack = new bool[allNodes];
  for(int i = 0; i < allNodes; i++)
  {
    visited[i] = false;
    recStack[i] = false;
  }

  // Call the recursive helper function
  for(int i = 0; i < allNodes; i++)
    if (recContainsCycle(connections, i, visited, recStack))
      return true;

  return false;
}

int main() { //V=allNodes; adj = connections;
  // Simple "table of edges"
  int edges[][2] = {
      {1,2},
      {1,3},
      {1,4},
      {2,3},
      {3,4},  // [6,3] cyclic; [3,4] acyclic
      {3,5},
      {3,6},
  };

  int allNodes = 7;         // Number of nodes
  list<int> *connections;    // List of lists of connected nodes (index is where the connection starts)

  connections = new list<int>[allNodes];

  // Copying from edges to connections
  for(int i = 0; i < allNodes; i++) {
    connections[edges[i][0]].push_back(edges[i][1]); // Add w to v’s list.
  }

  // Call THE FUNCTION
  if(containsCycle(connections, allNodes)) {
    cout << "Graph contains a cycle.";
  }
  else {
    cout << "Graph doesn't contain a cycle.";
  }
  return 0;
}

