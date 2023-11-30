#pragma once
#include <string>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:
	void compileShaders(const char* vertexCode, const char* fragmentCode);
	void checkCompileError(unsigned int shader, bool isShader = true);
public:
	unsigned int ID;

};

