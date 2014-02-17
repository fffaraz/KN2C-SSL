#include "rrtplan.h"
#include "rrtools.h"

#include <QDebug>
#include <math.h>
#include <limits>

#include "geom/polygon_2d.h"

/**
 * Static Members Initialization
 */

float   RRTPlan::baseAngle = 0.0;
float   RRTPlan::radius = 600;
float   RRTPlan::stepSize = 20;
float   RRTPlan::agentRadius = 5;
int     RRTPlan::maxStep = 30;

/**
 * @brief RRTPlan::RRTPlan
 * @param primaryNodeCount First, expand tree in some branch.
 * @param minWidth Universe's min width.
 * @param maxWidth Universe's max width.
 * @param minHeight Universe's min height.
 * @param maxHeight Universe's max height.
 * @param init Current position
 * @param goal Position will reach there.
 */

RRTPlan::RRTPlan(int primaryNodeCount,
                 int minWidth,
                 int maxWidth,
                 int minHeight,
                 int maxHeight,
                 Vector2D* init,
                 Vector2D* goal) :
    _primaryNodeCount(primaryNodeCount),
    _minWidth(minWidth),
    _maxWidth(maxWidth),
    _minHeight(minHeight),
    _maxHeight(maxHeight),
    _initVec(init),
    _goalVec(goal)
{
    this->_initNode = new TreeNode(this->_initVec);
    this->_goalNode = new TreeNode(this->_goalVec);

    this->_treeNodes.push_back(this->_initNode);
    this->generatePrimaryNodes(RRTPlan::radius);
}

void RRTPlan::setInitVector(double x, double y)
{
    //this->_treeEdges.clear();
    this->_treeNodes.clear();

    this->_initVec->x = x;
    this->_initVec->y = y;
    this->_initNode->setVector(x,y);

    this->generatePrimaryNodes(RRTPlan::radius);
}

void RRTPlan::setGoalVector(double x, double y)
{
    //this->_treeEdges.clear();
    this->_treeNodes.clear();

    this->_goalVec->x = x;
    this->_goalVec->y = y;
    this->_goalNode->setVector(x,y);

    this->generatePrimaryNodes(RRTPlan::radius);
}

void RRTPlan::generatePrimaryNodes(float radius)
{
    float baseAngle = - M_PI;
    float stepAngle = (2 * M_PI) / this->_primaryNodeCount;

    for (int i = 0; i < this->_primaryNodeCount; i ++, baseAngle += stepAngle)
    {
        Vector2D* newVector = new Vector2D(radius * cos(baseAngle), radius * sin(baseAngle));

        float dx = newVector->x;
        float dy = newVector->y;

        float m = fabs(dy / dx);

        if (dx * dx + dy * dy > RRTPlan::radius * RRTPlan::radius)
        {
            dx = RRTPlan::radius * cos(m);
            dy = RRTPlan::radius * sin(m);
        }

        int steps = std::abs(std::max(dx / RRTPlan::stepSize, dy / RRTPlan::stepSize));

        if (steps > maxStep)
            steps = maxStep;

        float xStep = dx / steps;
        float yStep = dy / steps;

        Vector2D *currentPoint = new Vector2D(initVector()->x, initVector()->y);
        Vector2D *temporaryPoint = new Vector2D(Vector2D::ERROR_VALUE, Vector2D::ERROR_VALUE);

        for (int i = 0; i < steps; i ++)
        {
            currentPoint->x += xStep;
            currentPoint->y += yStep;

            if (isValidPoint(currentPoint))
            {
                temporaryPoint->x = currentPoint->x;
                temporaryPoint->y = currentPoint->y;
            }
            else
            {
                break;
            }
        }

        if (!temporaryPoint->isValid())
            continue;

        TreeNode* newNode = new TreeNode(temporaryPoint);
        newNode->setParent(this->_initNode);

        if (newNode == NULL)
            continue;

        //TreeEdge* newEdge = new TreeEdge(this->_initNode, newNode);

        this->_treeNodes.push_back(newNode);
        //this->_treeEdges.push_back(newEdge);
    }
}

/**
 * @brief RRTPlan::isValidPoint
 * @param point
 * @return true, if point is valid (No collision with static obstacles.) .
 */
bool RRTPlan::isValidPoint(Vector2D *point)
{
    if (point->x > maxWidth()
            || point->x < minWidth()
            || point->y > maxHeight()
            || point->y < minHeight())
    {
        return false;
    }

    if (RRTools::contains(_obstacles, Vector2D(point->x, point->y)))
    {
        return false;
    }

    for (int i = 0; i < 4; i ++)
    {
        float x = point->x + RRTPlan::agentRadius * cos((M_PI / 2) * i);
        float y = point->y + RRTPlan::agentRadius * sin((M_PI / 2) * i);

        if (x > maxWidth()
                || x < minWidth()
                || y > maxHeight()
                || y < minHeight())
        {
            return false;
        }

        if (RRTools::contains(_obstacles, Vector2D(x,y)))
            return false;
    }

    return true;
}


