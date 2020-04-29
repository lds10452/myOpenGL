#include <Windows.h>
#include<glad\glad.h>//管理opengl函数指针
#include<GLFW\glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
#define PI 3.1415926
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LDSopenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSwapInterval(1);
	Shader ourShader("./res/shader.vs", "./res/shader.fs");

	float vertices[] = 
	{
		1.0,   1.0f, 0.0f, 1.0, 1.0f,   // 右上
		1.0,  -1.0, 0.0f, 1.0, 0.0f,   // 右下
		0.0,-1.0, 0.0f, 0.5, 0.0f,   // 左下
		0.0, 1.0, 0.0f, 0.5, 1.0f,   // 左上
		0.0,   1.0f, 0.0f, 0.5, 1.0f,   // 右上
		0.0,  -1.0, 0.0f, 0.5, 0.0f,   // 右下
		-1.0,-1.0, 0.0f, 0.0, 0.0f,   // 左下
		-1.0, 1.0, 0.0f, 0.0, 1.0f   // 左上
	};
	unsigned int indices[] = {
		//0, 1, 3, // first triangle
		//1, 2, 3  // second triangle
		//3,0,2,1
		3,2,0,1,7,6,4,5
	};

	ourShader.use();
	GLuint texcoordLoc=glGetAttribLocation(ourShader.ID,"aTexCoord");
	GLuint aPosLoc=glGetAttribLocation(ourShader.ID,"aPos");
	//GLuint aColorLoc=glGetAttribLocation(ourShader.ID,"aColor");
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPosLoc);

	glVertexAttribPointer(texcoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(texcoordLoc);

	unsigned int texture1,texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); 
	// set the texture wrapping parameters
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data1,*data2; 
	data1= stbi_load("./res/textures/1585302769594.png", &width, &height, &nrChannels, 0);//container.jpg
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	data2 = stbi_load("./res/textures/1585303063943.png", &width, &height, &nrChannels, 0);//awesomeface.png
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB , GL_UNSIGNED_BYTE, data2);//GL_RGBA
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2);

	bool flag=true;
	int temp=0;
	float offset=0.f;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		temp+=2;
		if (temp>180)
		{
			temp=0;
			flag=!flag;
			Sleep(500);
		}
		vertices[0]=cos(temp*PI/180);
		vertices[2]=sin(temp*PI/180);
		vertices[5]=cos(temp*PI/180);
		vertices[7]=sin(temp*PI/180);
		vertices[30]=cos((temp+180)*PI/180);
		vertices[32]=sin((temp+180)*PI/180);
		vertices[35]=cos((temp+180)*PI/180);
		vertices[37]=sin((temp+180)*PI/180);
		glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
		if (flag)
		{
			glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);
		}
		else
		{
			glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
		}
		glm::mat4 projection=glm::mat4(1.f);
		glm::mat4 view=glm::mat4(1.f);
		view=glm::lookAt(
			glm::vec3(0.0f,0.0,1.5),
			glm::vec3(0.0,0.0,0.0),
			glm::vec3(0.0,1.0,0.0)
			);
		projection=glm::perspective(45.f,1.f,0.01f,100.0f);//45.0f, 1.0f, 0.1f, 100.0f
		ourShader.setMat4("projection",glm::value_ptr(projection));
		ourShader.setMat4("view",glm::value_ptr(view));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(4*sizeof(indices[0])));

		glfwSwapBuffers(window);
		//glFinish();
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}