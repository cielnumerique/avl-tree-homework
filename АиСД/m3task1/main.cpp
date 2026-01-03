#include "ListGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"
#include "MatrixGraph.hpp"

int main() {
    const int size = 10;
    
    ListGraph listGraph(size);
    SetGraph setGraph(size);
    ArcGraph arcGraph(size);
    MatrixGraph matrixGraph(size);
    
    for (int i = 0; i < size - 1; ++i) {
        listGraph.AddEdge(i, i + 1);
        setGraph.AddEdge(i, i + 1);
        arcGraph.AddEdge(i, i + 1);
        matrixGraph.AddEdge(i, i + 1);
    }
    
    ListGraph copyListGraph(setGraph);
    SetGraph copySetGraph(matrixGraph);
    ArcGraph copyArcGraph(setGraph);
    MatrixGraph copyMatrixGraph(arcGraph);
    
    for (int i = 0; i < size - 1; ++i) {
        copyListGraph.GetNextVertices(i);
        copySetGraph.GetNextVertices(i);
        copyArcGraph.GetNextVertices(i);
        copyMatrixGraph.GetNextVertices(i);
        
        copyListGraph.GetPrevVertices(i + 1);
        copySetGraph.GetPrevVertices(i + 1);
        copyArcGraph.GetPrevVertices(i + 1);
        copyMatrixGraph.GetPrevVertices(i + 1);
    }
    
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(3, 7);
    listGraph.AddEdge(7, 2);
    
    MatrixGraph complexCopy(listGraph);
    
    return 0;
}
