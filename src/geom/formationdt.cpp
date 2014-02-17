// -*-c++-*-

/*!
  \file formation_dt.cpp
  \brief Delaunay Triangulation formation data classes Source File.
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "formation_dt.h"
#include "formationparser.h"

#include <segment_2d.h>
#include <line_2d.h>
//#include <rcsc/math_util.h>

#include <sstream>
#include <cstdio>

namespace rcsc {

const std::string FormationDT::NAME( "DelaunayTriangulation" );

/*-------------------------------------------------------------------*/
/*!

     */
FormationDT::FormationDT(int robotNum)
{
    M_robotNum = robotNum;
}

/*-------------------------------------------------------------------*/
/*!

     */
void
FormationDT::createFormationTable()
{
    FormationParser formationParser;
    M_sample_vector = formationParser.parse(M_robotNum);
    qDebug() << "Formation" << M_robotNum << "- Parsed Successfully";
    train();
    qDebug() << "All Positions Trained Successfully";
}

/*-------------------------------------------------------------------*/
/*!

     */
void
FormationDT::train()
{
    Rect2D pitch( Vector2D( -3050.0, -2050.0 ),
                  Size2D( 6100.0, 4100.0 ) );
    M_triangulation.init( pitch );

    QList<FormationData>::iterator end = M_sample_vector->end();
    for (QList<FormationData>::iterator it = M_sample_vector->begin();
         it != end;
         it ++)
    {
        M_triangulation.addVertex(it->ball);
    }

    M_triangulation.compute();
}

/*-------------------------------------------------------------------*/
/*!

     */
Vector2D
FormationDT::getPosition( const int unum,
                          const Vector2D & focus_point ) const
{
    if ( unum < 0 || 11 < unum )
    {
        std::cerr << __FILE__ << ":" << __LINE__
                  << " *** ERROR *** invalid unum " << unum
                  << std::endl;
        return Vector2D::INVALIDATED;
    }

    const DelaunayTriangulation::Triangle * tri
            = M_triangulation.findTriangleContains( focus_point );

    // linear interpolation
    return interpolate( unum, focus_point, tri );
}

/*-------------------------------------------------------------------*/
/*!

     */
void
FormationDT::getPositions(const Vector2D & focus_point,
                           QList<Vector2D> &positions ) const
{
    positions.clear();

    const DelaunayTriangulation::Triangle * tri
            = M_triangulation.findTriangleContains( focus_point );

    for ( int unum = 1; unum <= 11; ++unum )
    {
        positions.append(interpolate( unum, focus_point, tri ));
    }
}


/*-------------------------------------------------------------------*/
/*!

     */
Vector2D
FormationDT::interpolate( const int unum,
                          const Vector2D & focus_point,
                          const DelaunayTriangulation::Triangle * tri ) const
{

    if ( ! tri )
    {
        const DelaunayTriangulation::Vertex * v
                = M_triangulation.findNearestVertex( focus_point );

        if ( ! v )
        {
            std::cerr << __FILE__ << ":" << __LINE__
                      << " *** ERROR *** No vertex!"
                      << std::endl;
            return Vector2D::INVALIDATED;
        }

        try
        {
            //std::cerr << "found nearest vertex id= " << v->id() << std::endl;
            return M_sample_vector->at( v->id() ).robots[unum];
        }
        catch ( std::exception & e )
        {
            std::cerr << __FILE__ << ":" << __LINE__
                      << " exception caught! "
                      << e.what() << std::endl;
            return Vector2D::INVALIDATED;
        }
    }

    try
    {
        Vector2D result_0 = M_sample_vector->at( tri->vertex( 0 )->id() ).robots[unum];
        Vector2D result_1 = M_sample_vector->at( tri->vertex( 1 )->id() ).robots[unum];
        Vector2D result_2 = M_sample_vector->at( tri->vertex( 2 )->id() ).robots[unum];

        Line2D line_0( tri->vertex( 0 )->pos(),
                       focus_point );

        Segment2D segment_12( tri->vertex( 1 )->pos(),
                              tri->vertex( 2 )->pos() );

        Vector2D intersection_12 = segment_12.intersection( line_0 );

        if ( ! intersection_12.isValid() )
        {
            if ( focus_point.dist2( tri->vertex( 0 )->pos() ) < 1.0e-5 )
            {
                return result_0;
            }

            std::cerr << __FILE__ << ":" << __LINE__
                      << "***ERROR*** No intersection!\n"
                      << " focus=" << focus_point
                      << " line_intersection=" << intersection_12
                      << "\n v0=" << tri->vertex( 0 )->pos()
                      << " v1=" << tri->vertex( 1 )->pos()
                      << " v2=" << tri->vertex( 2 )->pos()
                      << std::endl;

            return ( result_0 + result_1 + result_2 ) / 3.0;
        }

        // distance from vertex_? to interxection_12
        double dist_1i = tri->vertex( 1 )->pos().dist( intersection_12 );
        double dist_2i = tri->vertex( 2 )->pos().dist( intersection_12 );

        // interpolation result of vertex_1 & vertex_2
        Vector2D result_12
                = result_1
                + ( result_2 - result_1 ) * ( dist_1i / ( dist_1i + dist_2i ) );

        // distance from vertex_0 to ball
        double dist_0b = tri->vertex( 0 )->pos().dist( focus_point );
        // distance from interxectin_12 to ball
        double dist_ib = intersection_12.dist( focus_point );

        // interpolation result of vertex_0 & intersection_12
        Vector2D result_012
                = result_0
                + ( result_12 - result_0 ) * ( dist_0b / ( dist_0b + dist_ib ) );

        return result_012;
    }
    catch ( std::exception & e )
    {
        std::cerr << __FILE__ << ":" << __LINE__
                  << " Exception caught!! "
                  << e.what()
                  << std::endl;
        return  Vector2D::INVALIDATED;
    }
}
}
