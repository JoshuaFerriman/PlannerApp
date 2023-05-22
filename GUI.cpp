#include "GUI.h"

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
};

GUI::GUI()
{


}

void GUI::InitialiseGUI()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    window = glfwCreateWindow(1200, 1200, "PlannerApp", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 1200, 1200);

    // Create Vertex Shader Object and get its reference
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void GUI::MainLoop()
{
    bool drawTriangle = true;

    bool authenticated = false;
    bool newProject = false;
    bool loginWindow = false;
    bool newUser = false;

    std::string username = "";
    std::string password = "";

    std::vector<Project> projects = {};



    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        if (drawTriangle)
            glDrawArrays(GL_TRIANGLES, 0, 3);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Project")) { newProject = true; }
                ImGui::Separator();
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }



            if (authenticated && ImGui::BeginMenu("User"))
            {
                if (ImGui::MenuItem("Logout")) { authenticated = false; }
                ImGui::EndMenu();
            }
            if (!authenticated && ImGui::BeginMenu("Login"))
            {

                if (ImGui::MenuItem("Login")) { loginWindow = true; }
                if (ImGui::MenuItem("Create account")) { newUser = true; }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();

        }

        if (loginWindow)
        {
            char usernameBuff[32] = "";
            char passwordBuff[32] = "";

            strncpy_s(usernameBuff, username.c_str(), sizeof(usernameBuff));
            strncpy_s(passwordBuff, password.c_str(), sizeof(passwordBuff));

            ImGui::Begin("Login");

            ImGui::Text("Username:");
            ImGui::InputText("##username", usernameBuff, IM_ARRAYSIZE(usernameBuff));
            username = usernameBuff;
            ImGui::Text("Password:");
            ImGui::InputText("##password", passwordBuff, IM_ARRAYSIZE(passwordBuff), ImGuiInputTextFlags_Password);
            password = passwordBuff;



            if (ImGui::Button("Login"))
            {
                strcpy_s(usernameBuff, "");
                strcpy_s(passwordBuff, "");

                User user(username, password);
                if (user.UserLogin(databaseAccessor))
                {
                    password = "";
                    username = "";

                    authenticated = true;
                    loginWindow = false;
                }
                else
                {
                    std::cout << "Login Failed";
                    authenticated = false;
                    loginWindow = false;

                }
            }

            ImGui::End();
        }

        if (newUser)
        {
            char usernameBuff[32] = "";
            char passwordBuff[32] = "";

            strncpy_s(usernameBuff, username.c_str(), sizeof(usernameBuff));
            strncpy_s(passwordBuff, password.c_str(), sizeof(passwordBuff));

            ImGui::Begin("Create Account");

            ImGui::Text("Username:");
            ImGui::InputText("##username", usernameBuff, IM_ARRAYSIZE(usernameBuff));
            username = usernameBuff;
            ImGui::Text("Password:");
            ImGui::InputText("##password", passwordBuff, IM_ARRAYSIZE(passwordBuff), ImGuiInputTextFlags_Password);           

            password = passwordBuff;

            if (ImGui::Button("Create Account"))
            {
                strcpy_s(usernameBuff, "");
                strcpy_s(passwordBuff, "");

                User user(username, password);
                if (user.UserCreate(databaseAccessor))
                {
                    password = "";
                    username = "";

                    authenticated = true;
                    newUser = false;
                }
                else
                {
                    std::cout << "User Create Failed";
                    authenticated = false;
                    newUser = false;

                }
            }

            ImGui::End();
        }

        for (Project project : projects)
        {
            ImGui::Begin(project.name.data());
            ImGui::Text(project.description.data());

            ImGui::End();
        }

        if (newProject)
        {
            time_t startDate = NULL;
            time_t dueDate = NULL;
            char str0[128] = "Hello, world!";
            char str1[512] = "Hello, world!";
            int objectiveNum = 0;
            int stepNum = 0;


            ImGui::Begin("New Project");

            ImGui::Text("Enter Project Name:");
            ImGui::InputText("##projectName", str0, IM_ARRAYSIZE(str0));

            ImGui::Text("Enter Project Description:");
            ImGui::InputTextMultiline("##projectDescription", str1, IM_ARRAYSIZE(str1));

            ImGui::Text("Enter number of initial objectives desired:");
            ImGui::InputInt("##projectObjectiveNum", &objectiveNum);

            ImGui::Text("Enter number of initial steps desired:");
            ImGui::InputInt("##projectStepNum", &stepNum);



            if (ImGui::Button("Create new project"))
            {
                projects.push_back(Project(str0, dueDate, startDate));
                newProject = false;
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
}

void GUI::CloseGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    // Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}