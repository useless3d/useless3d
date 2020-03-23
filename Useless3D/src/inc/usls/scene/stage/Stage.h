#pragma once

#include <vector>
#include <string>
#include <optional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/stage/Actor.h"
#include "usls/scene/stage/Camera.h"
#include "usls/scene/stage/RenderCommand.h"

namespace usls
{
    class Stage
    {
    private:
        bool                                        headless;
        bool                                        visible; // defaults to true, used to determine if this stage should be drawn or not
        std::optional<Camera>                       camera; // not required in headless mode
        std::vector<Actor>                          actors;
        std::vector<int>                            actorFreeSlots;

        std::optional<std::vector<RenderCommand>>   renderCommands;
        std::optional<std::vector<int>>             renderCommandsOrder;

        int                                         renderCommandExists(int sI, int mI, int tI);
        int                                         addRenderCommand(RenderCommand rc);

    public:
                            Stage(bool headless);

        void                loadActors(std::string filename);
        void                loadActors(std::string filename, int shaderIndex);
        void                loadActors(std::string filename, std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs);

        void                addActor(Actor a);
        void                removeActor(std::string name);
        void                removeActor(int index);

        bool                hasActorWithName(std::string name);
        void                setActorContainerSize(unsigned int size);
        void                show();
        void                hide();
        void                addPerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov);
        void                addOrthographicCamera(bool fixed, float nearPlane, float farPlane, float scale);

    };
}