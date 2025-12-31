#include <iostream>
#include <cassert>
#include <ctime>
#include <algorithm>

template< typename T >
class AvlTree
{
private:
    struct TreeNode
    {
        explicit TreeNode( const T & nodeValue )
        :   nodeData( nodeValue ),
            leftSubtree( nullptr ),
            rightSubtree( nullptr ),
            nodeHeightValue( 1 ),
            subtreeNodeCount( 1 )
        {}

        T nodeData;
        TreeNode * leftSubtree;
        TreeNode * rightSubtree;
        int nodeHeightValue;
        int subtreeNodeCount;
    };

    TreeNode * treeRoot;

public:
    AvlTree()
    :   treeRoot( nullptr )
    {}

    ~AvlTree()
    {
        DeleteEntireTree( treeRoot );
    }

    AvlTree( const AvlTree & ) = delete;
    AvlTree & operator=( const AvlTree & ) = delete;

    bool ContainsValue( const T & searchValue )
    {
        TreeNode * currentNode = treeRoot;
        while( currentNode )
        {
            if( currentNode->nodeData == searchValue )
            {
                return true;
            }
            if( currentNode->nodeData < searchValue )
            {
                currentNode = currentNode->rightSubtree;
            }
            else
            {
                currentNode = currentNode->leftSubtree;
            }
        }
        return false;
    }

    T FindOrderStatistic( unsigned targetOrder )
    {
        if( targetOrder > treeRoot->subtreeNodeCount )
        {
            throw std::runtime_error( "Invalid order value" );
        }
        int currentOrderPosition = GetSubtreeNodeCount( treeRoot->leftSubtree );
        TreeNode * currentTreeNode = treeRoot;
        while( currentOrderPosition != targetOrder )
        {
            if( targetOrder < currentOrderPosition )
            {
                currentTreeNode = currentTreeNode->leftSubtree;
            }
            else if( targetOrder > currentOrderPosition )
            {
                targetOrder = targetOrder - currentOrderPosition - 1;
                currentTreeNode = currentTreeNode->rightSubtree;
            }
            currentOrderPosition = GetSubtreeNodeCount( currentTreeNode->leftSubtree );
        }
        return currentTreeNode->nodeData;
    }

    void InsertValue( const T & insertValue )
    {
        treeRoot = InsertNode( treeRoot, insertValue );
    }

    void RemoveValue( const T & removeValue )
    {
        treeRoot = RemoveNode( treeRoot, removeValue );
    }

private:
    TreeNode * RemoveNode( TreeNode * currentNode, const T & valueToRemove )
    {
        if( !currentNode )
        {
            return nullptr;
        }
        if( currentNode->nodeData < valueToRemove )
        {
            currentNode->rightSubtree = RemoveNode( currentNode->rightSubtree, valueToRemove );
        }
        else if( currentNode->nodeData > valueToRemove )
        {
            currentNode->leftSubtree = RemoveNode( currentNode->leftSubtree, valueToRemove );
        }
        else
        {
            if( currentNode->leftSubtree == nullptr && currentNode->rightSubtree == nullptr )
            {
                delete currentNode;
                return nullptr;
            }
            else if( currentNode->leftSubtree == nullptr && currentNode->rightSubtree != nullptr )
            {
                TreeNode * rightChild = currentNode->rightSubtree;
                currentNode->nodeData = rightChild->nodeData;
                currentNode->leftSubtree = rightChild->leftSubtree;
                currentNode->rightSubtree = rightChild->rightSubtree;
                delete rightChild;
                return BalanceNode( currentNode );
            }
            else if( currentNode->leftSubtree != nullptr && currentNode->rightSubtree == nullptr )
            {
                TreeNode * leftChild = currentNode->leftSubtree;
                currentNode->nodeData = leftChild->nodeData;
                currentNode->leftSubtree = leftChild->leftSubtree;
                currentNode->rightSubtree = leftChild->rightSubtree;
                delete leftChild;
                return BalanceNode( currentNode );
            }
            else
            {
                TreeNode* parentNode = nullptr;
                TreeNode* minNode = currentNode->rightSubtree;
                
                while( minNode->leftSubtree != nullptr )
                {
                    parentNode = minNode;
                    minNode = minNode->leftSubtree;
                }
                
                currentNode->nodeData = minNode->nodeData;
                
                if( parentNode == nullptr )
                {
                    currentNode->rightSubtree = minNode->rightSubtree;
                }
                else
                {
                    parentNode->leftSubtree = minNode->rightSubtree;
                }
                
                delete minNode;
            }
        }
        return BalanceNode( currentNode );
    }

