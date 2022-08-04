#include <windows.h>

#include <set>
#include <map>
#include "IconsMaterialDesign.h"
#include "stdafx.h"
#include "EgForm.h"
#include "glm.h"
#include "trackball.h"
#include "mtxlib.h"

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseCore>
#include <Eigen/SparseCholesky>

using namespace std;

// 전역 변수 정의
/////////////////////////////////////////////////////////////
EgScene theScene;
EgEditor theEditor;
EgSelector theSelector;
ImGuiFileDialog theFileDialog;
std::vector<double> gScalarField;

int Width = 1280;
int Height = 800;

// 사용자 함수 정의
void InitScene(char* fname);
void LoadFont(ImGuiIO& io);

vector3 Unprojection(vector2 _2Dpos);
vector2 projection_helper(vector3 _3Dpos);
Eigen::MatrixXd ExeCholeskySolver(Eigen::SparseMatrix<double>* A, Eigen::SparseMatrix<double>* b);
map<int, set<int>> GetConnectMap(_GLMmodel* originMesh);
vector<double> LeastSquareSolver(set<int> controlIndices, map<int, set<int>> connectedMap, vector<Eigen::Vector3f> b_top, _GLMmodel* originMesh);
vector<vector<vector3>> CalE(_GLMmodel* iMesh);
Eigen::Matrix3f CalR(int index);
_GLMmodel* ReconstructModel(_GLMmodel* recMesh, vector<double> solveVertices);
void CalError(vector<double> solveVertices);
vector<double> DeformationIteration();

void Display();
void Menu();
// obj load
_GLMmodel* mesh;
_GLMmodel* originMesh;

int WindWidth, WindHeight;
int last_x, last_y;
int select_x, select_y;

typedef enum { SELECT_MODE, DEFORM_MODE } ControlMode;
ControlMode current_mode = SELECT_MODE;

std::vector<float*> colors;
vector<vector<int> > handles;
int selected_handle_id = -1;
bool deform_mesh_flag = false;

float err = 1;
float err_limit = 0.01f;
map<int, set<int>> connectedMap;
vector<vector<vector3>> e, e_p;

void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, timf, 0);
}
void Init()
{
	connectedMap = GetConnectMap(originMesh);
	e = CalE(originMesh);
}

