//
//  BeaconThread.cpp
//  BeaconJuce
//
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You
//
//

#include "BeaconThread.h"


void BeaconThread::run()
{
    for (int i=0; i<10; i++)
    {
        std::cout << getThreadName() << std::endl;
        sleep(rand() % 1000);
    }
    
    std::cout << "DONE! " << getThreadName() << std::endl;
}