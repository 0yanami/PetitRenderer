#version 410 core
#define NR_LIGHTS 10


// PHONG SHADER


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

in vec3 FragPos_in;
in vec2 TexCoords_in;
in vec3 Normal_in;
in vec4 FragPos_lightSpace_in[5];
  
uniform vec3 viewPos;
uniform vec2 screenSize;
uniform float exposure;

// SSAO
uniform bool SSAOenabled;
uniform sampler2D SSAOTexture;

uniform sampler2D shadowMap[5];

uniform Light lights[NR_LIGHTS];
uniform Material material;


vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ComputeShadow(vec3 lightDir, int sMapId);

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos_in);
    vec3 result = vec3(0,0,0);

    for(int i = 0; i < NR_LIGHTS; i++)
        if(lights[i].enabled)
            result += CalcLight(lights[i], Normal_in, FragPos_in, viewDir);    

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
  
    
    vec3 ambient = vec3(0,0,0);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);

    float gamma = 2.2;

    vec3 diffuseColor;
    vec3 specularColor;
    if(material.hasTexture){
        diffuseColor = pow(texture(material.diffuseTex,TexCoords_in).rgb,vec3(gamma));
        specularColor = pow(texture(material.specularTex,TexCoords_in).rgb,vec3(gamma));
        
    } else {
        diffuseColor = pow(material.diffuse,vec3(gamma));
        specularColor = pow(material.specular,vec3(gamma));
    }
    diffuseColor = vec3(1.0) - exp(-diffuseColor * exposure);
    specularColor = vec3(1.0) - exp(-specularColor * exposure);

    diffuseColor = pow(diffuseColor, vec3(1.0 / gamma));
    specularColor = pow(specularColor, vec3(1.0 / gamma));

    ambient  = light.ambient  * diffuseColor;
    diffuse  = light.diffuse  * diff * diffuseColor;
    specular = light.specular * spec * specularColor *vec3(material.specularStrength);


    if(SSAOenabled){
        float AOfactor = texture(SSAOTexture,vec2(gl_FragCoord.x/screenSize.x,gl_FragCoord.y/screenSize.y)).r;
        ambient *= vec3(AOfactor);
    }

    // calculate attenuation ( constant < 0 to bypass)
    if (light.constant > 0){
        float distance    = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			    light.quadratic * (distance));

        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
    }

    float shadow = 0;
    if(light.shadowMapId>=0){
        shadow = ComputeShadow(lightDir,light.shadowMapId);
    }

    return (ambient + (1.0-shadow)*(diffuse + specular));
}


float rand(vec2 co){
  return 1/exp(fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453));
}

float ComputeShadow(vec3 lightDir, int sMapId){
    vec3 projCoords = FragPos_lightSpace_in[sMapId].xyz / FragPos_lightSpace_in[sMapId].w;
    projCoords = projCoords * 0.5 + 0.5;

    //depth bias against acne
    float bias = max(0.006 * (1.0 - dot(Normal_in, lightDir)), 0.006);


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