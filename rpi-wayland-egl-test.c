#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <wayland-client.h>
#include <stdlib.h>

int main()
{
    const char *wayland_display_name = getenv("WAYLAND_DISPLAY");
    if (!wayland_display_name) {
        printf("WAYLAND_DISPLAY not set\n");
        return -1;
    }

    struct wl_display *wl_display = wl_display_connect(wayland_display_name);
    if (!wl_display) {
        printf("Failed to connect to Wayland display\n");
        return -1;
    }

    EGLDisplay display = eglGetDisplay((EGLNativeDisplayType)wl_display);
    if (display == EGL_NO_DISPLAY) {
        printf("Failed to get EGL display\n");
        wl_display_disconnect(wl_display);
        return -1;
    }

    if (!eglInitialize(display, NULL, NULL)) {
        printf("Failed to initialize EGL\n");
        wl_display_disconnect(wl_display);
        return -1;
    }

    EGLConfig config;
    EGLint numConfigs;
    EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    if (!eglChooseConfig(display, configAttribs, &config, 1, &numConfigs)) {
        printf("Failed to choose EGL config\n");
        eglTerminate(display);
        wl_display_disconnect(wl_display);
        return -1;
    }

    if (numConfigs != 1) {
        printf("Expected 1 EGL config, got %d\n", numConfigs);
        eglTerminate(display);
        wl_display_disconnect(wl_display);
        return -1;
    }

    EGLint pbufferAttribs[] = {
        EGL_WIDTH, 256,
        EGL_HEIGHT, 256,
        EGL_NONE,
    };

    EGLSurface surface = eglCreatePbufferSurface(display, config, pbufferAttribs);
    if (surface == EGL_NO_SURFACE) {
        printf("Failed to create EGL pixel buffer surface\n");
        eglTerminate(display);
        wl_display_disconnect(wl_display);
        return -1;
    }

    printf("Successfully created EGL pixel buffer surface\n");
    eglDestroySurface(display, surface);
    eglTerminate(display);
    wl_display_disconnect(wl_display);
    return 0;
}
