#include "stdafx.h"
#include "EgForm.h"
#include "trackball.h"
#include "glm.h"

static void RenderFps();
extern bool enableKeyboard;



static void ImGui_ImplGLUT_UpdateKeyboardMods()
{
	ImGuiIO &io = ImGui::GetIO();
	int mods = glutGetModifiers();
	io.KeyCtrl = (mods & GLUT_ACTIVE_CTRL) != 0;
	io.KeyShift = (mods & GLUT_ACTIVE_SHIFT) != 0;
	io.KeyAlt = (mods & GLUT_ACTIVE_ALT) != 0;
}

/*!
*	\brief Ű���� �̺�Ʈ�� ó���ϴ� �ݹ� �Լ�
*
*	\param key ����ڰ� ���� Ű�� �ƽ�Ű ���� ���޵�
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void Keyboard(unsigned char key, int x, int y)
{
	// ImGui Ű���� �̺�Ʈ ������ �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	//io.KeysDown[8] = false;
	if (key >= 32)
		io.AddInputCharacter((unsigned int)key);
	if (key >= 1 && key <= 26)	// CTRL + {a, ..., z}�� GLUT���� key ������ 1 ~ 26�� ���޵�
		io.KeysDown[key] = io.KeysDown[key - 1 + 'a'] = io.KeysDown[key - 1 + 'A'] = true;
	else if (key >= 'a' && key <= 'z')	// 'a' ~ 'z'�� 'A' ~ 'Z'�� �����ϰ� ó��
		io.KeysDown[key] = io.KeysDown[key - 'a' + 'A'] = true;
	else if (key >= 'A' && key <= 'Z')	// 'A' ~ 'Z'�� 'a' ~ 'z'�� �����ϰ� ó��
		io.KeysDown[key] = io.KeysDown[key - 'A' + 'a'] = true;
	else
		io.KeysDown[key] = true;

	ImGui_ImplGLUT_UpdateKeyboardMods();

	// ImGui �����찡 ���õǾ��ٸ� �����Ѵ�.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// EgForm ����
	EgMesh *pMesh = theSelector.GetSltMesh();
	switch (key)
	{
	case 27: // ESC Ű
		theEditor.Reset();
		theScene.m_MainCamera.m_ArcBallType = ARCBALL_FREE;
		break;

	case 'a':
	case 'A':
		break;

	case 'b':
		break;
	case 'B':
		if (ISPRESSED(VK_SHIFT))
		{
			theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
			theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_BRUSH;
			theEditor.m_EditToolType = EDIT_INACTIVE;
		}
		break;

	case 'c':
	case 'C':
		break;

	case 'd':
	case 'D':
		break;

	case 'f':
		theScene.m_HeadUpDisplay.SetFrontView();
		break;

	case 'F':
		if (ISPRESSED(VK_SHIFT))
		{
			theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
			theEditor.m_EditToolType = EDIT_INACTIVE;
		}
		break;

	case 'g':
		//theScene.m_bShowBkg = !theScene.m_bShowBkg;
		theScene.m_bShowFloor = !theScene.m_bShowFloor;
		break;

	case 'G':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE_CONNECTED;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
		}
		break;

	case 'h':
	case 'H':
		theScene.m_HeadUpDisplay.SetHomeView();
		break;

	case 'o':
	case 'O':
		theScene.m_MainCamera.m_CameraType = PROJECTION_ORTHO;
		break;

	case 'p':
	case 'P':
		theScene.m_MainCamera.m_CameraType = PROJECTION_PERS;
		break;

	case 'q':
	case 'Q':
		if (pMesh != NULL)
			theScene.AdjustViewFrustum(pMesh->m_BndBox);
		break;

	case 'r':
	case 'R':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
				theEditor.m_EditToolType = EDIT_ROT;
			else
			{
				::remesh(pMesh, 1.0, true, true);
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}
		}
		break;

	case 's':
	case 'S':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
			{
				theEditor.m_EditToolType = EDIT_SCL;
			}
			else
			{
				// ���õ� �ﰢ���� �������Ѵ�.
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_smooth_mesh_region(pMesh, Faces);
				}
				// ���õ� ������ ������ �Ѵ�.
				else if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgVertex *> Verts;
					for (EgObject *v : theSelector.m_SltObjList)
						Verts.push_back((EgVertex *)v);
					::get_smooth_mesh_region(pMesh, Verts);
				}
				// �޽� ��ü�� ������ �Ѵ�.
				else
					::get_smooth_mesh(pMesh);
			}
		}
		break;

	case 't':
		theScene.m_HeadUpDisplay.SetTopView();
		break;

	case 'T':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
				theEditor.m_EditToolType = EDIT_TRA;
		}
		break;

	case 'v':
		break;

	case 'V':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_VERT;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
		}
		break;

	case 'w':
	case 'W':
		if (pMesh != NULL)
		{
			if (pMesh->m_RenderOption & RENDER_WIRE)
				pMesh->m_RenderOption &= (~RENDER_WIRE);
			else
				pMesh->m_RenderOption |= RENDER_WIRE;
		}
		break;

	case 'x':
		theScene.m_MainCamera.m_ArcBallType = ARCBALL_X;
		break;

	case 'X':
		if (pMesh != NULL)
		{
			if (ISPRESSED(VK_SHIFT))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_MESH_PT;
				theEditor.m_EditToolType = EDIT_INACTIVE;
				//pMesh->UpdateEdgeLength(1);
			}
		}
		break;

	case 'y':
		theScene.m_MainCamera.m_ArcBallType = ARCBALL_Y;
		break;

	case 'z':
		theScene.m_MainCamera.m_ArcBallType = ARCBALL_Z;
		break;
	}
	// ȭ���� �����Ѵ�.
	glutPostRedisplay();
}

/*!
*	\brief Ű���� �̺�Ʈ�� ó���ϴ� �ݹ� �Լ�
*
*	\param key ����ڰ� �� Ű�� �ƽ�Ű ���� ���޵�
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void KeyboardUp(unsigned char key, int x, int y)
{
	//printf("char_up_func %d '%c'\n", c, c);
	ImGuiIO &io = ImGui::GetIO();
	if (key >= 1 && key <= 26)
		io.KeysDown[key] = io.KeysDown[key - 1 + 'a'] = io.KeysDown[key - 1 + 'A'] = false;
	else if (key >= 'a' && key <= 'z')
		io.KeysDown[key] = io.KeysDown[key - 'a' + 'A'] = false;
	else if (key >= 'A' && key <= 'Z')
		io.KeysDown[key] = io.KeysDown[key - 'A' + 'a'] = false;
	else
		io.KeysDown[key] = false;
	ImGui_ImplGLUT_UpdateKeyboardMods();
}

/*!
*	\brief ������ ó�� �����ǰų� ũ�Ⱑ ����� �� ȣ��Ǵ� �ݹ� �Լ�
*
*	\param w �������� �ʺ� ���޵�
*	\param h �������� ���̰� ���޵�
*/
void Reshape(int w, int h)
{
	// ImGui�� Reshape �̺�Ʈ ������ �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)w, (float)h);

	// ����� ����Ʈ�� �����Ѵ�.
	theScene.SetupViewport(w, h);
	Width = w;
	Height = h;
}

