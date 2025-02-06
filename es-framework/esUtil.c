//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// ESUtil.c
//
//    A utility library for OpenGL ES.  This library provides a
//    basic common framework for the example applications in the
//    OpenGL ES 2.0 Programming Guide.
//

///
//  Includes
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"
#include <pthread.h>

#ifdef USE_X11
#   include  <X11/Xlib.h>
#   include  <X11/Xatom.h>
#   include  <X11/Xutil.h>

// X11 related local variables
static Display *x_display = NULL;
#elif defined(USE_FB)
#   include <GLES2/gl2ext.h>
#   include <EGL/eglvivante.h>

static EGLNativeDisplayType* native_display = NULL;
#elif defined(USE_DRM)
#   include <fcntl.h>
#   include <xf86drm.h>
#   include <xf86drmMode.h>
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
static EGLint native_window = 0;
#   ifdef USE_GBM
#       include <gbm.h>
#   endif //USE_GBM
#endif //USE_X11

void eglErrorStr(EGLint eglError) {
    switch(eglError) {
        case EGL_SUCCESS:
            printf("The last function succeeded without error.\n");
            break;
        case EGL_NOT_INITIALIZED:
            printf("EGL is not initialized, or could not be initialized, for the specified EGL display connection.\n");
            break;
        case EGL_BAD_ACCESS:
            printf("EGL cannot access a requested resource (for example a context is bound in another thread).\n");
            break;
        case EGL_BAD_ALLOC:
            printf("EGL failed to allocate resources for the requested operation.\n");
            break;
        case EGL_BAD_ATTRIBUTE:
            printf("An unrecognized attribute or attribute value was passed in the attribute list.\n");
            break;
        case EGL_BAD_CONTEXT:
            printf("An EGLContext argument does not name a valid EGL rendering context.\n");
            break;
        case EGL_BAD_CONFIG:
            printf("An EGLConfig argument does not name a valid EGL frame buffer configuration.\n");
            break;
        case EGL_BAD_CURRENT_SURFACE:
            printf("The current surface of the calling thread is a window, pixel buffer or pixmap that is no longer valid.\n");
            break;
        case EGL_BAD_DISPLAY:
            printf("An EGLDisplay argument does not name a valid EGL display connection.\n");
            break;
        case EGL_BAD_SURFACE:
            printf("An EGLSurface argument does not name a valid surface (window, pixel buffer or pixmap) configured for GL rendering.\n");
            break;
        case EGL_BAD_MATCH:
            printf("Arguments are inconsistent (for example, a valid context requires buffers not supplied by a valid surface).\n");
            break;
        case EGL_BAD_PARAMETER:
            printf("One or more argument values are invalid.\n");
            break;
        case EGL_BAD_NATIVE_PIXMAP:
            printf("A NativePixmapType argument does not refer to a valid native pixmap.\n");
            break;
        case EGL_BAD_NATIVE_WINDOW:
            printf("A NativeWindowType argument does not refer to a valid native window.\n");
            break;
        case EGL_CONTEXT_LOST:
            printf("A power management event has occurred. The application must destroy all contexts and reinitialise OpenGL ES state and objects to continue rendering.\n");
            break;
    }
}

///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext (ESContext* esContext, EGLint attribList[])
{
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    printf("%s:%u\n", __FUNCTION__, __LINE__);

    // Get Display
#ifdef USE_X11
    display = eglGetDisplay((EGLNativeDisplayType)x_display);
#elif defined(USE_FB)
    display = eglGetDisplay(native_display);
#elif defined(USE_DRM)
    // Get an EGL display
#   ifdef USE_GBM
    printf("%s:%u\n", __FUNCTION__, __LINE__);
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    printf("%s:%u\n", __FUNCTION__, __LINE__);

    if (eglGetPlatformDisplayEXT != NULL) {
        display = eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_KHR, esContext->gbm_dev, NULL);
    }
    else {
        display = eglGetDisplay((EGLNativeDisplayType)esContext->gbm_dev);
    }
#   else
    printf("%s:%u\n", __FUNCTION__, __LINE__);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#   endif //USE_GBM
    printf("%s:%u\n", __FUNCTION__, __LINE__);
