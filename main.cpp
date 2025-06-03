// Copyright 2025 chrisfantasy

#define GLFW_DLL

#include <iostream>
#include "include/core.hpp"
#define GLAD_GL_IMPLEMENTATION
#include "include/win64_gl/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "include/win64_gl/GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

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

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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

/*
int main() {
    TR::Timer mainTimer(2s);
    auto curr_time = mainTimer.time_left();
    // int b =0;
    std::cout << "Welcome to the Touhou Rainbow Market Game! (Terminal Edition)";
    std::cout << "\nBut before I do... \n";

    mainTimer.timer_reset(2s);
    curr_time = mainTimer.time_left();

    while (curr_time >= 0s) {
        std::cout << "Let's start by testing the timer: " << curr_time.count();
        // curr_time++;
        curr_time = mainTimer.time_left();
        std::cout << "\r";
        // std::cin >> b;
    }
    int x;
    std::string ack;
    TR::Char_State y;
    TR::Player_ID a = TR::Player_ID::PI_Player_1;
    std::cout << "\nSelect your character \n{Reimu} {Marisa}\n";
    std::cin >> x;
    if (x == 1) {
        y = TR::S_Reimu;
    } else if (x == 2) {
        y = TR::S_Marisa;
    } else {
        y = TR::S_Null_Char;
    }
    std::cout << "Ok cool ";

    TR::Char NewPlayer(1, a, y);
    NewPlayer.showDesc();

    std::unique_ptr<TR::Lot> nPC_1(new TR::Lot());

    std::cout << NewPlayer.getPathway() << "\n";
    std::cout << "Here is your current lot for Player 1: \n\n";

    std::cout << NewPlayer.getLot()->getLotAll();
    std::cout << "Would you like to get this cool bug market? (y/n)\n";

    std::cin >> ack;
    if (ack == "y") {
        std::cout << "Where do you want to put it? (lot 1 - 5) \n";
        std::cin >> x;
        NewPlayer.getLot()->setLot(x, TR::Wriggle());
    }

    std::cout << NewPlayer.getLot()->getLotAll();



    return 0;
}
*/
