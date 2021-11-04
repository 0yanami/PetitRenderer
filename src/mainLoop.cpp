#include "mainLoop.hpp"

MainLoop::MainLoop(Scene& _scene, Ui& _ui, Camera& _camera)
    : scene(_scene), ui(_ui), cam(_camera) {

    // camera defines window/viewport size
    windowWidth = cam.getResWidth();
    windowHeight = cam.getResHeight();

    // GLFW
    glfwInit();
    // opengl 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 2);

    window = glfwCreateWindow(windowWidth, windowHeight,
                              windowName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    //glfwSetCursorPos(window,windowWidth/2, windowHeight/2);

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
    ImGuiIO& io = ImGui::GetIO(); //TODO: a voir en cas de bug imgui
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //setup inputs
    inputs = {&cam};

    deltaTime = 0.0;
    lastFrame = 0.0;

   glPatchParameteri(GL_PATCH_VERTICES, 3);

}

void MainLoop::run() {

    while (!glfwWindowShouldClose(window)) {
        inputs.processInput(window,deltaTime);

        if( windowHeight != cam.getResHeight()||
            windowWidth != cam.getResWidth()
            ){
            windowHeight = cam.getResHeight();
            windowWidth = cam.getResWidth();

            glfwSetWindowSize(window, windowWidth, windowHeight);
            glViewport(0, 0, windowWidth, windowHeight);
            //glfwSetCursorPos(window,windowWidth/2, windowHeight/2);
        }


        double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        //processInput(window);
        glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateFpsCounter(500);
        

        // render objects of scene;
        scene.render(cam);

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

//! Shows fps on window title, update rate in ms
void MainLoop::updateFpsCounter(uint32_t _updateRateMs){
    using namespace std::chrono;
    if ((int)(glfwGetTime()*1000)%_updateRateMs == 0.0) {
        std::stringstream sstr;
        sstr << windowName<<"  |  FPS : " << std::fixed << 
        std::setprecision(1) << 1/deltaTime;

        std::string titleStr = sstr.str();
        const char* title = (char*)titleStr.c_str();
        glfwSetWindowTitle(window, title);
    }
}


// end of render loop
MainLoop::~MainLoop() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}