#endif //USE_X11
    printf("%s:%u\n", __FUNCTION__, __LINE__);
    if ( display == EGL_NO_DISPLAY )
    {
        printf("display is EGL_NO_DISPLAY\n");
        return EGL_FALSE;
    }
    printf("%s:%u\n", __FUNCTION__, __LINE__);

    // Initialize EGL
    if ( !eglInitialize(display, &majorVersion, &minorVersion) )
    {
        EGLint error = eglGetError();
        printf("eglInitialize failed, eglError: %d\n", error);
        eglErrorStr(error);
        return EGL_FALSE;
    }
    printf("%s:%u\n", __FUNCTION__, __LINE__);

    // Get configs
    if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
    {
        printf("eglGetConfigs failed\n");
        return EGL_FALSE;
    }
    printf("%s:%u\n", __FUNCTION__, __LINE__);

    // Choose config
    if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
    {
        printf("eglChooseConfig failed\n");
        return EGL_FALSE;
    }

    printf("%s:%u\n", __FUNCTION__, __LINE__);
    // Create a surface
    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)esContext->hWnd, NULL);
    if ( surface == EGL_NO_SURFACE )
    {
        printf("eglCreateWindowSurface failed\n");
        return EGL_FALSE;
    }

    printf("%s:%u\n", __FUNCTION__, __LINE__);
    // Create a GL context
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
    if ( context == EGL_NO_CONTEXT )
    {
        printf("eglCreateContext failed\n");
        return EGL_FALSE;
    }

    printf("%s:%u\n", __FUNCTION__, __LINE__);
    // Make the context current
    if ( !eglMakeCurrent(display, surface, surface, context) )
    {
        printf("eglMakeCurrent failed\n");
        return EGL_FALSE;
    }

    printf("%s:%u\n", __FUNCTION__, __LINE__);
    esContext->eglDisplay = display;
    printf("%s:%u\n", __FUNCTION__, __LINE__);
    esContext->eglSurface = surface;
    printf("%s:%u\n", __FUNCTION__, __LINE__);
    esContext->eglContext = context;

    printf("CreateEGLContext complete\n");

    return EGL_TRUE;
}


#ifdef USE_X11
///
//  WinCreate()
//
//      This function initialized the native X11 display and window for EGL
//
EGLBoolean WinCreate(ESContext *esContext, const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    (void) ecfg;
    (void) num_config;
    /*
     * X11 native display initialization
     */

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
    win = XCreateWindow(
            x_display, root,
            0, 0, esContext->width, esContext->height, 0,
            CopyFromParent, InputOutput,
            CopyFromParent, CWEventMask,
            &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
            x_display,
            DefaultRootWindow ( x_display ),
            FALSE,
            SubstructureNotifyMask,
            &xev );

    esContext->hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}

///
//  userInterrupt()
//
//      Reads from X11 event loop and interrupt program if there is a keypress, or
//      window close action.
//
GLboolean userInterrupt(ESContext *esContext)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while ( XPending ( x_display ) )
    {
        XNextEvent( x_display, &xev );
        if ( xev.type == KeyPress )
        {
            if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
            {
                if (esContext->keyFunc != NULL)
                    esContext->keyFunc(esContext, text, 0, 0);
            }
        }
        if ( xev.type == DestroyNotify )
            userinterrupt = GL_TRUE;

        if ( xev.type == ConfigureNotify )
        {
            XConfigureEvent xce = xev.xconfigure;

            if (xce.width != esContext->width || xce.height != esContext->height)
            {
                // Optionally, call a user-defined resize callback
                if (esContext->windowResizeFunc)
                {
                    esContext->windowResizeFunc(esContext, xce.width, xce.height);
                }
            }
        }
    }
    return userinterrupt;
}

