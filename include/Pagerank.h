#ifndef PAGERANK_H
#define PAGERANK_H
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

struct adjacency_list {
	vector<int> neighbors;
	int outDegree;
};

class Pagerank
{
    public:
        Pagerank();
        virtual ~Pagerank();
        void create_graph (const char *file_name);
        void print_graph();
        void calculatePagerank();
        bool checkConvergence();
    protected:
    private:
        int nVertices;
        int nEdges;
        int nIterations = 0;
        double dampingFactor = 0.2;
        bool converged = false;
        vector<double> oldPageRanks, newPageRanks;
        adjacency_list *graph;
};

#endif // PAGERANK_H
