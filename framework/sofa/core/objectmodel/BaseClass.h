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
#ifndef SOFA_CORE_OBJECTMODEL_BASECLASS_H
#define SOFA_CORE_OBJECTMODEL_BASECLASS_H

#include <sofa/helper/system/config.h>
#include <sofa/helper/vector.h>
#include <sofa/core/core.h>
#include <string>
#include <map>

namespace sofa
{

namespace core
{

namespace objectmodel
{

/**
 *  \brief Class hierarchy reflection base class
 *
 *  This class provides information on the class and parent classes of components.
 *  It is created by using the SOFA_CLASS macro on each new class declaration.
 *  All classes deriving from Base should use the SOFA_CLASS macro within their declaration.
 *
 */
class SOFA_CORE_API BaseClass
{
protected:
    BaseClass();
    virtual ~BaseClass();

public:
    std::string namespaceName;
    std::string className;
    std::string templateName;
    std::string shortName;
    //std::string targetName;
    helper::vector<const BaseClass*> parents;

    bool hasParent(const BaseClass* c) const
    {
        if (*this == *c) return true;
        for (unsigned int i=0; i<parents.size(); ++i)
            if (parents[i]->hasParent(c)) return true;
        return false;
    }

    bool operator==(const BaseClass& c) const
    {
        if (this == &c) return true;
        return (this->namespaceName == c.namespaceName)
                && (this->className == c.className)
                && (this->templateName == c.templateName);
    }

