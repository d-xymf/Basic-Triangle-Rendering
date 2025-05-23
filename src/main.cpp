#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Vertex coordinates
GLfloat vertices[] = {
    // Positions                                // Colors
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    1.0f, 0.0f, 0.00f,  // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     0.0f, 1.0f, 0.00f,  // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  0.0f, 0.0f, 1.0f,  // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 1.0f, 0.0f, 1.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  0.0f, 1.0f, 1.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,     1.0f, 1.0f, 0.0f,  // Inner down
};

GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
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

    glViewport(0, 0, 800, 600);

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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // Link vertex coordinates
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Link vertex colors

    // Unbind everything
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Get the id of the "scale" uniform
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

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

        // Set "scale" uniform to 0.5
        glUniform1f(uniID, 0.5f);

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Send new frame to window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all our gl objects once finished
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwTerminate();
  
    return 0;
}

// Resize GLFWwindow whenever user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}