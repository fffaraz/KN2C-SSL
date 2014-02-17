#ifndef TREE_H
#define TREE_H

#include "geom/vector_2d.h"
#include <QList>

class TreeNode;
class TreeEdge;

using namespace rcsc;

typedef QList<TreeEdge*> TreeEdges;
typedef QList<TreeNode*> TreeNodes;

class TreeNode
{
    /** Static Field Members */
public:
    static int indexProvider;
    static int indexError;

    static float distanceEPS;

    /** Private Field Members */
private:
    int _index;
    Vector2D* _position;
    TreeEdges* _adjacentEdges;
    TreeNode* _parent;

    /** Indexers */
public:
    int index() const;
    Vector2D* position() const;
    TreeEdges* adjacentEdges() const;
    TreeNode* parent() const;

    void setParent(TreeNode*);
    void setVector(Vector2D*);
    void setVector(double,double);

    /** Constructors */
public:
    TreeNode(Vector2D*);
    TreeNode();

    /** Public Functions */
public:
    TreeEdge* addNeighbour(TreeNode*);
    void resetMemory()
    {
        this->_adjacentEdges->clear();
    }

    /** Static Functions */
public:
    static Vector2D* randomConfigPoint(float, float, float, float, float = 0);
    static bool checkOverlap(TreeNode*, TreeNode*);
};

class TreeEdge
{
    /** Static Field Members*/
public:
    static int indexProvider;
    static int indexError;

    /** Private Field Members */
private:
    int _index;
    TreeNode* _source;
    TreeNode* _destination;

    /** Indexers */
public:
    int index() const;
    TreeNode* source() const;
    TreeNode* destination() const;

    void setSource(TreeNode*);
    void setDestination(TreeNode*);

    /** Constructors */
public:
    TreeEdge(TreeNode*, TreeNode*);
    TreeEdge();
};

#endif // TREE_H
