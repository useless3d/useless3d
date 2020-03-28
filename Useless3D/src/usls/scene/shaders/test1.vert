#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 mvp;


void main() {
	
	// mvp is pre-calculated on cpu as: projection * view * model
	gl_Position = mvp * vec4(aPos, 1.0);

}