#include "light.hpp"

Light::Light(glm::vec3 _position, glm::vec3 _color){
        position = _position;

        diffuse = _color;
        ambiantStrength = 0.25f;
        specular = glm::vec3(1.0f, 1.0f, 1.0f);

        constant = 1.0f;
        linear = 0.22f;
        quadratic = 0.2f;
}