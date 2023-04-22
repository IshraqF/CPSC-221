/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum edge weight
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    // 1. Label all edges and vertices as unexplored. You will need
    //    to look in graph.h for the right functions.
    vector<Edge> edges = graph.getEdges();
    for(size_t i=0; i<edges.size(); i++){
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }
    vector<Vertex> verticies = graph.getVertices();
    for(size_t i=0; i<verticies.size(); i++){
        graph.setVertexLabel(verticies[i], "UNEXPLORED");
    }

    // 2. Use the BFS function in graph_tools to find the minimum edge.
    //    Don't forget to label it.
    Edge minEdge = BFS(graph, verticies[0]);
    graph.setEdgeLabel(minEdge.source, minEdge.dest, "MIN");
    return minEdge.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> parent;

    // TODO
    // 1. Set all vertices as unexplored
    vector<Vertex> vertices = graph.getVertices();
    int V = (int) vertices.size();
    for (int i=0; i<V; i++) {
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }

    vector<Edge> edges = graph.getEdges();
    int E = (int) edges.size();
    for (int i=0; i<E; i++) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    // 2. Do a modified BFS. See the BFS function below as a guideline, but
    //    your BFS here only needs to populate the "parent" map and done once the short-
    //    est path has been found.
    bool done;
    queue<Vertex> queue;
    graph.setVertexLabel(start, "VISITED");
    queue.push(start);
    done = false;

    while (!queue.empty() && !done) {
        Vertex vertex = queue.front();
        graph.setVertexLabel(vertex, "VISITED");
        vector<Vertex> adjacents = graph.getAdjacent(vertex);
        int A = (int) adjacents.size();

        for (int i=0; i<A; i++) {
            if (graph.getVertexLabel(adjacents[i])== "UNEXPLORED") {
                graph.setVertexLabel(adjacents[i], "VISITED");
                queue.push(adjacents[i]);
                parent[adjacents[i]] = vertex;
            }
            if (adjacents[i] == end) {
                done = true;
                break;
            }
        }

        if (!done) queue.pop();
    }

    // 3. Use the unordered map to trace from a path from the end to the start,
    //    counting edges. You should set edges to "minpath" here too.
    int minPath = -1;

    if (done) {
        minPath = (int) 0;
        Vertex currVertex = end;
        
        while (currVertex != start) {
            graph.setEdgeLabel(currVertex, parent[currVertex], "MINPATH");
            currVertex = parent[currVertex];
            minPath++;
        }
    }
    
    return minPath;
}

/**
 * Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    // 1. Create a disjoint sets object with one set per vertex
    vector<Vertex> vertices = graph.getVertices();
    int V = (int) vertices.size();
    DisjointSets disjointSets;
    disjointSets.addelements(V);

    // 2. Create a vector of all edges in the graph
    vector<Edge> edges = graph.getEdges();

    // 3. Sort the edges in ascending order by weight
    sort(edges.begin(), edges.end());

    // 4. Iterate through the edges in the sorted order, adding each
    //    edge to the MST if it does not create a cycle
    int numEdgesInMST = 0;
    int numEdges = (int) edges.size();
    for (int i = 0; i < numEdges; i++) {
        Vertex source = edges[i].source;
        Vertex dest = edges[i].dest;
        if (disjointSets.find(source) != disjointSets.find(dest)) {
            disjointSets.setunion(source, dest);
            graph.setEdgeLabel(source, dest, "MST");
            numEdgesInMST++;
            if (numEdgesInMST == V - 1) {
                break;  // MST is complete
            }
        }
    }

}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
