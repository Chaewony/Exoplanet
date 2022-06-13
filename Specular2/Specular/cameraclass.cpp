////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = -10.0f;
	m_position.y = 6.0f;
	m_position.z = -10.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 45.0f;
	m_rotation.z = 0.0f;

	DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//카메라 포지션 초기화 안됐었어서 계속 오류났음
	camPosition = XMLoadFloat3(&m_position);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	//XMVECTOR up, position, lookAt;
	//float yaw, pitch, roll;
	//XMMATRIX rotationMatrix;

	//// Setup the vector that points upwards.
	//up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//// Setup the position of the camera in the world.
	//position = XMLoadFloat3(&m_position);

	//// Setup where the camera is looking by default.
	//lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	//// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	//pitch = m_rotation.x * 0.0174532925f;
	//yaw   = m_rotation.y * 0.0174532925f;
	//roll  = m_rotation.z * 0.0174532925f;

	//// Create the rotation matrix from the yaw, pitch, and roll values.
	//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	//up = XMVector3TransformCoord(up, rotationMatrix);

	//// Translate the rotated camera position to the location of the viewer.
	//lookAt = position + lookAt;

	//// Finally create the view matrix from the three updated vectors.
	//m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

void CameraClass::RenderReflection(float height)
{
	XMVECTOR up, position, lookAt;
	float radians;

	XMFLOAT3 fposition;
	fposition.x = m_position.x;
	fposition.y = -m_position.y + (height * 2.0f);
	fposition.z = m_position.z;
	
	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	// For planar reflection invert the Y position of the camera.
	position = XMLoadFloat3(&fposition);
	

	// Calculate the rotation in radians.
	radians = m_position.y * 0.0174532925f;

	// Setup where the camera is looking.
	XMFLOAT3 flookAt;
	flookAt.x = sinf(radians) + m_position.x;;
	flookAt.y = fposition.y;
	flookAt.z = cosf(radians) + m_position.z;
	lookAt = XMLoadFloat3(&flookAt);

	// Create the view matrix from the three vectors.
	m_reflectionViewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}

XMMATRIX CameraClass::GetReflectionViewMatrix()
{
//	return XMMATRIX();
	return m_reflectionViewMatrix;
}

void CameraClass::UpdateCamera(float camPitch, float camYaw, float* moveLeftRight, float* moveBackForward)
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0.0f);

	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	camPosition += *moveLeftRight * camRight;
	camPosition += *moveBackForward * camForward;

	*moveLeftRight = 0.0f;
	*moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	m_viewMatrix = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}
