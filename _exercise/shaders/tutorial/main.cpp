#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "includes/shaders.h"

float vertices[] = {
	// positions        // colors
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
         std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	Shader ourShader("shaders/shaderclass.vs", "shaders/shaderclass.fs"); // you can name your shader files however you like

	// Setup vertex data
	unsigned int VAO, VBO;// Vertex Array Object & Vertex Buffer Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);


 	// the call to glVertexAttribPointer registered VBO as the 
	// vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. 
	// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally 
	// don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

	 // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window))
	{
		// INPUT PROCESSING & CLEAR CANVAS
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  		glClear(GL_COLOR_BUFFER_BIT);
		
		// RENDERING
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

		// RENDER ON SCREEN
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocate all resources once they've outlived their purpose.
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


	glfwTerminate();
    return 0;
}