#include "gfx.h"

#include <stdexcept>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "log.h"
#include "res.h"

ALLEGRO_DISPLAY *gfx::display = nullptr;
ALLEGRO_BITMAP *gfx::buffer = nullptr;
ALLEGRO_BITMAP *gfx::backbuffer = nullptr;

void gfx::start() {
    // initialize allegro
    if (!al_init())
        throw std::runtime_error("failed to initialize allegro!");
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    log::msg("Allegro initialized.");

    // create display; store pointer to backbuffer
    display = al_create_display(WND_W, WND_H);
    if (!display)
        throw std::runtime_error("failed to create display!");
    al_set_window_title(display, WND_TITLE);
    backbuffer = al_get_backbuffer(display);
    log::msg("Display created.");

    // create internal/intermediate buffer
    buffer = al_create_bitmap(GFX_W, GFX_H);
    al_set_target_bitmap(buffer);
    if(!buffer)
        throw std::runtime_error("failed to create intermediate buffer!");
    log::msg("Intermediate graphics buffer created.");
}

void gfx::end() {
    if(buffer)
        al_destroy_bitmap(buffer);
    log::msg("Intermediate graphics buffer destroyed.");
    if (display)
        al_destroy_display(display);
    log::msg("Display destroyed.");
}

void gfx::draw(res::Texture& tex, uint16_t x, uint16_t y) {
    al_draw_bitmap(tex.res->bmp, x, y, 0);
}

void gfx::draw_text(res::Font& fnt, uint16_t x, uint16_t y,
        std::string const& text) {
    // TODO
}

void gfx::flip() {
    al_set_target_bitmap(backbuffer);
    al_draw_scaled_bitmap(
            buffer, // source
            0, 0, GFX_W, GFX_H, // source x, y, w, h
            0, 0, WND_W, WND_H, // dest x, y, w, h
            0); // (flags)
    al_flip_display();
    al_set_target_bitmap(buffer);
}
