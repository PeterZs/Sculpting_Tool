#include "stdafx.h"
#include "EgForm.h"

#define EDIT_NEW_MTL 1000
static int SltMenuId = 0;
void AddMtl();
static EgMesh *gMesh = NULL;

void CreateMenuEdit()
{
	bool bEnabled, bSelected;
	EgMesh *pMesh = theSelector.GetSltMesh();	

	if (ImGui::BeginMenu("Edit"))
	{
		/*!	\brief 메쉬 조각툴 메뉴 */
		if (ImGui::BeginMenu("Sculpt"))
		{
			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_SCULPT_ADD) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Add(+)", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_SCULPT_ADD;
				theEditor.m_EditRadius = 0.05;
			}

			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_SCULPT_REMOVE) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Remove(-)", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_SCULPT_REMOVE;
				theEditor.m_EditRadius = 0.05;
			}

			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_SMOOTH) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Smooth", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_SMOOTH;
				theEditor.m_EditRadius = 0.05;
			}

			ImGui::EndMenu();
		}
		ImGui::Separator();

		/*!	\brief 메쉬를 이동/회전/스케일 편집한다. */
		if (ImGui::BeginMenu("Transform"))
		{
			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_TRA) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Translate", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_TRA;;
			}

			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_ROT) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Rotate", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_ROT;
			}

			bSelected = (theEditor.m_EditToolType == TypeEditTool::EDIT_SCL) ? true : false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Scale", 0, bSelected, bEnabled))
			{
				theEditor.m_EditToolType = TypeEditTool::EDIT_SCL;
			}

			bSelected = false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Normalize", 0, bSelected, bEnabled))
			{
				pMesh->Normalize();
				pMesh->UpdateBndBox();
				pMesh->m_VertexBuf.clear();
			}

			ImGui::EndMenu();
		}
				
		/*!	\brief 메쉬의 모델링 좌표계를 설정한다. */
		if (ImGui::BeginMenu("Model Coordnate"))
		{
			bSelected = false;
			bEnabled = (pMesh != NULL) ? true : false;
			if (ImGui::MenuItem("Set as WC", 0, false, bEnabled))
				pMesh->UpdateMC(0);
			
			if (ImGui::MenuItem("Set as AABB", 0, false, bEnabled))
				pMesh->UpdateMC(1);
			
			if (ImGui::MenuItem("Set as OBB", 0, false, bEnabled))
				pMesh->UpdateMC(2);
			
			ImGui::EndMenu();
		}
		ImGui::Separator();

		// 재질 메뉴
		if (ImGui::MenuItem("Add Material", 0, false, (pMesh != NULL)))
		{
			gMesh = pMesh;
			SltMenuId = EDIT_NEW_MTL;
		}
		ImGui::Separator();
		ImGui::EndMenu();
	}

	AddMtl();
}

void AddMtl()
{
	if (SltMenuId != EDIT_NEW_MTL)
		return;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize;
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(10.0f, 30.0f), ImGuiCond_Always, ImVec2(0.0, 0.0f));
	static float color[4] = { 0.4f,0.7f,0.0f,0.5f };

	if (ImGui::Begin("Material Dialog", nullptr, window_flags))
	{
		ImGui::ColorEdit4("Color", color);
		ImGui::Separator();

		// 적용 버튼
		if (ImGui::Button("Apply"))
		{
			EgMaterial *pMtl = ::create_material("", color[0], color[1], color[2], 32.0);
			gMesh->AddMaterial(pMtl);
			gMesh->SetMaterial(pMtl);
			ImGui::CloseCurrentPopup();
			SltMenuId = 0;
			theEditor.Reset();
			theSelector.SelectMesh(gMesh->m_Name);
		}

		// 취소 버튼
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			SltMenuId = 0;
			theEditor.Reset();
			theSelector.SelectMesh(gMesh->m_Name);
		}
	}
	ImGui::End();
}