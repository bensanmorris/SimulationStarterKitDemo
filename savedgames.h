#pragma once

#include <vector>
#include "TString.h"
#include "firefly.h"
using namespace firefly;

class GameScene;

class SavedGames
{
public:
    struct SavedGame
    {
        SavedGame(const std::tstring& n, const Vector3& p, const Vector3& l) : name(n), pos(p), lookAt(l)
        {}
        SavedGame()
        {}
        void Serialize(Archive&);
        std::tstring name;
        Vector3 pos;
        Vector3 lookAt;
    };
    typedef std::vector<SavedGame> Saves;
    
    SavedGames();
    
    void Add(const SavedGame&);
    void Remove(const SavedGame&);
    
    void Load();
    void Save();
    
    const Saves& GetSaves() const { return saves_; }
    const std::tstring GetSavesNames() const;
    
private:
    Saves saves_;
};
