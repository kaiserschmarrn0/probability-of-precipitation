#include "gfx.h"
#include <stdexcept>
#include "log.h"

ALLEGRO_DISPLAY *gfx::display = nullptr;

void gfx::start() {
    if (!al_init())
        throw std::runtime_error("failed to initialize allegro!");
    log::msg("Allegro initialized.");

    display = al_create_display(WND_W, WND_H);
    if (!display)
        throw std::runtime_error("failed to create display!");
    al_set_window_title(display, WND_TITLE);
    log::msg("Display created.");
}

void gfx::end() {
    if (display)
        al_destroy_display(display);
    log::msg("Display destroyed.");
}
