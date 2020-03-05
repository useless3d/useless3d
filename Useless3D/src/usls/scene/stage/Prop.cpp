#include "usls/scene/stage/Prop.h"

namespace usls
{
    Prop::Prop(std::string name, glm::vec3 translation, Rotation rotation, glm::vec3 scale, Mesh* mesh) :
        name(name),
        Transformable(translation, rotation, scale)
    {
        if (mesh != nullptr)
        {
            this->mesh = mesh;
        }
    }
    Prop::~Prop() {}

    void Prop::draw(Shader* appOrStageShader, Camera* camera)
    {
        if (this->mesh) 
        {
            this->mesh.value()->draw(appOrStageShader, camera, this->getMatrix());
        }
    }


}