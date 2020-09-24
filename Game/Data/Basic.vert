
attribute vec2 a_Position;

uniform float u_Time;

void main()
{
	vec2 pos = a_Position;

	//pos.x += 0.25;
	pos.x *= sin(u_Time * 3);

	//gl_Position = vec4( sin(u_Time * pos), 0, 1 ); // master hamid
	gl_Position = vec4( pos, 0, 1 );
}
