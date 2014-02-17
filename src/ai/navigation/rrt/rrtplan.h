#ifndef RRT_PLAN_H
#define RRT_PLAN_H

#include "geom/vector_2d.h"
#include "tree.h"
#include "obstacle.h"
#include "constants.h"

class RRTPlan
{
public:
    RRTPlan(int primaryNodeCount,
            int minWidth,
            int maxWidth,
            int minHeight,
            int maxHeight,
            Vector2D* init,
            Vector2D* goal);

public:
    static float baseAngle;
    static float stepSize;
    static float agentRadius;
    static float radius;

    static int maxStep;

private:
    /**
     * Initial and Target Vector Position.
     */
    Vector2D *_initVec;
    Vector2D *_goalVec;

    /**
     * Initial And Target Vector Postion based on _initVec and _goalVec.
     */
    TreeNode *_initNode;
    TreeNode *_goalNode;

    /**
     * Solution set of Nodes and Edges.
     */
    TreeNodes _treeNodes;
//    TreeEdges _treeEdges;

    /**
     * Set of Obstacles.
     */
    Obstacles _obstacles;

    /**
     * Field properties.
     */
    int _minWidth;
    int _maxWidth;

    int _minHeight;
    int _maxHeight;

    /**
     * @brief Number of primary nodes.
     */
    int _primaryNodeCount;
    bool _firstTimeCheck;
public:
    void setInitVector(double x, double y);
    void setGoalVector(double x, double y);

    Vector2D *initVector()
    {
        return _initVec;
    }

    Vector2D *goalVector()
    {
        return _goalVec;
    }

    TreeNode *initNode()
    {
        return _initNode;
    }

    TreeNode *goalNode()
    {
        return _goalNode;
    }

    TreeNodes treeNodes()
    {
        return _treeNodes;
    }

//    TreeEdges treeEdges()
//    {
//        return _treeEdges;
//    }

    int maxWidth()
    {
        return _maxWidth;
    }

    void setMaxWidth(int maxWidth)
    {
        this->_maxWidth = maxWidth;
    }

    int minWidth()
    {
        return _minWidth;
    }

    int maxHeight()
    {
        return _maxHeight;
    }

    void setMaxHeight(int maxHeight)
    {
        this->_maxHeight = maxHeight;
    }

    int minHeight()
    {
        return _minHeight;
    }

    void addObstacle(Obstacle * o)
    {
        _obstacles.push_front(o);
    }

    void clearObstacle()
    {
        foreach(Obstacle* ob, _obstacles)
            ob = NULL;

        _obstacles.clear();
    }

public:
    void generatePrimaryNodes(float);

    TreeNode* extendNode(Vector2D *);
    bool isValidPoint(Vector2D *);
    bool checkStraightRoute(TreeNode* start, TreeNode* end);
    bool buildRRT(RRTPlan *, int);

    TreeNode* extendTree(TreeNode*);
    TreeNode* extendTreeRand(TreeNode*);
};

#endif // RRT_PLAN_H
