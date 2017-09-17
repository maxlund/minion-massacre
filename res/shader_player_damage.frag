#version 120
uniform sampler2D texture;
uniform float time;

void main()
{
    float a = 0.8;
    float b = -1.2;

    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy);
    float timeScale = max(sin(min(time, 1.0) * 4.0 + 1.0), 0.0);
    float dist = length(distance(gl_TexCoord[0].xy, vec2(0.5, 0.5)) / vec2(0.5, 0.5));
    float result = timeScale * max(0.0, a * pow(dist, 2.0) + b * dist);
    gl_FragColor += vec4(result, -result * 2.0, -result * 2.0, 0.0);
}