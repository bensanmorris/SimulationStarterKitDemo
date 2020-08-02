#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "SDLHelper.h"

firefly::Keyboard::Key SDLHelper::TranslateKey(int key)
{
    switch(key)
    {
    case SDLK_a:
        return firefly::Keyboard::A;
        break;
    case SDLK_b:
        return firefly::Keyboard::B;
        break;
    case SDLK_c:
        return firefly::Keyboard::C;
        break;
    case SDLK_d:
        return firefly::Keyboard::D;
        break;
    case SDLK_e:
        return firefly::Keyboard::E;
        break;
    case SDLK_f:
        return firefly::Keyboard::F;
        break;
    case SDLK_g:
        return firefly::Keyboard::G;
        break;
    case SDLK_h:
        return firefly::Keyboard::H;
        break;
    case SDLK_i:
        return firefly::Keyboard::I;
        break;
    case SDLK_j:
        return firefly::Keyboard::J;
        break;
    case SDLK_k:
        return firefly::Keyboard::K;
        break;
    case SDLK_l:
        return firefly::Keyboard::L;
        break;
    case SDLK_m:
        return firefly::Keyboard::M;
        break;
    case SDLK_n:
        return firefly::Keyboard::N;
        break;
    case SDLK_o:
        return firefly::Keyboard::O;
        break;
    case SDLK_p:
        return firefly::Keyboard::P;
        break;
    case SDLK_q:
        return firefly::Keyboard::Q;
        break;
    case SDLK_r:
        return firefly::Keyboard::R;
        break;
    case SDLK_s:
        return firefly::Keyboard::S;
        break;
    case SDLK_t:
        return firefly::Keyboard::T;
        break;
    case SDLK_u:
        return firefly::Keyboard::U;
        break;
    case SDLK_v:
        return firefly::Keyboard::V;
        break;
    case SDLK_w:
        return firefly::Keyboard::W;
        break;
    case SDLK_x:
        return firefly::Keyboard::X;
        break;
    case SDLK_y:
        return firefly::Keyboard::Y;
        break;
    case SDLK_z:
        return firefly::Keyboard::Z;
        break;
    case SDLK_UP:
        return firefly::Keyboard::UP;
        break;
    case SDLK_DOWN:
        return firefly::Keyboard::DOWN;
        break;
    case SDLK_LEFT:
        return firefly::Keyboard::LEFT;
        break;
    case SDLK_RIGHT:
        return firefly::Keyboard::RIGHT;
        break;
    case SDLK_LSHIFT:
        return firefly::Keyboard::SHIFT;
        break;
    case SDLK_LCTRL:
        return firefly::Keyboard::CONTROL;
        break;
    case SDLK_DELETE:
        return firefly::Keyboard::DELETE_KEY;
        break;
    case SDLK_ESCAPE:
        return firefly::Keyboard::ESCAPE;
        break;
    case SDLK_SPACE:
        return firefly::Keyboard::SPACE;
        break;
    default:
        return firefly::Keyboard::UNDEFINED;
        break;
    }
}
