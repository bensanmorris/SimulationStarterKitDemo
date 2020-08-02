#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "GLWindow.h"

#include "firefly.h"
#include "SDLHelper.h"

#include "scene.h"

static const int SCREEN_WIDTH  = 640;
static const int SCREEN_HEIGHT = 480;

SDL_Window*			displayWindow = 0;
SDL_GLContext		displayContext;

#if FIREFLY_PLATFORM == PLATFORM_WIN32
extern int LoadScene(int argc, wchar_t* argv[]);
#else
extern int LoadScene(int argc, char* argv[]);
#endif
extern int DrawScene();
extern int DrawGui();
extern int DestroyScene();
extern DrawMode GetDrawMode();
extern void SetDrawMode(DrawMode);
class Scene;
extern Scene* gActiveScene;

void checkSDLError()
{
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        std::cout << "SDL Error:" << error << std::endl;
        SDL_ClearError();
    }
}

#if FIREFLY_PLATFORM == PLATFORM_WIN32
void Display_InitGL(int argc, wchar_t* argv[], firefly::IRenderer::GLADloadproc loadProc)
#else
void Display_InitGL(int argc, char* argv[], firefly::IRenderer::GLADloadproc loadProc)
#endif
{
    LoadScene(argc, argv);
}

void Display_DestroyGL()
{
    DestroyScene();
}

int Display_SetViewport(int width, int height)
{
    firefly::SDK::GetInstance().OnSize(width, height);
    return 1;
}

void Display_Render()
{
    DrawScene();
    SDL_GL_SwapWindow(displayWindow);
}

#if FIREFLY_PLATFORM == PLATFORM_WIN32
using namespace std;
string narrow(const wstring& str)
{
    ostringstream stm;
    const ctype<char>& ctfacet =
        use_facet< ctype<char> >(stm.getloc());

    for(size_t i = 0; i<str.size(); ++i)
        stm << ctfacet.narrow(str[i], 0);

    return stm.str();
}
int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
#else
int main(int argc, char* argv[])
#endif
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, FIREFLY_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, FIREFLY_GL_MINOR_VERSION);
    if(FIREFLY_GL_MAJOR_VERSION >= 3 && FIREFLY_GL_MINOR_VERSION >= 3)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    displayWindow  = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if(!displayWindow)
        return 1;
    displayContext = SDL_GL_CreateContext(displayWindow);
    if(!displayContext)
    {
        checkSDLError();
        return 2;
    }
    SDL_GL_MakeCurrent(displayWindow, displayContext);
    SDL_GL_SetSwapInterval(0);

    Display_InitGL(argc, argv, (firefly::IRenderer::GLADloadproc)SDL_GL_GetProcAddress);
    Display_SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            gActiveScene->HandleEvent(e);

            switch(e.type)
            {
            case SDL_KEYDOWN:
            {
                SDL_Keycode keyPressed = e.key.keysym.sym;
                switch(keyPressed)
                {
                case SDLK_F5:
                {
                    LoadScene(argc, argv);
                    break;
                }
                case SDLK_ESCAPE:
                {
                    switch(GetDrawMode())
                    {
                        case DrawMode::Game:
                        {
                            SetDrawMode(DrawMode::Gui);
                            break;
                        }
                        case DrawMode::Gui:
                        {
                            break;
                        }
                    }
                    break;
                }
                }
                firefly::SDK::GetInstance().OnKeyDown(SDLHelper::TranslateKey(e.key.keysym.sym));
                break;
            }

            case SDL_KEYUP:
            {
                firefly::SDK::GetInstance().OnKeyUp(SDLHelper::TranslateKey(e.key.keysym.sym));
                break;
            }

            case SDL_MOUSEMOTION:
            {
                firefly::SDK::GetInstance().OnMouseMove(e.button.button == SDL_BUTTON_LEFT ? firefly::Mouse::LEFT : firefly::Mouse::RIGHT, e.motion.x, e.motion.y);
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                firefly::SDK::GetInstance().OnMouseButtonDown(e.button.button == SDL_BUTTON_LEFT ? firefly::Mouse::LEFT : firefly::Mouse::RIGHT);
                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                firefly::SDK::GetInstance().OnMouseButtonUp(e.button.button == SDL_BUTTON_LEFT ? firefly::Mouse::LEFT : firefly::Mouse::RIGHT);
                break;
            }

            case SDL_WINDOWEVENT:
            {
                switch(e.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    Display_SetViewport(e.window.data1, e.window.data2);
                    break;
                }
                }
                break;
            }

            case SDL_QUIT:
            {
                quit = true;
                break;
            }

            }
        }        
        Display_Render();
    }

    Display_DestroyGL();
    SDL_GL_DeleteContext(displayContext);
    SDL_DestroyWindow(displayWindow);

    return 0;
}
