#ifndef Shader_my_H
#define Shader_my_H
#include <string>
class Shader_my
{
public:
	Shader_my(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:
	void compileShaders(const char* vertexCode, const char* fragmentCode);
	void checkCompileError(unsigned int Shader_my, bool isShader_my = true);
public:
	unsigned int ID;

};

#endif