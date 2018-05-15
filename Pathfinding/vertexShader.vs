varying float zeye;
varying float D;

void main(void)
{
   vec4 vertexPosition = gl_ModelViewMatrix * gl_Vertex;
   
   zeye = -vertexPosition.z;
   
   float x = vertexPosition.x;
   float y = vertexPosition.y;
   
   D = (x*x + y*y + zeye*zeye);
   
   gl_Position = ftransform();
}