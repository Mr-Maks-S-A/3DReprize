#include <Mesh/Mesh.hpp>



Mesh::Mesh(std::vector<float>& buffer, std::vector<uint32_t>& attrib_size){
    this->vert_size = 0;
    for(uint32_t var :  attrib_size) vert_size += var;

    this->number_of_vertices = buffer.size()/vert_size;
    
    glGenVertexArrays(1,&this->VAO);
    glGenBuffers(1,&this->VBO);
    

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER 
        ,sizeof(float) * buffer.size()
        ,buffer.data()
        ,GL_STATIC_DRAW);
        
        //Attrib
        for(int offset = 0, i = 0; i < attrib_size.size(); ++i){
            glVertexAttribPointer(i,attrib_size[i],GL_FLOAT,GL_FALSE,vert_size * sizeof(float), (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
            offset+= attrib_size[i];
        };

    glBindVertexArray(0);        
};

void Mesh::draw(){
    use();
    glDrawArrays(GL_TRIANGLES,0,number_of_vertices);
    unuse();
};
void Mesh::use(){
    glBindVertexArray(this->VAO);     
};
void Mesh::unuse(){
    glBindVertexArray(0);     
};





Mesh::~Mesh(){
    glDeleteVertexArrays(1,&this->VAO);
    glDeleteBuffers(1,&this->VBO);
};