TreeNode* RRTPlan::extendTree(TreeNode* extTreeNode)
{
    TreeNode* nearest = NULL;
    float minDist = std::numeric_limits< float >::max();
    for (int i = 0; i < _treeNodes.size(); i ++)
    {
        TreeNode* tn = _treeNodes.at(i);
        float tmp = tn->position()->dist2(*extTreeNode->position());
        if (tmp <= minDist)
        {
            minDist = tmp;
            nearest = tn;
        }
    }

    if (nearest == NULL)
        return NULL;

    float dx = extTreeNode->position()->x - nearest->position()->x;
    float dy = extTreeNode->position()->y - nearest->position()->y;

    float m = fabs(dy / dx);

    if (dx * dx + dy * dy > RRTPlan::radius * RRTPlan::radius)
    {
        dx = RRTPlan::radius * cos(m);
        dy = RRTPlan::radius * sin(m);
    }

    int steps = std::abs(std::max(dx / RRTPlan::stepSize, dy / RRTPlan::stepSize));

    if (steps > maxStep)
        steps = maxStep;

    float xStep = dx / steps;
    float yStep = dy / steps;

    Vector2D *currentPoint = new Vector2D(nearest->position()->x, nearest->position()->y);
    Vector2D *temporaryPoint = new Vector2D(Vector2D::ERROR_VALUE, Vector2D::ERROR_VALUE);

    for (int i = 0; i < steps; i ++)
    {
        currentPoint->x += xStep;
        currentPoint->y += yStep;

        if (isValidPoint(currentPoint))
        {
            temporaryPoint->x = currentPoint->x;
            temporaryPoint->y = currentPoint->y;
        }
        else
        {
            break;
        }
    }

    if (!temporaryPoint->isValid())
        return NULL;

    TreeNode* newNode = new TreeNode(temporaryPoint);
    newNode->setParent(nearest);

    // create bidirectional connection:
    //    TreeEdge* edge_new_old = nearest->addNeighbour(newNode);
    //    TreeEdge* edge_old_new = newNode->addNeighbour(nearest);

    //    if (edge_new_old != NULL)
    //    {
    //_treeEdges.push_front(edge_new_old);
    //_treeEdges.push_front(edge_old_new);

    _treeNodes.push_front(newNode);
    //    }

    return newNode;
}

TreeNode* RRTPlan::extendTreeRand(TreeNode* extNode)
{
    TreeNode* nearest = NULL;
    float minDist = std::numeric_limits< float >::max();
    for(int i = 0; i < _treeNodes.size(); i ++)
    {
        TreeNode* tn = _treeNodes.at(i);
        float tmp = tn->position()->dist2(*extNode->position());
        if (tmp <= minDist)
        {
            minDist = tmp;
            nearest = tn;
        }
    }

    if (nearest == NULL)
    {
#if RRT_DEBUG
        qDebug() << "Nearest is null!";
#endif
        return NULL;
    }

    int steps = RRTPlan::maxStep;

    float dx = extNode->position()->x - nearest->position()->x;
    float dy = extNode->position()->y - nearest->position()->y;

    if (dx * dx + dy * dy > steps * steps)
    {
        float dist = (float) sqrt(dx * dx + dy * dy);
        dx = (dx / dist) * steps;
        dy = (dy / dist) * steps;
    }


    if (abs(dx) < RRTPlan::stepSize && abs(dy) < RRTPlan::stepSize)
        steps = 1;

    float Xstep = dx / steps;
    float Ystep = dy / steps;

    Vector2D* dummyPoint = new Vector2D(nearest->position()->x,nearest->position()->y);
    Vector2D* lastDummyPoint = new Vector2D(-1,-1);

    for (int i = 0; i < steps; i++)
    {
        dummyPoint->x += Xstep;
        dummyPoint->y += Ystep;

        if (isValidPoint(dummyPoint))
        {
            lastDummyPoint = dummyPoint;
        }
        else
        {
            break;
        }
    }

    if (!lastDummyPoint->isValid())
        return NULL;

    TreeNode* newNode = new TreeNode(lastDummyPoint);
    newNode->setParent(nearest);

    // create bidirectional connection:
    //    TreeEdge* edge1 = nearest->addNeighbour(newNode);
    //    TreeEdge* edge2 = newNode->addNeighbour(nearest);

    //    if (edge1 != NULL)
    //    {
    //_treeEdges.push_front(edge1);
    //_treeEdges.push_front(edge2);

    _treeNodes.push_front(newNode);
    //    }

    return newNode;
}


