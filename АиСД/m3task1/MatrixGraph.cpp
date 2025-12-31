#include "MatrixGraph.hpp"
#include <cassert>

MatrixGraph::MatrixGraph( int vertex_count )
    : adjacency_matrix_( vertex_count, std::vector< bool >( vertex_count, false ) )
{}

MatrixGraph::MatrixGraph( const IGraph& other )
    : adjacency_matrix_( other.VerticesCount(), std::vector< bool >( other.VerticesCount(), false ) )
{
    for ( int i = 0; i < other.VerticesCount(); ++i ) {
        auto next_vertices = other.GetNextVertices( i );
        for ( int neighbor : next_vertices ) {
            AddEdge( i, neighbor );
        }
    }
}

bool MatrixGraph::IsValidIndex( int index ) const {
    return index >= 0 && index < VerticesCount();
}

void MatrixGraph::AddEdge( int from, int to ) {
    assert( IsValidIndex( from ) );
    assert( IsValidIndex( to ) );
    
    adjacency_matrix_[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return static_cast< int >( adjacency_matrix_.size() );
}

std::vector< int > MatrixGraph::GetNextVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    for ( int i = 0; i < VerticesCount(); ++i ) {
        if ( adjacency_matrix_[vertex][i] ) {
            result.push_back( i );
        }
    }
    return result;
}

std::vector< int > MatrixGraph::GetPrevVertices( int vertex ) const {
    assert( IsValidIndex( vertex ) );
    
    std::vector< int > result;
    for ( int i = 0; i < VerticesCount(); ++i ) {
        if ( adjacency_matrix_[i][vertex] ) {
            result.push_back( i );
        }
    }
    return result;
}