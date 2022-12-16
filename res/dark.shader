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

uniform vec4 u_color;
uniform sampler2D u_texture;

void main(){
    // color = u_color;

    vec4 tex_color = texture(u_texture, v_texture_uv);
    color = tex_color + u_color;
    
};
