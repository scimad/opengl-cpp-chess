#include "graphics/vertex_array.hpp"

class DrawableModel
{
private:

public:
    // vertex_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    float vertex_data[16] = {
     -50.0,  -50.0, 0.0, 0.0,
      50.0,  -50.0, 1.0, 0.0,
      50.0,   50.0, 1.0, 1.0,
     -50.0,   50.0, 0.0, 1.0
    };

    // index_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    unsigned int index_data[6] = {
        0, 1, 2,
        2, 3, 0
    };
    DrawableModel(/* args */);
    ~DrawableModel();
};


class DrawableModelV2
{
private:
public:
    // vertex_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    float vertex_data[16] = {
     -50.0,  -50.0, 0.0, 0.0,
      50.0,  -50.0, 1.0, 0.0,
      50.0,   50.0, 1.0, 1.0,
     -50.0,   50.0, 0.0, 1.0
    };

    // index_data stuff should (?) be heap allocated or maybe use std::vector kinda things 
    unsigned int index_data[6] = {
        0, 1, 2,
        2, 3, 0
    };

    DrawableModelV2(/* args */);
    ~DrawableModelV2();
};