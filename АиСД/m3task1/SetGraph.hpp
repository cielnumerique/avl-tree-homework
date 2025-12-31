#pragma once

#include "IGraph.hpp"
#include <vector>
#include <set>

class SetGraph : public IGraph {
public:
    explicit SetGraph( int vertex_count );
    SetGraph( const IGraph& other );
    ~SetGraph();
    
    virtual void AddEdge( int from, int to ) override;
    virtual int VerticesCount() const override;
    virtual std::vector< int > GetNextVertices( int vertex ) const override;
    virtual std::vector< int > GetPrevVertices( int vertex ) const override;

private:
    std::vector< std::set< int >* > adjacency_sets_;
    int vertex_count_;
    
    bool IsValidIndex( int index ) const;
};