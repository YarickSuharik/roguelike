#pragma once
#include "position.hpp"
#include "cell_content.hpp"
#include <memory>
#include <string>
#include <vector>

namespace rl {

    class Actor;
    class Camera;
    class PlayerCharacter;

    // даёт weak_from_this(): актёры получают слабую ссылку на мир, не становясь его владельцами
    class World : public std::enable_shared_from_this<World> {
    private:
        std::vector<std::shared_ptr<Actor>> m_actors;
        std::unique_ptr<std::string[]> m_tileMap;
        int m_mapWidth;
        int m_mapHeight;
        std::weak_ptr<Camera> m_cameraContext;
        std::weak_ptr<PlayerCharacter> m_playerCharacter;

        void clearWorldData();
        std::shared_ptr<Actor> getActorAt(Position pos) const;

    public:
        World();
        ~World();

        bool initializeMap(const std::string& mapFileName);

        template <typename T>
        std::weak_ptr<T> spawnActor(const std::string& name, Position startPos, const std::string& symbol) {
            auto actor = std::make_shared<T>(name, startPos, weak_from_this(), symbol);
            m_actors.push_back(actor);
            actor->onSpawned();
            return actor;
        }

        bool destroyActor(Actor* actor);

        void registerCamera(const std::weak_ptr<Camera>& camera);
        void notifyCameraRefresh() const;

        CellContent getObjectOnPos(Position pos) const;
        bool canMoveTo(Actor* movingActor, Position targetPos);

        int getWidth() const;
        int getHeight() const;
        std::string getTileAt(Position pos) const;

        void setPlayerCharacter(const std::weak_ptr<PlayerCharacter>& player);
        std::weak_ptr<PlayerCharacter> getPlayerCharacter() const;
    };

}
