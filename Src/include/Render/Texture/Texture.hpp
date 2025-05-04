#pragma once

#include <glad/glad.h>

#include <iostream> 
#include <cstdint> 
#include <string_view> 

using byte = unsigned char;




class Texture{
    public:
    uint32_t ID;
    int32_t m_Width, m_Height, m_Channels_original,m_Desired_original=4;


    Texture(std::string_view IMG_Path);
    ~Texture();
    
    void bind();
};