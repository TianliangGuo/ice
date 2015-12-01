// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_BATCH_REQUEST_INTERCEPTOR_H
#define ICE_BATCH_REQUEST_INTERCEPTOR_H

#include <IceUtil/Shared.h>

#include <Ice/ProxyF.h>
#ifdef ICE_CPP11_COMPILER
#   include <functional>
#endif

namespace Ice
{

class BatchRequest
{
public:

    virtual ~BatchRequest()
    {
    }

    virtual void enqueue() const = 0;
    virtual int getSize() const = 0;
    virtual const std::string& getOperation() const = 0;
    virtual const Ice::ObjectPrxPtr& getProxy() const = 0;
};

class BatchRequestInterceptor : public ICE_ENABLE_SHARED_FROM_THIS(BatchRequestInterceptor)
{
public:

    virtual void enqueue(const BatchRequest&, int, int) = 0;
};
ICE_DEFINE_PTR(BatchRequestInterceptorPtr, BatchRequestInterceptor);

#ifdef ICE_CPP11_COMPILER
ICE_API BatchRequestInterceptorPtr
newBatchRequestInterceptor(const ::std::function<void (const BatchRequest&, int, int)>&);
#endif

};

#endif
