attribute vec3 a_Position;
attribute vec4 a_Color;
attribute vec2 a_TexCoord;

varying vec4 v_Color;
varying vec2 v_TexCoord;

void main()
{
   gl_Position = vec4(a_Position, 1.0);
   v_Color = a_Color;
   v_TexCoord = a_TexCoord;
}
