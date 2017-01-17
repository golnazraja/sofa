/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU General Public License as published by the Free  *
* Software Foundation; either version 2 of the License, or (at your option)   *
* any later version.                                                          *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for    *
* more details.                                                               *
*                                                                             *
* You should have received a copy of the GNU General Public License along     *
* with this program. If not, see <http://www.gnu.org/licenses/>.              *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFAPHYSICSOUTPUTMESH_TETRAHEDRAL_IMPL_H
#define SOFAPHYSICSOUTPUTMESH_TETRAHEDRAL_IMPL_H

#include "SofaPhysicsAPI.h"

//#include <SofaBaseVisual/VisualModelImpl.h>
#include <SofaOpenglVisual/OglTetrahedralModel.h>
#include <sofa/core/visual/Shader.h>
#include <sofa/defaulttype/Vec.h>

class SofaPhysicsOutputMeshTetrahedron::Impl
{
public:

    Impl();
    ~Impl();

    const char* getName(); ///< (non-unique) name of this object
    ID          getID();   ///< unique ID of this object

    unsigned int getNbVertices(); ///< number of vertices
    const Real* getVPositions();  ///< vertices positions (Vec3)
    const Real* getVNormals();    ///< vertices normals   (Vec3)
    const Real* getVTexCoords();  ///< vertices UVs       (Vec2)
    int getTexCoordRevision();    ///< changes each time texture coord data are updated
    int getVerticesRevision();    ///< changes each time vertices data are updated
    
    unsigned int getNbVAttributes();                    ///< number of vertices attributes
    unsigned int getNbAttributes(int index);            ///< number of the attributes in specified vertex attribute 
    const char*  getVAttributeName(int index);          ///< vertices attribute name
    int          getVAttributeSizePerVertex(int index); ///< vertices attribute #
    const Real*  getVAttributeValue(int index);         ///< vertices attribute (Vec#)
    int          getVAttributeRevision(int index);      ///< changes each time vertices attribute is updated

    unsigned int getNbLines(); ///< number of lines
    const Index* getLines();   ///< lines topology (2 indices / line)
    int getLinesRevision();    ///< changes each time lines data is updated

    unsigned int getNbTetrahedrons(); /// number of Tetrahedrons
    const Index* getTetrahedrons();   /// Tetrahedrons topology (4 indices / Tetrahedrons)
    int getTetrahedronsRevision();    /// changes each time Tetrahedrons data is updated

    unsigned int getNbTriangles(); ///< number of triangles
    const Index* getTriangles();   ///< triangles topology (3 indices / triangle)
    int getTrianglesRevision();    ///< changes each time triangles data is updated

    unsigned int getNbQuads(); ///< number of quads
    const Index* getQuads();   ///< quads topology (4 indices / quad)
    int getQuadsRevision();    ///< changes each time quads data is updated

    //typedef sofa::component::visualmodel::VisualModelImpl SofaOutputMesh;
    //typedef SofaOutputMeshTetrahedron::DataTypes DataTypes;
    
    typedef sofa::defaulttype::Vec3fTypes Vec3f;

    typedef sofa::component::visualmodel::OglTetrahedralModel<Vec3f> SofaOutputMeshTetrahedron;

    typedef SofaOutputMeshTetrahedron::Coord Coord;

    typedef SofaOutputMeshTetrahedron::Tetrahedron Tetrahedron;
    typedef sofa::core::visual::ShaderElement SofaVAttribute;

    



protected:
    SofaOutputMeshTetrahedron::SPtr sObj;
    sofa::helper::vector<SofaVAttribute::SPtr> sVA;

public:
    SofaOutputMeshTetrahedron* getObject(){return sObj.get();}
    void setObject(SofaOutputMeshTetrahedron* o);
};

#endif // SOFAPHYSICSOUTPUTMESH_TETRAHEDRAL_IMPL_H
