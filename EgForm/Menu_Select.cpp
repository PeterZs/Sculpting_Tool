#include "stdafx.h"
#include "EgForm.h"

void CreateMenuSelect()
{
	EgMesh *pMesh = theSelector.GetSltMesh();
	if (ImGui::BeginMenu("Select"))
	{
		if (ImGui::BeginMenu("Select Tool"))
		{			
			if (ImGui::MenuItem("Rect", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_RECT))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_RECT;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Brush", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_BRUSH))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_BRUSH;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Lasso", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_LASSO))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_LASSO;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Circle", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_CIRCLE))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_CIRCLE;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Polyline", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_POLY))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_POLY;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Magic Wand(Basic)", 0, theSelector.m_SelectToolType == TypeSelectTool::SELECT_TOOL_MAGIC_WAND_BASIC, pMesh != NULL))
			{
				theSelector.m_SelectToolType = TypeSelectTool::SELECT_TOOL_MAGIC_WAND_BASIC;
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_MESH_PT;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Select Entity"))
		{
			if (ImGui::MenuItem("Mesh", 0, theSelector.m_SelectObjType == TypeSelectObj::SELECT_MESH))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_MESH;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Vertices", 0, theSelector.m_SelectObjType == TypeSelectObj::SELECT_VERT))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_VERT;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("Faces", 0, theSelector.m_SelectObjType == TypeSelectObj::SELECT_FACE))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_FACE;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			if (ImGui::MenuItem("MeshPt", 0, theSelector.m_SelectObjType == TypeSelectObj::SELECT_MESH_PT))
			{
				theSelector.m_SelectObjType = TypeSelectObj::SELECT_MESH_PT;
				theEditor.m_EditToolType = EDIT_INACTIVE;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Select Options"))
		{
			if (ImGui::MenuItem("Front Only", 0, theSelector.m_SelectModeType == TypeSelectMode::SELECT_MODE_FRONT_ONLY))
			{
				theSelector.m_SelectModeType = TypeSelectMode::SELECT_MODE_FRONT_ONLY;
			}
			if (ImGui::MenuItem("See Through", 0, theSelector.m_SelectModeType == TypeSelectMode::SELECT_MODE_SEE_THROUGH))
			{
				theSelector.m_SelectModeType = TypeSelectMode::SELECT_MODE_SEE_THROUGH;
			}
			if (ImGui::MenuItem("Inverse Selection", 0, theSelector.m_bInverseSelect))
			{
				theSelector.m_bInverseSelect = !theSelector.m_bInverseSelect;
			}
			if (ImGui::MenuItem("Inverse Now"))
			{
				theSelector.InverseSltObjList();
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}
}