/*!
*	\brief 3���� ����� ������ �ϴ� �Լ�
*/
//void Display()
//{
//	// ImGui �������� �����Ѵ�.
//	ImGui_ImplOpenGL2_NewFrame();
//	ImGui_ImplGLUT_NewFrame();
//
//	// ���� �޴��� �����Ѵ�.
//	if (ImGui::BeginMainMenuBar())
//	{
//		CreateMenuFile();
//		CreateMenuSelect();
//		CreateMenuEdit();
//		CreateMenuTools();
//		CreateMenuAnalyze();
//		CreateMenuDisplay();
//		CreateMenuHelp();
//		CreateMenuHw();
//		ImGui::EndMainMenuBar();
//	}
//
//	// Context �˾� �޴��� �����Ѵ�.
//	if (ImGui::BeginPopupContextVoid())
//	{
//		//CreateMenuFile();
//		//CreateMenuCreate();
//		CreateMenuSelect();
//		CreateMenuMaterial();
//		//CreateMenuEdit();
//		CreateMenuDelete();
//		ImGui::EndPopup();
//	}
//
//	// ImGui ���� �����츦 �����Ѵ�.
//	//static bool show_demo_window = true;
//	//ImGui::ShowDemoWindow(&show_demo_window);
//
//	// Į�� ���۸� �����,
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// ����� ������ �ϰ�
//	theScene.Render(false);
//
//	// �����⸦ ������ �ϰ�
//	theEditor.Render();
//
//	// ���ñ⸦ ������ �ϰ�
//	theSelector.Render();
//
//	// ImGui�� ������ �Ѵ�.
//	RenderFps();
//	ImGui::Render();
//	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
//
//
//	glPushMatrix();
//	tbMatrix();
//
//	// render solid model
//	glEnable(GL_LIGHTING);
//	glColor3f(1.0, 1.0, 1.0f);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glmDraw(mesh, GLM_SMOOTH);
//
//	// render wire model
//	glPolygonOffset(1.0, 1.0);
//	glEnable(GL_POLYGON_OFFSET_FILL);
//	glLineWidth(1.0f);
//	glColor3f(0.6, 0.0, 0.8);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glmDraw(mesh, GLM_SMOOTH);
//
//	// render handle points
//	glPointSize(4.5);
//	glEnable(GL_POINT_SMOOTH);
//	glDisable(GL_LIGHTING);
//	glBegin(GL_POINTS);
//	for (int handleIter = 0; handleIter < handles.size(); handleIter++)
//	{
//		glColor3fv(colors[handleIter % colors.size()]);
//		for (int vertIter = 0; vertIter < handles[handleIter].size(); vertIter++)
//		{
//			int idx = handles[handleIter][vertIter];
//			glVertex3fv((float*)&mesh->vertices[3 * idx]);
//		}
//	}
//	glEnd();
//	glPopMatrix();
//	glFlush();
//
//
//	// Į�� ���۸� ��ȯ�Ѵ�.
//	glutSwapBuffers();
//
//	// �ﰢ�� ���̵� �������� �޽��� �ﰢ���� ������ �Ѵ�.
//	theSelector.RenderForSelect();
//	glutPostRedisplay();
//}

