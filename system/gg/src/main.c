#include <include.h>

//832x624, 64x48
//only text
//

void gg_init(void) {
    
}

typedef struct {
    void (*gg_init)(void);
} gg_api_t;

gg_apt_t gg_api = {
    .init = gg_init
};
