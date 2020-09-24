
uniform float u_Time;

void main()
{
	gl_FragColor = vec4( sin(u_Time), 0, 1, 1 );
}