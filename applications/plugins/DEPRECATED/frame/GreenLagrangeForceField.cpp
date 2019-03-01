/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2019 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#define FRAME_GREENLAGRANGEFORCEFIELD_CPP

#include "GreenLagrangeForceField.inl"
#include <sofa/core/ObjectFactory.h>

namespace sofa
{

namespace component
{

namespace forcefield
{

using namespace sofa::defaulttype;

// Register in the Factory
int GreenLagrangeForceFieldClass = core::RegisterObject("Compute forces on deformation gradients")
        .add< GreenLagrangeForceField<DeformationGradient331dTypes> >()
        .add< GreenLagrangeForceField<DeformationGradient332dTypes> >()

        ;

template class SOFA_FRAME_API GreenLagrangeForceField<DeformationGradient331dTypes>;
template class SOFA_FRAME_API GreenLagrangeForceField<DeformationGradient332dTypes>;




}
}

} // namespace sofa

