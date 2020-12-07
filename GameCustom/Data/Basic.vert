attribute vec2 a_Position;
attribute vec2 a_UVCoord; //Input from our VBO

uniform vec2 u_ObjectScale;
uniform vec2 u_ObjectPos;

uniform vec2 u_CameraPos;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;
varying vec2 v_UVCoord; //Output to our Frag Shader

void main()
{
    vec2 pos = a_Position;

    // Object Scale.
    pos *= u_ObjectScale; 

    // Rotate
    pos += u_ObjectPos;

    // Offset from camera position
    pos -= u_CameraPos;

    // Divide to fit in clip space
    pos /= vec2(5, 5);
    //pos /= vec2(3.0f, 3.0f);

    v_UVCoord = a_UVCoord * u_UVScale + u_UVOffset;

    gl_Position = vec4( pos, 0, 1 );
}
