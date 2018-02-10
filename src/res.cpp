#include "res.h"

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>

#include "log.h"

void res::start() {
    // set resource loading path
    ALLEGRO_PATH *exe_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(exe_path, "res");
    al_change_directory(al_path_cstr(exe_path, '/'));
    al_destroy_path(exe_path);
    log::msg("Resource directory set.");
}
void res::end() {}

#define SS_RE_THROW(C) {std::stringstream ss; ss << C; throw std::runtime_error(ss.str());}

res::ALBITMAP_Wrapper::ALBITMAP_Wrapper(std::string const& fpath) {
    bmp = al_load_bitmap(fpath.c_str());
    if(!bmp)
        SS_RE_THROW("failed to load bitmap: " << fpath << " !");
}
res::ALBITMAP_Wrapper::~ALBITMAP_Wrapper() {
    al_destroy_bitmap(bmp);
}

res::ALFONT_Wrapper::ALFONT_Wrapper(std::string const& fpath, uint16_t size) {
    fnt = al_load_ttf_font(fpath.c_str(), size, 0);
    if(!fnt)
        SS_RE_THROW("failed to load font: " << fpath << " !");
}
res::ALFONT_Wrapper::~ALFONT_Wrapper() {
    al_destroy_font(fnt);
}

template<class T, class... TLoadArgs>
std::unordered_map<std::string, std::pair<T*, uint16_t>>
    res::Resource<T, TLoadArgs...>::table;

template<class T, class... TLoadArgs>
res::Resource<T, TLoadArgs...>::Resource(TLoadArgs... args) {
    // create the id by just combining the args with a stringstream
    using expander = int[];
    std::stringstream ss;
    (void)expander{0, (void(ss << "!(!^^" << std::forward<TLoadArgs>(args)),0)...};
    id = ss.str();

    if(table.count(id))
        table.at(id).second++;
    else
        table.emplace(id, std::pair<T*, uint16_t>(new T(args...), 1));
    res = table.at(id).first;
}

template<class T, class... TLoadArgs>
res::Resource<T, TLoadArgs...>::Resource(Resource<T, TLoadArgs...> const& other) {
    id = other.id;
    table.at(id).second++;
    res = table.at(id).first;
}

template<class T, class... TLoadArgs>
res::Resource<T, TLoadArgs...>::~Resource() {
    table.at(id).second--;
    if(!table.at(id).second) {
        delete res;
        table.erase(id);
    }
}

