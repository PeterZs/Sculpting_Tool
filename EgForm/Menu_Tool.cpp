#include "stdafx.h"
#include "EgForm.h"

#define TOOL_DECIMATE		1000
#define TOOL_REMESH			1001
#define TOOL_REMESH_INTR	1002
#define TOOL_REMESH_BNDRY	1003
#define TOOL_REMESH_RGN		1004
#define TOOL_STAMP			1005

static int SltMenuId = 0;
static void Remesh(EgMesh *pMesh);

//////////////////////////////////////////////////////////////////////////////
void CreateMenuTools()
{
	// 현재 선택된 객체의 클래스 이름을 구한다.
	EgMesh *pMesh = theSelector.GetSltMesh();
	std::string ClsName = (pMesh == NULL) ? "" : pMesh->GetClassName();
	bool bSelected = false;
	bool bEnabled = false;

	// Tool 메뉴를 생성한다.
	if (ImGui::BeginMenu("Tools"))
	{
		// 메쉬 분할 메뉴
		if (ImGui::MenuItem("Refine", 0, false, (pMesh != NULL)))
		{
			::get_refined_mesh(pMesh);
			pMesh->UpdateEdgeMate();
			pMesh->UpdateNormal();
			theEditor.Reset();
			theSelector.SelectMesh(pMesh->m_Name);
		}

		// 리메싱 메뉴
		if (ImGui::BeginMenu("Remeshing..."))
		{
			if (ImGui::MenuItem("Mesh", 0, false, (pMesh != NULL)))
				SltMenuId = TOOL_REMESH;

			if (ImGui::MenuItem("Interior", 0, false, (pMesh != NULL)))
				SltMenuId = TOOL_REMESH_INTR;

			if (ImGui::MenuItem("Boundary", 0, false, (pMesh != NULL)))
				SltMenuId = TOOL_REMESH_BNDRY;

			if (ImGui::MenuItem("Selected Region", 0, false, (pMesh != NULL)))
				SltMenuId = TOOL_REMESH_RGN;

			ImGui::EndMenu();
		}

		ImGui::Separator();
		///////////////////////////////////////////////////////////////////////////////////////

		// 메쉬 fairing 메뉴
		if (ImGui::BeginMenu("Fairing"))
		{
			if (ImGui::MenuItem("Min Area(uni. wgt.)", 0, bSelected, (pMesh != NULL)))
			{
				// 메쉬 전체를 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_membrane(pMesh, true);
				}

				// 선택 영역을 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theEditor.m_EditFaceRgn)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_membrane(pMesh, Faces, true);
				}
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_membrane(pMesh, Faces, true);
				}

				pMesh->UpdateNormal();
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			if (ImGui::MenuItem("Min Area(cot. wgt.)", 0, bSelected, (pMesh != NULL)))
			{
				// 메쉬 전체를 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_membrane(pMesh, false);
				}

				// 선택 영역을 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theEditor.m_EditFaceRgn)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_membrane(pMesh, Faces, false);
				}
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_membrane(pMesh, Faces, false);
				}

				pMesh->UpdateNormal();
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			if (ImGui::MenuItem("Min Curvature", 0, bSelected, (pMesh != NULL)))
			{
				// 메쉬 전체를 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_thin_plate(pMesh);
				}

				// 선택 영역을 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theEditor.m_EditFaceRgn)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_thin_plate(pMesh, Faces);
				}
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_thin_plate(pMesh, Faces);
				}

				pMesh->UpdateNormal();
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			if (ImGui::MenuItem("Min Variation", 0, bSelected, (pMesh != NULL)))
			{
				// 메쉬 전체를 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_minimum_variation(pMesh);
				}

				// 선택 영역을 fairing 하는 경우
				if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theEditor.m_EditFaceRgn)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_minimum_variation(pMesh, Faces);
				}
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::get_fair_mesh_minimum_variation(pMesh, Faces);
				}

				pMesh->UpdateNormal();
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			// Fairing 메뉴를 닫는다.
			ImGui::EndMenu();
		}

		// 메쉬 스무딩 메뉴
		if (ImGui::BeginMenu("Smoothing"))
		{
			if (ImGui::MenuItem("Mesh", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh(pMesh);
			}
			if (ImGui::MenuItem("Interior", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_interior(pMesh);
			}
			if (ImGui::MenuItem("Boundary", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_boundary(pMesh);
			}
			if (ImGui::MenuItem("Selected Region", 0, bSelected, (pMesh != NULL)))
			{
				if (theSelector.GetClsNameSltObj() == "EgVertex")
				{
					std::vector<EgVertex *> Verts;
					for (EgObject *v : theEditor.m_EditVertRgn)
						Verts.push_back((EgVertex *)v);
					if (!Verts.empty())
						::get_smooth_mesh_region(pMesh, Verts);
				}

				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					if (!Faces.empty())
						::get_smooth_mesh_region(pMesh, Faces);
				}
			}
			if (ImGui::MenuItem("Normal", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_normal(pMesh);
			}

			ImGui::EndMenu(); // Smooth 메뉴
		}

		// 메쉬 필터링 메뉴
		if (ImGui::BeginMenu("Filtering (low-pass)"))
		{
			if (ImGui::MenuItem("10%", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_low_pass_filter(pMesh, 0.1);
			}

			if (ImGui::MenuItem("5%", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_low_pass_filter(pMesh, 0.05);
			}

			if (ImGui::MenuItem("3%", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_low_pass_filter(pMesh, 0.03);
			}

			if (ImGui::MenuItem("1%", 0, bSelected, (pMesh != NULL)))
			{
				::get_smooth_mesh_low_pass_filter(pMesh, 0.01);
			}

			ImGui::EndMenu(); // Low-pass filtering 메뉴
		}
		ImGui::Separator();
		///////////////////////////////////////////////////////////////////////////////////////

		// 메쉬 매개화 메뉴
		pMesh = theSelector.GetSltMesh();
		if (ImGui::BeginMenu("Unfold"))
		{
			if (ImGui::MenuItem("Unit Square", 0, false, (pMesh != NULL)))
			{
				EgMesh *pRetMesh = ::get_unfold_mesh(pMesh, 0);
				if (pRetMesh != NULL)
					theScene.AddMesh(pRetMesh);
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			if (ImGui::MenuItem("Circle", 0, false, (pMesh != NULL)))
			{
				EgMesh *pRetMesh = ::get_unfold_mesh(pMesh, 1);
				if (pRetMesh != NULL)
					theScene.AddMesh(pRetMesh);
				theEditor.Reset();
				theSelector.SelectMesh(pMesh->m_Name);
			}

			if (ImGui::MenuItem("Conformal Mapping", 0, false, (pMesh != NULL)))
			{
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					EgFace *pFace = (EgFace *)theSelector.m_SltObjList[0];
					EgMesh *pRetMesh = ::get_unfold_mesh_conformal(pMesh, pFace);
					if (pRetMesh != NULL)
						theScene.AddMesh(pRetMesh);
					theEditor.Reset();
					theSelector.SelectMesh(pMesh->m_Name);
				}				
			}
			ImGui::EndMenu(); // Unfold
		}
		ImGui::EndMenu();
	}

	// 메뉴 대화 상자를 표시한다.
	Remesh(pMesh);
}

void Remesh(EgMesh *pMesh)
{
	if (SltMenuId != TOOL_REMESH && SltMenuId != TOOL_REMESH_INTR &&
		SltMenuId != TOOL_REMESH_BNDRY && SltMenuId != TOOL_REMESH_RGN)
		return;

	if (pMesh == NULL)
	{
		SltMenuId = 0;
		return;
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize;
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(10.0f, 30.0f), ImGuiCond_Always, ImVec2(0.0, 0.0f));
	static float ratio = 1.0f;

	if (ImGui::Begin("Remesh Dialog", nullptr, window_flags))
	{
		// 디테일 강도 슬라이드
		ImGui::Text("Edge Ratio:");
		ImGui::SameLine();

		ImGui::PushItemWidth(256.0f);
		ImGui::SliderFloat("##ratio", &ratio, 0.1f, 3.0f);
		ImGui::PopItemWidth();

		// 현재 평균 에지의 길이와 목표 에지의 길이 출력
		double AvgEdgeLen = pMesh->GetAvgEdgeLen();
		ImGui::Text("Curr. Edge Len.: %.5lf, \t Tar. Edge Len.: %.5lf", AvgEdgeLen, AvgEdgeLen * ratio);
		ImGui::Separator();

		// 적용 버튼		
		if (ImGui::Button("Apply"))
		{
			switch (SltMenuId)
			{
			case TOOL_REMESH:
				::remesh(pMesh, ratio, true, false);
				break;

			case TOOL_REMESH_INTR:
				::remesh(pMesh, ratio, true, true);
				break;

			case TOOL_REMESH_BNDRY:
				::remesh_bndry(pMesh, ratio, true);
				break;

				// 선택 영역을 remeshing 하는 경우
			case TOOL_REMESH_RGN:
				if (theSelector.GetClsNameSltObj() == "EgFace")
				{
					std::vector<EgFace *> Faces;
					for (EgObject *f : theSelector.m_SltObjList)
						Faces.push_back((EgFace *)f);
					::remesh_region(pMesh, ratio, true, Faces);
				}
				else
					printf("Select region to be remeshed...");
				break;
			}

			SltMenuId = 0;
			theEditor.Reset();
			theSelector.SelectMesh(pMesh->m_Name);
			ImGui::CloseCurrentPopup();
		}

		// 취소 버튼
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			SltMenuId = 0;
		}
	}
	ImGui::End();
}
