#pragma once

namespace usls::scene::mesh
{
	typedef int GLsizei;
	struct Renderable
	{
		unsigned int	VAO;
		unsigned int	VBO;
		unsigned int    EBO;
		GLsizei			indiceCount;
	};    
}