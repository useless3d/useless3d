

#include "usls/scene/stage/RenderCommand.h"

namespace usls::scene::stage
{

    RenderCommand::RenderCommand(int sI, int mI, int tI) :
        shaderIndex(sI),
        meshIndex(mI),
        textureIndex(tI) {}

    int RenderCommand::addActorIndex(int actorIndex)
    {
        int slotIndex;

        if (this->freeSlots.size() > 0)
        {
            slotIndex = this->freeSlots.back();
            this->freeSlots.pop_back();
            this->actorIndexes.at(slotIndex) = actorIndex;
        }
        else
        {
            slotIndex = this->actorIndexes.size();
            this->actorIndexes.push_back(actorIndex);
        }

        return slotIndex;
    }

    void RenderCommand::freeActorIndex(int actorSlot)
    {
        //this->actorIndexes.at(actorSlot) = -1;
        this->freeSlots.push_back(actorSlot);
    }

    const int& RenderCommand::getShaderIndex() const
    {
        return this->shaderIndex;
    }

    const int& RenderCommand::getMeshIndex() const
    {
        return this->meshIndex;
    }

    const int& RenderCommand::getTextureIndex() const
    {
        return this->textureIndex;
    }
    
    const std::vector<int>& RenderCommand::getActorIndexes() const
    {
        return this->actorIndexes;
    }
}