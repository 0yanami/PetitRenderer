#include "mainLoop.hpp"

MainLoop::MainLoop(Scene& _scene, Ui& _ui, Inputs& _inputs)
    : activeScene(_scene), ui(_ui), inputs(_inputs) {
    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 2);

    window = glfwCreateWindow(windowWidth, windowHeight,
                              windowName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    //Callbacks binding
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Inputs::mouse_callback);
    glfwSetScrollCallback(window, Inputs::scroll_callback);
    glfwSetFramebufferSizeCallback(window, Inputs::framebuffer_size_callback);

    //GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
 
    // ImGui Setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    deltaTime = 0.0;
    lastFrame = 0.0;
}

void MainLoop::run() {

    while (!glfwWindowShouldClose(window)) {
        inputs.processInput(window,deltaTime);


        double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        //processInput(window);
        glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateFpsCounter();

        

        // render things


        // imgui part
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("General Parameters");
        ImGui::Text("Selectionnez une scène à afficher:\n");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void MainLoop::updateFpsCounter(){ //TODO: a verifier (chrono)
    using namespace std::chrono;
    if ((int)(glfwGetTime()*1000)%200 == 0.0) {
        std::stringstream sstr;
        //double fps = 1.0 / ((glfwGetTime() - fpsTime) / 20.0);
        sstr << windowName<<"  |  frametime : " << std::setprecision(3) << 1/deltaTime;
        std::string titleStr = sstr.str();
        const char* title = (char*)titleStr.c_str();
        glfwSetWindowTitle(window, title);
    }
}

void MainLoop::setWindowSize(int w,int h){
    windowWidth = w;
    windowHeight = h;
}

// end of render loop
void MainLoop::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}