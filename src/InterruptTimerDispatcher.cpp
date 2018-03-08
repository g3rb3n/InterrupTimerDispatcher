#include "InterruptTimerDispatcher.h"

#include <Arduino.h>

#define MAX_INT 2147483647
#define MAX_UINT 4294967295
namespace g3rb3n
{

    InterruptHandler* InterruptTimerDispatcher::handlers[16];
    uint32_t InterruptTimerDispatcher::nexts[16];
    uint8_t InterruptTimerDispatcher::handlerCount;
    uint8_t InterruptTimerDispatcher::current;
    uint32_t InterruptTimerDispatcher::next;

    InterruptTimerDispatcher::~InterruptTimerDispatcher()
    {
    }
    
    InterruptTimerDispatcher::InterruptTimerDispatcher()
    {
        noInterrupts();
        timer0_isr_init();
        timer0_attachInterrupt(InterruptTimerDispatcher::ISR);
        timer0_write(0);
        interrupts();
    }

    void InterruptTimerDispatcher::handle(void)
    {
        handlers[current]->handle();
        nexts[current] += handlers[current]->next() * ESP.getCpuFreqMHz();
        setNext();
    }

    void InterruptTimerDispatcher::add(InterruptHandler* handler)
    {
        handlers[handlerCount] = handler;
        handler->handle();
        nexts[handlerCount] = ESP.getCycleCount() + handler->next() * ESP.getCpuFreqMHz();
        handlerCount++;
        setNext();
    }

    void InterruptTimerDispatcher::setNext()
    {
        current = 0;
        uint32_t count = ESP.getCycleCount();
        for (uint8_t idx = 0 ; idx < handlerCount ; ++idx)
            if (nexts[idx] < nexts[current])
                current = idx;
        timer0_write(nexts[current]); 
        next = nexts[current];
    }
}
