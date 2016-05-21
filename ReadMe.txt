//
// �����¼����¿�������
// BetterCarryingEachOther
// Assignment #4
// 

*���α׷� ����
�� ���α׷��� CSED451 ��4�� �����̴�.
���α׷��� �⺻������ �����̸�, �÷��̾�� W,A,D�� �̿��� ĳ���͸� �����Ͽ� ��ֹ��� ���� ���� �ָ����� ���� �ȴ�.
Q�� ������ ������ �ٲ� �� �ְ� R�� ������ ����� �� �� �ִ�.
���� 1���� ������ flat shading, gouraud shading, phong shading, wireframe shading�� ���� �ٲ� �� �� �ִ�.
���� 2���� ������ ��/���� �ٲ� ������ ������ �ٲپ� �� �� �ִ�.
���� 3���� ������ SSAO����� �Ѱ� �� �� �ִ�.

*����ȯ��
�� ������Ʈ�� ������ ���� ȯ�濡�� �ۼ��Ǿ���.
	- Visual Studio 2015
	- freeglut 2.8.1-1
	- GLEW 2.0

*������
���α׷� �ַ�� ������ VS 2015�� ��� �����ϸ� �ȴ�.

*���ϼ���

assn4.sln - ���α׷� �ַ�� �����̴�. �� ������ �̿��� ������Ʈ�� ���� �ȴ�.

.gitattributes.txt
.gitignore.txt - VS���� Git ����� �̿��ϸ鼭 ���� �����̴�.

"assn4" ����

*�ҽ�����

control.h
control.cpp - ����� ���α׷� ��Ʈ���� ���ô� �ҽ������̴�.

debug.h
debug.cpp - OpenGL���� ������ �������� ǥ�� ������� ���ִ� �Լ����� ���ǵǾ��ִ�.

deco.h
deco.cpp - ���ӿ� ������ ��Ĺ����� ����ִ� �ҽ������̴�. ����, ����, ���� ���Եȴ�.

enemy.h
enemy.cpp - ������ ���� ���ǰ� ����ִ� �ҽ������̴�. ���� ����, �׸��� ���� �θ� Ŭ������ ����ִ�.

framebuffer.h
framebuffer.cpp - �����ӹ��� ������Ʈ�� �� ����� ������� �����ӹ��� Ŭ������ ���ǵǾ��ִ�.

game.h
game.cpp - ������ �ʱ�ȭ, ������Ʈ, ��ο��� �������� ���밡 ����ִ� ����̴�.

generator.h
generator.cpp - Generator, MetaGenerator Ŭ������ ����ִ� �ҽ��̴�. 

InitShader.h
InitShader.cpp - ���̴��� �ҷ����� ����� ����ִ� �ҽ��̴�.

key.h
key.cpp - Ű ���۸��� ���õ� ����̴�.

light.h
light.cpp - ���ε�� ���� ������ ������Ʈ�� ���ǵ� �ҽ��̴�.

lodepng.h
lodepng.cpp - PNG�� �ҷ����µ� ���� �ҽ��̴�.

mat.h - ��İ� ����� ������ ���ǵ� �ҽ��̴�.

model.h
model.cpp - �� Ŭ������ ���Ǹ� ������ *.obj ������ �ҷ����� �κ��� �ִ� �ҽ��̴�.

main.cpp - �����Լ��� GLUT�ʱ�ȭ�� �����ϴ� �ҽ��̴�.

null.h
null.cpp - NullLimiter Ŭ������ ���ǵ� �ҽ��̴�.

object.h
object.cpp - Object �߻� Ŭ������ �׿� ���õ� �⺻���� �޼ҵ尡 ���ǵ� �ҽ��̴�.

player.h
player.cpp - Player Ŭ������ ���ǵ� �ҽ��̴�.

resource.h
resource.cpp - 3D ��, �ؽ�ó ���� �ҷ����� �����ϴ� �ҽ��̴�.

river.h
river.cpp - ���� �ǳʴ� �κп��� �ʿ��� Ŭ�������� ���ǵ� �ҽ��̴�.

shader.h
shader.cpp - ���̴� ����� �ִ� �ҽ��̴�.

texture.h
texture.cpp - �ؽ�ó Ŭ������ ���ǵ� �ҽ��̴�.

utility.h
utility.cpp - ���ӿ� ���� ���̴� ��Ÿ �Լ����� ���ǵ� �ҽ������̴�. float�� ����, �������� ���� �ִ�.

vec.h - ���Ϳ� ������ ������ ���ǵ� �ҽ��̴�.

view.h
view.cpp - ī�޶�� ���õ� ����� ����ִ� ����̴�.

*���̴� ����

���̴� ������ _v.glsl, _f.glsl, _g.glsl�� ������ �̸��� ������. ������ vertex shader, fragment shader, geometry shader�� �ǹ��Ѵ�.

flat_* - flat shading ���α׷�
gouraud_* - gouraud shading ���α׷�
phong_* - phong shading ���α׷�
wire_* - wireframe shading ���α׷�, hide shading�� �Բ� ����ؾ��Ѵ�.
hide_* - hide shading ���α׷�, wireframe shading�� �� ���� hidden line removal�� ����Ѵ�.
ssao_* - SSAO ���α׷�
blur_* - ���簢�� �帲ȿ�� ���α׷�
framepass_* - �ܼ� pass through ���α׷�

*���ҽ� ����

*.obj - 3D �� �����̴�.
*.png - �ؽ�ó �����̴�.
normal_*.png - �븻�� �����̴�.
