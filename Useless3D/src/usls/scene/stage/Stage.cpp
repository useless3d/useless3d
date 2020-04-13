#include <iostream>


#include "usls/App.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/AssetLoader.h"




namespace usls::scene::stage
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
            this->renderCommandsOrder = std::vector<size_t>();
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

	void Stage::loadArmature(std::string filename)
	{
		auto loader = AssetLoader(this, filename);
		loader.loadArmature();
	}

	void Stage::loadActor(std::string filename)
	{
		this->loadActors(filename);
	}

	void Stage::loadActor(std::string filename, int shaderIndex)
	{
		this->loadActors(filename, shaderIndex);
	}

	void Stage::loadActor(std::string filename,
		std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs)
	{
		this->loadActors(filename, actorShaderAssocs);
	}

    void Stage::loadActors(std::string filename)
    {
        if (!this->headless)
        {
            this->loadActors(filename, 0); // default shader is always index 0
            return;
        }

        auto loader = AssetLoader(this, filename);
        loader.loadActors();
    }

    void Stage::loadActors(std::string filename, int shaderIndex)
    {
        auto loader = AssetLoader(this, filename);
        loader.findShaderId = [&](std::string actorName) {
            return shaderIndex;
        };
        loader.loadActors();
    }

    void Stage::loadActors(std::string filename,
        std::vector<std::pair<int, std::vector<std::string>>> actorShaderAssocs)
    {
        auto loader = AssetLoader(this, filename);
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
        loader.loadActors();
    }

    const size_t Stage::getActorSize() const
    {
        return this->actors.size();
    }

    void Stage::addActor(Actor a)
    {
        size_t slotIndex;

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
            actor->getMeshIndex().has_value() &&
			actor->getTextureIndex().has_value()) // If we are not in headless mode, AND this actor has a shader, mesh, and texture
        {
            size_t shaderIndex = actor->getShaderIndex().value();
			size_t meshRenderableIndex = App::get().getScene()->getMesh(actor->getMeshIndex().value()).getMeshRenderableIndex().value();
			size_t textureIndex = actor->getTextureIndex().value();

            // Search the existing render commands to see if one exists for the given criteria
            std::optional<size_t> renderCommandIndex = this->renderCommandExists(shaderIndex, meshRenderableIndex, textureIndex);

            // If a render command does not exist for the given criteria, create one and get it's index
            if (!renderCommandIndex)
            {
                auto rc = RenderCommand(shaderIndex, meshRenderableIndex, textureIndex);
                renderCommandIndex = this->addRenderCommand(rc);
            }

            // Add this actor's slot index to the actorIndexes container of it's RenderCommand
			size_t indexOfActorInRenderCommand = this->renderCommands->at(renderCommandIndex.value()).addActorIndex(slotIndex);

            // Now add the renderCommandIndex AND indexOfActorInRenderCommandActorIndexes to the actor's 
            // std::optional<std::pair<int, int>> renderCommand member, which is used to quickly remove the 
            // actor from the render command if it is ever removed from the stage
            actor->addRenderCommand(std::pair<size_t, size_t>(renderCommandIndex.value(), indexOfActorInRenderCommand));

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
		return nullptr;
    }

    Actor* Stage::getActor(size_t index) 
    {
		if (this->actors.size() == 0 || !(index <= (this->actors.size() - 1)))
		{
			return nullptr;
		}
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

    void Stage::removeActor(size_t index)
    {
        Actor& a = this->actors.at(index);

        // free actor slot in render command
        if (this->renderCommands)
        {
            this->renderCommands.value().at(a.getRenderCommand().first).freeActorIndex(a.getRenderCommand().second);
        }

        a.setDeleted(true);
        this->actorFreeSlots.push_back(index);
    }

    size_t Stage::addRenderCommand(RenderCommand rc) 
    {
        this->renderCommands->push_back(rc);
        size_t renderCommandIndex = this->renderCommands->size() - 1;

        // loop through render commands and sort order saving indexes
        // within this->renderCommandsOrder

        std::vector<std::pair<size_t, size_t>> toSort;

        for (size_t i = 0; i < this->renderCommands->size(); i++) 
        {
            std::string cmdString = std::to_string(this->renderCommands->at(i).getShaderIndex()) +
                std::to_string(this->renderCommands->at(i).getMeshIndex()) +
                std::to_string(this->renderCommands->at(i).getTextureIndex());

            toSort.push_back(std::pair<size_t, size_t>(i, std::stoi(cmdString)));
        }

        std::sort(toSort.begin(), toSort.end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });

        this->renderCommandsOrder->clear();

        for (auto& p : toSort) 
        {
            this->renderCommandsOrder->push_back(p.first);
        }

        return renderCommandIndex;

    }

    std::optional<size_t> Stage::renderCommandExists(size_t sI, size_t mI, size_t tI)
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
        return std::nullopt;
    }

    const bool Stage::hasActorWithName(std::string name) const
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

    void Stage::printRenderCommands() const
    {

        //std::cout << this->renderCommands.value().size();

        std::cout << "RenderCommands\n";
        std::cout << "----------------------------------\n";
        for (auto& rc : this->renderCommands.value()) 
        {
            std::cout << "shaderIndex:" << rc.getShaderIndex() << " meshIndex:" << rc.getMeshIndex() << " textureIndex:" << rc.getTextureIndex() << "\n";
            std::cout << "actors:";
            for (auto& a : rc.getActorIndexes()) 
            {
                //std::cout << a << ",";
                if (a != -1) 
                {
                    std::cout << this->actors.at(a).getName() << ",";
                }
            }
            std::cout << "\norder:";
            for (auto& o : this->renderCommandsOrder.value()) 
            {
                std::cout << o << ",";
            }
            std::cout << "\n------------------------------\n";
        }

    }

    RenderCommand& Stage::getRenderCommand(size_t index)
    {
        return this->renderCommands->at(index);
    }

    const std::optional<std::vector<size_t>>& Stage::getRenderCommandsOrder() const
    {
        return this->renderCommandsOrder;
    }

    std::optional<Camera>& Stage::getCamera()
    {
        return this->camera;
    }

}