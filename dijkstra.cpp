#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;
using Graph = unordered_map<int, vector<pair<int,int> > >; //node, neighbor node, weight of neighbor node

int dijkstra(const Graph& graph, int start, int end){
    unordered_map<int, int> distance; //node, shortest distance
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<> > minHeap;

    for (const auto& node : graph){
        distance[node.first] = INT_MAX; //set dist of all nodes to inf
    }
    distance[start] = 0;
    minHeap.push({0,start});

    while (!minHeap.empty()){
        auto [dist, curr] = minHeap.top(); 
        minHeap.pop(); //delete smallest dist node
        if (curr == end) return dist;

        for (const auto& [neighbor, weight] : graph.at(curr)){
            int newDist = dist + weight;
            if (newDist < distance[neighbor]){
                distance[neighbor] = newDist;
                minHeap.push({newDist, neighbor});
            }
        }
    }
    return -1;
}
int main() {
    Graph graph = {
        {1, {{2, 1}, {5, 1}, {3, 1}}},
        {2, {{4, 1}}},
        {3, {{5, 1}}},
        {4, {{3, 1}}},
        {5, {}}
    };

    cout << "Shortest path from 1 to 2: " << dijkstra(graph, 1, 2) << endl;
    cout << "Shortest path from 1 to 5: " << dijkstra(graph, 1, 5) << endl;
    cout << "Shortest path from 2 to 5: " << dijkstra(graph, 2, 5) << endl;
    cout << "Shortest path from 5 to 1: " << dijkstra(graph, 5, 1) << endl;
    cout << "Shortest path from 2 to 1: " << dijkstra(graph, 2, 1) << endl;

    return 0;
}
