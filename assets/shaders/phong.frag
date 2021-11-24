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


in vec3 FragPos_frag;  
in vec3 Normal_frag;  
in vec2 TexCoords_frag;
in vec4 FragPos_lightSpace_frag[5];
  
uniform vec3 viewPos;
uniform Material material;

uniform sampler2D shadowMap[5];

#define NR_LIGHTS 10
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
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float ComputeShadow(vec3 lightDir, int sMapId){
    vec3 projCoords = FragPos_lightSpace_frag[sMapId].xyz / FragPos_lightSpace_frag[sMapId].w;
    projCoords = projCoords * 0.5 + 0.5;

    //depth bias against acne
    float bias = max(0.004 * (1.0 - dot(Normal_frag, lightDir)), 0.004);

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