#pragma once
#include "position.hpp"

namespace rl {

    class World;
    class Actor;

    class Camera {
    private:
        Position m_position;
        int m_width;
        int m_height;
        World* m_worldContext;
        Actor* m_trackedActor;

    public:
        Camera(Position startPos, int width, int height, World* worldContext);
        ~Camera();

        void refresh();
        void setCameraLocation(Position newPos);
        void setTrackedActor(Actor* actor);

        Position getCameraLocation() const;
        int getWidth() const;
        int getHeight() const;
        World* getWorldContext() const;
        Actor* getTrackedActor() const;
    };

}
