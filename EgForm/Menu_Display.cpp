#include "stdafx.h"
#include "EgForm.h"

void CreateMenuDisplay()
{
	EgMesh *pMesh = theSelector.GetSltMesh();
	bool bSelected, bEnabled;

	if (ImGui::BeginMenu("Rendering"))
	{
		bSelected = false;
		bEnabled = (pMesh == NULL) ? false : true;
		if (ImGui::MenuItem("Reset", 0, bSelected, bEnabled))
		{
			if (pMesh != NULL)
			{
				pMesh->m_RenderOption = RENDER_POLYGON | RENDER_BACK_FACE;
				// 메쉬의 디스플레이 리스트를 제거한다.
				pMesh->DeleteDisplayListOfAnalysis();
			}
		}
		ImGui::Separator();
		
		bSelected = (pMesh != NULL && pMesh->m_RenderOption & RENDER_POINT) ? true : false;
		bEnabled = (pMesh != NULL) ? true : false;
		if (ImGui::MenuItem("Points", 0, bSelected, bEnabled))
		{
			if (pMesh->m_RenderOption & RENDER_POINT)
				pMesh->m_RenderOption &= (~RENDER_POINT);
			else
				pMesh->m_RenderOption |= RENDER_POINT;
		}

		bSelected = (pMesh != NULL && pMesh->m_RenderOption & RENDER_POLYGON) ? true : false;
		bEnabled = (pMesh != NULL) ? true : false;
		if (ImGui::MenuItem("Polygon", 0, bSelected, bEnabled))
		{
			if (pMesh->m_RenderOption & RENDER_POLYGON)
				pMesh->m_RenderOption &= (~RENDER_POLYGON);
			else
				pMesh->m_RenderOption |= RENDER_POLYGON;
		}

		bSelected = (pMesh != NULL && pMesh->m_RenderOption & RENDER_WIRE) ? true : false;
		bEnabled = (pMesh != NULL) ? true : false;
		if (ImGui::MenuItem("Wireframe", 0, bSelected, bEnabled))
		{
			if (pMesh->m_RenderOption & RENDER_WIRE)
				pMesh->m_RenderOption &= (~RENDER_WIRE);
			else
				pMesh->m_RenderOption |= RENDER_WIRE;
		}
		ImGui::Separator();
		
		bSelected = (pMesh != NULL && pMesh->m_RenderOption & RENDER_TEXTURE) ? true : false;
		bEnabled = (pMesh != NULL && !pMesh->m_pTexels.empty() && !pMesh->m_pTextures.empty()) ? true : false;
		if (ImGui::MenuItem("Texture", 0, bSelected, bEnabled))
		{
			if (pMesh->m_RenderOption & RENDER_TEXTURE)
				pMesh->m_RenderOption &= (~RENDER_TEXTURE);
			else
				pMesh->m_RenderOption |= RENDER_TEXTURE;
		}

		bSelected = (pMesh != NULL && pMesh->m_RenderOption & RENDER_BACK_FACE) ? true : false;
		bEnabled = (pMesh != NULL) ? true : false;
		if (ImGui::MenuItem("Back Face", 0, bSelected, bEnabled))
		{
			if (pMesh->m_RenderOption & RENDER_BACK_FACE)
				pMesh->m_RenderOption &= (~RENDER_BACK_FACE);
			else
				pMesh->m_RenderOption |= RENDER_BACK_FACE;
		}
		ImGui::Separator();

		bSelected = (pMesh != NULL && pMesh->m_pMaterials[0]->m_Diffuse[3] != 1.0) ? true : false;
		bEnabled = (pMesh != NULL && !pMesh->m_pMaterials.empty()) ? true : false;
		if (ImGui::MenuItem("Transparent", 0, bSelected, bEnabled))
		{
			if (pMesh->m_pMaterials[0]->m_Diffuse[3] == 1.0)
				pMesh->SetTransparent(0.5f);
			else
				pMesh->SetTransparent(1.0f);
		}
		ImGui::Separator();

		if (ImGui::BeginMenu("Shading"))
		{
			bEnabled = (pMesh != NULL && pMesh->m_NormalType == NORMAL_VERTEX) ? true : false;
			bSelected = (pMesh != NULL && pMesh->m_NormalType == NORMAL_FACE) ? true : false;
			if (ImGui::MenuItem("Flat", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_FACE);
			}

			bEnabled = (pMesh != NULL && pMesh->m_NormalType == NORMAL_FACE) ? true : false;
			bSelected = (pMesh != NULL && pMesh->m_NormalType == NORMAL_VERTEX) ? true : false;
			if (ImGui::MenuItem("Gouraud", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_VERTEX);
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();

		if (ImGui::BeginMenu("GUIs"))
		{
			bSelected = (theScene.m_bShowBkg) ? true : false;
			if (ImGui::MenuItem("Grad. Bkg.", 0, bSelected, true))
			{
				theScene.m_bShowBkg = !theScene.m_bShowBkg;
			}
			bSelected = (theScene.m_bShowFloor) ? true : false;
			if (ImGui::MenuItem("Floor", 0, bSelected, true))
			{
				theScene.m_bShowFloor = !theScene.m_bShowFloor;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}