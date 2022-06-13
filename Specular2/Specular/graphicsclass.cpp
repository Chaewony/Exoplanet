////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;

	m_alien = 0;
	m_man = 0;
	m_Ground = 0;
	m_WaterModel = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_RefractionShader = 0;
	m_WaterShader = 0;
	m_Sky = 0;
	m_spaceship = 0;
	m_crater = 0;

	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;

	m_Stone = 0;
	m_InstanceShader = 0;
	m_Boat = 0;
	m_UFO = 0;

	//컬러값 저장할 변수 초기화
	m_BgColor = XMFLOAT4(0, 0, 0, 1);
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_InstanceShader = new InstanceShaderClass;
	if (!m_InstanceShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_InstanceShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the instance shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);


	// Create the first light object.
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}

	// Initialize the first light object.
	m_Light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light1->SetPosition(-3.0f, 1.0f, 3.0f);

	// Create the second light object.
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Initialize the second light object.
	m_Light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Light2->SetPosition(3.0f, 1.0f, 3.0f);

	// Create the third light object.
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Initialize the third light object.
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_Light3->SetPosition(-3.0f, 1.0f, -3.0f);

	// Create the fourth light object.
	m_Light4 = new LightClass;
	if (!m_Light4)
	{
		return false;
	}

	// Initialize the fourth light object.
	m_Light4->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetPosition(3.0f, 1.0f, -3.0f);

	m_alien = new ModelClass;
	if (!m_alien)
	{
		return false;
	}

	result = m_alien->Initialize(m_D3D->GetDevice(), L"./data/alien.obj", L"./data/alien_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the alien model object.", L"Error", MB_OK);
		return false;
	}

	m_man = new ModelClass;
	if (!m_man)
	{
		return false;
	}

	result = m_man->Initialize(m_D3D->GetDevice(), L"./data/man.obj", L"./data/man_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the man model object.", L"Error", MB_OK);
		return false;
	}

	m_Ground = new ModelClass;
	if (!m_Ground)
	{
		return false;
	}

	result = m_Ground->Initialize(m_D3D->GetDevice(), L"./data/field.obj", L"./data/field_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the field model object.", L"Error", MB_OK);
		return false;
	}

	m_WaterModel = new ModelClass;
	if (!m_WaterModel)
	{
		return false;
	}

	result = m_WaterModel->Initialize(m_D3D->GetDevice(), L"./data/water.obj", L"./data/water_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	m_Sky = new ModelClass;
	if (!m_Sky)
	{
		return false;
	}

	result = m_Sky->Initialize(m_D3D->GetDevice(), L"./data/sky.obj", L"./data/sky_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky model object.", L"Error", MB_OK);
		return false;
	}

	m_spaceship = new ModelClass;
	if (!m_spaceship)
	{
		return false;
	}

	result = m_spaceship->Initialize(m_D3D->GetDevice(), L"./data/spaceship.obj", L"./data/spaceship_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the spaceship model object.", L"Error", MB_OK);
		return false;
	}

	m_crater = new ModelClass;
	if (!m_crater)
	{
		return false;
	}

	result = m_crater->Initialize(m_D3D->GetDevice(), L"./data/crater.obj", L"./data/field_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the crater model object.", L"Error", MB_OK);
		return false;
	}

	m_Stone = new InstanceModelClass;
	if (!m_Stone)
	{
		return false;
	}

	result = m_Stone->Initialize(m_D3D->GetDevice(), L"./data/rocks.obj", L"./data/rock_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rock model object.", L"Error", MB_OK);
		return false;
	}

	m_Boat = new ModelClass;
	if (!m_Boat)
	{
		return false;
	}

	result = m_Boat->Initialize(m_D3D->GetDevice(), L"./data/boat.obj", L"./data/boat_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the boat model object.", L"Error", MB_OK);
		return false;
	}

	m_UFO = new ModelClass;
	if (!m_UFO)
	{
		return false;
	}

	result = m_UFO->Initialize(m_D3D->GetDevice(), L"./data/ufo.obj", L"./data/ufo_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ufo model object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction shader object.
	m_RefractionShader = new RefractionShaderClass;
	if (!m_RefractionShader)
	{
		return false;
	}

	// Initialize the refraction shader object.
	result = m_RefractionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	// Set the height of the water.
	m_waterHeight = 2.75f;

	// Initialize the position of the water.
	m_waterTranslation = 0.0f;

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light objects.
	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	

	if (m_InstanceShader)
	{
		m_InstanceShader->Shutdown();
		delete m_InstanceShader;
		m_InstanceShader = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the refraction shader object.
	if (m_RefractionShader)
	{
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the ground model object.
	if (m_Stone)
	{
		m_Stone->Shutdown();
		delete m_Stone;
		m_Stone = 0;
	}

	if (m_Boat)
	{
		m_Boat->Shutdown();
		delete m_Boat;
		m_Boat = 0;
	}

	if (m_UFO)
	{
		m_UFO->Shutdown();
		delete m_UFO;
		m_UFO = 0;
	}

	// Release the water model object.
	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	if (m_Sky)
	{
		m_Sky->Shutdown();
		delete m_Sky;
		m_Sky = 0;
	}

	if (m_spaceship)
	{
		m_spaceship->Shutdown();
		delete m_spaceship;
		m_spaceship = 0;
	}

	// Release the bath model object.
	if (m_Ground)
	{
		m_Ground->Shutdown();
		delete m_Ground;
		m_Ground = 0;
	}

	// Release the wall model object.
	if (m_man)
	{
		m_man->Shutdown();
		delete m_man;
		m_man = 0;
	}

	// Release the ground model object.
	if (m_alien)
	{
		m_alien->Shutdown();
		delete m_alien;
		m_alien = 0;
	}

	if (m_crater)
	{
		m_crater->Shutdown();
		delete m_crater;
		m_crater = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;

}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;
	static float skyrotation = 0.0f;
	static int dir = 1;
	static float translation = 0.0f;
	static float ufotranslation = 0.0f;
	static int ufodir = 1;

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	skyrotation += XM_PI * 0.0003f;
	if (skyrotation > 360.0f)
	{
		skyrotation -= 360.0f;
	}

	translation += dir * 0.2f;
	if (translation >= 1.0f)
	{
		dir = -1;
	}
	else if (translation <= 0.0f) {
		dir = 1;
	}
	
	ufotranslation += ufodir * 0.05f;
	if (ufotranslation >= 1.5f)
	{
		ufodir = -1;
	}
	else if (ufotranslation <= -1.5f) {
		ufodir = 1;
	}

	// Render the graphics scene.
	result = Render(rotation, translation, skyrotation, ufotranslation);
	if(!result)
	{
		return false;
	}
	
	// Update the position of the water to simulate motion.
	m_waterTranslation += 0.001f;
	if (m_waterTranslation > 1.0f)
	{
		m_waterTranslation -= 1.0f;
	}

	// Set the position and rotation of the camera.
	/*m_Camera->SetPosition(-10.0f, 6.0f, -10.0f);
	m_Camera->SetRotation(0.0f, 45.0f, 0.0f);*/

	return true;
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}

void GraphicsClass::SetBgColor(XMFLOAT4 color)
{
	m_BgColor = color;
}

D3DClass* GraphicsClass::GetD3DClass()
{
	return m_D3D;
}

ColorShaderClass* GraphicsClass::GetD3DClassColorShader()
{
	return m_ColorShader;
}

LightShaderClass* GraphicsClass::GetLightShaderClass()
{
	return m_LightShader;
}

void GraphicsClass::SetLight(int num)
{
}


bool GraphicsClass::Render(float rotation, float translation, float skyrotation, float ufotranslation)
{
	//XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	//
	//// Clear the buffers to begin the scene.
	//m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	//m_Camera->Render();

	//// Get the world, view, and projection matrices from the camera and d3d objects.
	//m_Camera->GetViewMatrix(viewMatrix);
	//m_D3D->GetWorldMatrix(worldMatrix);
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	//// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), 
	//	worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(), 
	//	m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
	//	m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//


	// Render the refraction of the scene to a texture.
	result = RenderRefractionToTexture();
	if (!result)
	{
		return false;
	}

	// Render the reflection of the scene to a texture.
	result = RenderReflectionToTexture(rotation, translation, skyrotation);
	if (!result)
	{
		return false;
	}

	// Render the scene as normal to the back buffer.
	result = RenderScene(rotation, translation, skyrotation,ufotranslation);
	if (!result)
	{
		return false;
	}


	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderRefractionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);



	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the bath model will be rendered.
	worldMatrix *= XMMatrixTranslation(0.0f, 2.0f, 0.0f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Ground->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_RefractionShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Ground->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
//	m_D3D->SetBackBufferRenderTarget();
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderReflectionToTexture(float rotation, float translation,float skyrotation)
{
	XMMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	XMFLOAT4 spotDiffuseColor[4];
	XMFLOAT4 lightPosition[4];
	bool result;

	// Create the diffuse color array from the four light colors.
	spotDiffuseColor[0] = m_Light1->GetDiffuseColor();
	spotDiffuseColor[1] = m_Light2->GetDiffuseColor();
	spotDiffuseColor[2] = m_Light3->GetDiffuseColor();
	spotDiffuseColor[3] = m_Light4->GetDiffuseColor();

	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1->GetPosition();
	lightPosition[1] = m_Light2->GetPosition();
	lightPosition[2] = m_Light3->GetPosition();
	lightPosition[3] = m_Light4->GetPosition();

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the wall model will be rendered.
	worldMatrix *= XMMatrixScaling(5.0f, 5.0f, 5.0f);
	worldMatrix = XMMatrixRotationY(skyrotation);


	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Sky->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader and the reflection view matrix.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Sky->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_Sky->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderScene(float rotation, float translation, float skyrotation,float ufotranslation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	XMFLOAT4 spotDiffuseColor[4];
	XMFLOAT4 lightPosition[4];
	bool result;

	// Create the diffuse color array from the four light colors.
	spotDiffuseColor[0] = m_Light1->GetDiffuseColor();
	spotDiffuseColor[1] = m_Light2->GetDiffuseColor();
	spotDiffuseColor[2] = m_Light3->GetDiffuseColor();
	spotDiffuseColor[3] = m_Light4->GetDiffuseColor();

	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1->GetPosition();
	lightPosition[1] = m_Light2->GetPosition();
	lightPosition[2] = m_Light3->GetPosition();
	lightPosition[3] = m_Light4->GetPosition();



	// Clear the buffers to begin the scene.
//	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_D3D->BeginScene(m_BgColor.x, m_BgColor.y, m_BgColor.z, m_BgColor.w); //background color


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

//외계인
	// Translate to where the ground model will be rendered.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix *= XMMatrixScaling(5.0f, 5.0f, 5.0f);
	worldMatrix *= XMMatrixTranslation(1.0f, 5.6f+translation, 1.0f);

	// Put the ground model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_alien->Render(m_D3D->GetDeviceContext());

	// Render the ground model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_alien->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_alien->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//man
	 //Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the wall model will be rendered.
	worldMatrix *= XMMatrixScaling(0.05f, 0.05f, 0.05f);
	worldMatrix *= XMMatrixTranslation(0.0f, 4.0f, -4.0f);
	

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_man->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_man->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_man->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//달
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the bath model will be rendered.
	worldMatrix *= XMMatrixTranslation(25.0f, 35.0f, 0.0f);
	worldMatrix *= XMMatrixScaling(0.1f, 0.1f, 0.1f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Ground->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Ground->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//보트
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the bath model will be rendered.
//	worldMatrix *= XMMatrixScaling(0.1f, 0.1f, 0.1f);
	worldMatrix *= XMMatrixTranslation(0.0f, 35.0f, 25.0f);
	worldMatrix *= XMMatrixScaling(0.1f, 0.1f, 0.1f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Boat->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Boat->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Boat->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//UFO
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to where the bath model will be rendered.
	worldMatrix = XMMatrixRotationY(rotation);

	worldMatrix *= XMMatrixTranslation(-13.0f, 17.5f+ ufotranslation, -5.0f);
//	worldMatrix *= XMMatrixScaling(0.7f, 0.7f, 0.7f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_UFO->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_UFO->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_UFO->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//스카이
	m_D3D->GetWorldMatrix(worldMatrix);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Sky->Render(m_D3D->GetDeviceContext());
	worldMatrix *= XMMatrixScaling(5.0f, 5.0f, 5.0f);
	worldMatrix = XMMatrixRotationY(skyrotation);

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Sky->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Sky->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//spaceship
	m_D3D->GetWorldMatrix(worldMatrix);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_spaceship->Render(m_D3D->GetDeviceContext());
	worldMatrix *= XMMatrixScaling(0.2f, 0.2f, 0.2f);
	worldMatrix *= XMMatrixRotationY(160);
	worldMatrix *= XMMatrixTranslation(11.0f, 3.0f, -5.0f);

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_spaceship->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_spaceship->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//crater1
	m_D3D->GetWorldMatrix(worldMatrix);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_crater->Render(m_D3D->GetDeviceContext());
	worldMatrix *= XMMatrixScaling(0.2f, 0.2f, 0.2f);
//	worldMatrix *= XMMatrixRotationY(160);
	worldMatrix *= XMMatrixTranslation(11.0f, 3.0f, -5.0f);

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_crater->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_crater->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//crater2
	m_D3D->GetWorldMatrix(worldMatrix);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_crater->Render(m_D3D->GetDeviceContext());
	worldMatrix *= XMMatrixScaling(0.2f, 0.2f, 0.2f);
//	worldMatrix *= XMMatrixRotationY(160);
	worldMatrix *= XMMatrixTranslation(-11.0f, 3.0f, -10.0f);

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_crater->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_crater->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//crater3
	m_D3D->GetWorldMatrix(worldMatrix);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_crater->Render(m_D3D->GetDeviceContext());
	worldMatrix *= XMMatrixScaling(0.2f, 0.2f, 0.2f);
	//	worldMatrix *= XMMatrixRotationY(160);
	worldMatrix *= XMMatrixTranslation(5.0f, 3.0f, 15.0f);

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_crater->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_crater->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		spotDiffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

//워터
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the camera reflection view matrix.
	reflectionMatrix = m_Camera->GetReflectionViewMatrix();


	worldMatrix *= XMMatrixScaling(10.0f, 0.0f, 10.0f);//사이즈 변경
	// Translate to where the water model will be rendered.
	worldMatrix *= XMMatrixTranslation(0.0f, m_waterHeight, 0.0f);

	// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WaterModel->Render(m_D3D->GetDeviceContext());
	
	// Render the water model using the water shader.
	result = m_WaterShader->Render(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
		m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
		m_waterTranslation, 0.5f);
	if (!result)
	{
		return false;
	}


//돌
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix *= XMMatrixScaling(0.55f, 0.55f, 0.55f);
	worldMatrix *= XMMatrixTranslation(-1.0f, 1.5f, 0.0f);
	m_Stone->Render(m_D3D->GetDeviceContext());

	result = m_InstanceShader->Render(m_D3D->GetDeviceContext(), m_Stone->GetIndexCount(), 15,
		worldMatrix, viewMatrix, projectionMatrix,
		m_Stone->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		true,true,true,
		spotDiffuseColor, lightPosition);

	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
