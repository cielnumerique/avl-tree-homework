#include "ListGraph.hpp"
#include <cassert>
#include <algorithm>

ListGraph::ListGraph( int vertex_count ) 
    : adjacency_lists_( vertex_count )
    , reverse_adjacency_lists_( vertex_count ) 
{}

ListGraph::ListGraph( const IGraph& other ) 
    : adjacency_lists_( other.VerticesCount() )
    , reverse_adjacency_lists_( other.VerticesCount() ) 
{
    for ( int i = 0; i < other.VerticesCount(); ++i ) {
        auto next_vertices = other.GetNextVertices( i );
        for ( int neighbor : next_vertices ) {
            AddEdge( i, neighbor );
        }
    }
}

bool ListGraph::IsValidIndex( int index ) const {
    return index >= 0 && index < VerticesCount();
}

void ListGraph::AddEdge( int from, int to ) {
    assert( IsValidIndex( from ) );
    assert( IsValidIndex( to ) );
    
    adjacency_lists_[from].push_back( to );
    reverse_adjacency_lists_[to].push_back( from );
}

int ListGraph::VerticesCount() const {
    return static_cast< int >( adjacency_lists_.size() );
}

std::vector< int > ListGraph::GetNextVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    return adjacency_lists_[vertex];
}

std::vector< int > ListGraph::GetPrevVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    return reverse_adjacency_lists_[vertex];
}