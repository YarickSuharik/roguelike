#include "camera.hpp"
#include "world.hpp"
#include "actor.hpp"
#include "cell_content.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

namespace rl {

    Camera::Camera(Position startPos, int width, int height, const std::weak_ptr<World>& worldContext)
        : m_position(startPos), m_width(width), m_height(height), m_worldContext(worldContext) {}

    Camera::~Camera() {}

    void Camera::refresh() {
        auto world = m_worldContext.lock();

        if (!world) {
            return;
        }

        int startX = m_position.x;
        int startY = m_position.y;

        if (auto tracked = m_trackedActor.lock()) {
            Position targetPos = tracked->getActorLocation();
            startX = targetPos.x - (m_width / 2);
            startY = targetPos.y - (m_height / 2);
        }

        std::vector<std::vector<std::string>> screenBuffer(m_height, std::vector<std::string>(m_width, " "));

        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                Position worldPos(startX + x, startY + y);

                CellContent content = world->getObjectOnPos(worldPos);

                if (auto actor = content.actorPtr.lock()) {
                    screenBuffer[y][x] = actor->getSymbol();
                }
                else {
                    screenBuffer[y][x] = world->getTileAt(worldPos);
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

    void Camera::setTrackedActor(const std::weak_ptr<Actor>& actor) {
        m_trackedActor = actor;
    }

    Position Camera::getCameraLocation() const { return m_position; }
    int Camera::getWidth() const { return m_width; }
    int Camera::getHeight() const { return m_height; }
    std::weak_ptr<World> Camera::getWorldContext() const { return m_worldContext; }
    std::weak_ptr<Actor> Camera::getTrackedActor() const { return m_trackedActor; }

}
