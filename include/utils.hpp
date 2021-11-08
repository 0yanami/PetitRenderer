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

static unsigned int loadCubeMapTexture(std::string _directory,
                                       std::string _ext) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // std::string texnames[6]{
    //	"right.",
    //	"left.",
    //	"top.",
    //	"bottom.",
    //	"front.",
    //	"back."
    //};

    std::vector<glm::vec2> texCoords{{3.0, 1.0}, {1.0, 1.0}, {1.0, 0.0},
                                     {1.0, 2.0}, {2.0, 1.0}, {0.0, 1.0}};

    int width, height, nrComponents;

    std::string fname = "textures/cubemaps/2/plain.jpg";
    std::cout << fname << std::endl;
    unsigned char* data =
        stbi_load(fname.c_str(), &width, &height, &nrComponents, 0);
    std::cout << width << "x" << height << "x" << nrComponents << std::endl;
    if (data) {
        size_t tileSize = width / 4;
        std::cout << "tilesize: " << tileSize << std::endl;
        std::vector<unsigned char> subImg;
        // subImg.reserve(tileSize*tileSize*3); TODO:
        for (size_t i = 0; i < 6; i++) {  // pour chaque image

            size_t decY = (tileSize * texCoords[i].y) * (nrComponents * width);
            size_t decX = tileSize * texCoords[i].x * nrComponents;

            std::cout << "start img " << i << std::endl;
            for (size_t j = decY; j < decY + (nrComponents * width * tileSize);
                 j += (nrComponents * width)) {  // decalage vertical 3*width
                for (size_t k = decX; k < decX + (tileSize * nrComponents);
                     k += nrComponents) {               // decalage horizontal
                    subImg.push_back(data[j + k]);      // r
                    subImg.push_back(data[j + k + 1]);  // g
                    subImg.push_back(data[j + k + 2]);  // b
                }
            }
            //if (i == 2) {  // rotate top
            //    std::vector<unsigned char> temp;
            //    for (size_t j = 0; j <  ; j += 3) {  // rows
            //        for (size_t k = 0; k < tileSize * tileSize * 3; k += tileSize * 3) {  // columns TODO:
            //            temp.push_back(subImg[k + j]);
            //            temp.push_back(subImg[k + j + 1]);
            //            temp.push_back(subImg[k + j + 2]);
            //        }
            //    }
            //    subImg = temp;
            //}
			 std::cout << "subimg " << i << " size: " << subImg.size()
                      << std::endl;
            if (i == 3) {  // rotate bottom
                std::vector<unsigned char> temp{};
                for (size_t j = tileSize-1 ; j >= 0; j -= 1) {
					
                    for (size_t k = 0; k < tileSize * tileSize ; k += tileSize ) {
						std::cout << (k + j) << std::endl;
                        temp.push_back(subImg[(k + j)*3 ]);
                        temp.push_back(subImg[(k + j)*3 +1 ]);
						temp.push_back(subImg[(k + j)*3 +2 ]);
                    }
                }
                subImg = temp;
            }
            std::cout << "subimg " << i << " size: " << subImg.size()
                      << std::endl;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                         tileSize, tileSize, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         &(subImg[0]));
            subImg.clear();
        }

        // std::cout << "texture[" << textureID <<"] loaded with path: " << path
        // << std::endl;
        stbi_image_free(data);
        std::cout << "Texture loaded at path: " << fname << std::endl;

    } else {
        std::cout << "Texture failed to load at path: " << fname << std::endl;
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
}

#endif