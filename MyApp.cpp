#include "MyApp.h"
#include "SDL_GLDebugMessageCallback.h"

#include <imgui.h>

CMyApp::CMyApp()
{
}

CMyApp::~CMyApp()
{
}

void CMyApp::SetupDebugCallback()
{
	// if the program is running in the debug context, allow and setup the debug callback function
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(SDL_GLDebugMessageCallback, nullptr);
	}
}

void CMyApp::InitShaders()
{
	m_programID = glCreateProgram();
	AttachShader( m_programID, GL_VERTEX_SHADER, "Shaders/Vert_PosCol.vert" );
	AttachShader( m_programID, GL_FRAGMENT_SHADER, "Shaders/Frag_PosCol.frag" );
	LinkProgram( m_programID );
}

void CMyApp::CleanShaders()
{
	glDeleteProgram( m_programID );
}

void CMyApp::InitGeometry()
{
	MeshObject<VertexPosColor> meshCPU;
	
	meshCPU.vertexArray =
	{
		{ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.2f, 0.6f, 1.0f) }, //base-left-back
		{ glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.1f, 0.8f, 0.2f) }, //base-right-back
		{ glm::vec3(-0.5, -0.5, 0.5), glm::vec3(1.0f, 0.8f, 0.1f) }, //base-left-front
		{ glm::vec3(0.5, -0.5, 0.5), glm::vec3(1.0f, 0.4f, 0.0f) }, //base-right-front
		{ glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.6f, 0.3f, 0.9f) }, //top-left-back
		{ glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.0f, 0.9f, 0.9f) }, //top-right-back
		{ glm::vec3(-0.5, 0.5, 0.5), glm::vec3(1.0f, 0.1f, 0.6f) }, //top-left-front
		{ glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8f, 0.8f, 0.8f) } //top-right-front
	};
	meshCPU.indexArray =
	{
		0, 1, 2, //bottom
		1, 3, 2, //bottom
		4, 6, 5, //top
		6, 7, 5, //top
		6, 2, 7, //front
		2, 3, 7, //front
		7, 3, 5, //right
		3, 1, 5, //right
		4, 5, 0, //back
		5, 1, 0, //back
		6, 4, 0, //left
		2, 6, 0 //left
	};

	// create a new VBO
	glCreateBuffers( 1, &vboID );

	// fill the VBO with data
	glNamedBufferData( vboID,	// load data into the VBO
					   meshCPU.vertexArray.size() * sizeof( VertexPosColor ),		// this many bytes
					   meshCPU.vertexArray.data(),	// reading from this memory address
					   GL_STATIC_DRAW );	// we won't write to our VBO after this, and we will use the data in it for every drawing

	// create index buffer
	glCreateBuffers( 1, &iboID );
	glNamedBufferData( iboID, meshCPU.indexArray.size() * sizeof( GLuint ), meshCPU.indexArray.data(), GL_STATIC_DRAW );

	count = static_cast<GLsizei>( meshCPU.indexArray.size() );

	// create 1 VAO
	glCreateVertexArrays( 1, &vaoID );

	// set the VBO to the VAO at index 0
	glVertexArrayVertexBuffer( vaoID, 0, vboID, 0, sizeof( VertexPosColor ) );

	// set the attributes

	// attribute at index 0: position
	glEnableVertexArrayAttrib( vaoID, 0 ); // enable the attribute
	glVertexArrayAttribBinding( vaoID, 0, 0 ); // bind the attribute to the VBO indexed 0
	glVertexArrayAttribFormat( vaoID, // set the attributes for the VAO
							   0,     // the attribute at index 0
							   3,     // 3 components: (x, y, z)
							   GL_FLOAT, // data type
							   GL_FALSE, // are the data normalized
							   offsetof( VertexPosColor, position ) // where does the attribute start within the area of sizeof(Vertex)
	);

	// attribute at index 1: color
	glEnableVertexArrayAttrib( vaoID, 1 );
	glVertexArrayAttribBinding( vaoID, 1, 0 );
	glVertexArrayAttribFormat( vaoID, 1, 3, GL_FLOAT, GL_FALSE, offsetof( VertexPosColor, color ) );

	// bind index buffer to VAO
	glVertexArrayElementBuffer( vaoID, iboID );
}

void CMyApp::CleanGeometry()
{
	glDeleteBuffers(1,      &vboID);
	glDeleteBuffers(1,      &iboID);
	glDeleteVertexArrays(1, &vaoID);
}

bool CMyApp::Init()
{
	SetupDebugCallback();

	// set the screen clearing color to blue-ish
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	InitShaders();
	InitGeometry();

	// other initializations

	glEnable(GL_CULL_FACE); // enable the culling of backwards facing polygons (from the point of view of the camera)
	glCullFace(GL_BACK);    // GL_BACK: backwards facing polygons, GL_FRONT: forwards facing polygons

	glEnable(GL_DEPTH_TEST); // enabling depth testing (obstruction)

	// camera
	m_camera.SetView(
		glm::vec3(0.0, 0.0, 100.0),   // the camera's position  - eye
		glm::vec3(0.0, 0.0, 0.0),   // the position that the camera is looking at  - at
		glm::vec3(0.0, 1.0, 0.0));  // the world's up direction  - up

	m_cameraManipulator.SetCamera( &m_camera );

	return true;
}

