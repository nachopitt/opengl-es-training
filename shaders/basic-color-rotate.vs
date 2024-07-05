attribute vec4 vPosition;
attribute vec4 aColor;
varying vec4 vColor;
uniform mat4 modelViewProjection;
void main()
{
   vColor = aColor;
   gl_Position = modelViewProjection * vPosition;
}
