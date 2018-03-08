#ifndef _InterruptTimerDispatcher_H
#define _InterruptTimerDispatcher_H

#include <Arduino.h>
#include <inttypes.h>
#include "InterruptHandler.h"

namespace g3rb3n
{

    class InterruptTimerDispatcher
    {

    private:
        static InterruptHandler *handlers[16];
        static uint32_t nexts[16];
        static uint8_t handlerCount;
        static uint8_t current;
        static uint32_t next;

    public:
        static InterruptTimerDispatcher& getInstance()
        {
            static InterruptTimerDispatcher instance;
            return instance;
        }
        InterruptTimerDispatcher(InterruptTimerDispatcher const&) = delete;
        void operator=(InterruptTimerDispatcher const&) = delete;

        ~InterruptTimerDispatcher();

        static void handle();
        static void add(InterruptHandler* handler);
    private:
        InterruptTimerDispatcher();
        static void setNext();
    };
  
}

#endif
