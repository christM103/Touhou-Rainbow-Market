// Copyright 2025 chrisfantasy

#define GLFW_DLL

#include <iostream>
#include "include/core.hpp"
#define GLAD_GL_IMPLEMENTATION
#include "include/win64_gl/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "include/win64_gl/GLFW/glfw3.h"

/* Resizing the window when the user trys to resize the window */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    glfwInit(); // Starting up GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // For GL version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // For GL version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Open GL core

    // Initial variables
    GLFWmonitor* monitor(glfwGetPrimaryMonitor()); // Current monitor being used
    int width(0), height(0); // Current width & height

    /* Finding the total physical size of the current monitor being used */
    glfwGetMonitorWorkarea(monitor, NULL, NULL, &width, &height); 

    /* Changing the width and height to match the ratio 800 x 600 */
    width = width/10 * 4;
    height = height/20 * 11;
    
    /* Creation of the window variable */
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) { // Checking whether the window is valid or not
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize the window

    /* Initialize OpenGL functions for the program */    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, width, height); // Give OpenGL the rendering size of the window

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // For every resize request

    /* GLFW checks for whether the window is still open; Does a render loop */
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); // Constantly updates each color pixel in the window
        glfwPollEvents(); // Checks whether event or inputs are happening
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
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
