#include <allegro5/allegro.h>
#include <string>
#include <stdexcept>

#include "log.h"
#include "gfx.h"
#include "evt.h"

typedef unsigned int uint;

struct element{
    uint type;
    int pos_x;
    int pos_y;
};


/* proto */

static void events_loop();

/* def */

static void
events_loop()
{
    evt::Event ev;
    bool redraw = true;

    while(true) {
        ev = evt::get();

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_Q:
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    break;
                case ALLEGRO_KEY_W:
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    break;
            }
        }

        if (redraw) {
            redraw = false;
            al_flip_display();
        }
    }
}


void start_all() {
    log::start();
    gfx::start();
    evt::start();
}

void end_all() {
    evt::end();
    gfx::end();
    log::end();
}

int
main()
{
    try {
        start_all();
        events_loop();
    }
    catch (std::runtime_error const& err) {
        log::error(err.what());
    }
    end_all();

    return 0;
}
