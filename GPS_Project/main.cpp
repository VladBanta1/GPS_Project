#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint grassTexture;
GLuint skyTexture;

GLuint loadTexture(const char* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (!data)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureID;
}

void drawGround()
{
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0); glVertex3f(-50, 0, -50);
    glTexCoord2f(10, 0); glVertex3f(50, 0, -50);
    glTexCoord2f(10, 10); glVertex3f(50, 0, 50);
    glTexCoord2f(0, 10); glVertex3f(-50, 0, 50);

    glEnd();
}

void drawSky()
{
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, skyTexture);

    glBegin(GL_QUADS);

    // BACK
    glTexCoord2f(0, 0); glVertex3f(-500, 0, -500);
    glTexCoord2f(1, 0); glVertex3f(500, 0, -500);
    glTexCoord2f(1, 1); glVertex3f(500, 500, -500);
    glTexCoord2f(0, 1); glVertex3f(-500, 500, -500);

    // FRONT
    glTexCoord2f(0, 0); glVertex3f(-500, 0, 500);
    glTexCoord2f(1, 0); glVertex3f(500, 0, 500);
    glTexCoord2f(1, 1); glVertex3f(500, 500, 500);
    glTexCoord2f(0, 1); glVertex3f(-500, 500, 500);

    // LEFT
    glTexCoord2f(0, 0); glVertex3f(-500, 0, -500);
    glTexCoord2f(1, 0); glVertex3f(-500, 0, 500);
    glTexCoord2f(1, 1); glVertex3f(-500, 500, 500);
    glTexCoord2f(0, 1); glVertex3f(-500, 500, -500);

    // RIGHT
    glTexCoord2f(0, 0); glVertex3f(500, 0, -500);
    glTexCoord2f(1, 0); glVertex3f(500, 0, 500);
    glTexCoord2f(1, 1); glVertex3f(500, 500, 500);
    glTexCoord2f(0, 1); glVertex3f(500, 500, -500);

    // TOP
    glTexCoord2f(0, 0); glVertex3f(-500, 500, -500);
    glTexCoord2f(1, 0); glVertex3f(500, 500, -500);
    glTexCoord2f(1, 1); glVertex3f(500, 500, 500);
    glTexCoord2f(0, 1); glVertex3f(-500, 500, 500);

    // BOTTOM
    glTexCoord2f(0, 0); glVertex3f(-500, 0, -500);
    glTexCoord2f(1, 0); glVertex3f(500, 0, -500);
    glTexCoord2f(1, 1); glVertex3f(500, 0, 500);
    glTexCoord2f(0, 1); glVertex3f(-500, 0, 500);

    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "GPS P1 Scene", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "GLAD failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    grassTexture = loadTexture("textures/grass.jpg");
    skyTexture = loadTexture("textures/sky.jpg");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.7f, 1.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-2, 2, -1.5, 1.5, 1, 1000);

        // camera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, -3, -30);
        glRotatef(30, 1, 0, 0);

        drawSky();
        drawGround();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}