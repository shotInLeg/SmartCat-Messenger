#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void PollThread::run()
{
    while(1)
    {
        if( queueFunction.size() != 0 )
        {

        }
    }

    done();
}

void PollThread::addQueue(int(*p)(QString) )
{
    queueFunction.push_back(p);
}

