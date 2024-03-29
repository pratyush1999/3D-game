#include "airplane.h"
#include "main.h"

Airplane::Airplane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 20;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float w=0.5;
    float fac=0.5;
    static const GLfloat vertex_buffer_data[] = {
        -1.0f*fac,-1.0f*fac,-1.0f, // triangle 1 : begin
        -1.0f*fac,-1.0f*fac, 1.0f,
        -1.0f*fac, 1.0f*fac, 1.0f, // triangle 1 : end
        1.0f*fac, 1.0f*fac,-1.0f, // triangle 2 : begin
        -1.0f*fac,-1.0f*fac,-1.0f,
        -1.0f*fac, 1.0f*fac,-1.0f, // triangle 2 : end
        1.0f*fac,-1.0f*fac, 1.0f,
        -1.0f*fac,-1.0f*fac,-1.0f,
        1.0f*fac,-1.0f*fac,-1.0f,
        1.0f*fac, 1.0f*fac,-1.0f,
        1.0f*fac,-1.0f*fac,-1.0f,
        -1.0f*fac,-1.0f*fac,-1.0f,
        -1.0f*fac,-1.0f*fac,-1.0f,
        -1.0f*fac, 1.0f*fac, 1.0f,
        -1.0f*fac, 1.0f*fac,-1.0f,
        1.0f*fac,-1.0f*fac, 1.0f,
        -1.0f*fac,-1.0f*fac, 1.0f,
        -1.0f*fac,-1.0f*fac,-1.0f,
        -1.0f*fac, 1.0f*fac, 1.0f,
        -1.0f*fac,-1.0f*fac, 1.0f,
        1.0f*fac,-1.0f*fac, 1.0f,
        1.0f*fac, 1.0f*fac, 1.0f,
        1.0f*fac,-1.0f*fac,-1.0f,
        1.0f*fac, 1.0f*fac,-1.0f,
        1.0f*fac,-1.0f*fac,-1.0f,
        1.0f*fac, 1.0f*fac, 1.0f,
        1.0f*fac,-1.0f*fac, 1.0f,
        1.0f*fac, 1.0f*fac, 1.0f,
        1.0f*fac, 1.0f*fac,-1.0f,
        -1.0f*fac, 1.0f*fac,-1.0f,
        1.0f*fac, 1.0f*fac, 1.0f,
        -1.0f*fac, 1.0f*fac,-1.0f,
        -1.0f*fac, 1.0f*fac, 1.0f,
        1.0f*fac, 1.0f*fac, 1.0f,
        -1.0f*fac, 1.0f*fac, 1.0f,
        1.0f*fac,-1.0f*fac, 1.0f,
    };
    float fac1=1.5;
        static const GLfloat wings_vertex_buffer_data[] = {
        //wings
        2.0f*fac*fac1, 0.0f*fac, 0.0f,
        1*fac,w*fac,w,
        1*fac,-w*fac,w,

        2.0f*fac*fac1, 0.0f*fac, 0.0f,
        1*fac,w*fac,w,
        1*fac,w*fac,-w,

        2.0f*fac*fac1, 0.0f*fac, 0.0f,
        1*fac,w*fac,-w,
        1*fac,-w*fac,-w,

        2.0f*fac*fac1, 0.0f*fac, 0.0f,
        1*fac,-w*fac,-w,
        1*fac,-w*fac,w,


        -2.0f*fac*fac1, 0.0f*fac, 0.0f,
        -1*fac,w*fac,w,
        -1*fac,-w*fac,w,

        -2.0f*fac*fac1, 0.0f*fac, 0.0f,
        -1*fac,w*fac,w,
        -1*fac,w*fac,-w,

        -2.0f*fac*fac1, 0.0f*fac, 0.0f,
        -1*fac,w*fac,-w,
        -1*fac,-w*fac,-w,

        -2.0f*fac*fac1, 0.0f*fac, 0.0f,
        -1*fac,-w*fac,-w,
        -1*fac,-w*fac,w
    };
                int n1=100, n=100;
                        int i=0;
                                float z1=-1.0f;
                                        double radius=0.5;
    GLfloat rear_vertex_buffer_data[9*n*n1];
    for (int z = 0; z < n1; ++z)
    {
        double theta=0;
        double angle=(2*3.1416)/n;
        while(i<9*n*(z+1))
        {
            rear_vertex_buffer_data[i++]=0.0f;
            rear_vertex_buffer_data[i++]=0.0f;
            rear_vertex_buffer_data[i++]=z1;

             rear_vertex_buffer_data[i++]=radius*cos(theta)*fac;
            rear_vertex_buffer_data[i++]=radius*sin(theta)*fac;
            rear_vertex_buffer_data[i++]=z1;
            theta+=angle;
            rear_vertex_buffer_data[i++]=radius*cos(theta)*fac;
            rear_vertex_buffer_data[i++]=radius*sin(theta)*fac;
            rear_vertex_buffer_data[i++]=z1;
        }
        z1-=0.01f;
    }
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
     this->wings = create3DObject(GL_TRIANGLES, 8*3, wings_vertex_buffer_data, COLOR_GREEN, GL_FILL);
          this->rear = create3DObject(GL_TRIANGLES, 3*n*n1, rear_vertex_buffer_data, COLOR_GREEN, GL_FILL);

}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->wings);
    draw3DObject(this->rear);
}

void Airplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Airplane::tick() {
   // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

