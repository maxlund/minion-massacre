#version 120
uniform sampler2D texture;

void main()
{
    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor.g = gl_FragColor.r;
	gl_FragColor.b = gl_FragColor.r;
	gl_FragColor *= 0.8;
}
