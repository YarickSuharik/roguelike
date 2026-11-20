#include "camera.hpp"
#include "world.hpp"
#include "actor.hpp"
#include "cell_content.hpp"
#include <iostream>
#include <vector>

namespace rl {

    Camera::Camera(Position startPos, int width, int height, World* worldContext)
        : m_position(startPos), m_width(width), m_height(height), m_worldContext(worldContext), m_trackedActor(nullptr) {}

    Camera::~Camera() {}

    void Camera::refresh() {
        if (m_worldContext == nullptr) {
            return;
        }

        int startX = m_position.x;
        int startY = m_position.y;

        if (m_trackedActor != nullptr) {
            Position targetPos = m_trackedActor->getActorLocation();
            startX = targetPos.x - (m_width / 2);
            startY = targetPos.y - (m_height / 2);
        }

        std::vector<std::vector<std::string>> screenBuffer(m_height, std::vector<std::string>(m_width, " "));

        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                int worldX = startX + x;
                int worldY = startY + y;
                Position worldPos(worldX, worldY);

                CellContent content = m_worldContext->getObjectOnPos(worldPos);

                if (content.isWall) {
                    screenBuffer[y][x] = m_worldContext->getTileAt(worldPos);
                }
                else if (content.actorPtr != nullptr) {
                    screenBuffer[y][x] = content.actorPtr->getSymbol();
                }
                else {
                    screenBuffer[y][x] = m_worldContext->getTileAt(worldPos);
                }
            }
        }

        system("cls");
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                std::cout << screenBuffer[y][x];
            }
            std::cout << "\n";
        }
    }

    void Camera::setCameraLocation(Position newPos) {
        m_position = newPos;
    }

    void Camera::setTrackedActor(Actor* actor) {
        m_trackedActor = actor;
    }

    Position Camera::getCameraLocation() const { return m_position; }
    int Camera::getWidth() const { return m_width; }
    int Camera::getHeight() const { return m_height; }
    World* Camera::getWorldContext() const { return m_worldContext; }
    Actor* Camera::getTrackedActor() const { return m_trackedActor; }

}
