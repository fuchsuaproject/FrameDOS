#include <include.h>

void gg_init(void) {
    
}

typedef struct {
    void (*gg_init)(void);
} gg_api_t;

gg_apt_t gg_api = {
    .init = gg_init
};
