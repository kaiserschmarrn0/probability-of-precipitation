#ifndef EVT_H_
#define EVT_H_

#include <allegro5/allegro.h>

namespace evt {
    /* constants */
    double const UPDATE_RATE = 1.0/60.0;

    /* setup functions */
    void start();
    void end();

    /* utils */
    typedef ALLEGRO_EVENT Event;
    Event get();

    /* allegro internals */
    extern ALLEGRO_EVENT_QUEUE *ev_q;
    extern ALLEGRO_TIMER *timer;
}

#endif
