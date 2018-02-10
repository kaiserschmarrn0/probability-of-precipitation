#ifndef RES_H_
#define RES_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <unordered_map>

namespace res {
    /* setup functions */
    void start();
    void end();

    /* 1st level allegro resource wrappers */
    class ALBITMAP_Wrapper {
    public:
        ALBITMAP_Wrapper(std::string const& fpath);
        ~ALBITMAP_Wrapper();
        ALLEGRO_BITMAP *bmp;
    };

    class ALFONT_Wrapper {
    public:
        ALFONT_Wrapper(std::string const& fpath, uint16_t size);
        ALFONT_Wrapper(ALFONT_Wrapper const& other) =delete;
        ~ALFONT_Wrapper();
        ALLEGRO_FONT *fnt;
    };

    /* resource handler template */
    template<class T, class... TLoadArgs>
    class Resource {
    protected:
        // a table of loaded resources: name --> (resource, # of uses)
        static std::unordered_map<std::string, std::pair<T*, uint16_t>> table;

        // the table id of the resource
        std::string id;

    public:
        // calls loader if needbe
        Resource(TLoadArgs... args);

        // copy
        Resource(Resource<T, TLoadArgs...> const& other);

        // destroy a resource if we're the only one using it
        ~Resource();

        // the resource
        T *res;
    };

    /* externally-used resource classes */
    template class Resource<ALBITMAP_Wrapper, std::string const&>;
    template class Resource<ALFONT_Wrapper, std::string const&, uint16_t>;
    typedef Resource<ALBITMAP_Wrapper, std::string const&> Texture;
    typedef Resource<ALFONT_Wrapper, std::string const&, uint16_t> Font;
}

#endif
