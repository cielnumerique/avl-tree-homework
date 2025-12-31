#pragma once

#include "IGraph.hpp"
#include <vector>

class ListGraph : public IGraph {
public:
    explicit ListGraph( int vertex_count );
    ListGraph( const IGraph& other );
    
    virtual void AddEdge( int from, int to ) override;
    virtual int VerticesCount() const override;
    virtual std::vector< int > GetNextVertices( int vertex ) const override;
    virtual std::vector< int > GetPrevVertices( int vertex ) const override;

private:
    std::vector< std::vector< int > > adjacency_lists_;
    std::vector< std::vector< int > > reverse_adjacency_lists_;
    
    bool IsValidIndex( int index ) const;
};