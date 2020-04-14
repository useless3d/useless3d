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

namespace usls::scene::stage
{
    class Stage
    {
    private:
        const bool                                  headless;
        bool                                        visible; // defaults to true, used to determine if this stage should be drawn or not
        std::optional<Camera>                       camera; // not required in headless mode
        std::vector<Actor>                          actors;
        std::vector<size_t>                         actorFreeSlots;

        std::optional<std::vector<RenderCommand>>   renderCommands;
        std::optional<std::vector<size_t>>          renderCommandsOrder;

		std::optional<size_t>                       renderCommandExists(size_t sI, size_t mI, size_t tI);
        size_t                                      addRenderCommand(RenderCommand rc);

    public:
													Stage(bool headless);

		void										loadActor(std::string filename);
		void										loadActor(std::string filename, int shaderIndex);
		void										loadActor(std::string filename, std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs);
        void										loadActors(std::string filename);
        void										loadActors(std::string filename, int shaderIndex);
        void										loadActors(std::string filename, std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs);

        void										addActor(Actor a);
        void										removeActor(std::string name);
        void										removeActor(size_t index);
        Actor*										getActor(size_t index);
        Actor*										getActor(std::string name);
        const size_t								getActorSize() const;

        void										printRenderCommands() const;
        RenderCommand&								getRenderCommand(size_t index);
        const std::optional<std::vector<size_t>>&	getRenderCommandsOrder() const;

        std::optional<Camera>&						getCamera();

        const bool									hasActorWithName(std::string name) const;
        void										setActorContainerSize(unsigned int size);
        void										show();
        void										hide();
        void										addPerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov);
        void										addOrthographicCamera(bool fixed, float nearPlane, float farPlane, float scale);
        


    };
}