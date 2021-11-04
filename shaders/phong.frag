#version 410 core
out vec4 FragColor;

struct Material {
    vec3  diffuse;
    vec3  specular;
    float shininess;
    float specularStrength;
};


//light bulb light
struct PointLight {
    bool enabled; 
    vec3 position; 

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic; 
}; 


in vec3 FragPos_frag;  
in vec3 Normal_frag;  
in vec2 TexCoords_frag;
  
uniform vec3 viewPos;
uniform Material material;

#define NR_POINT_LIGHTS 64
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

void main(){
    
    vec3 viewDir = normalize(viewPos - FragPos_frag);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        if(pointLights[i].enabled)
            result += CalcPointLight(pointLights[i], Normal_frag, FragPos_frag, viewDir);    

    FragColor = vec4(result, 1.0);

}

// Calculate values for point lights
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(light.position - FragPos_frag);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - FragPos_frag);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			    light.quadratic * (distance * distance));    
    // combine results

    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular
                    *vec3(material.specularStrength);

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}