#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//header file for transformation
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<stb/stb_image.h>

//header files for shaders
#include<fstream>
#include<sstream>
#include<streambuf>
#include<string>

#include "Shader.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);





int main() {
	//std::cout << "hello world" << std::endl;

	//glm test transformation
	/*
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); 
	glm::mat4 trans = glm::mat4(1.0f);// creating an indentity matrix in programming language
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	cout << vec.x << " " << vec.y << " " << vec.z << endl;
	*/
	 
	//glm scaling and rotation;
	/*
	glm::vec4 vec1(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 trans1 = glm::mat4(1.0f);
	trans1 = glm::rotate(trans1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.1f));//rotation
	trans1 = glm::scale(trans1,glm::vec3(0.5f,0.5f,0.5f));// scaling ,first the scaling is done then rotaion happen think of this like a matrix multiplucation
	vec1 = trans1 * vec1;
	cout << vec1.x << " " << vec1.y << " " << vec1.z << endl;
	*/
	
	glfwInit();

	//open gl version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	


	if (window == NULL) {//window not created 
		cout << "Could not create a window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//here if window is not null window is created

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//shaders
	//compile vertex shaders
		//vertex array
	Shader shader("Assets/vertex_core.glsl", "Assets/fragment_core.glsl");

	Shader shader2("Assets/vertex_core.glsl", "Assets/fragmnet_core2.glsl");

	float vertices[] = {
		//position						colors             Texture Cordinate

	 -0.5f, -0.5f,  0.0f,		    1.0f,1.0f,0.5f,                 0.0f,0.0f,     //bottom left
	 -0.5f,  0.5f,  0.0f,			0.5f,1.0f,0.75f,				0.0f,1.0f,     //top left
	  0.5f, -0.5f,  0.0f,			0.6f,1.0f,0.2f,					1.0f,0.0f,	   //bottom right
	  0.5f,  0.5f,  0.0f,			1.0f,0.2f,1.0f,					1.0f,1.0f      // top right


	};

	
	 
	unsigned int indicies[] = {
		0, 1, 2,//first triangle
		3, 1, 2//second triangle
	};
	/*float vertices[] = {
		//position						colors

		-0.5f, -0.5f,  0.0f,		    1.0f,1.0f,0.5f,//top right
		 -0.5f, 0.5f,  0.0f,			0.5f,1.0f,0.75f,//top left
		 0.5f,  -0.5f, 0.0f,		    0.6f,1.0f,0.2f,//bottom left
		 0.5f,  0.5f,  0.0f,			1.0f,0.2f,1.0f//bottom right



	};
	unsigned int indicies[] = {
		0, 1, 2,//first triangle
		3, 1, 2//second triangle
	};
	*/
	
	//VAO vertex array object and VBO refers to vertex buffer object,here VAO save the data in the form of VBO bind to the index values like VAO[0]=VBO, so from VAO[0] value graphic card know to which vertex data to look for and then we will pass data in the shader program
	unsigned int VAO, VBO,EBO;//EBO stands for element buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);
	//bind buffer
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set vertex attribute pointers
	
	//position of vertices since we have given the attribute value 3 in the below function it will only read till 3 vertices
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 *sizeof(float)));
	glEnableVertexAttribArray(1);

	// for Texture coordinate
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float), (void*)(6 * sizeof(float)));
	// now wehave to enable it
	glEnableVertexAttribArray(2);

	//Texture
	unsigned int texture1,texture2;//for loading another texture
	glGenTextures(1, &texture1);//to generate the texture buffer
	glBindTexture(GL_TEXTURE_2D, texture1);
	//parameter that we have to include
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//image filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//load images
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Assets/image1.jpg",&width,&height,&nChannels,0);


	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "Failed to load Texture" << std::endl;
	}
	//stbi_image_free(data);
	stbi_image_free(data);
	//for second texture
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	data = stbi_load("Assets/image3.jpg", &width, &height, &nChannels, 0);
	 
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	shader.activate();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);


	//set up EBO to store the indicies of the rectangle that are top right top left and bottom right and bottom left
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	//for the transformation of shaders rotate and translate and scaling
	/*
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.activate();
	shader.setMat4("transform", trans);
	
	glm::mat4 trans2 = glm::mat4(1.0f);
	trans2 = glm::scale(trans2, glm::vec3(1.5f));
	trans2 = glm::rotate(trans2,glm::radians(15.f),glm::vec3(0.0f,0.0f,1.0f));
	shader2.activate();
	shader2.setMat4("transform", trans2);
	*/

	while (!glfwWindowShouldClose(window)){
		//process input window
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//render
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);//to activat texture buffer
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		/*trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.activate();
		shader.setMat4("transform", trans);
		*/

		

		//draw shapes
		glBindVertexArray(VAO);//now by this opengl konw that which vertex to look at as result it know which  vertex buffer object to callout;

		//first trinagle using vertex shader
		shader.activate();
		
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//second triangle 
		//glUseProgram(shaderProgram[1]);

		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(float)));
		
		/*trans2 = glm::rotate(trans2, glm::radians((float)glfwGetTime() / -100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader2.activate();
		shader2.setMat4("transform", trans2);
		*/

		//shader2.activate();
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(GLuint)));
		
		
		glBindVertexArray(0);
		//send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)//resize the window dimensions if user resize the window
{
	glViewport(0, 0, width, height);
};
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

