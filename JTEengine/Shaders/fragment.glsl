#version 460

in vec3 VertColor;

out vec4 FragColor;

void main() {
	FragColor = vec4(VertColor, 1.0);
}