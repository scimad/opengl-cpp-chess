# OpenGL-CPP-Chess

Keywords: OpenGL, Chess, CPP, OpenGL-Chess, C++ Game Development

All knowledge is derived. All time is borrowed. Acknowledgement to Cherno and Ekbana. All glories to the Divine.

This is a simple (and very bad implementation) of the Chess Game (which is not even complete and even contains many bugs, such as in en-passant rule). This project was done as a refresher of some basic C++ and OpenGL stuffs. No specific game representaion was used though most stuffs are written in a piece centric manner. One may find the project to be:

* too much Object Oriented than required
* too generalized for the OpenGL rendering part
* too cryptic on the gameplay and rules implementation part
* inefficient in different ways
* badly programmed, wrong and even misleading.

Disclaimer is that this hobby project is not meant to be better than existing implementations in anyway and is here just for educational purpose. It's unlikely that the project will be continued further but let's keep the possibility open. I wanted to implement a version where users can play this over network, but like many things in my life, this remains incomlete.

While I didn't complete the project, I really learned and practiced quite a few new things:

* Different intermediate level C++ stuffs (including but not limited to smart pointers, forward declaration, STL containers, macros, enums, typecasting, C++ standards, etc.)
* C++ Project source organization (specially for Games, including assets, source files, CMakeLists, etc)
* Basic theory of OpenGL (Buffers and Buffer Layout, Rendering, MVP stuffs, libraries related / associated with OpenGL (such as GLM))
* Basic introduction to Game-Engine and game-engine development
* Oh, I almost forgot, the debugger!! Amazing stuff!

One may use this code in anyway they like and make this code as their own, except for the inspiration taken from `TheCherno` for the OpenGL part.

Side Notes (Kept for personal and / or acknowledgement purpose):

* ^1 :

i.e. where you create, where you assin, how you retain the pointer variable is still valid
if the window is created appropriately (e.g. w.r.t GLEWInit(), glfwMakeContextCurrent(window), etc
For now it works, but might need to use glfwSetWindowUserPointer(), glfwGetWindowUserPointer()
https://discourse.glfw.org/t/what-is-a-possible-use-of-glfwgetwindowuserpointer/1294/2

* ^2 :

Why VertexBuffer Layout is need is explained [here](https://youtu.be/x0H--CL2tUI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=800)

* ^3:
Downloaded from [here](https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces)


Email: scimad2.71@gmail.com (Madhav Om)
