#version 410 core

out vec4 FragColor;

struct Material {
    bool hasTexture;
    vec3 diffuse;
    vec3 specular;
    sampler2D  diffuseTex;
    sampler2D  specularTex;
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

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos_frag);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        if(pointLights[i].enabled)
            result += CalcPointLight(pointLights[i], Normal_frag, FragPos_frag, viewDir);    

    FragColor = vec4(result, 1.0);
}

// Calculate values for point lights
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			    light.quadratic * (distance * distance));    

    vec3 ambient  = vec3(0,0,0);
    vec3 diffuse  = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    // combine results
    if(material.hasTexture){
        ambient  = light.ambient  * vec3(texture(material.diffuseTex,TexCoords_frag));
        diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseTex,TexCoords_frag));
        specular = light.specular * spec * vec3(texture(material.specularTex,TexCoords_frag))
                    *vec3(material.specularStrength);
    } else {
        ambient  = light.ambient  * material.diffuse;
        diffuse  = light.diffuse  * diff * material.diffuse;
        specular = light.specular * spec * material.specular * vec3(material.specularStrength);
    }

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}