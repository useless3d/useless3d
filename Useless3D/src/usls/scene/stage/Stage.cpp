#include <iostream>


#include "usls/scene/stage/Stage.h"




namespace usls
{

    Stage::Stage(bool visible) :
        visible(visible)
    {
        // Default actors container to 1000 slots. If more space
        // is required, call setActorContainerSize before adding
        // actors to the stage. If this is not done and actors
        // are added past the reserved limit, will result in
        // undefined behavior (as push_back will reallocate
        // all data to a new block every time push_back is called)
        this->actors.reserve(1000);
    }

    void Stage::setActorContainerSize(unsigned int size)
    {
        this->actors.reserve(size);
    }

    void Stage::hide()
    {
        this->visible = false;
    }

    void Stage::show()
    {
        this->visible = true;
    }

    void Stage::addPerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov)
    {
        this->camera = Camera(
            CameraType::PERSPECTIVE,
            fixed,
            nearPlane,
            farPlane,
            fov
        );
    }

    void Stage::addOrthographicCamera(bool fixed, float nearPlane, float farPlane, float scale)
    {
        this->camera = Camera(
            CameraType::ORTHOGRAPHIC,
            fixed,
            nearPlane,
            farPlane,
            scale
        );
    }

    void Stage::addActors(std::string filename)
    {

    }

    void Stage::addActor()

    bool Stage::hasActorWithName(std::string name)
    {
        for (auto& a : this->actors)
        {
            if (a.getName() == name)
            {
                return true;
            }
        }
        return false;
    }

}