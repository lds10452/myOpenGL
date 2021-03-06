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
	bool next=false;
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
		if (!next&&temp>256)
		{
			temp=0;
			next=true;
		}
		if (next&&temp>512)
		{
			temp=0;
			flag=!flag;
			next=false;
			Sleep(500);
		}
		offset=temp/512.f;
		if (!next)
		{
			vertices[1]=1.0;
			vertices[4]=1.0;
			vertices[15]=0.0;
			vertices[16]=1.0;
			vertices[19]=1.0;

			vertices[20]=0.0;
			vertices[21]=1.0;
			vertices[24]=1.0;
			vertices[36]=1.0;
			vertices[39]=1.0;

			vertices[15]=2*offset;
			vertices[18]=0.5+offset;
			vertices[20]=-2*offset;
			vertices[23]=0.5-offset;
		}
		else
		{
			vertices[1]=1-2*offset;
			vertices[4]=1-offset;
			vertices[15]=1.0;
			vertices[16]=1-2*offset;
			vertices[19]=1-offset;

			vertices[20]=-1.0;
			vertices[21]=1-2*offset;
			vertices[24]=1.0-offset;
			vertices[36]=1-2*offset;
			vertices[39]=1-offset;
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		if (flag)
		{
			glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);
		}
		else
		{
			glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
		}
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