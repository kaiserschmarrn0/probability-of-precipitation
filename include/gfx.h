#ifndef GFX_H_
#define GFX_H_

#include <allegro5/allegro.h>

namespace gfx {
    /* window information */
    unsigned int const WND_W = 1600;
    unsigned int const WND_H = 900;
    const char* const WND_TITLE = "Je'Game";

    /* internal display buffer dimensions */
    unsigned int const GFX_W = 512;
    unsigned int const GFX_H = 288;

    /* setup functions */
    void start();
    void end();

    /* allegro internals */
    extern ALLEGRO_DISPLAY *display;
}

#endif
