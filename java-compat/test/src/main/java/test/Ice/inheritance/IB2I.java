// **********************************************************************
//
// Copyright (c) 2003-present ZeroC, Inc. All rights reserved.
//
// **********************************************************************

package test.Ice.inheritance;

import test.Ice.inheritance.Test.MA.IAPrx;
import test.Ice.inheritance.Test.MB.IB2Prx;
import test.Ice.inheritance.Test.MB._IB2Disp;

public final class IB2I extends _IB2Disp
{
    public
    IB2I()
    {
    }

    @Override
    public IAPrx
    iaop(IAPrx p, Ice.Current current)
    {
        return p;
    }

    @Override
    public IB2Prx
    ib2op(IB2Prx p, Ice.Current current)
    {
        return p;
    }
}
