#version 430

// variables from VBO
layout( location = 0 ) in vec3 inputObjectSpacePosition;
layout( location = 1 ) in vec3 inputColor;

// the values to be passed on in the pipeline
out vec3 color;

// the shader's outside parameters

// transformation matrices
uniform mat4 world;
uniform mat4 viewProj; // The view and projection matrices are passed on together by multiplying them together.

void main()
{
	gl_Position  = viewProj * world * vec4( inputObjectSpacePosition, 1.0 );
	color = inputColor;
}
