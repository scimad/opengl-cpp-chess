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
    
    //IMPORTANT: Remember how you use this pointer ^1
    window = gui.gui_window;

    DrawableModel dqueen_model;
    VertexArray va_dqueen;
    VertexBuffer vb_dqueen(dqueen_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices
    VertexBufferLayout layout_dqueen;
    layout_dqueen.push<float>(2); //for x, y
    layout_dqueen.push<float>(2); //for texture u, v
    va_dqueen.addBuffer(vb_dqueen, layout_dqueen);
    IndexBuffer ib_dqueen(dqueen_model.index_data, 6);
    Shader shader_dqueen("../res/dark.shader");
    shader_dqueen.bind();
    shader_dqueen.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    Texture texture_dqueen("../assets/Chess_qdt45.svg.png"); // ^3
    texture_dqueen.bind();
    shader_dqueen.setUniform1i("u_texture", 0);
    /* If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered
    // depending on the program logic*/
    // va_dqueen.unbind();
    // vb_dqueen.unbind();
    // ib_dqueen.unbind();
    // shader_dqueen.unbind();

    DrawableModelV2 lrook_model;
    VertexArray va_lrook;
    VertexBuffer vb_lrook(lrook_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices, all models might not have same vb   
    // Following code reproduces the bug (i.e. the vertex buffer must for some reason be initialized at the time of creation. Why?)
    // VertexBuffer vb_lrook;
    // vb_lrook = VertexBuffer(lrook_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices, all models might not have same vb    
    VertexBufferLayout layout_lrook;
    layout_lrook.push<float>(2); // for x, y
    layout_lrook.push<float>(2); // for texture u, v
    va_lrook.addBuffer(vb_lrook, layout_lrook);
    IndexBuffer ib_lrook(lrook_model.index_data, 6);
    Shader shader_lrook("../res/light.shader");
    shader_lrook.bind();
    shader_lrook.setUniform4f("u_color", 0.0, 0.1, 0.2, 0.0);
    Texture texture_lrook("../assets/Chess_rlt45.svg.png"); // ^3
    texture_lrook.bind();
    shader_lrook.setUniform1i("u_texture", 0);

    /* If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered
    // depending on the program logic
    */
    // va_lrook.unbind();
    // vb_lrook.unbind();
    // ib_lrook.unbind();
    // shader_lrook.unbind();



    DrawableModel dking_model;
    VertexArray va_dking;
    VertexBuffer vb_dking(dking_model.vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices
    VertexBufferLayout layout_dking;
    layout_dking.push<float>(2); //for x, y
    layout_dking.push<float>(2); //for texture u, v
    va_dking.addBuffer(vb_dking, layout_dking);
    IndexBuffer ib_dking(dking_model.index_data, 6);
    Shader shader_dking("../res/dark.shader");
    shader_dking.bind();
    shader_dking.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    Texture texture_dking("../assets/Chess_kdt45.svg.png"); // ^3
    texture_dking.bind();
    shader_dking.setUniform1i("u_texture", 0);
    /* If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered
    // depending on the program logic*/
    // va_dking.unbind();
    // vb_dking.unbind();
    // ib_dking.unbind();
    // shader_dking.unbind();

    glm::vec3 translation_1(100, 100, 0);
    glm::vec3 translation_2(200, 200, 0);
    glm::mat4 model = glm::mat4(1.0);

    // glm::mat4 mvp = proj * view * model;

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
            renderer.old_draw(va_dqueen, ib_dqueen, shader_dqueen, texture_dqueen);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + translation_2);
            glm::mat4 mvp = gui.proj * gui.view * model;

            shader_lrook.bind();
            // shader.setUniform1i("u_texture", 0);
            shader_lrook.setUniformMat4f("u_MVP", mvp);
            shader_lrook.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va_lrook, ib_lrook, shader_lrook, texture_lrook);
        }


        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(450, 300, 0) + translation_1);
            glm::mat4 mvp = gui.proj * gui.view * model;
            // Following shader binding is actually refactored / solved using Materials
            shader_dking.bind();
            // shader.setUniform1i("u_texture", 0);
            shader_dking.setUniformMat4f("u_MVP", mvp);
            shader_dking.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va_dking, ib_dking, shader_dking, texture_dking);
        }

        


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        renderer.clear();
        glfwPollEvents();
    }

    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}
