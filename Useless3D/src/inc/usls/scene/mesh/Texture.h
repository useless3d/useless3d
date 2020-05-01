#pragma once

#include <string>


namespace usls::scene::mesh
{
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};
}