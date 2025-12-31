#include "SetGraph.hpp"
#include <cassert>
#include <algorithm>

SetGraph::SetGraph( int vertex_count )
    : vertex_count_( vertex_count )
{
    adjacency_sets_.resize( vertex_count_ );
    for ( int i = 0; i < vertex_count_; ++i ) {
        adjacency_sets_[i] = new std::set< int >();
    }
}

SetGraph::SetGraph( const IGraph& other )
    : vertex_count_( other.VerticesCount() )
{
    adjacency_sets_.resize( vertex_count_ );
    for ( int i = 0; i < vertex_count_; ++i ) {
        adjacency_sets_[i] = new std::set< int >();
    }
    
    for ( int i = 0; i < vertex_count_; ++i ) {
        auto next_vertices = other.GetNextVertices( i );
        for ( int neighbor : next_vertices ) {
            AddEdge( i, neighbor );
        }
    }
}

SetGraph::~SetGraph() {
    for ( auto set_ptr : adjacency_sets_ ) {
        delete set_ptr;
    }
}

bool SetGraph::IsValidIndex( int index ) const {
    return index >= 0 && index < vertex_count_;
}

void SetGraph::AddEdge( int from, int to ) {
    assert( IsValidIndex( from ) );
    assert( IsValidIndex( to ) );
    
    adjacency_sets_[from]->insert( to );
}

int SetGraph::VerticesCount() const {
    return vertex_count_;
}

std::vector< int > SetGraph::GetNextVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    const std::set< int >& vertex_set = *adjacency_sets_[vertex];
    result.reserve( vertex_set.size() );
    
    for ( int neighbor : vertex_set ) {
        result.push_back( neighbor );
    }
    return result;
}

std::vector< int > SetGraph::GetPrevVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    
    for ( int i = 0; i < vertex_count_; ++i ) {
        if ( adjacency_sets_[i]->find( vertex ) != adjacency_sets_[i]->end() ) {
            result.push_back( i );
        }
    }
    return result;
}