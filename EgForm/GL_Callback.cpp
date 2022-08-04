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
*	\brief 키보드 이벤트를 처리하는 콜백 함수
*
*	\param key 사용자가 누른 키의 아스키 값이 전달됨
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void Keyboard(unsigned char key, int x, int y)
{
	// ImGui 키보드 이벤트 정보를 설정한다.
	ImGuiIO &io = ImGui::GetIO();
	//io.KeysDown[8] = false;
	if (key >= 32)
		io.AddInputCharacter((unsigned int)key);
	if (key >= 1 && key <= 26)	// CTRL + {a, ..., z}는 GLUT에서 key 값으로 1 ~ 26이 전달됨
		io.KeysDown[key] = io.KeysDown[key - 1 + 'a'] = io.KeysDown[key - 1 + 'A'] = true;
	else if (key >= 'a' && key <= 'z')	// 'a' ~ 'z'와 'A' ~ 'Z'를 동일하게 처리
		io.KeysDown[key] = io.KeysDown[key - 'a' + 'A'] = true;
	else if (key >= 'A' && key <= 'Z')	// 'A' ~ 'Z'와 'a' ~ 'z'를 동일하게 처리
		io.KeysDown[key] = io.KeysDown[key - 'A' + 'a'] = true;
	else
		io.KeysDown[key] = true;

	ImGui_ImplGLUT_UpdateKeyboardMods();

	// ImGui 윈도우가 선택되었다면 리턴한다.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// EgForm 구현
	EgMesh *pMesh = theSelector.GetSltMesh();
	switch (key)
	{
	case 27: // ESC 키
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
				// 선택된 삼각형을 스무딩한다.
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_smooth_mesh_region(pMesh, Faces);
				}
				// 선택된 정점을 스무딩 한다.
				else if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgVertex *> Verts;
					for (EgObject *v : theSelector.m_SltObjList)
						Verts.push_back((EgVertex *)v);
					::get_smooth_mesh_region(pMesh, Verts);
				}
				// 메쉬 전체를 스무딩 한다.
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
	// 화면을 갱신한다.
	glutPostRedisplay();
}

/*!
*	\brief 키보드 이벤트를 처리하는 콜백 함수
*
*	\param key 사용자가 뗀 키의 아스키 값이 전달됨
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
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
*	\brief 윈도우 처음 생성되거나 크기가 변경될 때 호출되는 콜백 함수
*
*	\param w 윈도우의 너비가 전달됨
*	\param h 윈도우의 높이가 전달됨
*/
void Reshape(int w, int h)
{
	// ImGui의 Reshape 이벤트 정보를 설정한다.
	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)w, (float)h);

	// 장면의 뷰포트를 설정한다.
	theScene.SetupViewport(w, h);
	Width = w;
	Height = h;
}

/*!
*	\brief 3차원 장면을 렌더링 하는 함수
*/
//void Display()
//{
//	// ImGui 프레임을 생성한다.
//	ImGui_ImplOpenGL2_NewFrame();
//	ImGui_ImplGLUT_NewFrame();
//
//	// 메인 메뉴를 생성한다.
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
//	// Context 팝업 메뉴를 생성한다.
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
//	// ImGui 데모 윈도우를 생성한다.
//	//static bool show_demo_window = true;
//	//ImGui::ShowDemoWindow(&show_demo_window);
//
//	// 칼라 버퍼를 지우고,
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// 장면을 렌더링 하고
//	theScene.Render(false);
//
//	// 편집기를 렌더링 하고
//	theEditor.Render();
//
//	// 선택기를 렌더링 하고
//	theSelector.Render();
//
//	// ImGui를 렌더링 한다.
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
//	// 칼라 버퍼를 교환한다.
//	glutSwapBuffers();
//
//	// 삼각형 아이디를 색상으로 메쉬의 삼각형을 렌더링 한다.
//	theSelector.RenderForSelect();
//	glutPostRedisplay();
//}

