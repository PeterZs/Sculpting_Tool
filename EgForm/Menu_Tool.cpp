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
	// ���� ���õ� ��ü�� Ŭ���� �̸��� ���Ѵ�.
	EgMesh *pMesh = theSelector.GetSltMesh();
	std::string ClsName = (pMesh == NULL) ? "" : pMesh->GetClassName();
	bool bSelected = false;
	bool bEnabled = false;

	// Tool �޴��� �����Ѵ�.
	if (ImGui::BeginMenu("Tools"))
	{
		// �޽� ���� �޴�
		if (ImGui::MenuItem("Refine", 0, false, (pMesh != NULL)))
		{
			::get_refined_mesh(pMesh);
			pMesh->UpdateEdgeMate();
			pMesh->UpdateNormal();
			theEditor.Reset();
			theSelector.SelectMesh(pMesh->m_Name);
		}

		// ���޽� �޴�
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

		// �޽� fairing �޴�
		if (ImGui::BeginMenu("Fairing"))
		{
			if (ImGui::MenuItem("Min Area(uni. wgt.)", 0, bSelected, (pMesh != NULL)))
			{
				// �޽� ��ü�� fairing �ϴ� ���
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_membrane(pMesh, true);
				}

				// ���� ������ fairing �ϴ� ���
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
				// �޽� ��ü�� fairing �ϴ� ���
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_membrane(pMesh, false);
				}

				// ���� ������ fairing �ϴ� ���
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
				// �޽� ��ü�� fairing �ϴ� ���
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_thin_plate(pMesh);
				}

				// ���� ������ fairing �ϴ� ���
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
				// �޽� ��ü�� fairing �ϴ� ���
				if (theSelector.GetClsNameSltObj() == "EgMesh")
				{
					::get_fair_mesh_minimum_variation(pMesh);
				}

				// ���� ������ fairing �ϴ� ���
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

			// Fairing �޴��� �ݴ´�.
			ImGui::EndMenu();
		}

		// �޽� ������ �޴�
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

			ImGui::EndMenu(); // Smooth �޴�
		}

		// �޽� ���͸� �޴�
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

			ImGui::EndMenu(); // Low-pass filtering �޴�
		}
		ImGui::Separator();
		///////////////////////////////////////////////////////////////////////////////////////

		// �޽� �Ű�ȭ �޴�
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

	// �޴� ��ȭ ���ڸ� ǥ���Ѵ�.
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
		// ������ ���� �����̵�
		ImGui::Text("Edge Ratio:");
		ImGui::SameLine();

		ImGui::PushItemWidth(256.0f);
		ImGui::SliderFloat("##ratio", &ratio, 0.1f, 3.0f);
		ImGui::PopItemWidth();

		// ���� ��� ������ ���̿� ��ǥ ������ ���� ���
		double AvgEdgeLen = pMesh->GetAvgEdgeLen();
		ImGui::Text("Curr. Edge Len.: %.5lf, \t Tar. Edge Len.: %.5lf", AvgEdgeLen, AvgEdgeLen * ratio);
		ImGui::Separator();

		// ���� ��ư		
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

				// ���� ������ remeshing �ϴ� ���
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

		// ��� ��ư
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			SltMenuId = 0;
		}
	}
	ImGui::End();
}
