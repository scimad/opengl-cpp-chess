#include "chess/game.hpp"

// int main() {
//     ChessGame game;
//     game.run();
// }


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
    
    ChessGame game;



    // Choose OpenGL version and setup either compatibility profile or core profile 
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));      // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLCALL(GLFWwindow *window = glfwCreateWindow(960, 540, "ZR :: Cherno-OpenGL", NULL, NULL));

    if (!window){
        zr::log("Failed to create GLFW window.", zr::VERBOSITY_LEVEL::ERROR);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    zr::log("Successfully created GLFW window.");

    // glfwSwapInterval(1);

    // Initialize GLEW
    GLenum err = glewInit();                      //Must do after glfwMakeContextCurrent() or alternatively after properly initializing GLUT
    if (GLEW_OK != err){
        zr::log("Failed to initialize GLEW. Err: " + std::string((const char*)(glewGetErrorString(err))), zr::VERBOSITY_LEVEL::WARNING);
        glfwTerminate();
        return -1;
    }
    zr::log("Successfully initialized GLEW.");
    zr::log("OpenGL Version: " + std::string((const char*) glGetString(GL_VERSION)));

    glClearColor(0.2, 0.2, 0.2, 0.0);

    // Create new vertex buffer
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

    // This gives transparency to transparent regions of pngs
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Creating va, vb, layout using abstraction
    VertexArray va;
    VertexBuffer vb(vertex_data, 4 * 4 * sizeof(float)); //4 vertices, 4 float data per vertices 

    // Need to tell the layout of the buffer [Explanation is here: https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800]
    VertexBufferLayout layout;
    layout.push<float>(2); //for x, y
    layout.push<float>(2); //for texture u, v
    va.addBuffer(vb, layout);

    glm::vec3 translation_1(100, 100, 0);
    glm::vec3 translation_2(200, 200, 0);

    // glm::mat4 proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // This seems to be default(?)
    glm::mat4 proj = glm::ortho(0.0, 960.0, 0.0, 540.0, -1.0, 1.0);
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 model = glm::mat4(1.0);

    // glm::mat4 mvp = proj * view * model;

    // Creating ibo
    IndexBuffer ib(index_data, 6);

    // The path of the is with respect to ZR/opengl/build/.
    Shader shader("../res/basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.0, 0.2, 0.5, 0.0);
    // shader.setUniformMat4f("u_MVP", mvp);

    Texture texture_rl("/home/scimad/Desktop/OpenGL-CPP-Chess/assets/Board.png");                          //https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces
    Texture texture_qd("/home/scimad/Desktop/OpenGL-CPP-Chess/assets/Chess_ndt45.svg.png");
    texture_qd.bind();
    shader.setUniform1i("u_texture", 0); 
    //If we have multiple vertex buffer objects and layouts to be bind within the loop, then:
    // Unbind everything here and bind the buffers individually that are to be rendered 
    // depending on the program logic
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;

    

    bool show_demo_window = true;
    bool show_another_window = false;
    
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
            glm::mat4 mvp = proj * view * model;
            // Following shader binding is actually refactored / solved using Materials
            shader.bind();
            // shader.setUniform1i("u_texture", 0);
            shader.setUniformMat4f("u_MVP", mvp);
            shader.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va, ib, shader, texture_qd);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(300, 300, 0) + translation_2);
            glm::mat4 mvp = proj * view * model;

            shader.bind();
            // shader.setUniform1i("u_texture", 0);
            shader.setUniformMat4f("u_MVP", mvp);
            shader.setUniform4f("u_color", r, 0, 0, 0.0); //if uniform is not used in shader, it gives error / notification
            renderer.old_draw(va, ib, shader, texture_rl);
        }
        // if (show_demo_window){
        //     ImGui::ShowDemoWindow(&show_demo_window);
        // }

        {
            static float f = 0.0f;
            static int counter = 0;

        }

        // // Show another simple window.
        // if (show_another_window){
        //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //     ImGui::Text("Hello from another window!");
        //     if (ImGui::Button("Close Me"))
        //         show_another_window = false;
        //     ImGui::End();
        // }

       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        renderer.clear();
        glfwPollEvents();
    }


    glfwTerminate(); // Refer to the notes on README.md of this project   
    return 0;
}