#else
#if defined(USE_FB)
EGLBoolean FBCreate(ESContext *esContext) {
    native_display = (EGLNativeDisplayType)fbGetDisplayByIndex(USE_FB);
    if (native_display == NULL) {
        return EGL_FALSE;
    }

    esContext->hWnd = (EGLNativeWindowType)fbCreateWindow(native_display, 0, 0, 0, 0);
    return EGL_TRUE;
}
#elif defined(USE_DRM)
EGLBoolean DRMCreate(ESContext *esContext) {
    drmModeConnector *connector;

    // Open the DRM device (Renesas typically uses /dev/dri/card0)
    esContext->drm_fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);
    if (esContext->drm_fd < 0)
    {
        fprintf(stderr, "Failed to open DRM device\n");
        return EGL_FALSE;
    }

    // Get DRM resources
    drmModeRes *resources = drmModeGetResources(esContext->drm_fd);
    if (!resources)
    {
        perror("Failed to get DRM resources");
        return EGL_FALSE;
    }

    // Find a connected connector
    for (int i = 0; i < resources->count_connectors; i++)
    {
        connector = drmModeGetConnector(esContext->drm_fd, resources->connectors[i]);
        if (connector && connector->connection == DRM_MODE_CONNECTED)
        {
            esContext->connector = connector;
            break;
        }
        drmModeFreeConnector(connector);
        connector = NULL;
    }

    if (!connector || connector->connection != DRM_MODE_CONNECTED)
    {
        fprintf(stderr, "No connected DRM connector found\n");
        return EGL_FALSE;
    }

    // Find a suitable connector mode
    for (int i = 0; i < connector->count_modes; i++)
    {
        drmModeModeInfo* mode = connector->modes + i;
        if (mode->hdisplay == esContext->width && mode->vdisplay == esContext->height) {
            esContext->mode_info = mode;
            break;
        }
    }

    // Use the first mode in the connector as the default
    if (esContext->mode_info == NULL) {
        esContext->mode_info = connector->modes;
    }

    // Find a suitable encoder for the connector
    esContext->encoder = drmModeGetEncoder(esContext->drm_fd, connector->encoder_id);

    // Find the CRTC
    // for (int i = 0; i < resources->count_crtcs; i++)
    // {
    //     if (resources->crtcs[i] & connector->encoders[0])
    //     {
    //         esContext->crtc = drmModeGetCrtc(esContext->drm_fd, resources->crtcs[i]);
    //         break;
    //     }
    // }
    esContext->crtc = drmModeGetCrtc(esContext->drm_fd, esContext->encoder->crtc_id);

    if (!esContext->crtc)
    {
        fprintf(stderr, "Failed to find a suitable CRTC\n");
        return EGL_FALSE;
    }

    drmModeFreeResources(resources);

    printf("DRM setup complete: mode %s, resolution %dx%d, connector_id %d\n",
           esContext->mode_info->name, esContext->mode_info->hdisplay, esContext->mode_info->vdisplay, connector->connector_id);

#ifdef USE_GBM
    // Create a GBM device
    esContext->gbm_dev = gbm_create_device(esContext->drm_fd);
    if (!esContext->gbm_dev)
    {
        fprintf(stderr, "Failed to create GBM device\n");
        return EGL_FALSE;
    }

    // Create a GBM surface
    esContext->gbm_surface = gbm_surface_create(esContext->gbm_dev,
                                     esContext->mode_info->hdisplay,
                                     esContext->mode_info->vdisplay,
                                     GBM_BO_FORMAT_XRGB8888,
                                     GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
    if (!esContext->gbm_surface)
    {
        fprintf(stderr, "Failed to create GBM surface\n");
        return EGL_FALSE;
    }

    // Pass the EGL surface as the native window handle
    esContext->hWnd = (EGLNativeWindowType)esContext->gbm_surface;

    printf("GBM setup complete\n");
#else
    esContext->hWnd = (EGLNativeWindowType)&(native_window);
#endif //USE_GBM

    return EGL_TRUE;
}

#endif // USE_FB
GLboolean userInterrupt(ESContext *esContext) {
    return GL_FALSE;
}
#endif // USE_X11

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

static pthread_t esThread;

