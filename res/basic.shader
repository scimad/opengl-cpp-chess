#shader vertex
#version 330 core
layout(location = 0) in vec4 position;		//taking in from vertex buffer
layout(location = 1) in vec2 texture_uv;		//taking in from vertex buffer

out vec2 v_texture_uv;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * position;
    v_texture_uv = texture_uv;
};


#shader fragment
#version 330 core
layout (location = 0) out vec4 color;
in vec2 v_texture_uv;

uniform vec4 u_highlight_color;
uniform int square_type;

uniform sampler2D u_texture;

void main(){
    vec4 tex_color = texture(u_texture, v_texture_uv);
    color = tex_color;
    if (square_type == 1){         // selected piece
        if ((color.a != 0.0)){
            color = 0.2 * color + 0.8 * u_highlight_color;
        }
        else
        {
            color = 0.3 * u_highlight_color;;
        }
    } else if (square_type == 2) { // normal legal move to empty square
        color = vec4(0.0, 0.8, 0.0, 0.25);
    } else if (square_type == 3) { // capturing square
        color = vec4(1.0, 0, 0, 1.0);
    } else if (square_type == 4) { // castling square
        color = vec4(1.0, 0, 0, 1.0);
    } else if (square_type == 5) { // check square
        color = vec4(0.9, 0.0, 0.0, 0.6);
    }

};
