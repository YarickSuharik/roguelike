#pragma once
#include "position.hpp"
#include "cell_content.hpp"
#include <string>
#include <vector>

namespace rl {

    class Actor;
    class Camera;
    class PlayerCharacter;

    class World {
    private:
        std::vector<Actor*> m_actors;
        std::string** m_tileMap;
        int m_mapWidth;
        int m_mapHeight;
        Camera* m_cameraContext;

        PlayerCharacter* m_playerCharacter;

        void clearWorldData();
        Actor* getActorAt(Position pos) const;

    public:
        World();
        ~World();

        bool initializeMap(const std::string& mapFileName);
        void registerActor(Actor* actor);
        void unregisterActor(Actor* actor);

        void registerCamera(Camera* camera);
        void notifyCameraRefresh() const;

        CellContent getObjectOnPos(Position pos) const;
        bool canMoveTo(Actor* movingActor, Position targetPos);

        int getWidth() const;
        int getHeight() const;
        std::string getTileAt(Position pos) const;

        void setPlayerCharacter(PlayerCharacter* player);
        PlayerCharacter* getPlayerCharacter() const;
    };

}
