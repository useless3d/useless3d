#version 450 core

out vec4 FragColor;


void main() {

	//FragColor = mix(texture(texture1, TexCoord), texture(texture1, TexCoord), 0.2);
	FragColor = vec4(0.9, 0.0, 0.9, 1.0);

}