int main(int argc, char** argv)
{


	// 메모리 누수 감지 옵션을 설정한다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// GLUT 초기화 및 디스플레이 모드 설정한다.
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // GLUT_MULTISAMPLE (안티앨리어싱을 위한 모드, 속도 저하)

	// OpenGL 윈도우 생성한다.
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sculpting Tool");

	// ImGui를 초기화 한다.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	// ImGui::StyleColorsLight();
	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();

	// 사용할 폰트를 로딩한다.
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.Fonts->AddFontFromFileTTF("asset/DroidSans.ttf", 15.f);
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	static const ImWchar icons_ranges[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
	io.Fonts->AddFontFromFileTTF("asset/MaterialIcons-Regular.ttf", 20.f, &icons_config, icons_ranges);



	// GLUT 콜백 함수를 등록한다.
	ImGui_ImplGLUT_InstallFuncs();
	glutDisplayFunc(Display);


	// theScene 초기화 한다.
	theScene.InitScene(true);
	theScene.m_HeadUpDisplay.m_BkgColor.Set(0.3, 0.99, 0.99);
	theScene.m_hWndView = GetForegroundWindow();

	mesh = glmReadOBJ("../data/bunny.obj");
	originMesh = glmReadOBJ("../data/bunny.obj");

	glmUnitize(mesh);
	glmFacetNormals(mesh);
	glmVertexNormals(mesh, 90.0);

	glmUnitize(originMesh);
	glmFacetNormals(originMesh);
	glmVertexNormals(originMesh, 90.0);
	Init();

	// 메시지 루프에 진입한다.
	glutMainLoop();

	// ImGui 메뉴를 정리한다.
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

void InitScene(char* fname)
{
	// 전역 객체 초기화
	theEditor.Reset();
	theSelector.Reset();

	// 장면 초기화
	int Width = theScene.m_MainCamera.m_ViewWidth;
	int Height = theScene.m_MainCamera.m_ViewHeight;
	if (fname == NULL)
		theScene.InitScene(true);
	else
		theScene.InitScene(false);
	if (fname != NULL)
	{
		// 메쉬 파일 불러오기
		if (::get_file_ext(fname) == "obj")
			::import_obj(&theScene, fname);
		if (::get_file_ext(fname) == "stl")
			::import_stl(&theScene, fname);
		if (::get_file_ext(fname) == "off")
			::import_off(&theScene, fname);
	}
	theScene.SetupViewport(Width, Height);
	theScene.SetupViewFrustum();
	theScene.SetupViewTransform();
}

//void LoadFont(ImGuiIO& io)
//{
//	io.Fonts->AddFontFromFileTTF("./fonts/Roboto-Medium.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/arial.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/ProggyTiny.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/ALGER.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/Cousine-Regular.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/Along.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/ENPKAV.ttf", 15.0f);
//
//	io.Fonts->AddFontFromFileTTF("./fonts/DroidSans.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/HANBaekB.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/Gaesung.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/YSHN05.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("./fonts/YWDA05.ttf", 15.0f);
//	//io.Fonts->AddFontFromFileTTF("./fonts/PENHL.ttf", 15.0f);
//	//io.Fonts->AddFontFromFileTTF("./fonts/webdings.ttf", 15.0f);
//}



vector3 Unprojection(vector2 _2Dpos)
{
	float Depth;
	int viewport[4];
	double ModelViewMatrix[16];    // Model_view matrix
	double ProjectionMatrix[16];   // Projection matrix

	glPushMatrix();
	tbMatrix();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

	glPopMatrix();

	glReadPixels((int)_2Dpos.x, viewport[3] - (int)_2Dpos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Depth);

	double X = _2Dpos.x;
	double Y = _2Dpos.y;
	double wpos[3] = { 0.0 , 0.0 , 0.0 };

	gluUnProject(X, ((double)viewport[3] - Y), (double)Depth, ModelViewMatrix, ProjectionMatrix, viewport, &wpos[0], &wpos[1], &wpos[2]);

	return vector3(wpos[0], wpos[1], wpos[2]);
}

vector2 projection_helper(vector3 _3Dpos)
{
	int viewport[4];
	double ModelViewMatrix[16];    // Model_view matrix
	double ProjectionMatrix[16];   // Projection matrix

	glPushMatrix();
	tbMatrix();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

	glPopMatrix();

	double wpos[3] = { 0.0 , 0.0 , 0.0 };
	gluProject(_3Dpos.x, _3Dpos.y, _3Dpos.z, ModelViewMatrix, ProjectionMatrix, viewport, &wpos[0], &wpos[1], &wpos[2]);

	return vector2(wpos[0], (double)viewport[3] - wpos[1]);
}


Eigen::MatrixXd ExeCholeskySolver(Eigen::SparseMatrix<double>* A, Eigen::SparseMatrix<double>* b)
{
	Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> solver(*A);

	cout << "---------------------------------------------------------" << endl;
	cout << "Start to solve LeastSquare method by Cholesky solver" << endl;
	cout << "---------------------------------------------------------" << endl;

	Eigen::MatrixXd res = solver.solve(*b);

	return res;
}

map<int, set<int>> GetConnectMap(_GLMmodel* originMesh)
{
	map<int, set<int>> res;

	for (int i = 0; i < originMesh->numtriangles; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			res.insert(pair<int, set<int>>(originMesh->triangles[i].vindices[j], set<int>()));

			res[originMesh->triangles[i].vindices[j]].insert(originMesh->triangles[i].vindices[(j + 1) % 3]);
			res[originMesh->triangles[i].vindices[j]].insert(originMesh->triangles[i].vindices[(j + 2) % 3]);
		}
	}

	return res;
}

vector<double> LeastSquareSolver(set<int> controlIndices, map<int, set<int>> connectedMap, vector<Eigen::Vector3f> b_top, _GLMmodel* originMesh)
{
	// Solve Ax = b
	Eigen::SparseMatrix<double> A(originMesh->numvertices + controlIndices.size(), originMesh->numvertices);
	Eigen::SparseMatrix<double> b(originMesh->numvertices + controlIndices.size(), 3);
	vector<Eigen::Triplet<double>> tripletListA, tripletListb;
	Eigen::Triplet<double> value;

	// Laplacian
	int row = 0;
	for (auto iterMap = ++connectedMap.begin(); iterMap != connectedMap.end(); ++iterMap, ++row)
	{
		int col = row;

		tripletListA.push_back(Eigen::Triplet<double>(row, col, (*iterMap).second.size()));
		for (auto iterSet = (*iterMap).second.begin(); iterSet != (*iterMap).second.end(); ++iterSet)
		{
			col = (*iterSet) - 1;

			value = Eigen::Triplet<double>(row, col, -1.0f);
			tripletListA.push_back(value);
		}
	}

	// b_top (0.5 * (Ri + Rj)(eij))
	for (int i = 0; i < originMesh->numvertices; ++i)
	{
		value = Eigen::Triplet<double>(i, 0, b_top[i][0]);
		tripletListb.push_back(value);
		value = Eigen::Triplet<double>(i, 1, b_top[i][1]);
		tripletListb.push_back(value);
		value = Eigen::Triplet<double>(i, 2, b_top[i][2]);
		tripletListb.push_back(value);
	}

	// Constraint
	row = 0;
	for (auto iter = controlIndices.begin(); iter != controlIndices.end(); ++iter, ++row)
	{
		value = Eigen::Triplet<double>(mesh->numvertices + row, *iter - 1, 1);
		tripletListA.push_back(value);

		for (int i = 0; i < 3; ++i)
		{
			value = Eigen::Triplet<double>(mesh->numvertices + row, i, mesh->vertices[*iter * 3 + i]);
			tripletListb.push_back(value);
		}
	}

	A.setFromTriplets(tripletListA.begin(), tripletListA.end());
	b.setFromTriplets(tripletListb.begin(), tripletListb.end());

	Eigen::SparseMatrix<double> ATA = A.transpose() * A;
	b = A.transpose() * b;

	Eigen::MatrixXd x;

	x = ExeCholeskySolver(&ATA, &b);

	vector<double> res;

	for (int i = 0; i < x.rows(); ++i)
	{
		for (int j = 0; j < x.cols(); ++j)
		{
			res.push_back(x.row(i).col(j).value());
		}
	}

	return res;
}

vector<vector<vector3>> CalE(_GLMmodel* iMesh)
{
	vector<vector<vector3>> res;

	for (int i = 0; i < iMesh->numvertices; ++i)
	{
		res.push_back(vector<vector3>());
		for (auto iter = connectedMap[i].begin(); iter != connectedMap[i].end(); ++iter)
		{
			vector3 v = (vector3(
				iMesh->vertices[3 * (i + 1) + 0] - iMesh->vertices[3 * (*iter) + 0],
				iMesh->vertices[3 * (i + 1) + 1] - iMesh->vertices[3 * (*iter) + 1],
				iMesh->vertices[3 * (i + 1) + 2] - iMesh->vertices[3 * (*iter) + 2]));
			res[i].push_back(v);
		}
	}

	return res;
}

Eigen::Matrix3f CalR(int index)
{
	Eigen::Matrix3f R;
	Eigen::MatrixXf eij(1, 3), eij_p(1, 3);
	Eigen::Matrix3f Si = Eigen::Matrix3f::Zero();

	for (int j = 0; j < connectedMap[index].size(); ++j)
	{
		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				Si(x, y) += e[index][j][x] * e_p[index][j][y];
			}
		}
	}

	Eigen::JacobiSVD<Eigen::MatrixXf> svd(Si, Eigen::ComputeFullU | Eigen::ComputeFullV);
	Eigen::MatrixXf U = svd.matrixU();
	Eigen::MatrixXf V = svd.matrixV();
	Eigen::MatrixXf S = svd.singularValues();

	R = V * U.transpose();

	return R;
}