bool RRTPlan::checkStraightRoute(TreeNode* start, TreeNode* end)
{
    Segment2D segment (*start->position(), *end->position());
    Vector2D tmp1, tmp2;

    foreach(Obstacle *ob, _obstacles)
    {
        switch(ob->region()->type())
        {
        case REGION_CIRCLE2D:
        {
            Circle2D *obCir = dynamic_cast<Circle2D*>(ob->region());

            if (obCir->intersection(segment, &tmp1, &tmp2) != 0)
            {
                //qDebug() << "Intersect With Circle (" << obCir->center().x << "," << obCir->center().y << "), (" << obCir->radius() << ")";
                return false;
            }

            break;
        }
        case REGION_TRIANGLE2D:
        {
            Triangle2D *obTri = dynamic_cast<Triangle2D*>(ob->region());

            if (obTri->intersection(segment, &tmp1, &tmp2) != 0)
            {
                //qDebug() << "Intersect With Tri";
                return false;
            }

            break;
        }
        case REGION_RECT2D:
        {
            Rect2D *obRect = dynamic_cast<Rect2D*>(ob->region());

            if (obRect->intersection(segment, &tmp1, &tmp2) != 0)
            {
                //qDebug() << "Intersect With Rect";
                return false;
            }

            break;
        }
        default:
            break;
        }
    }

    //qDebug() << "Merged [Direct Mode]";
    return true;
}

/**
 * @brief RRTPlan::buildRRT
 * @param destTree
 * @param iterates
 * @return true, if RRT Tree built successfully.
 */

bool RRTPlan::buildRRT(RRTPlan * destTree, int iterates)
{
    if (checkStraightRoute(initNode(), goalNode()))
    {
        _treeNodes.clear();
        _treeNodes.append(goalNode());
//        qDebug() << "First time is okay!";
        return true;
    }

    RRTPlan *firstTree = this;
    RRTPlan *secondTree = destTree;

    for (int i = 0; i < iterates; i++)
    {
        TreeNode *rand = new TreeNode(TreeNode::randomConfigPoint(0, maxWidth(),0, maxHeight()));
        TreeNode *newnode1 = firstTree->extendTreeRand(rand);

        if(newnode1 != NULL)
        {
            /*
              Check straight route too goal node before making new nodes!
              */
//            if ()
//            {
//                if (firstTree->goalNode()->index() == initNode()->index())
//                {
//                    _treeNodes.clear();
//                    _treeNodes.append(newnode1);
//                }
//                else
//                {
//                    TreeNode* traverse = newnode1;
//                    while (traverse != NULL)
//                    {
//                        if (traverse->parent() != NULL
//                                && traverse->parent()->index() == initNode()->index())
//                        {
//                            _treeNodes.clear();
//                            _treeNodes.append(traverse);
//                            break;
//                        }

//                        traverse = traverse->parent();
//                    }
//                }

                //qDebug() << "Check Straight Route After Expanding (" << i << ") Nodes.";
//                return true;
//            }

            TreeNode* newnode2 = secondTree->extendTree(newnode1);

            if (newnode2 != NULL)
            {
                if (TreeNode::checkOverlap(newnode1,newnode2))
                {
                    //_treeEdges.clear();
                    _treeNodes.clear();

                    TreeNode* traverse = newnode1;
                    while(traverse != NULL)
                    {
                        _treeNodes.push_back(traverse);

                        //                        if (traverse->parent() != NULL)
                        //                            _treeEdges.push_back(new TreeEdge(traverse->parent(), traverse));

                        traverse = traverse->parent();
                    }

                    traverse = newnode2;
                    while(traverse != NULL)
                    {
                        _treeNodes.push_back(traverse);
                        //                        if (traverse->parent() != NULL)
                        //                            _treeEdges.push_back(new TreeEdge(traverse->parent(), traverse));

                        traverse = traverse->parent();
                    }

                    TreeNode* rootChild = new TreeNode();

                    foreach(TreeNode* n, _treeNodes)
                    {
                        if (n->parent() != NULL &&
                                n->parent()->index() == initNode()->index())
                        {
                            rootChild->setVector(n->position()->x, n->position()->y);
                            rootChild->setParent(n->parent());
                            break;
                        }
                    }

                    //_treeEdges.clear();
                    _treeNodes.clear();
                    _treeNodes.append(rootChild);

#if RRT_DEBUG
                    qDebug() << "Merged!";
#endif
                    return true;
                }
            }

            RRTPlan *temp = firstTree;
            firstTree = secondTree;
            secondTree = temp;
        }
    }

#if RRT_DEBUG
    qDebug() << "Failed;
#endif
    return false;
}
