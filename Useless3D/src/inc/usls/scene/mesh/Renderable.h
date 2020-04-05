#pragma once

namespace usls::scene::mesh
{
	struct Renderable
	{
		unsigned int	VAO;
		unsigned int	VBO;
		unsigned int    EBO;
		unsigned int    indiceCount;
	};    
}