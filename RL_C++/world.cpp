#include "world.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>

namespace rl {

    World::World()
        : m_tileMap(nullptr), m_mapWidth(0), m_mapHeight(0), m_cameraContext(nullptr) {}

    World::~World() {
        clearWorldData();
    }

    void World::clearWorldData() {
        if (m_tileMap != nullptr) {
            for (int i = 0; i < m_mapHeight; ++i) {
                delete[] m_tileMap[i];
            }
            delete[] m_tileMap;
            m_tileMap = nullptr;
        }
        m_actors.clear();
        m_mapWidth = 0;
        m_mapHeight = 0;
        m_cameraContext = nullptr;
    }

    void World::registerCamera(Camera* camera) {
        m_cameraContext = camera;
    }

    void World::notifyCameraRefresh() const {
        if (m_cameraContext != nullptr) {
            m_cameraContext->refreshCamera();
            Sleep(300);
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

        m_tileMap = new std::string * [m_mapHeight];
        for (int i = 0; i < m_mapHeight; ++i) {
            m_tileMap[i] = new std::string[m_mapWidth];
            auto& currentLine = parsedLines[i];
            for (int j = 0; j < m_mapWidth; ++j) {
                if (j < static_cast<int>(currentLine.size())) {
                    m_tileMap[i][j] = currentLine[j];
                }
                else {
                    m_tileMap[i][j] = " ";
                }
            }
        }

        return true;
    }

    CellContent World::getObjectOnPos(Position pos) const {
        if (pos.x < 0 || pos.x >= m_mapWidth || pos.y < 0 || pos.y >= m_mapHeight) {
            return CellContent(true, nullptr);
        }

        if (m_tileMap == nullptr) {
            return CellContent(true, nullptr);
        }

        std::string tile = m_tileMap[pos.y][pos.x];
        if (tile != " ") {
            return CellContent(true, nullptr);
        }

        Actor* foundActor = getActorAt(pos);
        return CellContent(false, foundActor);
    }

    bool World::canMoveTo(Actor* movingActor, Position targetPos) {
        CellContent content = getObjectOnPos(targetPos);

        if (content.isWall) {
            return false;
        }

        if (content.actorPtr != nullptr && content.actorPtr != movingActor) {
            bool isBlocked = content.actorPtr->onCollisionEvent();
            if (isBlocked) {
                return false;
            }
        }

        return true;
    }

    void World::registerActor(Actor* actor) {
        if (actor == nullptr) return;
        m_actors.push_back(actor);
    }

    void World::unregisterActor(Actor* actor) {
        if (actor == nullptr) return;
        auto it = std::find(m_actors.begin(), m_actors.end(), actor);
        if (it != m_actors.end()) {
            m_actors.erase(it);
        }
    }

    Actor* World::getActorAt(Position pos) const {
        for (Actor* actor : m_actors) {
            if (actor != nullptr) {
                Position actorPos = actor->getActorLocation();
                if (actorPos.x == pos.x && actorPos.y == pos.y) {
                    return actor;
                }
            }
        }
        return nullptr;
    }

    std::string World::getTileAt(Position pos) const {
        if (pos.x < 0 || pos.x >= m_mapWidth || pos.y < 0 || pos.y >= m_mapHeight || m_tileMap == nullptr) {
            return " ";
        }
        return m_tileMap[pos.y][pos.x];
    }

    int World::getWidth() const { return m_mapWidth; }
    int World::getHeight() const { return m_mapHeight; }

}
