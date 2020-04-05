#pragma once

#include <vector>

namespace usls::scene::stage
{
    class RenderCommand
    {
    private:
        std::vector<int>			actorIndexes;
        std::vector<int>			freeSlots;
        
        int							shaderIndex;
        int							meshIndex;
        int							textureIndex;

    public:
									RenderCommand(int sI, int mI, int tI = -1);

        const int&					getShaderIndex() const;
        const int&					getMeshIndex() const;
        const int&					getTextureIndex() const;

        const std::vector<int>&		getActorIndexes() const;

        int							addActorIndex(int actorIndex);
        void						freeActorIndex(int actorSlot);
    };
}