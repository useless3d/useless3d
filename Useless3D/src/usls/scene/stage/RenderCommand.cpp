

#include "usls/scene/stage/RenderCommand.h"

namespace usls
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

    void RenderCommand::removeActorIndex(int actorSlot)
    {
        this->actorIndexes.at(actorSlot) = -1;
        this->freeSlots.push_back(actorSlot);
    }

    int RenderCommand::getShaderIndex()
    {
        return this->shaderIndex;
    }

    int RenderCommand::getMeshIndex()
    {
        return this->meshIndex;
    }

    int RenderCommand::getTextureIndex()
    {
        return this->textureIndex;
    }
    
}