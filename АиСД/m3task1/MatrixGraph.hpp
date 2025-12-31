#pragma once

#include "IGraph.hpp"
#include <vector>

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph( int vertex_count );
    MatrixGraph( const IGraph& other );
    
    virtual void AddEdge( int from, int to ) override;
    virtual int VerticesCount() const override;
    virtual std::vector< int > GetNextVertices( int vertex ) const override;
    virtual std::vector< int > GetPrevVertices( int vertex ) const override;

private:
    std::vector< std::vector< bool > > adjacency_matrix_;
    
    bool IsValidIndex( int index ) const;
};