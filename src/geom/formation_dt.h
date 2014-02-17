// -*-c++-*-

/*!
  \file formation_dt.h
  \brief formation data classes using Delaunay Triangulation Header File.
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

#ifndef RCSC_FORMATION_FORMATION_DT_H
#define RCSC_FORMATION_FORMATION_DT_H

#include "geom/delaunay_triangulation.h"
#include "formationdata.h"
#include "etc/base.h"

#include <QList>

namespace rcsc {

/*!
  \class FormationDT
  \brief formation which utilizes Delaunay Triangulation
*/
class FormationDT {
public:

    static const std::string NAME; //!< type name
    int M_robotNum;
    DelaunayTriangulation M_triangulation;
    QList<FormationData> * M_sample_vector;

    /*!
      \brief just call the base class constructor to initialize formation method name
    */
    FormationDT(int robotNum);

    void createFormationTable(PlayMode pm);
    void train();
    Vector2D getPosition( const int unum,
                          const Vector2D & focus_point ) const;
private:

    Vector2D interpolate( const int unum,
                          const Vector2D & focus_point,
                          const DelaunayTriangulation::Triangle * tri ) const;
};
}
#endif
