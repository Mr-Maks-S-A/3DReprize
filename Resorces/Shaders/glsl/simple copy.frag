#version 450

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}


// in vec4 Color;

// out vec4 FragColor;

// void main(){  
//     FragColor = Color;  
// }





// #version 460  
// varying vec3 color;  
// void main(){  
//     gl_FragColor = vec4(color, 1.0);  
// }


// #version 450

// layout (location = 0 ) out vec4 outColor;

// void main(){
//     outColor = vec4(1.0, 0.0, 0.0, 1.0);
// }

