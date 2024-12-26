#include <render_engine/render_engine.h>

using std::cout;

void RenderEngine::StartRendering()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!InitilizeWindow()) { return; }
	if (!MainRendering()) { return; }
}

bool RenderEngine::InitilizeWindow()
{
	if (!glfwInit()) { return false; }
	window = glfwCreateWindow(win_width, win_height, "Himura The Adventure", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGL()) { return false; }
	glViewport(0, 0, win_width, win_height);
	return true;
}

bool RenderEngine::MainRendering()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return true;
}