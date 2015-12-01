// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestI.h>
#include <TestCommon.h>

using namespace std;

MyDerivedClassI::MyDerivedClassI()
{
}

Ice::ObjectPrxPtr
MyDerivedClassI::echo(const Ice::ObjectPrxPtr& obj, const Ice::Current&)
{
    return obj;
}

void
MyDerivedClassI::shutdown(const Ice::Current& c)
{
    c.adapter->getCommunicator()->shutdown();
}

Ice::Context
MyDerivedClassI::getContext(const Ice::Current&)
{
    return _ctx;
}

bool
MyDerivedClassI::ice_isA(const std::string& s, const Ice::Current& current) const
{
    _ctx = current.ctx;
#ifdef ICE_CPP11_MAPPING
    return Test::MyDerivedClassDisp::ice_isA(s, current);
#else
    return Test::MyDerivedClass::ice_isA(s, current);
#endif
}
