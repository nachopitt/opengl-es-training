attribute vec4 vPosition;
attribute vec4 aColor;
varying vec4 vColor;
void main()
{
   vColor = aColor;
   gl_Position = vPosition;
}
