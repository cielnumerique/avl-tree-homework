#pragma once

#include "IGraph.hpp"
#include <vector>
#include <utility>

class ArcGraph : public IGraph {
public:
    explicit ArcGraph( int vertex_count );
    ArcGraph( const IGraph& other );
    
    virtual void AddEdge( int from, int to ) override;
    virtual int VerticesCount() const override;
    virtual std::vector< int > GetNextVertices( int vertex ) const override;
    virtual std::vector< int > GetPrevVertices( int vertex ) const override;

private:
    std::vector< std::pair< int, int > > edges_list_;
    int vertex_count_;
    
    bool IsValidIndex( int index ) const;
};