    bool operator!=(const BaseClass& c) const
    {
        return !((*this)==c);
    }
};

// To specify template classes in C macro parameters, we can't write any commas, hence templates with more than 2 parameters have to use the following macros
#define SOFA_TEMPLATE(Class,P1) Class<P1>
#define SOFA_TEMPLATE2(Class,P1,P2) Class<P1,P2>
#define SOFA_TEMPLATE3(Class,P1,P2,P3) Class<P1,P2,P3>
#define SOFA_TEMPLATE4(Class,P1,P2,P3,P4) Class<P1,P2,P3,P4>

// This macro should now be used at the beginning of all declarations of classes with 1 base class
#define SOFA_CLASS(T,Parent) \
    typedef ::sofa::core::objectmodel::TClass< T, Parent > MyClass; \
    typedef Parent Inherit1; \
    SOFA_CLASS_DECL

// This macro should now be used at the beginning of all declarations of classes with 2 base classes
#define SOFA_CLASS2(T,Parent1,Parent2) \
    typedef ::sofa::core::objectmodel::TClass< T, std::pair<Parent1,Parent2> > MyClass; \
    typedef Parent1 Inherit1; \
    typedef Parent2 Inherit2; \
    SOFA_CLASS_DECL

// This macro should now be used at the beginning of all declarations of classes with 3 base classes
#define SOFA_CLASS3(T,Parent1,Parent2,Parent3) \
    typedef ::sofa::core::objectmodel::TClass< T, std::pair<Parent1,std::pair<Parent2,Parent3> > > MyClass; \
    typedef Parent1 Inherit1; \
    typedef Parent2 Inherit2; \
    typedef Parent3 Inherit3; \
    SOFA_CLASS_DECL

// This macro should now be used at the beginning of all declarations of classes with 4 base classes
#define SOFA_CLASS4(T,Parent1,Parent2,Parent3,Parent4) \
    typedef ::sofa::core::objectmodel::TClass< T, std::pair<std::pair<Parent1,Parent2>,std::pair<Parent3,Parent4> > > MyClass; \
    typedef Parent1 Inherit1; \
    typedef Parent2 Inherit2; \
    typedef Parent3 Inherit3; \
    typedef Parent4 Inherit4; \
    SOFA_CLASS_DECL

// This macro should now be used at the beginning of all declarations of classes with 5 base classes
#define SOFA_CLASS5(T,Parent1,Parent2,Parent3,Parent4,Parent5) \
    typedef ::sofa::core::objectmodel::TClass< T, std::pair<std::pair<Parent1,Parent2>,std::pair<Parent3,std::pair<Parent4,Parent5> > > > MyClass; \
    typedef Parent1 Inherit1; \
    typedef Parent2 Inherit2; \
    typedef Parent3 Inherit3; \
    typedef Parent4 Inherit4; \
    typedef Parent5 Inherit5; \
    SOFA_CLASS_DECL

// This macro should now be used at the beginning of all declarations of classes with 5 base classes
#define SOFA_CLASS6(T,Parent1,Parent2,Parent3,Parent4,Parent5,Parent6) \
    typedef ::sofa::core::objectmodel::TClass< T, std::pair<std::pair<Parent1,Parent2>,std::pair<std::pair<Parent3,Parent4>,std::pair<Parent5,Parent6> > > > MyClass; \
    typedef Parent1 Inherit1; \
    typedef Parent2 Inherit2; \
    typedef Parent3 Inherit3; \
    typedef Parent4 Inherit4; \
    typedef Parent5 Inherit5; \
    typedef Parent6 Inherit6; \
    SOFA_CLASS_DECL

// Do not use this macro directly, use SOFA_CLASS instead
#define SOFA_CLASS_DECL                                                 \
    static const MyClass* GetClass() { return MyClass::get(); }         \
    virtual const ::sofa::core::objectmodel::BaseClass* getClass() const \
    { return GetClass(); }                                              \
    template<class SOFA_T> ::sofa::core::objectmodel::BaseData::BaseInitData \
    initData(Data<SOFA_T>* field, const char* name, const char* help,   \
             ::sofa::core::objectmodel::BaseData::DataFlags dataflags)                             \
    {                                                                   \
        ::sofa::core::objectmodel::BaseData::BaseInitData res;          \
        this->initData0(field, res, name, help, dataflags);             \
        res.parentClass = GetClass()->className.c_str();                \
        return res;                                                     \
    }                                                                   \
    template<class SOFA_T> ::sofa::core::objectmodel::BaseData::BaseInitData \
    initData(Data<SOFA_T>* field, const char* name, const char* help,   \
             bool isDisplayed=true, bool isReadOnly=false)              \
    {                                                                   \
        ::sofa::core::objectmodel::BaseData::BaseInitData res;          \
        this->initData0(field, res, name, help,                         \
                        isDisplayed, isReadOnly);                       \
        res.parentClass = GetClass()->className.c_str();                      \
        return res;                                                     \
    }                                                                   \
    template<class SOFA_T> typename Data<SOFA_T>::InitData initData(    \
        Data<SOFA_T>* field, const SOFA_T& value, const char* name,     \
        const char* help, bool isDisplayed=true, bool isReadOnly=false) \
    {                                                                   \
        typename Data<SOFA_T>::InitData res;                            \
        this->initData0(field, res, value, name, help,                  \
                        isDisplayed, isReadOnly);                       \
        res.parentClass = GetClass()->className.c_str();                      \
        return res;                                                     \
    }                                                                   \
    using Inherit1::sout;                                               \
    using Inherit1::serr;                                               \
    using Inherit1::sendl

template <class Parents>
class TClassParents
{
public:
    static int nb()
    {
        return 1;
    }
    static const BaseClass* get(int i)
    {
        if (i==0)
            return Parents::GetClass();
        else
            return NULL;
    }
};

template<>
class TClassParents<void>
{
public:
    static int nb()
    {
        return 0;
    }
    static const BaseClass* get(int)
    {
        return NULL;
    }
};

template<class P1, class P2>
class TClassParents< std::pair<P1,P2> >
{
public:
    static int nb()
    {
        return TClassParents<P1>::nb() + TClassParents<P1>::nb();
    }
    static const BaseClass* get(int i)
    {
        if (i<TClassParents<P1>::nb())
            return TClassParents<P1>::get(i);
        else
            return TClassParents<P2>::get(i-TClassParents<P1>::nb());
    }
};

template <class T, class Parents = void>
class TClass : public BaseClass
{
protected:
    TClass()
    {
        T* ptr = NULL;
        namespaceName = T::namespaceName(ptr);
        className = T::className(ptr);
        templateName = T::templateName(ptr);
        shortName = T::shortName(ptr);
//#ifdef SOFA_TARGET
//        targetName = sofa_tostring(SOFA_TARGET);
//#endif
        parents.resize(TClassParents<Parents>::nb());
        for (int i=0; i<TClassParents<Parents>::nb(); ++i)
            parents[i] = TClassParents<Parents>::get(i);
    }
    virtual ~TClass() {}

public:

    static const TClass<T, Parents>* get()
    {
        static TClass<T, Parents> *singleton = new TClass<T, Parents>;
        return singleton;
    }
};

} // namespace objectmodel

} // namespace core

} // namespace sofa



#endif