_GLMmodel* ReconstructModel(_GLMmodel* recMesh, vector<double> solveVertices)
{
	for (int i = 0; i < solveVertices.size(); ++i)
	{
		recMesh->vertices[i + 3] = solveVertices[i];
	}

	return recMesh;
}

void CalError(vector<double> solveVertices)
{
	float err_tmp = 0;

	for (int i = 0; i < solveVertices.size(); ++i)
	{
		err_tmp = max(fabs(mesh->vertices[i + 3] - solveVertices[i]), err_tmp);
	}

	err = min(err_tmp, err);
}

vector<double> DeformationIteration()
{
	vector<double> res;

	e_p = CalE(mesh);

	vector<Eigen::Vector3f> b_top;
	vector<Eigen::Matrix3f> R;
	Eigen::Matrix3f Ri, Rj;
	Eigen::Vector3f eij, b_temp;


	for (int i = 0; i < mesh->numvertices; ++i)
	{
		R.push_back(CalR(i));
	}

	for (int i = 0; i < mesh->numvertices; ++i)
	{
		b_temp = Eigen::Vector3f::Zero();
		for (auto iter = connectedMap[i + 1].begin(); iter != connectedMap[i + 1].end(); ++iter)
		{
			eij = Eigen::Vector3f(originMesh->vertices[3 * (i + 1) + 0] - originMesh->vertices[3 * (*iter) + 0],
				originMesh->vertices[3 * (i + 1) + 1] - originMesh->vertices[3 * (*iter) + 1],
				originMesh->vertices[3 * (i + 1) + 2] - originMesh->vertices[3 * (*iter) + 2]);

			Ri = R[i];
			Rj = R[*iter - 1];
			b_temp += 0.5f * (Ri + Rj) * eij;
		}
		b_top.push_back(b_temp);
	}

	set<int> controlIndices;

	for (int i = 0; i < handles.size(); ++i)
	{
		for (int j = 0; j < handles[i].size(); ++j)
		{
			controlIndices.insert(handles[i][j]);
		}
	}

	res = LeastSquareSolver(controlIndices, connectedMap, b_top, originMesh);

	return res;
}

