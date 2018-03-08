#ifndef _InterruptHandler_H
#define _InterruptHandler_H

#include <Arduino.h>
#include <inttypes.h>

namespace g3rb3n
{

    class InterruptHandler
    {
        public:
            ~InterruptHandler();

            virtual void handle() = 0;
            virtual uint32_t next() = 0;
    };
  
}

#endif
