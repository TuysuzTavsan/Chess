#version 330 core

in vec2 texCoord;

uniform sampler2D bgTexture;
uniform sampler2D hoverTexture;
uniform sampler2D activeTexture;

uniform int state;

void main()
{
	switch(state)
	{
		case 0:
			gl_FragColor = texture(bgTexture, texCoord);
			break;
		case 1:
			gl_FragColor = texture(hoverTexture, texCoord);
			break;
		case 2:
			gl_FragColor = texture(activeTexture, texCoord);
			break;
	}
	
	
};