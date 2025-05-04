#include <Render/Texture/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(std::string_view IMG_Path){
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    if (byte *img_data = stbi_load(IMG_Path.data(), &m_Width, &m_Height, &m_Channels_original, m_Desired_original);
        img_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Width, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(img_data); 
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

}; 

Texture::~Texture(){
    glDeleteTextures(1,&ID);
};

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D , ID);
};