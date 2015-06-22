
uniform float t;

void main()
{
	float r = abs(sin(t / 2.0));
	float g = abs(cos(t / 3.0 + 1));
	float b = 0.75;
	gl_FragColor = vec4(r, g, b, 1.0);
}