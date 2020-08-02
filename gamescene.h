#pragma once

#include "firefly.h"
#include "scene.h"

namespace firefly
{
    class Light;
    class OctreeSceneItem;
    class SceneItem;
    class TerrainCamera;
    class Archive;
};
using namespace firefly;

struct Tiles;

enum Action
{
    NewGame,
    ResumeGame,
    LoadGame
};

class GameScene : public Scene
{
public:
    GameScene();
    virtual ~GameScene();
    
    virtual void Activate();
    virtual void Deactivate();
    virtual void Init();
    virtual void Update();
    virtual void Destroy();
    virtual void HandleEvent(SDL_Event&);
    virtual void SetSettings(const Settings&);
    virtual const Settings& GetSettings() const;
    
    void SetAction(Action a);
    void LoadGame(const SavedGames::SavedGame&);
    void Init(const Vector3& cameraPos, const Vector3& cameraLookAt);
    void Serialize(Archive& ar);
    
private:
    
    SceneItem*       scene_;
    Action           action_;
    bool             needsRestart_;
};
