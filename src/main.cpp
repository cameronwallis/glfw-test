#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void frame_buffer_size_callback(GLFWwindow *window, int width, int height);

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

    while(!glfwWindowShouldClose(window))
    {
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
