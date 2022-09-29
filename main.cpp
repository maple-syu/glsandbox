#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <iostream>
#include <ostream>

const char *vertexshadersource = "\n"
    "#version 330 core\n"
    "    layout (location = 0) in vec3 aPos;\n"
    "    void main () {\n"
    "        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "    }\n"
    "\0";

const char *fragmentShaderSourcePink = "\n"
    "#version 330 core\n"
    "    out vec4 FragColor;\n"
    "    void main(){\n"
    "        FragColor = vec4(1.0, 0.67, 1.0, 1.0);\n"
    "    }\n"
;

const char *fragmentShaderSourceBlue = "\n"
    "#version 330 core\n"
    "    out vec4 FragColor;\n"
    "    void main(){\n"
    "        FragColor = vec4(0.44, 0.74, 0.97, 1.0);\n"
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
    
    //Two Triangles
    float exVertsOne[] = {
        //Tri One
        -1.0f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };
    float exVertsTwo[] = {
        //Tri Two
        0.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
    };
    unsigned int exIndiciesOne[] = {
        0, 2, 1,
    };

    unsigned int exIndiciesTwo[] = {
        0, 2, 1,
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

    //Setting fragment shader pink
    unsigned int fragmentShaderPink;
    fragmentShaderPink = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderPink, 1, &fragmentShaderSourcePink, NULL);
    glCompileShader(fragmentShaderPink);

    //Setting fragment shader blue
    unsigned int fragmentShaderBlue;
    fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderBlue, 1, &fragmentShaderSourceBlue, NULL);
    glCompileShader(fragmentShaderBlue);

    //Creating shader program
    unsigned int shaderProgramPink;
    shaderProgramPink = glCreateProgram();
    glAttachShader(shaderProgramPink, vertexShader);
    glAttachShader(shaderProgramPink, fragmentShaderPink);
    glLinkProgram(shaderProgramPink);

    unsigned int shaderProgramBlue;
    shaderProgramBlue = glCreateProgram();
    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramBlue);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderPink);
    glDeleteShader(fragmentShaderBlue);
    
    //setting vertex ARRAY object
    unsigned int VAOs[2] ;
    glGenVertexArrays(2, VAOs);
    glBindVertexArray(VAOs[0]);

    //setting element buffer object
    unsigned int EBOs[2];
    glGenBuffers(2, EBOs);

    //Seting vertex buffer object
    unsigned int VBOs[2];
    glGenBuffers(2, VBOs);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
   
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(exVertsOne), exVertsOne, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(exIndiciesOne), exIndiciesOne, GL_STATIC_DRAW);

    //vertex attribute
    //location in vertShader, size of vertex attribute (vec3 so it's 3), using floats, not normalized, sizeof stride (3 floats, so 3 times the size of float), offset is 0 cast as void.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(exVertsTwo), exVertsTwo, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(exIndiciesTwo), exIndiciesTwo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        //rendering
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        //draw triangle
        glUseProgram(shaderProgramPink);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glUseProgram(shaderProgramBlue);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(1);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgramPink);
    glDeleteProgram(shaderProgramBlue);
    glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);

    glfwTerminate();
    
    return 0;

}
