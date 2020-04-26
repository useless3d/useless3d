#version 450 core

const int MAX_BONES = 100;


layout (location = 0) in vec3	aPos;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec2	aTexCoord;
layout (location = 3) in ivec4	aBoneIds;
layout (location = 4) in vec4	aWeights;


out vec2 TexCoord;


uniform mat4 mvp;
uniform mat4 bones[MAX_BONES];


void main() 
{
	mat4 boneTransform	=	bones[aBoneIds[0]] * aWeights[0];
	boneTransform		+=	bones[aBoneIds[1]] * aWeights[1];
	boneTransform		+=	bones[aBoneIds[2]] * aWeights[2];
	boneTransform		+=	bones[aBoneIds[3]] * aWeights[3];

	gl_Position = mvp * boneTransform * vec4(aPos, 1.0);
	//gl_Position = boneTransform * vec4(aPos, 1.0);
	//gl_Position = mvp * vec4(aPos, 1.0);

    
	TexCoord = aTexCoord;
}