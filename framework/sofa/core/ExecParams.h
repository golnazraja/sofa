/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 4      *
*                (c) 2006-2009 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                              SOFA :: Framework                              *
*                                                                             *
* Authors: M. Adam, J. Allard, B. Andre, P-J. Bensoussan, S. Cotin, C. Duriez,*
* H. Delingette, F. Falipou, F. Faure, S. Fonteneau, L. Heigeas, C. Mendoza,  *
* M. Nesme, P. Neumann, J-P. de la Plata Alcade, F. Poyer and F. Roy          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_CORE_EXEC_PARAMS_H
#define SOFA_CORE_EXEC_PARAMS_H

#include <sofa/helper/system/atomic.h>
#include <sofa/core/core.h>

namespace sofa
{

namespace core
{

#if defined(SOFA_MAX_THREADS)
enum { SOFA_DATA_MAX_ASPECTS = 2*SOFA_MAX_THREADS };
#else
enum { SOFA_DATA_MAX_ASPECTS = 1 };
#endif

/// Class gathering parameters use by most components methods, and transmitted by all visitors
class SOFA_CORE_API ExecParams
{
public:

    /// Modes of execution
    enum ExecMode
    {
        EXEC_NONE = 0,
        EXEC_DEFAULT,
        EXEC_DEBUG,
        EXEC_GPU,
        EXEC_GRAPH,
        EXEC_KAAPI
    };

private:

    static sofa::helper::system::atomic<int> g_nbThreads;

    class SOFA_CORE_API ExecParamsThreadStorage
    {
    public:
        /// Mode of execution requested
        ExecMode execMode;

        /// Index of current thread (0 corresponding to the only thread in sequential mode, or first thread in parallel mode)
        int threadID;

        /// Aspect index for the current thread
        int aspectID;

        ExecParamsThreadStorage(int tid);
    };

    static ExecParamsThreadStorage* threadStorage();

    ExecParamsThreadStorage* storage;

    ExecParams(ExecParamsThreadStorage* s)
        : storage(s)
    {
    }

public:

    /// Mode of execution requested
    ExecMode execMode() const { return storage->execMode; }

    /// Index of current thread (0 corresponding to the only thread in sequential mode, or first thread in parallel mode)
    int threadID() const { return storage->threadID; }

    /// Number of threads currently known to Sofa
    int nbThreads() const { return g_nbThreads; }

    /// Aspect index for the current thread
    int aspectID() const { return storage->aspectID; }

    ExecParams()
        : storage(threadStorage())
    {
    }

    /// Get the default ExecParams, to be used to provide a default values for method parameters
    static ExecParams* defaultInstance();

    /// Request a specific mode of execution
    ExecParams& setExecMode(ExecMode v) { storage->execMode = v; return *this; }

    /// Specify the index of the current thread
    ExecParams& setThreadID(int v) { storage->threadID = v; return *this; }

    /// Specify the aspect index of the current thread
    ExecParams& setAspectID(int v) { storage->aspectID = v; return *this; }

};

} // namespace core

} // namespace sofa

#endif
