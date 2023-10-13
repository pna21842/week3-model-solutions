
#include "core.h"
#include "MyShapes.h"
#include "RandomPoints.h"

using namespace std;

//
// Global variables
//

// Example textures
GLuint playerTexture;
GLuint blockTexture;

// Model solution for random points walkthrough
RandomPoints points = RandomPoints(100);

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;


//
// Function prototypes
//
GLuint loadTexture(string filename, FREE_IMAGE_FORMAT srcImageType);
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();


int main() {

	//
	// 1. Initialisation
	//
	
	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black


	//
	// Setup textures
	//

	// Setup textures
	playerTexture = loadTexture(string("Assets\\Textures\\player1_ship.png"), FIF_PNG);
	blockTexture = loadTexture(string("Assets\\Textures\\mcblock01.png"), FIF_PNG);

	// Setup random points
	points = RandomPoints(100);


	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}


GLuint loadTexture(string filename, FREE_IMAGE_FORMAT srcImageType) {

	// Load and validate bitmap
	FIBITMAP* loadedBitmap = FreeImage_Load(srcImageType, filename.c_str(), BMP_DEFAULT);

	if (!loadedBitmap) {

		cout << "FreeImage: Could not load image " << filename << endl;
		return 0;
	}

	// Comvert to RGBA format
	FIBITMAP* bitmap32bpp = FreeImage_ConvertTo32Bits(loadedBitmap);
	FreeImage_Unload(loadedBitmap);

	if (!bitmap32bpp) {

		cout << "FreeImage: Conversion to 32 bits unsuccessful for image " << filename << endl;
		return 0;
	}

	// Image loaded and converted - setup new texture object
	GLuint newTexture = 0;

	// If image loaded, setup new texture object in OpenGL
	glGenTextures(1, &newTexture); // can create more than 1!

	if (newTexture) {

		glBindTexture(GL_TEXTURE_2D, newTexture);

		// Setup texture image properties
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			FreeImage_GetWidth(bitmap32bpp),
			FreeImage_GetHeight(bitmap32bpp),
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			FreeImage_GetBits(bitmap32bpp));

		// Setup texture filter and wrap properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	// Once the texture has been setup, the image data is copied into OpenGL.  We no longer need the originally loaded image
	FreeImage_Unload(bitmap32bpp);

	return newTexture;
}


// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//points.render();
	//points.renderTexturedPoints(playerTexture);
	//drawTexturedQuad(blockTexture);
	//drawSemiCircleSolution();
	//drawLShape();
	drawLShape_OneStrip();
}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {
}

