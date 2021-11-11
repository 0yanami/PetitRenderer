#ifndef UTILS_H
#define UTILS_H

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>
#endif
#include <glad/glad.h>

#include <iostream>

static unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = GL_RGBA;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // std::cout << "texture[" << textureID <<"] loaded with path: " << path
        // << std::endl;
        stbi_image_free(data);
    } else {
        std::cout
            << "Texture failed to load at path: " << path << std::endl
            << "For more info, check CubeMap's documentation on file naming."
            << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

static unsigned int loadCubeMapTexture(std::string _directory) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    std::string texnames[6]{"right",  "left",  "top",
                            "bottom", "front", "back"};
    
    std:: string exts[3] {".png",".jpg",".jpeg"};
    std::string fname;
    unsigned char* data;

    int width, height, nrComponents;
    for (int i = 0; i < 6; i++) {

        for(int j = 0 ; j<3; j++){ //check extension
            fname = _directory+texnames[i]+exts[j];
            std::cout << fname << std::endl;
            data = stbi_load(fname.c_str(), &width, &height, &nrComponents, 0);
            if(data){break;}
        }

        std::cout << fname << std::endl;
        std::cout << width << "x" << height << "x" << nrComponents << std::endl;

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            
            stbi_image_free(data);
            std::cout << "Texture loaded at path: " << fname << std::endl;

        } else {
            std::cout << "Texture failed to load at path: " << fname
                      << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
}

#endif