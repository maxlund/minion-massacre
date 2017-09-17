#version 120
uniform sampler2D texture;
uniform float freezeScale;
uniform float poisonClock;
uniform float poisonScale;

void main()
{
    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor.b += freezeScale;

	gl_FragColor.g += max(sin(min(1 - poisonClock, 1.0) * 4.0 + 1.0) * poisonScale, 0.0);
}
