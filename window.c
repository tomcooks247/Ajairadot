#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

// Global Variables

// Function Declarations

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void createVS(unsigned int* vs, const char *vss);
void createFS(unsigned int* fs, const char *fss);
void createSP(unsigned int* vs, unsigned int* fs, unsigned int* sp);

int main() {
	glfwInit();
	
	// Defining which OpenGL version is going to be used
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Creating a window
	int w = 800, h = 600;
	GLFWwindow* window = glfwCreateWindow(w, h, "test", NULL, NULL);

	// Making the created window root and setting
	// Key callback functionalities for inputs
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	// The shaders are temporarily residing here now hardcoded
	const char *vss = "#version 300 es\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main () {\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"}";

	const char *fss = "#version 300 es\n"
	"precision mediump float;\n"
	"out vec4 FragColor;\n"
	"void main () {\n"
	"	FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
	"}";

	// Temporary variables to create a simple green triangle
	unsigned int vs, fs, sp, vao, vbo;
	float vertices[] = {
		0.0, 0.5, 0.0,      // top
		0.25, 0.0, 0.0,    //  right
		-0.25, 0.0, 0.0   //   left
	};

	createVS(&vs, vss);
	createFS(&fs, fss);
	createSP(&vs, &fs, &sp);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0 );
	glEnableVertexAttribArray(0);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0, 0.3, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);

		glBindVertexArray(vao);
		glUseProgram(sp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleaning up after the Render loop
	glfwDestroyWindow(window);
	glfwTerminate();
}

//Function Definitions

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void createVS(unsigned int* vs, const char *vss) {
	*vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vs, 1, &vss, NULL);
	glCompileShader(*vs);
}

void createFS(unsigned int* fs, const char *fss) {
	*fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fs, 1, &fss, NULL);
	glCompileShader(*fs);
}

void createSP(unsigned int* vs, unsigned int* fs, unsigned int* sp) {
	*sp = glCreateProgram();
	glAttachShader(*sp, *vs);
	glAttachShader(*sp, *fs);
	glLinkProgram(*sp);
}
