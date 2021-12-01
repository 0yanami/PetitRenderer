#include "ui.hpp"

#include "scene.hpp"

Ui::~Ui(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Ui::load(GLFWwindow* _window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); //TODO: a voir en cas de bug imgui
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void Ui::render(Scene* _scene){
    scene = _scene;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Scene parameters");

    
    ImGui::Text("Selectionnez une scène à afficher:\n");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void lightParams(){
    if(ImGui::TreeNode("Lights Parameters")){
        ImGui::Text("Light to Modify:\n");

        //display the light of light to choose from
        const char* items[100];
        std::vector<Light*>& lights = _scene->getLights();
        std::vector<std::string> lightNames;
        for (Light* li : lights)
            lightNames.push_back(li->getName());

        for(int i = 0; i<lightNames.size();i++){
            items[i] = lightNames[i].c_str();
        } 

        ImGui::ListBox("listbox", &lightListIndex, items, lightNames.size(), 5);
        Light* light = lights[lightListIndex];

        std::string lightText = "\n"+light->getName()+" parameters:\n";
        ImGui::Text(lightText.c_str());
        // Change parameters for selected light

        //diffuse color
        static float multLight = 1.0; 
        float diffuse[3] = { light->getDiffuse()[0]/multLight,
                             light->getDiffuse()[1]/multLight,
                             light->getDiffuse()[2]/multLight };
        ImGui::ColorEdit3("Color", diffuse);
        ImGui::DragFloat("Color Multiplier",&multLight,1.0,0.01,100.0);
        light->setDiffuse({diffuse[0]*multLight,
                        diffuse[1]*multLight,
                        diffuse[2]*multLight});              

        // change pos
        float pos[3] = {light->getPos()[0], light->getPos()[1], light->getPos()[2]};
        ImGui::DragFloat3("Position", pos,0.1f,-10.0f,10.0f);
        light->setPosition({pos[0],pos[1],pos[2]});
        // delete the light
        if (ImGui::Button("Delete Light") && lights.size() > 1) {
            if(lightListIndex < lights.size()-1){
                lights.erase(lights.begin()+lightListIndex);
            }
            else{
                lights.pop_back();
                lightListIndex-=1;
            }
        }
        ImGui::TreePop();
    }
}