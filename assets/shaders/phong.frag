#version 410 core

#define NR_LIGHTS 10

struct Material {
    bool hasTexture;
    vec3 diffuse;
    vec3 specular;
    sampler2D  diffuseTex;
    sampler2D  specularTex;
    float shininess;
    float specularStrength;
};

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


out vec4 FragColor;

in vec3 FragPos_frag;
in vec3 Normal_frag;
in vec2 TexCoords_frag;
in vec4 FragPos_lightSpace_frag[5];

uniform bool SSAOenabled;
uniform vec3 viewPos;
uniform vec2 screenSize;

uniform sampler2D SSAOTexture;
uniform sampler2D shadowMap[5];

uniform Material material;
uniform Light lights[NR_LIGHTS];


vec3 Calclight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ComputeShadow(vec3 lightDir, int sMapId);

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos_frag);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_LIGHTS; i++)
        if(lights[i].enabled)
            result += Calclight(lights[i], Normal_frag, FragPos_frag, viewDir);    

    FragColor = vec4(result, 1.0);
}

// Calculate values for point lights
vec3 Calclight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
 
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
    if(SSAOenabled){
        float AOfactor = texture(SSAOTexture,vec2(gl_FragCoord.x/screenSize.x,gl_FragCoord.y/screenSize.y)).r;
        ambient *= vec3(AOfactor);
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

    float shadow = 0;
    // if light has shadow map
    if(light.shadowMapId>=0){
        shadow = ComputeShadow(lightDir,light.shadowMapId);
    }

    return (ambient + (1.0-shadow)*(diffuse + specular));
}

float rand(vec2 co){
  return 1/exp(fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453));
}


float ComputeShadow(vec3 lightDir, int sMapId){
    vec3 projCoords = FragPos_lightSpace_frag[sMapId].xyz / FragPos_lightSpace_frag[sMapId].w;
    projCoords = projCoords * 0.5 + 0.5;

    //depth bias against acne
    float bias = max(0.006 * (1.0 - dot(Normal_frag, lightDir)), 0.006);


    //get half of tex res for sampling
    float offset = textureSize(shadowMap[sMapId],0).x*0.5;
    
    float lightDepth;
    float shadow = 0;
    // test for each sample point
    int samples = 16;
    for(int i = 0; i<samples; i++){

        vec2 rnd = vec2(rand(projCoords.xy*float(i)), rand(projCoords.yx*float(i+1)));

        lightDepth = texture(shadowMap[sMapId], projCoords.xy+(rnd/offset) ).x;
        if(projCoords.z > lightDepth  + bias){
            shadow += 1/float(samples);
        }
    }

    return shadow;  
}