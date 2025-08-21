/*  GLAD before GLFW.The include file for GLAD includes the required OpenGL headers
 behind the scenes (like GL/gl.h) so be sure to include GLAD before other header 
 files that require OpenGL (like GLFW).  */ 

#include<iostream>
#include<glad.h>
#include<GLFW/glfw3.h>

 // Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



// Function Prototype
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW we are using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using CORE profile, meaning modern functions only. 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Datatype is openGL's version of float. 
	GLfloat vertices[] = { -0.5f, -0.5f, 0.0f,
						 0.5f, -0.5f, 0.0f,
						 0.0f,  0.5f, 0.0f };
	
	// Create Window Object. Here, the GLFWwindow pointer type is actually an opaque struct. 
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL-proj", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << "/n";
		glfwTerminate();
		return -1;
	}

	// Introduce window to current context
	glfwMakeContextCurrent(window);
	// Renders and fills window if size changes 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD loads all OpenGL function pointers 
	gladLoadGL();

	/*  Tells OpenGL the area of the window we want to render.This goes from bottom left
	to top right corner of window. */
	glViewport(0, 0, 800, 800);

	
	
	//                        CREATING VERTEX AND FRAGMENT SHADERS:
	//-----------------------------------------------------------------------------------------

	/*  Datatype is openGL's version of unsigned int ( +ve int only ). It returns a number ID.
	 This uniquely identifies this shader in the GPU�s memory.

	 Here, we create a vertex shader object. It returns the reference value of the object. 
	 Shaders are openGL objects that are in the background and the only way to access them is 
	 through references. This applies to all openGL objects. */ 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/* Now that we have the obj, we can store the source code string inside it. The 1 is to say
	that the entire source code is in a single string. Null is added to tell openGL that each 
	string ends with a null terminator, i.e it is a standard c string. Hence we don't 
	have to manually input the length of each string individually in the case that we pass the 
	source code as multiple strings. Rather, we just tell openGL to look for the null terminator. */
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);


	/* So far, all we have done is store the code in the shader object's memory on the GPU.
	   Now we need to compile that code. */
	glCompileShader(vertexShader);

	
	
	// Now do the same for fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Wrapping them up into one unified SHADER PROGRAM
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//This is what sets up our graphics pipeline. It links the shaders. It checks if 
	//the outputs of the vertex shader match the inputs of the fragment shader and combines it 
	//  into one GPU-executable program.
	glLinkProgram(shaderProgram);

	//Now that we've stored everything we need in the shaderProgram, we can delete 
	// the vertex and fragment shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------



	
	
	//                            SENDING INFORMATION TO THE GPU:
	//--------------------------------------------------------------------------------------------
	/* So far, we've defined vertex data and told the GPU how to process vertex data within 
	   the vertex and fragment shaders, but we haven't actually sent any of this data to the GPU.
	   Since sending information between the CPU and GPU adds a lot of overhead, we create a 
	   vertex buffer so that we can send all vertices at once and not one by one so that the GPU
	   can process data directly from the buffer without extra CPU calls. */

	// Here we create a vertex buffer object where we'll store our vertex data. 
	// But BEFORE that, we also create a vertex array object to store all our VBOs. For more info,
	// skip to comment after glBufferData(). 

	// We use glGenBuffers to make the buffer object, put 1 as a parameter to imply we're 
	// storing vertices of only one 3D object, put address of VBO as next parameter to store  
	// unique ID of buffer.
	GLuint VAO = 0;
	
	GLuint VBO = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	
	/* Next, we bind. 
     
	 What exactly is binding? 
	 The first time you bind an object is when the object is created. 
	 That is because "glGen*" functions don't actually create an object, 
	 they instead create a name for an object (like creating a new unique ID number.) 
	 The object only actually gets created when you first bind it.

     Read more here: https://tinyurl.com/gl-binding

	 OpenGL has many types of buffer objects and the buffer type of a vertex 
	 buffer object is GL_ARRAY_BUFFER.OpenGL allows us to bind to several buffers at 
	 once as long as they have a different buffer type. 

	 We can bind the newly created buffer to the GL_ARRAY_BUFFER target with the 
	 glBindBuffer function.When you bind a buffer to GL_ARRAY_BUFFER, that buffer 
	 is now considered the active �vertex data� buffer.  */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Next, we store data in VBO. The fourth parameter specifies how we want the graphics card 
	to manage the given data. This can take 3 forms:

    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.

      The position data of the triangle does not change, is used a lot, and stays the same for 
	  every render call so its usage type should best be GL_STATIC_DRAW. If, for instance, 
	  one would have a buffer with data that is likely to change frequently, a usage type of 
	  GL_DYNAMIC_DRAW ensures the graphics card will place the data in memory that allows for 
	  faster writes. */	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* In this program, we only have 1 object to render and hence only need one VBO. In future 
	   programs, we may want to render more than 1 object. In that case, it is tiresome to 
	   manually bind another VBO to GL_ARRAY_BUFFER over and over again depending on how many 
	   objects there are. Therefore, it is in best practice to use vertex array objects starting 
	   now so that switching between VBOs becomes a smoother process.
	   
	   VAO has already been created before VBO and has been binded (as in it is the active object
	   in use by openGL now) .
	   
	   Now we need to tell openGL how to read the VBO which is storing our vertices.
	   This is covered best in the "Hello Window" section of learnopengl.com. 

	   In short, 
	   1st parameter is the index of the vertex attribute we want to use. 
	   2nd is how many values per vertex.
	   3rd is the datatype of our vertices.
	   4th is if we're using integers or not. We're not. 
	   5th is the length of each vertex attribute. Since we have 3 co-oords, size is 3*float
	   6th is the offset of where the position data begins in the buffer. 
	   Since the position data is at the start of the data array this value is just 0. 
	    */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Just to stay safe, lets unbind our VOA and VBA so that we don't accidently overwrite them
	// if the function is called anywhere else in the program. 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------






	//                                     RENDER LOOP:
	// As long as the window doesn't close,glfw tells OpenGL to keep processing GLFWwindow events.
	//-------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
	
		// Read fun def. It checks for esc_key press. If pressed, window closes. 
		processInput(window);

		/*  This tells OpenGL to prepare to clear front color buffer for a new one (Setting back
	        color buffer).
	        First 3 numbers are rgb values, last is for opacity; 1 max, 0 min. */
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// This executes the command to set back color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//-------------Using all functions we made so far-----------------

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// 1-type of primitive to draw, 2-index starting point, 3-number of vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//----------------------------------------------------------------

		// This swaps front and back buffer 
		glfwSwapBuffers(window);

		// Poll IO events (keys pressed/released, mouse moved etc.)
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	
	
	glfwDestroyWindow(window);
	

	glfwTerminate();

	
	
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}