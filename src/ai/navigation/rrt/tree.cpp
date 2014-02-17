#include "tree.h"
#include <QDebug>

int TreeNode::indexProvider = 0;
int TreeNode::indexError = INT_MAX;
float TreeNode::distanceEPS = 4;

int TreeEdge::indexProvider = 0;
int TreeEdge::indexError = INT_MAX;

/**
    Implementation of TreeNode class.
*/
TreeNode::TreeNode(Vector2D* position)
{
    this->_index = TreeNode::indexProvider ++;
    this->_position = position;
    this->_adjacentEdges = new TreeEdges();
    this->_parent = NULL;
}

TreeNode::TreeNode()
{
    this->_index = TreeNode::indexError;
    this->_position = NULL;
    this->_adjacentEdges = NULL;
    this->_parent = NULL;
}

int TreeNode::index() const
{
    return _index;
}

Vector2D* TreeNode::position() const
{
    return _position;
}

TreeEdges* TreeNode::adjacentEdges() const
{
    return _adjacentEdges;
}

TreeNode* TreeNode::parent() const
{
    return _parent;
}

void TreeNode::setParent(TreeNode * parent)
{
    this->_parent = parent;
}

void TreeNode::setVector(Vector2D* position)
{
    this->_position = position;
}

void TreeNode::setVector(double x, double y)
{
    if (this->_position == NULL)
    {
        this->_position = new Vector2D(x,y);
    }
    else
    {
        this->_position->x = x;
        this->_position->y = y;
    }
}

TreeEdge* TreeNode::addNeighbour(TreeNode* node)
{
    TreeEdges::const_iterator it;
    for (it = _adjacentEdges->begin(); it != _adjacentEdges->end(); it++)
        if ((*it)->index() == node->index())
            return NULL;

    TreeEdge* edge = new TreeEdge(this, node);
    _adjacentEdges->push_front(edge);
    return edge;
}

Vector2D* TreeNode::randomConfigPoint(float minWidth, float maxWidth, float minHeight, float maxHeight,float offset)
{
    float width = offset + ((float) rand() / RAND_MAX) * maxWidth;
    float height = offset + ((float) rand() / RAND_MAX) * maxHeight;

    return new Vector2D(width - minWidth, height - minHeight);
}

bool TreeNode::checkOverlap(TreeNode* node1, TreeNode* node2)
{
    return node1->position()->dist(*node2->position()) < TreeNode::distanceEPS;
}

/**
    Implementation of TreeEdge class.
*/
TreeEdge::TreeEdge(TreeNode* source, TreeNode* destination)
{
    this->_index = TreeEdge::indexProvider++;
    this->setSource(source);
    this->setDestination(destination);
}

TreeEdge::TreeEdge()
{
    this->_index = TreeEdge::indexError;
    this->setSource(NULL);
    this->setDestination(NULL);
}

int TreeEdge::index() const
{
    return _index;
}

TreeNode* TreeEdge::source() const
{
    return _source;
}

TreeNode* TreeEdge::destination() const
{
    return _destination;
}

void TreeEdge::setSource(TreeNode * source)
{
    this->_source = source;
}

void TreeEdge::setDestination(TreeNode * destination)
{
    this->_destination = destination;
}
