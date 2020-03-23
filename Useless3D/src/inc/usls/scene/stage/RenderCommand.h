#pragma once

#include <vector>

namespace usls
{
    class RenderCommand
    {
    private:
        std::vector<int>    actorIndexes;
        std::vector<int>    freeSlots;
        
        int                 shaderIndex;
        int                 meshIndex;
        int                 textureIndex;

    public:
                            RenderCommand(int sI, int mI, int tI = -1);

        int                 getShaderIndex();
        int                 getMeshIndex();
        int                 getTextureIndex();

        int                 addActorIndex(int actorIndex);
        void                removeActorIndex(int actorSlot);
    };
}