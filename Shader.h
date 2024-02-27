#ifndef SHADER_H

#define SHADER_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//header file for transformation
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//header files for shaders
#include<fstream>
#include<sstream>
#include<streambuf>
#include<string>

class Shader {
public:
	unsigned int id;
	Shader(const char* vertexSahderPath, const char* fragmentShaderPath);
	void activate();
	//utility function
	std::string  loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	//uniform function
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    
    void setMat3(const std::string& name, glm::mat3 val);
    void setMat4(const std::string& name, glm::mat4 val);
};
#endif