    TreeNode * InsertNode( TreeNode * currentNode, const T & valueToInsert )
    {
        if( !currentNode )
        {
            return new TreeNode( valueToInsert );
        }
        if( currentNode->nodeData <= valueToInsert )
        {
            currentNode->rightSubtree = InsertNode( currentNode->rightSubtree, valueToInsert );
        }
        else
        {
            currentNode->leftSubtree = InsertNode( currentNode->leftSubtree, valueToInsert );
        }
        return BalanceNode( currentNode );
    }

    TreeNode * BalanceNode( TreeNode * nodeToBalance )
    {
        UpdateNodeHeight( nodeToBalance );
        UpdateSubtreeNodeCount( nodeToBalance );
        switch( CalculateBalanceFactor( nodeToBalance ) )
        {
            case 2:
            {
                if( CalculateBalanceFactor( nodeToBalance->rightSubtree ) < 0 )
                {
                    nodeToBalance->rightSubtree = RotateRight( nodeToBalance->rightSubtree );
                }
                return RotateLeft( nodeToBalance );
            }
            case -2:
            {
                if( CalculateBalanceFactor( nodeToBalance->leftSubtree ) > 0 )
                {
                    nodeToBalance->leftSubtree = RotateLeft( nodeToBalance->leftSubtree );
                }
                return RotateRight( nodeToBalance );
            }
            default:
                return nodeToBalance;
        }
    }

    int CalculateBalanceFactor( TreeNode * node )
    {
        return GetNodeHeight( node->rightSubtree ) - GetNodeHeight( node->leftSubtree );
    }

    void UpdateNodeHeight( TreeNode * node )
    {
        node->nodeHeightValue = std::max( GetNodeHeight( node->leftSubtree ), GetNodeHeight( node->rightSubtree ) ) + 1;
    }

    int GetNodeHeight( TreeNode * node )
    {
        return node ? node->nodeHeightValue : 0;
    }

    int GetSubtreeNodeCount( TreeNode * node )
    {
        return node ? node->subtreeNodeCount : 0;
    }

    void UpdateSubtreeNodeCount( TreeNode * node )
    {
        node->subtreeNodeCount = GetSubtreeNodeCount( node->leftSubtree ) + GetSubtreeNodeCount( node->rightSubtree ) + 1;
    }

    TreeNode * RotateLeft( TreeNode * pivotNode )
    {
        TreeNode * newRoot = pivotNode->rightSubtree;
        pivotNode->rightSubtree = newRoot->leftSubtree;
        newRoot->leftSubtree = pivotNode;

        UpdateNodeHeight( pivotNode );
        UpdateNodeHeight( newRoot );
        UpdateSubtreeNodeCount( pivotNode );
        UpdateSubtreeNodeCount( newRoot );
        return newRoot;
    }

    TreeNode * RotateRight( TreeNode * pivotNode )
    {
        TreeNode * newRoot = pivotNode->leftSubtree;
        pivotNode->leftSubtree = newRoot->rightSubtree;
        newRoot->rightSubtree = pivotNode;
        UpdateNodeHeight( pivotNode );
        UpdateNodeHeight( newRoot );
        UpdateSubtreeNodeCount( pivotNode );
        UpdateSubtreeNodeCount( newRoot );
        return newRoot;
    }

    void DeleteEntireTree( TreeNode * node )
    {
        if( node )
        {
            DeleteEntireTree( node->leftSubtree );
            DeleteEntireTree( node->rightSubtree );
            delete node;
        }
    }
};

void ProcessCommands( std::istream & inputStream, std::ostream & outputStream )
{
    int commandCount = 0;
    inputStream >> commandCount;
    AvlTree< int > orderStatisticTree;
    int commandValue = 0;
    int orderIndex = 0;

    for( int i = 0; i < commandCount; ++i )
    {
        inputStream >> commandValue >> orderIndex;
        if( commandValue > 0 )
        {
            orderStatisticTree.InsertValue( commandValue );
        }
        if( commandValue < 0 )
        {
            orderStatisticTree.RemoveValue( -commandValue );
        }
        outputStream << orderStatisticTree.FindOrderStatistic( orderIndex ) << std::endl;
    }
}

int main()
{
    ProcessCommands( std::cin, std::cout );
    return 0;
}