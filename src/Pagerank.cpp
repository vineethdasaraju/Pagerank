#include "Pagerank.h"
#include <fstream>

Pagerank::Pagerank()
{
    //ctor
    graph = NULL;
}

Pagerank::~Pagerank()
{
    //dtor
    delete[] graph;
}

void Pagerank::create_graph(const char *file_name){

// -O3 -march=native

    ifstream inFile;
    int source, destination, weight;
    inFile.open(file_name);
    if(!inFile.is_open()){
        cout << "\n***Input file doesn't exist!***\n" << endl;
		exit(0);
    }

    cout << "I/O started" << endl;

    inFile >> nVertices;
    inFile >> nEdges;

    if(graph!=NULL) delete[] graph;
    graph = new adjacency_list[nVertices];

    for(int i = 0; i<nEdges; i++){
        inFile >> source;
        inFile >> destination;
        inFile >> weight;

        if(source > nVertices || destination > nVertices){
            cout << "Vertices out of bounds" << endl;
            exit(0);
        }
        graph[source].neighbors.push_back(destination);
        graph[source].outDegree++;
        graph[destination].neighbors.push_back(source);
        graph[destination].outDegree++;
        //cout << "Source: " << source << ", destination: "<< destination << ", weight: "<< weight << endl;
    }
    inFile.close();
    for(int i = 0; i<nVertices; i++){
        oldPageRanks.push_back(((double)1/(double)nVertices));
        newPageRanks.push_back(0);
    }
    cout << "I/O Completed" << endl;
}

void Pagerank :: print_graph(){
    if(graph != NULL){
        ofstream outFile;
        outFile.open("output.txt");
        if(!outFile.is_open()){
            cout << "\n***Input file doesn't exist!***\n" << endl;
            exit(0);
        }
        outFile << "nvertices: " << nVertices << ", damping factor: " << dampingFactor << endl;
        for(int i = 0; i < nVertices; i++){
            outFile << "Pagerank of node " << i << " is: " << oldPageRanks[i] << endl;
        }
        outFile << "Iterated " << nIterations << " times." << endl;
        double sum = 0; double maximum = -2;
        for(int i = 0; i<nVertices; i++){
            sum += oldPageRanks[i];
            maximum = max(maximum, oldPageRanks[i]);
        }
        outFile << "Sum: " << sum << ", max: " << maximum << endl;
    } else {
        cout << "Graph is null!" << endl;
    }
}

void Pagerank :: calculatePagerank(){
    if(graph!=NULL){
        while(!converged || nIterations < 20){
            for(int i = 0; i < nVertices; i++){
                newPageRanks[i] = (double)dampingFactor / (double)nVertices;
                for(int j = 0; j < graph[i].outDegree; j++) {
                    int neighbour = graph[i].neighbors[j];
                    //cout << "node: " << i << ", neighbour: " << neighbour << ", size: " << oldPageRanks.size() << endl;
                    if(neighbour > oldPageRanks.size()) cout << "neighbour not in range" << endl;
                    newPageRanks[i] += (1-dampingFactor) * (double)oldPageRanks[neighbour]/(double)graph[neighbour].outDegree;
                }
                //cout << "graph[" << i << "].newPagernk: " << newPageRanks[i] << endl;
            }
            if(Pagerank :: checkConvergence()){
                cout << "Convergence found for iteration " << nIterations+1 << endl;
                converged = true;
            } else {
                converged = false;
            }
            for(int i = 0; i < nVertices; i++){
                oldPageRanks[i] = newPageRanks[i];
                newPageRanks[i] = 0;
            }
            nIterations++;
        }
        cout << "Iterated " << nIterations << " times." << endl;
    } else {
        cout << "Graph is null!" << endl;
    }
}

bool Pagerank :: checkConvergence(){
    for(int i = 0; i<nVertices; i++){
        //cout << "graph[" <<i<<"].newPagernk - graph["<<i<<"].oldPageRnk: " << newPageRanks[i] - oldPageRanks[i] << endl;
        if(newPageRanks[i] - oldPageRanks[i] > 0.0005 || newPageRanks[i] - oldPageRanks[i] < -0.0005) return false;
    };
    return true;
    //return false;
}
