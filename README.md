# Exoplanet

## How to control
“W”, “S”, “A”, “D”: forward, backward, left, right move.
<br/>Mouse move: change camera’s viewing (a.k.a. look-at) direction.
<br/><br/>Display different filtering effects using keyboard inputs.
<br/>“1”: the point filter mode (D3D11_FILTER_MIN_MAG_MIP_POINT) 
<br/>“2”: the linear filter mode (D3D11_FILTER_MIN_MAG_MIP_LINEAR)
<br/>“3”: the anisotropic filter mode (D3D11_FILTER_ANISOTROPIC)
<br/><br/>Change the background color using keyboard inputs. 
<br/>“r”: red, “g”: green, “b”: blue

## Application features
1. Translate and rotate multiple objects continuously in the scene:
<br/>UFO – Y axis rotation, up down translation
<br/>Alien - up down translation
2. The water shader as a visual effect:
<br/>reflecton shader and refraction shader 이용, 물에 하늘이 반사되고 바닥인 구덩이의 텍스쳐가 굴절되어 보임.
3. Apply Phong illumination model (ambient, diffuse, specular lights) and multiple point lights:
<br/>specular를 이용하여 sky dome에 해가 있는 듯한 효과(실제 sky dome아님)를 내고, multiple point lights를 이용하여 물구덩이 주변으로 무지개 빛 조명을 줌
4. Use a camera to navigate throughout the scene using the keyboard and mouse inputs.
5. Use the instancing technique to display multiple copied models:
<br/>행성 바닥에 배치된 돌들, 3D Max에서 4개의 모델을 하나로 합친 다음 DX11에서 인스턴싱을 함.
<br/>인스턴싱을 할 모델에만 적용할 쉐이더와 일반 모델에 적용할 쉐이더를 분리함.

## Implementation issues
1. 회전 시 제자리 회전이 안되는 것(해결o)
<br/>정확히는 모르겠지만 인스턴싱 때문에 행렬 계산이 꼬이는 것으로 생각됨. 인스턴싱 모델용 쉐이더를 분리하여 문제를 해결함.
2. reflection shader 상이 여러 개 맺히는 것(해결x)
<br/>reflection matrix 구하는 과정이 잘못된 것으로 생각하고 있으나 해결을 하지 못해 물결을 크게 주어 상이 여러 개 맺히는 걸 안보이게 했다.

## Difficulty (Implementation issues 제외한 것)
에셋 구하기, 모델 적절히 배치하기, 스테이지 꾸미기
<br/>
***
### 환경
Visual Studio 2019, DirectX 11
### Credits
사용 에셋:
<br/>alien - mixamo
<br/>man - mixamo
<br/>field - 박지민, 백상연
<br/>water - https://www.cgtrader.com/free-3d-models/various/various-models/ocean-surface
<br/>sky - 박지민
<br/>spaceship - https://free3d.com/3d-model/rocket-ship-v1--579030.html
<br/>crater - 박지민
<br/>rock - https://www.cgtrader.com/free-3d-models/exterior/landscape/free-rock-2c86049e-42e2-4e7b-83fc-1092c7ab16fe
<br/>boat - https://www.cgtrader.com/free-3d-models/watercraft/recreational-watercraft/wooden-boat-1-c0a63329-883b-4a22-8520-1d33e6394748
<br/>UFO - https://free3d.com/3d-model/ufo-saucer-v1--190141.html
<br/>
<br/>Framework:
<br/>rastertek, CGP(1)수업
### Youtube Link
https://youtu.be/TJ0ptx0zWFc
