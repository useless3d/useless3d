#pragma once

namespace usls::scene::mesh
{
	struct VertexBoneData
	{
		unsigned int	ids[4]; // 4 bones allowed per vertex
		float			weights[4];
	};
}