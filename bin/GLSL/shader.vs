#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform int type;
void main()
{
   gl_Position = vec4(aPos, 1.0); 
   if(type==0)  
   {
		ourColor = vec3(aColor.x, aColor.y, aColor.z);
   }else if(type==1)
   {
		ourColor = vec3(aColor.z, aColor.x, aColor.y);
   }else if(type==2)
   {
		ourColor = vec3(aColor.y, aColor.z, aColor.x);
   }
   
};