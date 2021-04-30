#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_manager.hpp"

void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main(int argc, char **argv)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;    
    }
    
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    // Data

    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // ** VAO **

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    int success;
    char info_log[512];

    // ********************************* LOADING VERTEX SHADER *****************************
    ShaderManager vertex_shdr_manager("./shaders/vertex.vert");

    unsigned int vertex_shdr;
    vertex_shdr = glCreateShader(GL_VERTEX_SHADER);

    const char *vertex_shdr_source = vertex_shdr_manager.get_source();

    glShaderSource(vertex_shdr, 1, &vertex_shdr_source, nullptr);
    glCompileShader(vertex_shdr);

    glGetShaderiv(vertex_shdr, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex_shdr, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPLATION_FAILED\n" << info_log << std::endl; 
    }
    // ****************************** DONE VERTEX SHADER ***************************************
    // ****************************** LOADING FRAGMENT SHADER **********************************
    ShaderManager fragment_shdr_manager("./shaders/fragment.frag");

    unsigned int fragment_shdr;
    fragment_shdr = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_shdr_source = fragment_shdr_manager.get_source();

    glShaderSource(fragment_shdr, 1, &fragment_shdr_source, nullptr);
    glCompileShader(fragment_shdr);

    glGetShaderiv(fragment_shdr, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment_shdr, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPLATION_FAILED\n" << info_log << std::endl; 
    }
    // ****************************** DONE FRAGMENT SHADER *************************************

    unsigned int shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shdr);
    glAttachShader(shader_program, fragment_shdr);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << info_log << std::endl; 
    }

    glDeleteShader(vertex_shdr);
    glDeleteShader(fragment_shdr);
    glUseProgram(shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(0));
    glEnableVertexAttribArray(0);



    while(!glfwWindowShouldClose(window))
    {
        // Input
        process_input(window);

        // Rendering Commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}