void Display()
{
	// ImGui 프레임을 생성한다.
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	/////////////////////////////////////////////////////////////////
	//if (ImGui::BeginMenuBar())
	//	{
	//		CreateMenuFile();
	//		CreateMenuSelect();
	//		CreateMenuEdit();
	//		CreateMenuTools();
	//		CreateMenuAnalyze();
	//		CreateMenuDisplay();
	//		//CreateMenuHelp();
	//		//CreateMenuHw();
	//		//ImGui::EndMainMenuBar();

	//		// Menu bar goes here...
	//		ImGui::EndMenuBar();
	//	}

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("SculptingTool", nullptr, window_flags);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(380, 850));

	CreateMenuTools();
	CreateMenuAnalyze();
	CreateMenuDisplay();
	CreateMenuSelect();
	CreateMenuEdit();
	CreateMenuFile();

	// for each of the toolbar buttons


	// This is just to differentiate the regions, you might add a solid rectangle
	// to act as the toolbar background or something fancier instead.
	ImGui::Separator();

	ImGui::BeginChild("WindowContents");

	// Window contents go here...
	//Menu();
	ImGui::EndChild();
	ImGui::End();

	/////////////////////////////////////////////////////////////////

	// 메인 메뉴를 생성한다.
	/*
	if (ImGui::BeginMainMenuBar())
	{
	   CreateMenuFile();
	   CreateMenuSelect();
	   CreateMenuEdit();
	   CreateMenuTools();
	   CreateMenuAnalyze();
	   CreateMenuDisplay();
	   CreateMenuHelp();
	   CreateMenuHw();
	   ImGui::EndMainMenuBar();
	}
	*/

	// Context 팝업 메뉴를 생성한다.
	if (ImGui::BeginPopupContextVoid())
	{
		//CreateMenuFile();
		//CreateMenuCreate();
		CreateMenuSelect();
		CreateMenuMaterial();
		//CreateMenuEdit();
		CreateMenuDelete();
		ImGui::EndPopup();
	}

	// ImGui 데모 윈도우를 생성한다.
	//static bool show_demo_window = true;
	//ImGui::ShowDemoWindow(&show_demo_window);

	// 칼라 버퍼를 지우고,
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 장면을 렌더링 하고
	theScene.Render(false);

	// 편집기를 렌더링 하고
	theEditor.Render();

	// 선택기를 렌더링 하고
	theSelector.Render();

	// ImGui를 렌더링 한다.
	//RenderFps();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// render handle points
	glPointSize(4.5);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for (int handleIter = 0; handleIter < handles.size(); handleIter++)
	{
		glColor3fv(colors[handleIter % colors.size()]);
		for (int vertIter = 0; vertIter < handles[handleIter].size(); vertIter++)
		{
			int idx = handles[handleIter][vertIter];
			glVertex3fv((float*)&mesh->vertices[3 * idx]);
		}
	}
	glEnd();
	//glPopMatrix();
	glFlush();


	// 칼라 버퍼를 교환한다.
	glutSwapBuffers();

	// 삼각형 아이디를 색상으로 메쉬의 삼각형을 렌더링 한다.
	theSelector.RenderForSelect();
	glutPostRedisplay();
}