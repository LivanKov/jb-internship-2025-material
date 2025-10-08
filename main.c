// This file is not available, is up to the student to create it.
// #include "render.h"

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct Core_Data {
    const char* title;
    int         width;
    int         height;
    uint32_t*   framebuffer;
};

typedef struct Core_Data* (*pfn_gfx_create_context)(struct Core_Data*, int, int, const char*);
typedef void (*pfn_gfx_init_context)(struct Core_Data*);
typedef void (*pfn_gfx_close)(struct Core_Data*);
typedef void (*pfn_gfx_loop)(struct Core_Data*);
typedef void (*pfn_gfx_render)(struct Core_Data*, int);
typedef unsigned long (*pfn_gfx_time)(void);
typedef int (*pfn_gfx_get_dim)(void);
typedef const char* (*pfn_gfx_get_title)(void);
typedef uint32_t* (*pfn_gfx_allocate_framebuffer)(struct Core_Data*);

int main(void) {
    void *handle = dlopen("./librender_x86_64.so", RTLD_NOW | RTLD_LOCAL);

    pfn_gfx_create_context gfx_create_context = (pfn_gfx_create_context)dlsym(handle, "gfx_create_context");
    pfn_gfx_init_context   gfx_init_context   = (pfn_gfx_init_context)  dlsym(handle, "gfx_init_context");
    pfn_gfx_close          gfx_close_fn       = (pfn_gfx_close)         dlsym(handle, "gfx_close");
    pfn_gfx_loop           gfx_loop_fn        = (pfn_gfx_loop)          dlsym(handle, "gfx_loop");
    pfn_gfx_render         gfx_render_fn      = (pfn_gfx_render)        dlsym(handle, "gfx_render");
    pfn_gfx_get_dim        gfx_get_width      = (pfn_gfx_get_dim)       dlsym(handle, "gfx_get_width_screen");
    pfn_gfx_get_dim        gfx_get_height     = (pfn_gfx_get_dim)       dlsym(handle, "gfx_get_height_screen");
    pfn_gfx_get_title      gfx_get_title      = (pfn_gfx_get_title)     dlsym(handle, "gfx_get_window_title");
    pfn_gfx_allocate_framebuffer gfx_alloc_fb = (pfn_gfx_allocate_framebuffer) dlsym(handle, "gfx_allocate_framebuffer");

    //Both width and height seem to be hardcoded within the function
    int width = gfx_get_width(); 
    int height = gfx_get_height(); 
    const char* title = gfx_get_title();

    const size_t CTX_SIZE = 0x448;
    void* raw_ctx = malloc(CTX_SIZE);
    
    if (!raw_ctx) {
        fprintf(stderr, "malloc context failed\n");
        dlclose(handle);
        return EXIT_FAILURE;
    }

    memset(raw_ctx, 0, CTX_SIZE);
    struct Core_Data* ctx = (struct Core_Data*)raw_ctx;

    ctx = gfx_create_context(ctx, width, height, title);

    ctx->framebuffer = gfx_alloc_fb(ctx);
    if (!ctx->framebuffer) {
        fprintf(stderr, "allocate framebuffer failed\n");
        free(raw_ctx);
        dlclose(handle);
        return EXIT_FAILURE;
    }

    gfx_init_context(ctx);

    for (;;) {
        gfx_render_fn(ctx, 1);
        gfx_loop_fn(ctx);
    }

    gfx_close_fn(ctx);
    free(raw_ctx);
    dlclose(handle);
    return EXIT_SUCCESS;
}
