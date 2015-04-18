#include "ScreenManager.h"

int ScreenManager::m_Width ,ScreenManager::m_Height;

ScreenManager::ScreenManager(int width ,int height ,char *title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;

	if(!init())
		glfwTerminate();
}

ScreenManager::ScreenManager(void){

}

ScreenManager::~ScreenManager(void)
{
	
}

bool ScreenManager::init(){
	if(!glfwInit()){
		std::cout<<"Failed to initialize GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR ,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR ,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE ,GL_FALSE);

	window = glfwCreateWindow(m_Width ,m_Height ,m_Title ,NULL ,NULL);

	if(window == NULL){
		std::cout<<"Failed to create window\n";
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
		
	if(glewInit() != GLEW_OK){
		std::cout<<"Failed to initialize GLEW\n";
		return false;
	}	

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	glViewport(0 ,0 ,m_Width ,m_Height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	input = Input(window);

	return true;
}



void ScreenManager::clear() const{
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
}

void ScreenManager::render() const{
	/*GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;*/
	glfwSwapBuffers(window);
}

void ScreenManager::update() const{
	if (Input::isKeyPressed(GLFW_KEY_ESCAPE)){
		glfwSetWindowShouldClose(window, 1);
	}
	glfwPollEvents();
}

bool ScreenManager::isClosed() const{
	return glfwWindowShouldClose(window) == 1;
}

void ScreenManager::dispose() const{
	glfwTerminate();
}

int ScreenManager::getWidth(){
	return m_Width;
}

int ScreenManager::getHeight(){
	return m_Height;
}