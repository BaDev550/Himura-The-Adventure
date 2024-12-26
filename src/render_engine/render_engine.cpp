#include <render_engine/render_engine.h>
#include <iostream>

using std::cout;

void RenderEngine::Init()
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BAXGameEngine->Init();
	return true;
}

bool RenderEngine::MainRendering()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		BAXGameEngine->Update(deltaTime);
		BAXGameEngine->ProcessInput(deltaTime, window);

		BAXGameEngine->Render();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return true;
}