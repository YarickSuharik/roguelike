#pragma once
#include "position.hpp"
#include <memory>

namespace rl {

    class World;
    class Actor;

    class Camera {
    private:
        Position m_position;
        int m_width;
        int m_height;
        std::weak_ptr<World> m_worldContext;
        std::weak_ptr<Actor> m_trackedActor;

    public:
        Camera(Position startPos, int width, int height, const std::weak_ptr<World>& worldContext);
        ~Camera();

        void refresh();
        void setCameraLocation(Position newPos);
        void setTrackedActor(const std::weak_ptr<Actor>& actor);

        Position getCameraLocation() const;
        int getWidth() const;
        int getHeight() const;
        std::weak_ptr<World> getWorldContext() const;
        std::weak_ptr<Actor> getTrackedActor() const;
    };

}
