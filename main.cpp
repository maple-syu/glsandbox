#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <iostream>
#include <ostream>

#include <vector>

const char *vertexshadersource = "\n"
    "#version 330 core\n"
    "    layout (location = 0) in vec3 aPos;\n"
    "    void main () {\n"
    "        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "    }\n"
    "\0";

const char *fragmentShaderSource = "\n"
    "#version 330 core\n"
    "    out vec4 FragColor;\n"
    "    void main(){\n"
    "        FragColor = vec4(1.0, 0.67, 1.0, 1.0);\n"
    "    }\n"
;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int testNumber(int input){
    return input + 12;
}

int main (int argc, char * argv[]){
    //int myInt = 0;
    
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
        return -1;
    }
    /*
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        return -1;
    }
    */
    glViewport(0, 0, 800, 600);
    //glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /*
    float triVerts[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    */

    float indexVerts[] = {
        //
        0.5f, 0.5f, 0.0f,       //top right
        0.5f, -0.5f, 0.0f,      //bottom right
        -0.5f, -0.5f, 0.0f,     //bottom left
        -0.5f, 0.5f, 0.0f       //bottom right
    };

    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3
    };

    //Setting vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexshadersource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Setting fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Creating shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //setting vertex ARRAY object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //setting element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //Seting vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indexVerts), indexVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    //vertex attribute
    //location in vertShader, size of vertex attribute (vec3 so it's 3), using floats, not normalized, sizeof stride (3 floats, so 3 times the size of float), offset is 0 cast as void.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Enable shader program

    //Bind Vertex Array object
    
    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        //rendering
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        //draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    
    return 0;

}