/*!
*	\brief ������ ���� �ϴܿ� FPS�� ����ϴ� �Լ�
*/
static void RenderFps()
{
	// ����� �������� ��ġ�� ������ �����Ѵ�.
	const float DISTANCE = 10.0f;
	static int corner = 3;
	ImGuiIO &io = ImGui::GetIO();
	if (corner != -1)
	{
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f);

	// �����츦 �����ϰ� �޽����� ����Ѵ�.
	bool open = true;
	bool *p_open = &open;
	if (ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		float fps = ImGui::GetIO().Framerate;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
		//ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
		ImGui::End();
	}
}

/*!
*	\brief ���콺 �̺�Ʈ�� ó���ϴ� �ݹ� �Լ�
*
*	\param glut_button ���콺 ��ư ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param state ���콺 ��ư�� ���� ����(GLUT_UP, GLUT_DOWN)
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void Mouse(int glut_button, int state, int x, int y)
{
	// ImGui ���콺 �̺�Ʈ ����(��ġ, ��ư ����, ����)�� �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	int button = -1;
	if (glut_button == GLUT_LEFT_BUTTON) button = 0;
	if (glut_button == GLUT_RIGHT_BUTTON) button = 1;
	if (glut_button == GLUT_MIDDLE_BUTTON) button = 2;
	if (button != -1 && state == GLUT_DOWN)
		io.MouseDown[button] = true;
	if (button != -1 && state == GLUT_UP)
		io.MouseDown[button] = false;

	// ImGui �����찡 ���õǾ��ٸ� �����Ѵ�.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// ���콺 ��ư�� ���� ���,
	if (state == GLUT_DOWN)
	{
		switch (glut_button)
		{
		case GLUT_LEFT_BUTTON:
			// ����� ȸ���� �غ� �ϰų�(m_SceneManipulateType�� �����)
			theScene.LButtonDown(x, y);

			// ���� ��ü�� ������ �غ� �ϰų�(m_bEditInProgress�� true�� �����)
			theEditor.LButtonDown(x, y);

			// ���ο� ��ü ������ ���� �غ� �Ѵ�(m_bSelectInProgress�� true�� �����).
			theSelector.LButtonDown(x, y);
			break;

		case GLUT_MIDDLE_BUTTON:
			// ����� �̵��� �غ��Ѵ�(m_SceneManipulateType�� �����) 
			theScene.MButtonDown(x, y);
			break;
		}
	}

	// ���콺 ��ư�� �� ���,
	if (state == GLUT_UP)
	{
		switch (glut_button)
		{
		case GLUT_LEFT_BUTTON:
			// ����� ȸ���� �����ϰų�,
			theScene.LButtonUp(x, y);

			// ���õ� ��ü�� ������ �����ϰų�,
			theEditor.LButtonUp(x, y);

			// ���ο� ��ü�� �����Ѵ�.
			theSelector.LButtonUp(x, y);
			break;

		case GLUT_MIDDLE_BUTTON:
			// ����� �̵��� �����Ѵ�.
			theScene.MButtonUp(x, y);
			break;
		}
	}
}

/*!
*	\brief ��ư�� ������ ���콺�� ������ ��쿡 ȣ��Ǵ� �ݹ� �Լ�
*
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void Motion(int x, int y)
{
	// ImGui ���콺 �̺�Ʈ ������ �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	// ImGui �����찡 ���õǾ��ٸ� �����Ѵ�.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// ����� Ÿ�̸Ӱ� �� �ִٸ� �����Ѵ�.
	if (theScene.m_bTimer)
		return;

	// ����� ȸ��(�̵�) �ϰų�,
	theScene.MouseMove(x, y);

	// ���õ� ��ü�� �����ϰų�,
	theEditor.MouseMove(x, y);

	// ���� ������ �����Ѵ�.
	theSelector.MouseMove(x, y);

	// ȭ���� �����Ѵ�.
	glutPostRedisplay();
}

/*!
*	\brief ���콺�� ������ ��쿡 ȣ��Ǵ� �ݹ� �Լ�
*	\note ��ư�� ������ �ʰ� �������� ȣ���
*
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void PassiveMotion(int x, int y)
{
	// ImGui ���콺 �̺�Ʈ ������ �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	// ���콺 �����Ϳ� ��ø�Ǵ� �������� �ڵ��� ã�ų�,
	theEditor.MouseMove(x, y);

	// ���콺 �����Ϳ� ��ø�Ǵ� ��ü(����, �ﰢ��)�� ã�´�.
	theSelector.MouseMove(x, y);

	// ȭ���� �����Ѵ�.
	glutPostRedisplay();
}

/*!
*	\brief ���콺 ��ũ���� ó���ϴ� �ݹ� �Լ�
*
*	\param button ���콺 ��ư ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir ��ũ���� ����
*	\param x ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void MouseWheel(int button, int dir, int x, int y)
{
	// ImGui ���콺 �̺�Ʈ ������ �����Ѵ�.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	if (dir > 0)
		io.MouseWheel += 1.0;
	else if (dir < 0)
		io.MouseWheel -= 1.0;

	// ImGui �����찡 ���õǾ��ٸ� �����Ѵ�.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// ����� �������� �����ϰų�,
	theScene.MouseWheel(dir);

	// ���� ���� ���� ������ �����ϰų�,
	theEditor.MouseWheel(dir);

	// ���� �귯���� ���� ������ �����Ѵ�.
	theSelector.MouseWheel(dir);

	// ȭ���� �����Ѵ�.
	glutPostRedisplay();
}

static void ImGui_ImplGLUT_UpdateSpecialMods()
{
	ImGuiIO &io = ImGui::GetIO();
	int mods = glutGetModifiers();
	io.KeyCtrl = (mods & GLUT_ACTIVE_CTRL) != 0;
	io.KeyShift = (mods & GLUT_ACTIVE_SHIFT) != 0;
	io.KeyAlt = (mods & GLUT_ACTIVE_ALT) != 0;
}

void Special(int key, int x, int y)
{
	// ImGui ����
	//printf("key_down_func %d\n", key);
	ImGuiIO &io = ImGui::GetIO();
	if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
		io.KeysDown[key + 256] = true;

	ImGui_ImplGLUT_UpdateSpecialMods();

	// ȭ���� �����Ѵ�.
	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y)
{
	// ImGui ����
	//printf("key_up_func %d\n", key);
	ImGuiIO &io = ImGui::GetIO();
	if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
		io.KeysDown[key + 256] = false;

	ImGui_ImplGLUT_UpdateSpecialMods();
}

/*!
*	\brief GLUT �ݹ� �Լ��� ����Ѵ�.
*/
void ImGui_ImplGLUT_InstallFuncs()
{
	// �ݹ� �Լ��� ����Ѵ�.
	glutReshapeFunc(Reshape);
	//glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
}
