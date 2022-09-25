#include <glad/gl.h>
//#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main (int argc, char * argv[]){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "glfwinit" << std::endl;
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLSandbox", NULL, NULL);
    if (window == NULL) {
        std::cout <<"failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
    }
    /*
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        return -1;
    }
    */
    glViewport(0, 0, 800, 600);
    //glViewport();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
    float triVerts[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        //rendering
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    
    return 0;

}
