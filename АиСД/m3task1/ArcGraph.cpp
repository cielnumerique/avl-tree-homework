#include "ArcGraph.hpp"
#include <cassert>
#include <algorithm>

ArcGraph::ArcGraph( int vertex_count )
    : vertex_count_( vertex_count )
{}

ArcGraph::ArcGraph( const IGraph& other )
    : vertex_count_( other.VerticesCount() )
{
    for ( int i = 0; i < other.VerticesCount(); ++i ) {
        auto next_vertices = other.GetNextVertices( i );
        for ( int neighbor : next_vertices ) {
            AddEdge( i, neighbor );
        }
    }
}

bool ArcGraph::IsValidIndex( int index ) const {
    return index >= 0 && index < vertex_count_;
}

void ArcGraph::AddEdge( int from, int to ) {
    assert( IsValidIndex( from ) );
    assert( IsValidIndex( to ) );
    
    edges_list_.emplace_back( from, to );
}

int ArcGraph::VerticesCount() const {
    return vertex_count_;
}

std::vector< int > ArcGraph::GetNextVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    for ( const auto& edge : edges_list_ ) {
        if ( edge.first == vertex ) {
            result.push_back( edge.second );
        }
    }
    return result;
}

std::vector< int > ArcGraph::GetPrevVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    for ( const auto& edge : edges_list_ ) {
        if ( edge.second == vertex ) {
            result.push_back( edge.first );
        }
    }
    return result;
}