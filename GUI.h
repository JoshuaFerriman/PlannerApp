#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Project.h"
#include "User.h"


class GUI
{
	//Fields
public:

private:
	GLFWwindow* window;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	DatabaseAccessor databaseAccessor;

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	//Functions
public:
	GUI();
	void InitialiseGUI();
	void MainLoop();
	void CloseGUI();

private:

};