#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

#include "usls/scene/Shader.h"


namespace usls
{

    Shader::Shader(std::string name, unsigned int id) :
        name(name),
        id(id)
    {}

    const unsigned int Shader::getId()
    {
        return this->id;
    }

    void Shader::use() 
    {
        glUseProgram(this->id);
    }

    void Shader::setBool(const std::string & name, bool value) const 
    {
        glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string & name, int value) const 
    {
        glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
    }

    void Shader::setMat4(const std::string & name, glm::mat4 value) const 
    {
        glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1,
            GL_FALSE, glm::value_ptr(value));
    }

}