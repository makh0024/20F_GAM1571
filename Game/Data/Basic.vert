
attribute vec2 a_Position;
attribute vec2 b_Position;

uniform float u_Time;
uniform vec2 u_Increment;

void main()
{
	vec2 pos = a_Position + u_Increment;
	
	//vec2 finalpos = u_Increment + pos;
	//pos.x += 0.25;
	//pos.x *= sin(u_Time * 3);

	pos = pos - 5;
	pos = pos / 5;

	//gl_Position = vec4( sin(u_Time * pos), 0, 1 ); // master hamid
	gl_Position = vec4( pos , 0, 1 );
}