/*!
*	\brief 윈도우 좌측 하단에 FPS를 출력하는 함수
*/
static void RenderFps()
{
	// 출력할 윈도우의 위치와 투명도를 설정한다.
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

	// 윈도우를 생성하고 메시지를 출력한다.
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
*	\brief 마우스 이벤트를 처리하는 콜백 함수
*
*	\param glut_button 마우스 버튼 정보(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param state 마우스 버튼의 상태 정보(GLUT_UP, GLUT_DOWN)
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void Mouse(int glut_button, int state, int x, int y)
{
	// ImGui 마우스 이벤트 정보(위치, 버튼 정보, 상태)를 설정한다.
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

	// ImGui 윈도우가 선택되었다면 리턴한다.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// 마우스 버튼을 누른 경우,
	if (state == GLUT_DOWN)
	{
		switch (glut_button)
		{
		case GLUT_LEFT_BUTTON:
			// 장면의 회전을 준비 하거나(m_SceneManipulateType이 변경됨)
			theScene.LButtonDown(x, y);

			// 선택 객체의 편집을 준비 하거나(m_bEditInProgress가 true로 변경됨)
			theEditor.LButtonDown(x, y);

			// 새로운 객체 선택을 위한 준비를 한다(m_bSelectInProgress가 true로 변경됨).
			theSelector.LButtonDown(x, y);
			break;

		case GLUT_MIDDLE_BUTTON:
			// 장면의 이동을 준비한다(m_SceneManipulateType이 변경됨) 
			theScene.MButtonDown(x, y);
			break;
		}
	}

	// 마우스 버튼을 뗀 경우,
	if (state == GLUT_UP)
	{
		switch (glut_button)
		{
		case GLUT_LEFT_BUTTON:
			// 장면의 회전을 종료하거나,
			theScene.LButtonUp(x, y);

			// 선택된 객체의 편집을 종료하거나,
			theEditor.LButtonUp(x, y);

			// 새로운 객체를 선택한다.
			theSelector.LButtonUp(x, y);
			break;

		case GLUT_MIDDLE_BUTTON:
			// 장면의 이동을 종료한다.
			theScene.MButtonUp(x, y);
			break;
		}
	}
}

/*!
*	\brief 버튼을 누르고 마우스를 움직일 경우에 호출되는 콜백 함수
*
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void Motion(int x, int y)
{
	// ImGui 마우스 이벤트 정보를 설정한다.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	// ImGui 윈도우가 선택되었다면 리턴한다.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// 장면의 타이머가 켜 있다면 리턴한다.
	if (theScene.m_bTimer)
		return;

	// 장면을 회전(이동) 하거나,
	theScene.MouseMove(x, y);

	// 선택된 객체를 편집하거나,
	theEditor.MouseMove(x, y);

	// 선택 영역을 정의한다.
	theSelector.MouseMove(x, y);

	// 화면을 갱신한다.
	glutPostRedisplay();
}

/*!
*	\brief 마우스를 움직일 경우에 호출되는 콜백 함수
*	\note 버튼을 누르지 않고 움직여도 호출됨
*
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void PassiveMotion(int x, int y)
{
	// ImGui 마우스 이벤트 정보를 설정한다.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	// 마우스 포인터와 중첩되는 편집기의 핸들을 찾거나,
	theEditor.MouseMove(x, y);

	// 마우스 포인터와 중첩되는 객체(정점, 삼각형)를 찾는다.
	theSelector.MouseMove(x, y);

	// 화면을 갱신한다.
	glutPostRedisplay();
}

/*!
*	\brief 마우스 스크롤을 처리하는 콜백 함수
*
*	\param button 마우스 버튼 정보(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir 스크롤의 방향
*	\param x 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y 좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void MouseWheel(int button, int dir, int x, int y)
{
	// ImGui 마우스 이벤트 정보를 설정한다.
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	if (dir > 0)
		io.MouseWheel += 1.0;
	else if (dir < 0)
		io.MouseWheel -= 1.0;

	// ImGui 윈도우가 선택되었다면 리턴한다.
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		return;

	// 장면의 스케일을 조절하거나,
	theScene.MouseWheel(dir);

	// 편집 툴의 편집 영역을 조절하거나,
	theEditor.MouseWheel(dir);

	// 선택 브러쉬의 선택 영역을 조절한다.
	theSelector.MouseWheel(dir);

	// 화면을 갱신한다.
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
	// ImGui 구현
	//printf("key_down_func %d\n", key);
	ImGuiIO &io = ImGui::GetIO();
	if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
		io.KeysDown[key + 256] = true;

	ImGui_ImplGLUT_UpdateSpecialMods();

	// 화면을 갱신한다.
	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y)
{
	// ImGui 구현
	//printf("key_up_func %d\n", key);
	ImGuiIO &io = ImGui::GetIO();
	if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
		io.KeysDown[key + 256] = false;

	ImGui_ImplGLUT_UpdateSpecialMods();
}

/*!
*	\brief GLUT 콜백 함수를 등록한다.
*/
void ImGui_ImplGLUT_InstallFuncs()
{
	// 콜백 함수를 등록한다.
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
