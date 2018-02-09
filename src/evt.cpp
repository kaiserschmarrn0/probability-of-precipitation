#include "evt.h"
#include <stdexcept>
#include "log.h"
#include "gfx.h"

ALLEGRO_EVENT_QUEUE *evt::ev_q = nullptr;
ALLEGRO_TIMER *evt::timer = nullptr;

void evt::start() {
    if (!al_install_keyboard())
        throw std::runtime_error("failed to install the keyboard!");
    log::msg("Keyboard installed.");
    
    if (!al_install_mouse())
        throw std::runtime_error("failed to install the mouse!");
    log::msg("Mouse installed.");

    ev_q = al_create_event_queue();
    if (!ev_q)
        throw std::runtime_error("failed to create the event queue!");
    log::msg("Event queue created.");

    timer = al_create_timer(UPDATE_RATE);
    if (!timer)
        throw std::runtime_error("failed to create the update timer!");
    al_start_timer(timer);
    log::msg("Update timer started.");

    al_register_event_source(ev_q, al_get_display_event_source(gfx::display));
    al_register_event_source(ev_q, al_get_keyboard_event_source());
    al_register_event_source(ev_q, al_get_mouse_event_source());
    al_register_event_source(ev_q, al_get_timer_event_source(timer));
    log::msg("Events registered.");
}

void evt::end() {
    if (timer) {
        al_destroy_timer(timer);
        timer = nullptr;
    }
    if (ev_q) {
        al_destroy_event_queue(ev_q);
        ev_q = nullptr;
    }
    log::msg("Events shut down.");
}

evt::Event evt::get() {
    ALLEGRO_EVENT ret;
    al_wait_for_event(ev_q, &ret);
    return ret;
}
