#version 330 core

in vec2 texCoord;

uniform vec4 aColor;
uniform sampler2D texture0;
uniform bool isTexture;

void main()
{

	if(isTexture)
	{
		gl_FragColor = texture(texture0, texCoord);
	}
	else
	{
	gl_FragColor = aColor;
	}

};