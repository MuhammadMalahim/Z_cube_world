#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Utils
#include "GLUtils.hpp"
#include "Camera.h"
#include "CameraManipulator.h"

struct SUpdateInfo
{
	float ElapsedTimeInSec = 0.0f; // Elapsed time since the start of the program
	float DeltaTimeInSec   = 0.0f; // Elapsed time since the last update
};

class CMyApp
{
public:
	CMyApp();
	~CMyApp();

	bool Init();
	void Clean();

	void Update( const SUpdateInfo& );
	void Render();
	void RenderGUI();

	void KeyboardDown(const SDL_KeyboardEvent&);
	void KeyboardUp(const SDL_KeyboardEvent&);
	void MouseMove(const SDL_MouseMotionEvent&);
	void MouseDown(const SDL_MouseButtonEvent&);
	void MouseUp(const SDL_MouseButtonEvent&);
	void MouseWheel(const SDL_MouseWheelEvent&);
	void Resize(int, int);

	void OtherEvent( const SDL_Event& );
protected:
	void SetupDebugCallback();

	// Data variables

	float m_ElapsedTimeInSec = 0.0f;

	//glm::mat4 m_objectWorldTransform[10];
	glm::mat4 m_objectWorldTransform2;
	glm::mat4 m_objectWorldTransforms[2];

	// Camera
	Camera m_camera;
	CameraManipulator m_cameraManipulator;

	// OpenGL stuff

	// Variables needed for the shaders
	GLuint m_programID = 0; // program of the shaders

	// Initialization, and deletion of the shaders
	void InitShaders();
	void CleanShaders();

	// Variables related to geometry

	GLuint  vaoID = 0; // Vertex Array Object resource identifier
	GLuint  vboID = 0; // Vertex Buffer Object resource identifier
	GLuint  iboID = 0; // Index Buffer Object resource identifier
	GLsizei count = 0; // how many indices/vertices should we draw

	// Initialization and deletion of geometry
	void InitGeometry();
	void CleanGeometry();

	//my_variables
	float m_timespeed = 1.f;
	float m_myElapsedTime = 0.f;

	glm::vec3 m_base_mesh[5] = {
		glm::vec3(0, 0, 0), //middle
		glm::vec3(0, 1, 0), //top
		glm::vec3(0, -1, 0), //bottom
		glm::vec3(-1, 1, 0), //top-left
		glm::vec3(1, -1, 0) //bottom-right
	};
	glm::vec3 m_z_cube[9] = {
		glm::vec3(0, 0, 0), //center
		glm::vec3(-2.5, -2.5, -2.5), //base-left-back
		glm::vec3(2.5, -2.5, -2.5), //base-right-back
		glm::vec3(-2.5, -2.5, 2.5), //base-left-front
		glm::vec3(2.5, -2.5, 2.5), //base-right-front
		glm::vec3(-2.5, 2.5, -2.5), //top-left-back
		glm::vec3(2.5, 2.5, -2.5), //top-right-back
		glm::vec3(-2.5, 2.5, 2.5), //top-left-front
		glm::vec3(2.5, 2.5, 2.5)  //top-right-front
	};
	float m_lambda;
	float m_parabola_x;
	float m_parabola_y;
	glm::vec3 m_parabola;
	float m_formation_count = 1;

};

