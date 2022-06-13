////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
//추가
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include "rendertextureclass.h"

#include "InstanceModelClass.h"
#include "InstanceShaderClass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	CameraClass* GetCamera();

	//저장된 컬러값을 변경해주는 함수 
	void SetBgColor(XMFLOAT4 color);
	D3DClass* GetD3DClass();
	ColorShaderClass* GetD3DClassColorShader();

	LightShaderClass* GetLightShaderClass();

	void SetLight(int num);

private:
	bool Render(float, float, float,float);


private:
	bool RenderRefractionToTexture();
	bool RenderReflectionToTexture(float rotation, float translation, float skyrotation);
	bool RenderScene(float, float, float,float);


private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;

	ModelClass* m_alien, * m_man, * m_Ground, * m_WaterModel;
	ModelClass* m_Boat, * m_UFO, * m_Sky, *m_spaceship, *m_crater;
	LightClass* m_Light;

	InstanceModelClass* m_Stone;
	InstanceModelClass* m_Stone2;

	LightShaderClass* m_LightShader;
	InstanceShaderClass* m_InstanceShader;

	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture;

	RefractionShaderClass* m_RefractionShader;
	WaterShaderClass* m_WaterShader;

	float m_waterHeight, m_waterTranslation;

	LightClass* m_Light1, * m_Light2, * m_Light3, * m_Light4;

	//컬러값 저장할 변수
	XMFLOAT4 m_BgColor;
	ColorShaderClass* m_ColorShader;

};

#endif