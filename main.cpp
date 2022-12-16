#include "chess/game.hpp"

#include "graphics/gui.hpp"
#include "graphics/model.hpp"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main(){

    GLFWwindow* window;
    Gui gui;
    
    // IMPORTANT: Remember how you use this pointer
    // i.e. where you create, where you assin, how you retain the pointer variable is still valid
    // if the window is created appropriately (e.g. w.r.t GLEWInit(), glfwMakeContextCurrent(window), etc
    // For now it works, but might need to use glfwSetWindowUserPointer(), glfwGetWindowUserPointer()
    // https://discourse.glfw.org/t/what-is-a-possible-use-of-glfwgetwindowuserpointer/1294/2
    window = gui.gui_window;

    // Create new vertex buffer

    DrawableModel dqueen, lrook;

    float vertex_data[] = {
     -50.0,  -50.0, 0.0, 0.0,
      50.0,  -50.0, 1.0, 0.0,
      50.0,   50.0, 1.0, 1.0,
     -50.0,   50.0, 0.0, 1.0
    };

    unsigned int index_data[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Creating va, vb, layout using abstraction
    VertexArray va_dqueen, va_lrook;
    VertexBuffer vb_dqueen(vertex_data, 4 * 4 * sizeof(float));  //4 vertices, 4 float data per vertices
    VertexBuffer vb_lrook(vertex_data, 4 * 4 * sizeof(float));   //4 vertices, 4 float data per vertices, all models might not have same vb 



    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
    VertexBufferLayout layout_dqueen;
    layout_dqueen.push<float>(2); //for x, y
    layout_dqueen.push<float>(2); //for texture u, v
    va_dqueen.addBuffer(vb_dqueen, layout_dqueen);

    va_lrook.addBuffer(vb_dqueen, layout_dqueen);

    glm::vec3 translation_1(100, 100, 0);
    glm::vec3 translation_2(200, 200, 0);

    glm::mat4 model = glm::mat4(1.0);

    // glm::mat4 mvp = proj * view * model;

    // Creating ibo
    IndexBuffer ib_dqueen(index_data, 6);
    IndexBuffer ib_lrook(index_data, 6);

    // The path of the is with respect to ZR/opengl/build/.
    Shader shader_dqueen("../res/dark.shader");
    shader_dqueen.bind();
    shader_dqueen.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);

    Shader shader_lrook("../res/light.shader");
    shader_lrook.bind();
    shader_lrook.setUniform4f("u_color", 0.0, 0.1, 0.2, 0.0);
    
    // shader.setUniformMat4f("u_MVP", mvp);

    Texture texture_rl("../assets/Chess_rlt45.svg.png");                          //https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces
    Texture texture_qd("../assets/Chess_qdt45.svg.png");
    texture_qd.bind();
    shader_dqueen.setUniform1i("u_texture", 0);
    shader_lrook.setUniform1i("u_texture", 0);//??????????????????????????????????????????????????????s
    //If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered 
    // depending on the program logic
    va_dqueen.unbind();
    vb_dqueen.unbind();
    ib_dqueen.unbind();
    shader_dqueen.unbind();

    va_lrook.unbind();
    vb_lrook.unbind();
    ib_lrook.unbind();
    shader_lrook.unbind();

    Renderer renderer;


    // Utility variables
    static bool exit_flag = false;
    float r = 0.0f;
    float increament = 0.0025f;

    /* Loop until the user closes the window */
    while (!exit_flag){
        r += increament;
        if (r > 0.25 || r < 0) increament *= -1;
        exit_flag = glfwWindowShouldClose(window);
        processInput(window);
        /* Render here */
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + translation_1);
            glm::mat4 mvp = gui.proj * gui.view * model;
            // Following shader binding is actually refactored / solved using Materials
            shader_dqueen.bind();
            // shader.setUniform1i("u_texture", 0);
            shader_dqueen.setUniformMat4f("u_MVP", mvp);
            shader_dqueen.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va_dqueen, ib_dqueen, shader_dqueen, texture_qd);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + translation_2);
            glm::mat4 mvp = gui.proj * gui.view * model;

            shader_lrook.bind();
            // shader.setUniform1i("u_texture", 0);
            shader_lrook.setUniformMat4f("u_MVP", mvp);
            shader_lrook.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va_lrook, ib_lrook, shader_lrook, texture_rl);
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        renderer.clear();
        glfwPollEvents();
    }


    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
