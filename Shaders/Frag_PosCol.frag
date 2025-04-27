#version 430

// per-fragment attributes coming in from the pipeline
in vec3 color;

// output value - the color of the fragment
out vec4 outputColor;

uniform vec3 addedcolor = vec3(0);

void main()
{
	outputColor = vec4( color + addedcolor, 1.0 );
}
