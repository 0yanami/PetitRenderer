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
struct Light { 
    bool enabled;
    int shadowMapId;   
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
in vec4 Fragpos_lightSpace_eval_out[5];
  
uniform vec3 viewPos;
uniform Material material;
uniform sampler2D shadowMap[5];

uniform bool SSAOenabled;
uniform sampler2D SSAOTexture;


uniform vec2 screenSize;

#define NR_LIGHTS 10
uniform Light lights[NR_LIGHTS];

float ComputeShadow(vec3 lightDir, int sMapId);
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);  

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos_eval_out);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_LIGHTS; i++)
        if(lights[i].enabled)
            result += CalcLight(lights[i], Normal_eval_out, FragPos_eval_out, viewDir);    

    FragColor = vec4(result, 1.0);
}

// Calculate values for point lights
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
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
    
    // calculate attenuation ( constant < 0 to bypass)
    if (light.constant > 0){
        float distance    = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			    light.quadratic * (distance * distance));

        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
    }

    if(SSAOenabled){
        float AOfactor = texture(SSAOTexture,vec2(gl_FragCoord.x/screenSize.x,gl_FragCoord.y/screenSize.y)).r;
        ambient *= vec3(AOfactor);
    }
    

    float shadow = 0;
    if(light.shadowMapId>=0){
        shadow = ComputeShadow(lightDir,light.shadowMapId);
    }

    return (ambient + (1.0-shadow)*(diffuse + specular));
}

float ComputeShadow(vec3 lightDir, int sMapId){
    vec3 projCoords = Fragpos_lightSpace_eval_out[sMapId].xyz / Fragpos_lightSpace_eval_out[sMapId].w;
    projCoords = projCoords * 0.5 + 0.5;

    //depth bias against acne
    float bias = max(0.005 * (1.0 - dot(Normal_eval_out, lightDir)), 0.005);

    //samples around unit circle
    vec2 circle[8] = vec2[](
        vec2( 0.7, 0.7 ),
        vec2( -0.7, 0.7 ),
        vec2( 0.7, -0.7 ),
        vec2( -0.7, -0.7 ),
        vec2( 1, 0 ),
        vec2( 0, 1 ),
        vec2( -1, 0 ),
        vec2( 0, -1 )
    );

    //get half of tex res for sampling
    float offset = textureSize(shadowMap[sMapId],0).x*0.8;
    
    float lightDepth;
    float shadow = 0;
    // test for each sample point
    for(int i = 0; i<8; i++){

        lightDepth = texture(shadowMap[sMapId], projCoords.xy + circle[i]/offset ).x;
        if(projCoords.z > lightDepth  + bias){
            //add up shadow if point is in shadow
            shadow += 0.125;
        }
    }

    return shadow;  
}