#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGL();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}