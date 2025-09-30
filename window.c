#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	int w = 800, h = 600;
	GLFWwindow* window = glfwCreateWindow(w, h, "test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0, 0.3, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}
