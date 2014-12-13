//
//  BeaconThread.h
//  BeaconJuce
//
//  Created by Elska on 11/17/14.
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
