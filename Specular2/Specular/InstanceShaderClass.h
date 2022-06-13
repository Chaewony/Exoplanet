
////////////////////////////////////////////////////////////////////////////////
// Filename: instanceshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INSTANCESHADERCLASS_H_
#define _INSTANCESHADERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>

#include <fstream>

using namespace std;
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderClass
////////////////////////////////////////////////////////////////////////////////
class InstanceShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct LightPositionBufferType
	{
		XMFLOAT4 lightPosition[4];
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float specularPower;
		XMFLOAT4 specularColor;
	};

	struct LSettingBufferType
	{
		int isAmbient;
		int isDiffuse;
		int isSpecular;///HLSLø°º≠ bool¿∫ 4byte....
		int padding1;
	};

	struct LightColorBufferType
	{
		XMFLOAT4 spotDiffuseColor[4];
	};


public:
	InstanceShaderClass();
	InstanceShaderClass(const InstanceShaderClass&);
	~InstanceShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, int instanceCount,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		ID3D11ShaderResourceView* texture,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
		XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower,
		bool isAmbient, bool isDiffuse, bool isSpecular,
		XMFLOAT4 spotDiffuseColor[], XMFLOAT4 lightPosition[]);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext,
		XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
		ID3D11ShaderResourceView* texture,
		XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower,
		bool isAmbient, bool isDiffuse, bool isSpecular,
		XMFLOAT4 spotDiffuseColor[], XMFLOAT4 lightPosition[]);
	void RenderShader(ID3D11DeviceContext*, int, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lSettingBuffer;

	ID3D11Buffer* m_lightColorBuffer;
	ID3D11Buffer* m_lightPositionBuffer;
};

#endif