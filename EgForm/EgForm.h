#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <crtdbg.h>
#include <direct.h>

// OpenGL 관련 헤더 파일
#include "GL\freeglut.h"
#include "IL\ilut.h"

// EgPlus 관련 헤더 파일
#include "EgMath\egmath.h"
#include "EgMesh\egmesh.h"
#include "EgScene\egscene.h"

#include "egtools_decimator.h"

// ImGui 관련 헤더 파일
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glut.h"
#include "ImGui\imgui_impl_opengl2.h"
#include "ImGuiFileDialog.h"

#ifdef NDEBUG
	#ifdef _DEBUG
	#undef _DEBUG
	#endif
#endif

// 열거형 타입 선언
enum TypeSimulate
{
	SIMULATE_NONE = 0,
	SIMULATE_HEAT_FLOW = 1,
	SIMULATE_BZR_CRV_ON_MESH,
	SIMULATE_HERMITE_CRV_ON_MESH,
	SIMULATE_TRANSLATE_CRV_ON_MESH,
	SIMULATE_MIN_DIST,
	SIMULATE_MIN_DIST_MAP,
	SIMULATE_INTERSECT_RAY,
	SIMULATE_MESH_MESH_INTERSECT,
	SIMULATE_OFFSET_POLYLINE,
	SIMULATE_OFFSET_CYLINDER,
};

// 전역 변수 정의
///////////////////////////////////////////
extern EgScene theScene;
extern EgEditor theEditor;
extern EgSelector theSelector;
extern ImGuiFileDialog theFileDialog;
extern std::vector<double> gScalarField;

extern int Width;
extern int Height;
///////////////////////////////////////////

extern void InitScene(char *fname);

// 메인 함수들
extern void CreateMenuFile();
extern void CreateMenuSelect();
extern void CreateMenuEdit();
extern void CreateMenuDisplay();
extern void CreateMenuTools();
extern void CreateMenuAnalyze();
extern void CreateMenuDelete();
extern void CreateMenuHelp();
extern void CreateMenuHw();


// Popup 메뉴 함수들
extern void CreateMenuMaterial();



