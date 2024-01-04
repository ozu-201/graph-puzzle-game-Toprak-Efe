//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//


#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    void Graph::addEdge(int from, int to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges[from].insert(edge);
    }

    Graph::~Graph() {
        delete[] edges;
    }

    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    int *Graph::breadthFirstSearch(bool *visited, int startNode, int endNode) {
        int *costForPath = new int[vertexCount];
        int *previousVertex = new int[vertexCount];
        memset(costForPath, 0, sizeof(int)*vertexCount);
        memset(previousVertex, 0, sizeof(int)*vertexCount);

        int shortestPathLength = 0;
        bool found = false;

        int fromNode, toNode;
        Edge* edge;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        /* Iterate through the queue until it is empty. */
        while (!queue.isEmpty() && !found){
            fromNode = queue.dequeue()->getData();
            /* For each node, calculate their corresponding cost and write their . */
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    costForPath[toNode] = costForPath[fromNode] + 1;
                    previousVertex[toNode] = fromNode;
                    if (toNode == endNode) {
                        shortestPathLength = costForPath[toNode];
                        found = true;
                        break;
                    }
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }

        int *path = new int[shortestPathLength+2];
        path[0] = shortestPathLength+2;
        path[shortestPathLength+1] = endNode;
        path[1] = startNode;

        fromNode = previousVertex[endNode];
        int index = shortestPathLength;
        while (fromNode != startNode) {
            path[shortestPathLength] = fromNode;
            fromNode = previousVertex[fromNode];
            shortestPathLength--;
        }
        return path;
    }

    void Graph::getPathBreadth(std::vector<std::string> &dict, int from, int to) {
        bool *visited = new bool[vertexCount];
        int *path = breadthFirstSearch(visited, from, to);
        int length = path[0];
        for (int i = 0; i < length-2; i++) {
            std::cout << dict[path[i+1]] << "->";
        }
        std::cout << dict[path[length-1]] << '\n';
    }

    void Graph::getPathDijkstra(std::vector<std::string> &dict, int from, int to) {
        Path *paths = dijkstra(from);
        Path pathToGoal = paths[to];

        int pen = pathToGoal.getPrevious();
        int length = 1;
        while (pen != from) {
            length++;
            pen = paths[pen].getPrevious();
        }

        pen = to;
        int *vertices = new int[length];
        for (int i = length; i > -1; i--) {
            vertices[i] = pen;
            pen = paths[pen].getPrevious();
        }

        for (int i = 0; i < length; i++) {
            std::cout << dict[vertices[i]] << "->";
        }
        std::cout << dict[to];

    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }

        return shortestPaths;
    }

    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }

}