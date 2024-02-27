#include "Shader.h"
using namespace std;
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	int success;
	char infoLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id,vertexShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);

	//catch errors
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
	std:: cout << "linking error" << std::endl << infoLog << std::endl;

	}

}
void Shader::activate() {
	glUseProgram(id);
}
//tell us which source code is we actually looking for either vertex_core or fragemnt_core
string Shader:: loadShaderSrc(const char* filename) {
	ifstream file;
	stringstream buf;// to read the data
	string ret = "";
	file.open(filename);

	if (file.is_open()) {
		buf << file.rdbuf();// here buffer is reading the file and the string which buufer read we will put the value of that string in ret variable so that we can return ret in the end of the function
		ret = buf.str();//ret value is updated by the string value in the buffer

	}
	else {
		cout << "Could not open the file" << filename << endl;
	}
	file.close();
	return ret;
}
GLuint Shader::compileShader(const char* filepath, GLenum type) {
	int success;
	char infoLog[512];
	GLuint ret = glCreateShader(type);
	string ShaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = ShaderSrc.c_str();
	glShaderSource(ret, 1, &shader, NULL);
	glCompileShader(ret);

	glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ret, 512, NULL, infoLog);//if success is false the it will be called and the parameters that glGetShadersInfoLog will take are the vertexShaders,size o the infolog array that we created above,takes NULL and the array itself

		cout << "Error with fragment shader comp::" << endl << infoLog << endl;
	}
	return ret;
}

void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}



void Shader::setMat3(const std::string& name, glm::mat3 val) {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setMat4(const std::string& name, glm::mat4 val) {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}