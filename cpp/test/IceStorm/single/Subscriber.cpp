// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>
#include <Single.h>
#include <fstream>

#ifdef WIN32
#   include <io.h>
#endif

using namespace std;
using namespace Ice;
using namespace IceStorm;

class SingleI : public Single
{
public:

    SingleI(const CommunicatorPtr& communicator) :
	_communicator(communicator),
	_count(0)
    {
    }

    virtual void event(const Current&)
    {
	++_count;
	if (_count == 10)
	{
	    _communicator->shutdown();
	}
    }

private:

    CommunicatorPtr _communicator;
    int _count;
};

void
createLock(const string& name)
{
    ofstream f(name.c_str());
}

void
deleteLock(const string& name)
{
#ifdef WIN32
    _unlink(name.c_str());
#else
    unlink(name.c_str());
#endif
}

int
run(int argc, char* argv[], const CommunicatorPtr& communicator)
{
    string lockfile = "subscriber.lock";

    if (argc != 1)
    {
	lockfile = argv[1];
    }
    createLock(lockfile);

    PropertiesPtr properties = communicator->getProperties();
    const char* managerEndpointsProperty = "IceStorm.TopicManager.Endpoints";
    string managerEndpoints = properties->getProperty(managerEndpointsProperty);
    if (managerEndpoints.empty())
    {
	cerr << argv[0] << ": property `" << managerEndpointsProperty << "' is not set" << endl;
	return EXIT_FAILURE;
    }

    ObjectPrx base = communicator->stringToProxy("TopicManager:" + managerEndpoints);
    IceStorm::TopicManagerPrx manager = IceStorm::TopicManagerPrx::checkedCast(base);
    if (!manager)
    {
	cerr << argv[0] << ": `" << managerEndpoints << "' is not running" << endl;
	return EXIT_FAILURE;
    }

    ObjectAdapterPtr adapter = communicator->createObjectAdapterWithEndpoints("SingleAdapter", "default");
    ObjectPtr single = new SingleI(communicator);
    ObjectPrx object = adapter->add(single, stringToIdentity("single#events"));

    IceStorm::QoS qos;
    //TODO: qos["reliability"] = "batch";
    try
    {
	manager->subscribe(qos, object);
    }
    catch(const IceStorm::NoSuchTopic& e)
    {
	cerr << argv[0] << ": NoSuchTopic: " << e.name << endl;
	return EXIT_FAILURE;
    }

    adapter->activate();

    communicator->waitForShutdown();

    deleteLock(lockfile);

    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    CommunicatorPtr communicator;

    try
    {
	addArgumentPrefix("IceStorm");
	communicator = initialize(argc, argv);
	status = run(argc, argv, communicator);
    }
    catch(const Exception& ex)
    {
	cerr << ex << endl;
	status = EXIT_FAILURE;
    }

    if (communicator)
    {
	try
	{
	    communicator->destroy();
	}
	catch(const Exception& ex)
	{
	    cerr << ex << endl;
	    status = EXIT_FAILURE;
	}
    }

    return status;
}
