#pragma once


namespace usls::scene::mesh
{
	struct VertexBoneData
	{
		unsigned int	ids[4] = {0,0,0,0}; // 4 bones allowed per vertex
		float			weights[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	};
}