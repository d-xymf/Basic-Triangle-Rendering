#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Vertex coordinates
GLfloat vertices[] = {
    // Positions           // Colors            // UV coordinates
    -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f // Lower right corner
};

GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2, // Lower triangle
};

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);

    // Create shader program with our vertex and frag shaders
    Shader shaderProgram("../../../resources/shaders/default.vert", "../../../resources/shaders/default.frag");

    // Create a Vertex Array Object
    VAO VAO1;

    // Make it the current Vertex Array Object by binding it
    VAO1.Bind();

    // Create a VBO and an EBO for our vertices and indices
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Link the VBO to our VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // Link vertex coordinates
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Link vertex colors
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Link vertex colors

    // Unbind everything
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Textures
    Texture oakPlanks("../../../resources/textures/planks_oak.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    // Set texture as uniform "tex0" so it can be used in shaders
    oakPlanks.texUnit(shaderProgram, "tex0", 0);

    // Set framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main shader loop
    while(!glfwWindowShouldClose(window))
    {
        // Color window
        glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which shader program to use
        shaderProgram.Activate();

        // Bind oakPlanks texture
        oakPlanks.Bind();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Send new frame to window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all our gl objects once finished
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    oakPlanks.Delete();
    shaderProgram.Delete();

    glfwTerminate();
  
    return 0;
}

// Resize GLFWwindow whenever user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}