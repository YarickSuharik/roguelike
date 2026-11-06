#include "world.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include "player_character.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace rl {

    World::World()
        : m_mapWidth(0), m_mapHeight(0) {}

    World::~World() {
        clearWorldData();
    }

    void World::clearWorldData() {
        m_tileMap.reset();
        m_actors.clear();
        m_mapWidth = 0;
        m_mapHeight = 0;
        m_cameraContext.reset();
        m_playerCharacter.reset();
    }

    void World::registerCamera(const std::weak_ptr<Camera>& camera) {
        m_cameraContext = camera;
    }

    void World::notifyCameraRefresh() const {
        if (auto camera = m_cameraContext.lock()) {
            camera->refresh();
        }
    }

    bool World::initializeMap(const std::string& mapFileName) {
        std::string fullPath = "../RL_data/Maps/" + mapFileName;
        std::ifstream file(fullPath);

        if (!file.is_open()) {
            std::cout << "[World Error] Failed to open map file: " << fullPath << "\n";
            clearWorldData();
            return false;
        }

        std::vector<std::vector<std::string>> parsedLines;
        std::string line;
        int maxWidth = 0;

        while (std::getline(file, line)) {
            std::vector<std::string> currentParsedLine;
            for (size_t i = 0; i < line.length();) {
                std::string symbol = "";
                unsigned char c = line[i];
                if (c < 0x80) {
                    symbol += line[i];
                    i += 1;
                }
                else if ((c & 0xE0) == 0xC0) {
                    symbol += line.substr(i, 2);
                    i += 2;
                }
                else if ((c & 0xF0) == 0xE0) {
                    symbol += line.substr(i, 3);
                    i += 3;
                }
                else if ((c & 0xF8) == 0xF0) {
                    symbol += line.substr(i, 4);
                    i += 4;
                }
                else {
                    symbol += line[i];
                    i += 1;
                }
                currentParsedLine.push_back(symbol);
            }
            parsedLines.push_back(currentParsedLine);
            if (static_cast<int>(currentParsedLine.size()) > maxWidth) {
                maxWidth = static_cast<int>(currentParsedLine.size());
            }
        }
        file.close();

        if (parsedLines.empty()) {
            clearWorldData();
            return false;
        }

        m_mapHeight = static_cast<int>(parsedLines.size());
        m_mapWidth = maxWidth;
        m_tileMap = std::make_unique<std::string[]>(m_mapWidth * m_mapHeight);

        for (int y = 0; y < m_mapHeight; ++y) {
            const auto& currentLine = parsedLines[y];
            for (int x = 0; x < m_mapWidth; ++x) {
                if (x < static_cast<int>(currentLine.size())) {
                    m_tileMap[y * m_mapWidth + x] = currentLine[x];
                }
                else {
                    m_tileMap[y * m_mapWidth + x] = " ";
                }
            }
        }

        return true;
    }

    CellContent World::getObjectOnPos(Position pos) const {
        if (pos.x < 0 || pos.x >= m_mapWidth || pos.y < 0 || pos.y >= m_mapHeight) {
            return CellContent(true, {});
        }

        if (!m_tileMap) {
            return CellContent(true, {});
        }

        if (m_tileMap[pos.y * m_mapWidth + pos.x] != " ") {
            return CellContent(true, {});
        }

        return CellContent(false, getActorAt(pos));
    }

    bool World::canMoveTo(Actor* movingActor, Position targetPos) {
        CellContent content = getObjectOnPos(targetPos);

        if (content.isWall) {
            return false;
        }

        if (auto occupant = content.actorPtr.lock()) {
            if (occupant.get() != movingActor && occupant->onCollisionEvent()) {
                return false;
            }
        }

        return true;
    }

    bool World::destroyActor(Actor* actor) {
        if (actor == nullptr) {
            return false;
        }

        auto it = std::find_if(m_actors.begin(), m_actors.end(),
            [actor](const std::shared_ptr<Actor>& entry) { return entry.get() == actor; });

        if (it == m_actors.end()) {
            return false;
        }

        m_actors.erase(it);
        return true;
    }

    std::shared_ptr<Actor> World::getActorAt(Position pos) const {
        for (const auto& actor : m_actors) {
            Position actorPos = actor->getActorLocation();
            if (actorPos.x == pos.x && actorPos.y == pos.y) {
                return actor;
            }
        }
        return nullptr;
    }

    std::string World::getTileAt(Position pos) const {
        if (pos.x < 0 || pos.x >= m_mapWidth || pos.y < 0 || pos.y >= m_mapHeight || !m_tileMap) {
            return " ";
        }
        return m_tileMap[pos.y * m_mapWidth + pos.x];
    }

    int World::getWidth() const { return m_mapWidth; }
    int World::getHeight() const { return m_mapHeight; }

    void World::setPlayerCharacter(const std::weak_ptr<PlayerCharacter>& player) {
        m_playerCharacter = player;
    }

    std::weak_ptr<PlayerCharacter> World::getPlayerCharacter() const {
        return m_playerCharacter;
    }

}