static void* esThreadRoutine(void* arg) {
    ESContext* esContext = (ESContext*)arg;

#if defined(USE_DRM)
    drmVBlank vbl;
    long vblank_tval_sec;
    long vblank_tval_usec;
    unsigned long vblank_count = 0;
    long vblank_diff_ms = 0;
    int ret;

    while (1) {
        // Clear the drmVBlank structure
        memset(&vbl, 0, sizeof(vbl));

        // Configure the vbl request
        vbl.request.type = DRM_VBLANK_RELATIVE;  // Wait for a relative vblank
        vbl.request.sequence = 1;  // Wait for the next vblank

        // Wait for the VBlank event
        ret = drmWaitVBlank(esContext->drm_fd, &vbl);
        if (ret) {
            perror("drmWaitVBlank failed");
            break;
        }

        if (vblank_count) {
            vblank_diff_ms = (vbl.reply.tval_sec - vblank_tval_sec) * 1000 + (vbl.reply.tval_usec - vblank_tval_usec) / 1000.0;
            printf("VBlank event, vblank difference: %ld\n", vblank_diff_ms);
        }

        vblank_count++;
        vblank_tval_sec = vbl.reply.tval_sec;
        vblank_tval_usec = vbl.reply.tval_usec;
    }
#else
    (void)esContext;
#endif //USE_DRM

    return NULL;
}

///
//  esInitContext()
//
//      Initialize ES utility context.  This must be called before calling any other
//      functions.
//
void ESUTIL_API esInitContext ( ESContext *esContext )
{
    if ( esContext != NULL )
    {
        memset( esContext, 0, sizeof( ESContext) );
    }
}


///
//  esCreateWindow()
//
//      title - name for title bar of window
//      width - width of window to create
//      height - height of window to create
//      flags  - bitwise or of window creation flags
//          ES_WINDOW_ALPHA       - specifies that the framebuffer should have alpha
//          ES_WINDOW_DEPTH       - specifies that a depth buffer should be created
//          ES_WINDOW_STENCIL     - specifies that a stencil buffer should be created
//          ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
//
GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags )
{
#ifdef USE_X11
    EGLint attribList[] =
    {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };
#elif defined(USE_FB)
    EGLint attribList[] = {
        EGL_SAMPLES,        0,
        EGL_RED_SIZE,       8,
        EGL_GREEN_SIZE,     8,
        EGL_BLUE_SIZE,      8,
        EGL_ALPHA_SIZE,     EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     0,
        EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
        EGL_NONE
    };
#else
    EGLint attribList[] = {
        EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,  // Request OpenGL ES 2.0
        EGL_RED_SIZE,       8,
        EGL_GREEN_SIZE,     8,
        EGL_BLUE_SIZE,      8,
        EGL_ALPHA_SIZE,     8,                    // Set alpha size if needed
        EGL_DEPTH_SIZE,     8,                   // Enable depth buffer (16-bit)
        EGL_STENCIL_SIZE,   8,                    // Optional: Stencil buffer
        EGL_SAMPLES,        0,                    // Optional: Enable 4x MSAA
        EGL_NONE
    };
#endif //USE_X11

    if ( esContext == NULL )
    {
        printf("Invalid esContext\n");
        return GL_FALSE;
    }

    esContext->width = width;
    esContext->height = height;

#ifdef USE_X11
    if ( !WinCreate ( esContext, title) )
#elif defined(USE_FB)
    if (!FBCreate(esContext))
#elif defined(USE_DRM)
    if (!DRMCreate(esContext))
#endif //USE_X11
    {
        printf("Window creation failed\n");
        return GL_FALSE;
    }


    if ( !CreateEGLContext ( esContext, attribList) )
    {
        printf("CreateEGLContext failed\n");
        return GL_FALSE;
    }

    printf("esCreateWindow success\n");
    return GL_TRUE;
}


///
//  esMainLoop()
//
//    Start the main loop for the OpenGL ES application
//

