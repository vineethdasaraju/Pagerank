#include <iostream>
#include <fstream>
#include <vector>
#include "Pagerank.h"

using namespace std;

int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    Pagerank pgrnk;
    pgrnk.create_graph("input_100000.txt");
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Time for I/O: " << time_spent << endl;
    pgrnk.calculatePagerank();
    pgrnk.print_graph();
    return 0;
}
