#version 410 core

// PN TRIANGLES TESSELLATION SHADER

out vec4 FragColor;

struct Material {
    bool hasTexture;
    vec3  diffuse;
    vec3  specular;
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


in vec3 FragPos_eval_out;  
in vec2 TexCoord_eval_out;  
in vec3 Normal_eval_out;
  
uniform vec3 viewPos;
uniform Material material;

#define NR_POINT_LIGHTS 64
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos_eval_out);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        if(pointLights[i].enabled)
            result += CalcPointLight(pointLights[i], Normal_eval_out, FragPos_eval_out, viewDir);    

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
    // combine results

    vec3 ambient = vec3(0,0,0);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    if(material.hasTexture){
        ambient  = light.ambient  * vec3(texture(material.diffuseTex,TexCoord_eval_out));
        diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseTex,TexCoord_eval_out));
        specular = light.specular * spec * vec3(texture(material.specularTex,TexCoord_eval_out))
                    *vec3(material.specularStrength);
    } else {
        ambient  = light.ambient  * material.diffuse;
        diffuse  = light.diffuse  * diff * material.diffuse;
        specular = light.specular * spec * material.specular *vec3(material.specularStrength);
    }

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}