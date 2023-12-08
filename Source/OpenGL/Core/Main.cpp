#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "./Shader.h"
#include "../Tools/FileTools.h"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setVetex(
    unsigned int VAO, unsigned int VBO, unsigned int EBO, 
    float vertices[], long long int verticesSize, 
    unsigned int indices[], long long int indicesSize, bool color = false);
int initWindows(GLFWwindow** window);

int main()
{
    GLFWwindow* window = nullptr;
    if (initWindows(&window)<0)
    {
        return -1;
    }
    
    std::string programDir = FileTools::getProgramDir();
    std::string vsPath = programDir + "/GLSL/shader.vs";
    std::string fsPath = programDir + "/GLSL/shader.fs";
    Shader ourShader(vsPath.c_str(), fsPath.c_str());

    vsPath = programDir + "/GLSL/shader1.vs";
    fsPath = programDir + "/GLSL/shader1.fs";    
    Shader ourShader1(vsPath.c_str(), fsPath.c_str());
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.0f,  1.0f, 0.0f,  1.0f,0.0f,0.0f, // top right
         0.0f,  0.0f, 0.0f,  0.0f,1.0f,0.0f,// bottom right
        -1.0f,  0.0f, 0.0f,  0.0f,0.0f,1.0f,// bottom left
        -1.0f,  1.0f, 0.0f,   0.0f,0.0f,0.0f// top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 2, 3,  // first Triangle
        0, 1, 2 // second Triangle
    };

    float vertices2[] = {
         1.0f, 0.0f, 0.0f, 
         1.0f, -1.0f, 0.0f, 
         0.0f, -1.0f, 0.0f,  
         0.0f, 0.0f, 0.0f
    };

    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    setVetex(VAOs[0], VBOs[0], EBO, vertices, sizeof(vertices), indices, sizeof(indices),true);
    setVetex(VAOs[1], VBOs[1], EBO, vertices2, sizeof(vertices2), indices, sizeof(indices));

    //可以解绑VBO，因为调用glvertexattributpointer，已将VBO注册为当前绑定的顶点缓冲区对象，所以可以安全的解除绑定
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //当前不使用VAO
    //glBindVertexArray(0);
    //是否使用线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(ourShader.ID);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(ourShader1.ID);
        float timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        float greenValue = (sin(timeValue*2) / 2.0f) + 0.5f;
        float blueValue = (sin(timeValue*4) / 2.0f) + 0.5f;
        float xfloat = sin(timeValue) / 2.0f-0.5f;
        int vertexColorLocation = glGetUniformLocation(ourShader1.ID, "outcolor");
        glUniform4f(vertexColorLocation, redValue, greenValue,blueValue, 1.0f);
        ourShader1.setFloat("xfloat", xfloat);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(ourShader.ID);
    glDeleteProgram(ourShader1.ID);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

int initWindows(GLFWwindow** window)
{
    // glfw: initialize and configure
   // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if ((*window) == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

void setVetex(unsigned int VAO, unsigned int VBO, unsigned int EBO,
    float vertices[], long long int verticesSize,
    unsigned int indices[], long long int indicesSize, bool color)
{
    //1、绑定顶点数组对象
    glBindVertexArray(VAO);
    // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用（存储顶点）
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    // 3、复制我们的索引数组到一个索引缓冲中，供OpenGL使用（存储顶点的索引）
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    

    if (color)
    {
        //4、设定顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)(sizeof(float)*3));
        glEnableVertexAttribArray(1);
    }
    else
    {
        //4、设定顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}