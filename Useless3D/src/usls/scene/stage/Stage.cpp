#include <iostream>


#include "usls/scene/stage/Stage.h"
#include "usls/scene/stage/ActorLoader.h"




namespace usls
{

    Stage::Stage(bool headless) :
        headless(headless),
        visible(true)
    {
        // Default actors container to 1000 slots. If more space
        // is required, call setActorContainerSize before adding
        // actors to the stage. If this is not done and actors
        // are added past the reserved limit, will result in
        // undefined behavior (as push_back will reallocate
        // all data to a new block every time push_back is called)
        this->actors.reserve(1000);

        if (!this->headless)
        {
            this->renderCommands = std::vector<RenderCommand>();
            this->renderCommandsOrder = std::vector<int>();
        }

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

    void Stage::loadActors(std::string filename)
    {
        if (!this->headless)
        {
            this->loadActors(filename, 0); // default shader is always index 0
            return;
        }

        auto loader = ActorLoader(this, filename);
        loader.execute();
    }

    void Stage::loadActors(std::string filename, int shaderIndex)
    {
        auto loader = ActorLoader(this, filename);
        loader.findShaderId = [&](std::string actorName) {
            return shaderIndex;
        };
        loader.execute();
    }

    void Stage::loadActors(std::string filename,
        std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs)
    {
        auto loader = ActorLoader(this, filename);
        loader.findShaderId = [&](std::string actorName) {
            
            for (auto& a : actorShaderAssocs)
            {
                for (auto& p : a.second)
                {
                    if (actorName.find(p) != std::string::npos)
                    {
                        return a.first;
                    }
                }
            }

            return 0; // if no shader assoc found, use default shader

        };
        loader.execute();
    }

    const unsigned int Stage::getActorSize() const
    {
        return this->actors.size();
    }

    void Stage::addActor(Actor a)
    {
        int slotIndex;

        if (this->actorFreeSlots.size() > 0)
        {
            slotIndex = this->actorFreeSlots.back();
            this->actorFreeSlots.pop_back();
            this->actors.at(slotIndex) = a;
        }
        else
        {
            slotIndex = this->actors.size();
            this->actors.push_back(a);
        }

        auto actor = &this->actors.at(slotIndex);

        if (!this->headless && 
            actor->getShaderIndex().has_value() && 
            actor->getMeshIndex().has_value()) // If we are not in headless mode, AND this actor has a shader and mesh
        {
            int textureId = actor->getTextureIndex().has_value() ? actor->getTextureIndex().value() : -1;

            // Search the existing render commands to see if one exists for the given criteria
            int renderCommandIndex = this->renderCommandExists(actor->getShaderIndex().value(), actor->getMeshIndex().value(), textureId);

            // If a render command does not exist for the given criteria, create one and get it's index
            if (renderCommandIndex == -1)
            {
                auto rc = RenderCommand(actor->getShaderIndex().value(), actor->getMeshIndex().value(), textureId);
                renderCommandIndex = this->addRenderCommand(rc);
            }

            // Add this actor's slot index to the actorIndexes container of it's RenderCommand
            int indexOfActorInRenderCommand = this->renderCommands->at(renderCommandIndex).addActorIndex(slotIndex);

            // Now add the renderCommandIndex AND indexOfActorInRenderCommandActorIndexes to the actor's 
            // std::optional<std::pair<int, int>> renderCommand member, which is used to quickly remove the 
            // actor from the render command if it is ever removed from the stage
            actor->addRenderCommand(std::pair<int, int>(renderCommandIndex, indexOfActorInRenderCommand));

        }
    }

    Actor* Stage::getActor(std::string name)
    {
        for (auto& a : this->actors) 
        {
            if (a.getName() == name) 
            {
                return &a;
            }
        }
    }

    Actor* Stage::getActor(int index) {
        return &this->actors.at(index);
    }

    void Stage::removeActor(std::string name) 
    {
        for (unsigned int i = 0; i < this->actors.size(); i++)
        {
            auto a = this->actors.at(i);
            if (a.getName() == name)
            {
                this->removeActor(i);
            }
        }
    }

    void Stage::removeActor(int index)
    {
        auto a = this->actors.at(index);

        // remove actor from render command
        if (this->renderCommands)
        {
            this->renderCommands.value().at(a.getRenderCommand().first).removeActorIndex(a.getRenderCommand().second);
        }

        a.setDeleted(true);
        this->actorFreeSlots.push_back(index);
    }

    int Stage::addRenderCommand(RenderCommand rc) {

        this->renderCommands->push_back(rc);
        int renderCommandIndex = this->renderCommands->size() - 1;

        // loop through render commands and sort order saving indexes
        // within this->renderCommandsOrder

        std::vector<std::pair<int, int>> toSort;

        for (unsigned int i = 0; i < this->renderCommands->size(); i++) {

            std::string cmdString = std::to_string(this->renderCommands->at(i).getShaderIndex()) +
                std::to_string(this->renderCommands->at(i).getMeshIndex()) +
                std::to_string(this->renderCommands->at(i).getTextureIndex());

            toSort.push_back(std::pair<int, int>(i, std::stoi(cmdString)));

        }

        std::sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });

        this->renderCommandsOrder->clear();

        for (auto& p : toSort) {
            this->renderCommandsOrder->push_back(p.first);
        }

        return renderCommandIndex;

    }

    int Stage::renderCommandExists(int sI, int mI, int tI)
    {
        for (unsigned int i = 0; i < this->renderCommands->size(); i++)
        {
            if ((this->renderCommands.value()[i].getShaderIndex() == sI) &&
                (this->renderCommands.value()[i].getMeshIndex() == mI) &&
                (this->renderCommands.value()[i].getTextureIndex() == tI))
            {
                return i;
            }
        }
        return -1;
    }

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

    void Stage::printRenderCommands() 
    {

        //std::cout << this->renderCommands.value().size();

        std::cout << "RenderCommands\n";
        std::cout << "----------------------------------\n";
        for (auto& rc : this->renderCommands.value()) {
            std::cout << "shaderIndex:" << rc.getShaderIndex() << " meshIndex:" << rc.getMeshIndex() << " textureIndex:" << rc.getTextureIndex() << "\n";
            std::cout << "actors:";
            for (auto& a : rc.getActorIndexes()) {
                //std::cout << a << ",";
                if (a != -1) {
                    std::cout << this->actors.at(a).getName() << ",";
                }
            }
            std::cout << "\norder:";
            for (auto& o : this->renderCommandsOrder.value()) {
                std::cout << o << ",";
            }
            std::cout << "\n------------------------------\n";
        }

    }

    const std::optional<std::vector<RenderCommand>>& Stage::getRenderCommands() const
    {
        return this->renderCommands;
    }

}