void ESUTIL_API esMainLoop ( ESContext *esContext )
{
    struct timeval t1, t2;
    struct timezone tz;
    float deltatime;
    float totaltime = 0.0f;
    unsigned int frames = 0;

    gettimeofday ( &t1 , &tz );

    pthread_create(&esThread, NULL, esThreadRoutine, (void*)esContext);

    while(userInterrupt(esContext) == GL_FALSE)
    {
        gettimeofday(&t2, &tz);
        deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

        if (esContext->updateFunc != NULL)
            esContext->updateFunc(esContext, deltatime);
        if (esContext->drawFunc != NULL)
            esContext->drawFunc(esContext);

        eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

#if defined(USE_GBM)
        struct gbm_bo* bo = esContext->gbm_bo;
        uint32_t fb = esContext->gbm_fb;

        esContext->gbm_bo = gbm_surface_lock_front_buffer(esContext->gbm_surface);

        drmModeAddFB(
                esContext->drm_fd,
                esContext->mode_info->hdisplay,
                esContext->mode_info->vdisplay,
                24,
                32,
                gbm_bo_get_stride(esContext->gbm_bo),
                gbm_bo_get_handle(esContext->gbm_bo).u32,
                &esContext->gbm_fb
        );
        drmModeSetCrtc(
                esContext->drm_fd,
                esContext->crtc->crtc_id,
                esContext->gbm_fb,
                0,
                0,
                &esContext->connector->connector_id,
                1,
                esContext->mode_info
        );

        if (bo != NULL) {
            drmModeRmFB(esContext->drm_fd, fb);
            gbm_surface_release_buffer(esContext->gbm_surface, bo);
        }
#endif //USE_GBM

        totaltime += deltatime;
        frames++;
        if (totaltime >  2.0f)
        {
            printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
            totaltime -= 2.0f;
            frames = 0;
        }
    }
}


///
//  esRegisterDrawFunc()
//
void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void (ESCALLBACK *drawFunc) (ESContext* ) )
{
    esContext->drawFunc = drawFunc;
}


///
//  esRegisterUpdateFunc()
//
void ESUTIL_API esRegisterUpdateFunc ( ESContext *esContext, void (ESCALLBACK *updateFunc) ( ESContext*, float ) )
{
    esContext->updateFunc = updateFunc;
}


///
//  esRegisterKeyFunc()
//
void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext,
        void (ESCALLBACK *keyFunc) (ESContext*, unsigned char, int, int ) )
{
    esContext->keyFunc = keyFunc;
}

///
//  esRegisterWindowResizeFunc()
//
void ESUTIL_API esRegisterWindowResizeFunc(ESContext *esContext,
                                  void(ESCALLBACK *windowResizeFunc)(ESContext *, int, int))
{
    esContext->windowResizeFunc = windowResizeFunc;
}

///
// esLogMessage()
//
//    Log an error message to the debug output for the platform
//
void ESUTIL_API esLogMessage ( const char *formatStr, ... )
{
    va_list params;
    char buf[BUFSIZ];

    va_start ( params, formatStr );
    vsprintf ( buf, formatStr, params );

    printf ( "%s", buf );

    va_end ( params );
}


///
// esLoadTGA()
//
//    Loads a 24-bit TGA image from a file. This is probably the simplest TGA loader ever.
//    Does not support loading of compressed TGAs nor TGAa with alpha channel. But for the
//    sake of the examples, this is sufficient.
//

char* ESUTIL_API esLoadTGA ( char *fileName, int *width, int *height )
{
    char *buffer = NULL;
    FILE *f;
    unsigned char tgaheader[12];
    unsigned char attributes[6];
    unsigned int imagesize;

    f = fopen(fileName, "rb");
    if(f == NULL) return NULL;

    if(fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
    {
        fclose(f);
        return NULL;
    }

    if(fread(attributes, sizeof(attributes), 1, f) == 0)
    {
        fclose(f);
        return 0;
    }

    *width = attributes[1] * 256 + attributes[0];
    *height = attributes[3] * 256 + attributes[2];
    imagesize = attributes[4] / 8 * *width * *height;
    buffer = malloc(imagesize);
    if (buffer == NULL)
    {
        fclose(f);
        return 0;
    }

    if(fread(buffer, 1, imagesize, f) != imagesize)
    {
        free(buffer);
        return NULL;
    }
    fclose(f);
    return buffer;
}