void CMyApp::Clean()
{
	CleanShaders();
	CleanGeometry();
}

void CMyApp::Update( const SUpdateInfo& updateInfo )
{
	m_ElapsedTimeInSec = updateInfo.ElapsedTimeInSec;
	m_cameraManipulator.Update( updateInfo.DeltaTimeInSec );
	m_myElapsedTime += updateInfo.DeltaTimeInSec * m_timespeed;

	m_lambda = (sin(m_myElapsedTime * (2 * 3.14) / 10)+1)*0.5;
	m_parabola_x = -10 * (1.f - m_lambda) + 10 * m_lambda;
	m_parabola_y = 0.05 * pow(m_parabola_x, 2);
	m_parabola = glm::vec3(m_parabola_x, m_parabola_y, 0);
}

void CMyApp::Render()
{
	// clear the framebuffer (GL_COLOR_BUFFER_BIT)
	// ... and the depth buffer (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram( m_programID );
	glUniform3f(ul("addedcolor"), 0.f,0.f,0.f);
	glUniformMatrix4fv( ul("viewProj"), 1, GL_FALSE, glm::value_ptr( m_camera.GetViewProj() ) );


	for (int n = 0; n < m_formation_count; n++)
	{

		float fi = n * (2 * 3.14 / m_formation_count);
		float radius = m_formation_count > 1 ? 15: 0;
		//Cube Made of Zs
		for (int i = 1; i < 9; i++)
		{
			// Z (base_mesh):
			for (int j = 0; j < 5; j++)
			{
				glm::mat4 transformation =  glm::translate<float>(glm::vec3(radius * cos(fi), radius * sin(fi), 0)) *
											glm::translate<float>(m_parabola) * 
											glm::translate<float>(m_z_cube[i]) * 
											glm::translate<float>(m_base_mesh[j]);

				glUniformMatrix4fv(ul("world"), 1, GL_FALSE, glm::value_ptr(transformation));
				glBindVertexArray(vaoID);
				glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
			}
		}
	}


	// turn the shader off
	glUseProgram( 0 );

	// break the binding to the VAO
	glBindVertexArray( 0 );
}

void CMyApp::RenderGUI()
{
	if (ImGui::Button("+"))
	{
		m_formation_count++;
	}
	else if (ImGui::Button("-") && m_formation_count > 0) 
	{
		m_formation_count--;
	}
}

// https://wiki.libsdl.org/SDL2/SDL_KeyboardEvent
// https://wiki.libsdl.org/SDL2/SDL_Keysym
// https://wiki.libsdl.org/SDL2/SDL_Keycode
// https://wiki.libsdl.org/SDL2/SDL_Keymod

void CMyApp::KeyboardDown(const SDL_KeyboardEvent& key)
{	
	if ( key.repeat == 0 ) // It was pressed for the first time
	{
		if ( key.keysym.sym == SDLK_F5 && key.keysym.mod & KMOD_CTRL )
		{
			CleanShaders();
			InitShaders();
		}
		if ( key.keysym.sym == SDLK_F1 )
		{
			GLint polygonModeFrontAndBack[ 2 ] = {};
			// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGet.xhtml
			glGetIntegerv( GL_POLYGON_MODE, polygonModeFrontAndBack ); // Query the current polygon mode! It gives separate modes for front and back.
			GLenum polygonMode = ( polygonModeFrontAndBack[ 0 ] != GL_FILL ? GL_FILL : GL_LINE ); // Let's toggle between FILL and LINE!
			// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml
			glPolygonMode( GL_FRONT_AND_BACK, polygonMode ); // Let's set the new one!
		}
	}
	m_cameraManipulator.KeyboardDown( key );
}

void CMyApp::KeyboardUp(const SDL_KeyboardEvent& key)
{
	m_cameraManipulator.KeyboardUp( key );
}

// https://wiki.libsdl.org/SDL2/SDL_MouseMotionEvent

void CMyApp::MouseMove(const SDL_MouseMotionEvent& mouse)
{
	m_cameraManipulator.MouseMove( mouse );
}

// https://wiki.libsdl.org/SDL2/SDL_MouseButtonEvent

void CMyApp::MouseDown(const SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(const SDL_MouseButtonEvent& mouse)
{
}

// https://wiki.libsdl.org/SDL2/SDL_MouseWheelEvent

void CMyApp::MouseWheel(const SDL_MouseWheelEvent& wheel)
{
	m_cameraManipulator.MouseWheel( wheel );
}


// two new parameters for the resized window's width (_w) and height (_h)
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);
	m_camera.SetAspect( static_cast<float>(_w) / _h );
}

// For handling other, more exotic events that haven't been handled yet
// https://wiki.libsdl.org/SDL2/SDL_Event

void CMyApp::OtherEvent( const SDL_Event& ev )
{

}
