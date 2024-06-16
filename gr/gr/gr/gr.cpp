﻿#include <iostream>
#include <vector>
#include <limits>
#include <set>

using namespace std;

class Graph {
    int numVertices;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

    void addEdge(int start, int end, int weight) {
        adjList[start].push_back(make_pair(end, weight));
        // Uncomment the next line for an undirected graph
        // adjList[end].push_back(make_pair(start, weight));
    }

    void dijkstra(int start) {
        vector<int> dist(numVertices, numeric_limits<int>::max());
        set<pair<int, int>> queue;
        dist[start] = 0;
        queue.insert(make_pair(0, start));

        while (!queue.empty()) {
            int current = queue.begin()->second;
            queue.erase(queue.begin());

            for (auto edge : adjList[current]) {
                int neighbor = edge.first;
                int weight = edge.second;
                if (dist[current] + weight < dist[neighbor]) {
                    queue.erase(make_pair(dist[neighbor], neighbor));
                    dist[neighbor] = dist[current] + weight;
                    queue.insert(make_pair(dist[neighbor], neighbor));
                }
            }
        }

        for (int i = 0; i < numVertices; ++i)
            cout << "Shortest path to vertex " << i << " is " << dist[i] << endl;
    }
};

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices and edges: ";
    cin >> numVertices >> numEdges;

    Graph g(numVertices);
    cout << "Enter the edges in the format 'start end weight':\n";
    for (int i = 0; i < numEdges; ++i) {
        int start, end, weight;
        cin >> start >> end >> weight;
        g.addEdge(start, end, weight);
    }

    int startVertex;
    cout << "Enter the starting vertex for finding shortest paths: ";
    cin >> startVertex;
    g.dijkstra(startVertex);

    return 0;
}
