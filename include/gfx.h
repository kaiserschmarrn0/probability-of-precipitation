#ifndef GFX_H_
#define GFX_H_

#include <allegro5/allegro.h>
#include <string>
#include <stdint.h>

#include "res.h"

namespace gfx {
    /* window information */
    unsigned int const WND_W = 1600;
    unsigned int const WND_H = 900;
    const char* const WND_TITLE = "Probability of Precipitation";

    /* internal display buffer dimensions */
    unsigned int const GFX_W = 512;
    unsigned int const GFX_H = 288;

    /* setup functions */
    void start();
    void end();

    /* drawing functions */
    void draw(res::Texture& tex, uint16_t x, uint16_t y);
    void draw_text(res::Font& fnt, uint16_t x, uint16_t y,
            std::string const& text);
    void flip();

    /* allegro internals */
    extern ALLEGRO_DISPLAY *display;
    extern ALLEGRO_BITMAP *buffer; // GFX_W x GFX_H
    extern ALLEGRO_BITMAP *backbuffer; // WND_W x WND_H
}

#endif
