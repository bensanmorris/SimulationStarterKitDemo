#include "guiscene.h"
#include "gamescene.h"

#include "firefly.h"
using namespace firefly;

#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "GLWindow.h"
#include "savedgames.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

extern SDL_Window* displayWindow;
extern SDL_GLContext displayContext;
extern void SetDrawMode(DrawMode);
extern void SetAction(Action);
extern SavedGames savedGames;
extern bool haveGame;
void SaveGame(const std::tstring& name);

static SDL_Event quit_ev;

GuiScene::GuiScene() : activeScreen_(Screen::MainScreen)
{
    quit_ev.type = SDL_QUIT;
}

GuiScene::~GuiScene()
{}

void GuiScene::Init()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    const char* glsl_version = "#version 330";
    ImGui_ImplSDL2_InitForOpenGL(displayWindow, displayContext);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void GuiScene::Destroy()
{
    ImGui_ImplSDL2_Shutdown();
}

void GuiScene::Activate()
{
}

void GuiScene::Deactivate()
{
}

void GuiScene::Update()
{
    SDK::GetInstance().GetRenderer().Clear(FIREFLY_COLOR_BUFFER_BIT | FIREFLY_DEPTH_BUFFER_BIT);
    SDK::GetInstance().GetRenderer().BindFrameBufferDefault(IRenderer::FrameBufferTarget::FrameBuffer);
    SDK::GetInstance().GetRenderer().ResetShaders();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(displayWindow);
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    ImGui::SetNextWindowPosCenter();
    bool dummy = false;
    ImGui::Begin("Menu", &dummy, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    
    switch(activeScreen_)
    {
        case MainScreen:
        {
            if(ImGui::Button("New Game"))
            {
                ImGui::End();
                ImGui::Render();
                SetAction(Action::NewGame);
                SetDrawMode(DrawMode::Game);
                break;
            }
            
            if(haveGame)
            {
                if(ImGui::Button("Resume Game"))
                {
                    ImGui::End();
                    ImGui::Render();
                    SetAction(Action::ResumeGame);
                    SetDrawMode(DrawMode::Game);
                    break;
                }
            }
            
            if(!savedGames.GetSaves().empty())
            {
                if(ImGui::Button("Load Game"))
                {
                    activeScreen_ = LoadScreen;
                    ImGui::End();
                    ImGui::Render();
                    break;
                }
            }
            
            if(haveGame)
            {
                if(ImGui::Button("Save Game"))
                {
                    activeScreen_ = SaveScreen;
                    ImGui::End();
                    ImGui::Render();
                    
                    break;
                }
            }
            
            if(ImGui::Button("Settings"))
            {
                activeScreen_ = SettingsScreen;
                ImGui::End();
                ImGui::Render();
                break;
            }
            
            if(ImGui::Button("Quit"))
            {
                ImGui::End();
                ImGui::Render();
                SDL_PushEvent(&quit_ev);
                break;
            }
            ImGui::End();
            ImGui::Render();
            break;
        }
        case SettingsScreen:
        {
            if(ImGui::Button("Main Menu"))
            {
                ImGui::End();
                ImGui::Render();
                activeScreen_ = MainScreen;
                break;
            }

            // sample settings
            ImGui::Checkbox("Show State Switches", &settings_.showStateSwitches);
            ImGui::Checkbox("Show Rendered Object Count", &settings_.showRenderedObjectCount);
            
            ImGui::End();
            ImGui::Render();
            break;
        }
            
        case LoadScreen:
        {
            if(ImGui::Button("Main Menu"))
            {
                ImGui::End();
                ImGui::Render();
                activeScreen_ = MainScreen;
                break;
            }
            
            std::tstring saves = savedGames.GetSavesNames();
            static int currentItem  = 0;
            ImGui::Combo("Saved Games", &currentItem, saves.c_str(), 3);
            if(ImGui::Button("Load"))
            {
                SetAction(Action::LoadGame);
                settings_.loadGame = savedGames.GetSaves()[currentItem];
                SetDrawMode(DrawMode::Game);
                activeScreen_ = MainScreen;
            }
            
            ImGui::End();
            ImGui::Render();
            break;
        }
            
        case SaveScreen:
        {
            if(ImGui::Button("Main Menu"))
            {
                ImGui::End();
                ImGui::Render();
                activeScreen_ = MainScreen;
                break;
            }
            
            static char buf[255] = "My Save Game";
            ImGui::InputText("Save As", buf, IM_ARRAYSIZE(buf));
            if(ImGui::Button("Save"))
            {
                SaveGame(buf);                
                ImGui::End();
                ImGui::Render();
                activeScreen_ = MainScreen;
                break;
            }
            
            ImGui::End();
            ImGui::Render();
            break;
        }
    };
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiScene::HandleEvent(SDL_Event& e)
{
    ImGui_ImplSDL2_ProcessEvent(&e);
}

void GuiScene::SetSettings(const Settings& settings)
{
    Scene::SetSettings(settings);
}

const Scene::Settings& GuiScene::GetSettings() const
{
    return Scene::GetSettings();
}
