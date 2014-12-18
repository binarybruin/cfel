//
//  BeaconThread.h
//  BeaconJuce
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You
//
//

#ifndef __BeaconJuce__BeaconThread__
#define __BeaconJuce__BeaconThread__

#include "../JuceLibraryCode/JuceHeader.h"

class BeaconThread : public Thread
{
public:    
    BeaconThread(const String &threadName) : Thread(threadName)
    {
        
    }
    void run() override;
};



#endif /* defined(__BeaconJuce__BeaconThread__) */
