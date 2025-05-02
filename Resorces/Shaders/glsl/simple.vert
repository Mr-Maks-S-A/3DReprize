#version 460  

attribute vec3 vCol;  
attribute vec2 vPos;

uniform mat4 MVP;  
varying vec3 color;  

void main(){  
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);  
    color = vCol;  
}

// #version 450

// vec4 positions_x_y_z_w[3] = vec4[](
//     vec4( 0.0, -0.5, 0.0, 1.0),
//     vec4( 0.5,  0.5, 0.0, 1.0),
//     vec4(-0.5,  0.5, 0.0, 1.0)
// );

// void main(){
//     gl_Position = positions_x_y_z_w[gl_VertexIndex];
// }

