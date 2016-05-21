//
// 버스는서로태워야제맛
// BetterCarryingEachOther
// Assignment #4
// 

*프로그램 개요
본 프로그램은 CSED451 제4번 과제이다.
프로그램은 기본적으로 게임이며, 플레이어는 W,A,D를 이용해 캐릭터를 조종하여 장애물을 피해 가장 멀리까지 가면 된다.
Q를 누르면 시점을 바꿀 수 있고 R을 누르면 재시작 할 수 있다.
숫자 1번을 누르면 flat shading, gouraud shading, phong shading, wireframe shading를 각각 바꿔 볼 수 있다.
숫자 2번을 누르면 낮/밤을 바꿔 광원을 성질을 바꾸어 볼 수 있다.
숫자 3번을 누르면 SSAO기능을 켜고 끌 수 있다.

*개발환경
본 프로젝트는 다음과 같은 환경에서 작성되었다.
	- Visual Studio 2015
	- freeglut 2.8.1-1
	- GLEW 2.0

*실행방법
프로그램 솔루션 파일을 VS 2015로 열어서 실행하면 된다.

*파일설명

assn4.sln - 프로그램 솔루션 파일이다. 이 파일을 이용해 프로젝트를 열면 된다.

.gitattributes.txt
.gitignore.txt - VS에서 Git 기능을 이용하면서 생긴 파일이다.

"assn4" 폴더

*소스파일

control.h
control.cpp - 잡다한 프로그램 컨트롤을 도맡는 소스파일이다.

debug.h
debug.cpp - OpenGL에서 나오는 오류들을 표준 출력으로 빼주는 함수들이 정의되어있다.

deco.h
deco.cpp - 게임에 나오는 장식물들이 들어있는 소스파일이다. 도로, 나무, 꽃이 포함된다.

enemy.h
enemy.cpp - 적군에 대한 정의가 들어있는 소스파일이다. 차와 버스, 그리고 적군 부모 클래스가 들어있다.

framebuffer.h
framebuffer.cpp - 프레임버퍼 오브젝트를 한 덩어리로 묶어놓은 프레임버퍼 클래스가 정의되어있다.

game.h
game.cpp - 게임의 초기화, 업데이트, 드로우의 전반적인 뼈대가 들어있는 모듈이다.

generator.h
generator.cpp - Generator, MetaGenerator 클래스가 들어있는 소스이다. 

InitShader.h
InitShader.cpp - 셰이더를 불러오는 모듈이 들어있는 소스이다.

key.h
key.cpp - 키 버퍼링과 관련된 모듈이다.

light.h
light.cpp - 가로등과 실제 점광원 오브젝트가 정의된 소스이다.

lodepng.h
lodepng.cpp - PNG를 불러오는데 쓰는 소스이다.

mat.h - 행렬과 행렬의 연산이 정의된 소스이다.

model.h
model.cpp - 모델 클래스의 정의를 포함해 *.obj 파일을 불러오는 부분이 있는 소스이다.

main.cpp - 메인함수와 GLUT초기화를 포함하는 소스이다.

null.h
null.cpp - NullLimiter 클래스가 정의된 소스이다.

object.h
object.cpp - Object 추상 클래스와 그와 관련된 기본적인 메소드가 정의된 소스이다.

player.h
player.cpp - Player 클래스가 정의된 소스이다.

resource.h
resource.cpp - 3D 모델, 텍스처 등을 불러오고 정의하는 소스이다.

river.h
river.cpp - 강을 건너는 부분에서 필요한 클래스들이 정의된 소스이다.

shader.h
shader.cpp - 셰이더 모듈이 있는 소스이다.

texture.h
texture.cpp - 텍스처 클래스가 정의된 소스이다.

utility.h
utility.cpp - 게임에 자주 쓰이는 기타 함수들이 정의된 소스파일이다. float형 난수, 선형보간 등이 있다.

vec.h - 벡터와 벡터의 연산이 정의된 소스이다.

view.h
view.cpp - 카메라와 관련된 기능이 들어있는 모듈이다.

*셰이더 파일

셰이더 파일은 _v.glsl, _f.glsl, _g.glsl로 끝나는 이름을 가진다. 각각은 vertex shader, fragment shader, geometry shader를 의미한다.

flat_* - flat shading 프로그램
gouraud_* - gouraud shading 프로그램
phong_* - phong shading 프로그램
wire_* - wireframe shading 프로그램, hide shading과 함께 사용해야한다.
hide_* - hide shading 프로그램, wireframe shading을 할 때에 hidden line removal에 사용한다.
ssao_* - SSAO 프로그램
blur_* - 정사각형 흐림효과 프로그램
framepass_* - 단순 pass through 프로그램

*리소스 파일

*.obj - 3D 모델 파일이다.
*.png - 텍스처 파일이다.
normal_*.png - 노말맵 파일이다.
