// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include <TestI.h>

using namespace std;
using namespace Ice;

void
TestI::transient(const Current& current)
{
    cerr << "TestI::transient" << endl;
    CommunicatorPtr communicator = current.adapter->getCommunicator();
    
    ObjectAdapterPtr adapter =
        communicator->createObjectAdapterWithEndpoints("TransientTestAdapter", "default -p 9999");
    adapter->activate();
    cerr << "TestI::transient activate" << endl;
    adapter->destroy();
    cerr << "TestI::transient ok" << endl;
}

void
TestI::deactivate(const Current& current)
{
    current.adapter->deactivate();
    IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(100));
}

string
CookieI::message() const
{
    return "blahblah";
}
