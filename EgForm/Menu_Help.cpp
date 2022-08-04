#include "stdafx.h"
#include "EgForm.h"
//
//void CreateMenuHelp()
//{
//	static int SltMenuId = 0;
//	if (ImGui::BeginMenu("Help"))
//	{
//		if (ImGui::MenuItem("About..."))
//		{
//			SltMenuId = 1;			
//		}
//
//		if (ImGui::MenuItem("Hot Keys..."))
//		{
//			SltMenuId = 2;
//		}
//		ImGui::EndMenu(); // Help
//	}
//
//	// About 메뉴
//	if (SltMenuId == 1)
//	{
//		ImGui::OpenPopup("About EgForm");
//		if (ImGui::BeginPopupModal("About EgForm", 0, ImGuiWindowFlags_AlwaysAutoResize))
//		{
//			ImGui::Text("EgForm (version 1.0.0)");
//			ImGui::Text("Developer: Jungho Park and Seung-Hyun Yoon");
//			ImGui::Text("Contact: shyun@dongguk.edu");
//			ImGui::Text("http://gaia.dongguk.edu");
//			ImGui::Text("Copyright (c) 2019 - 2021");
//			ImGui::Separator();
//			if (ImGui::Button("    Ok    "))
//			{
//				ImGui::CloseCurrentPopup();
//				SltMenuId = 0;
//			}
//			ImGui::EndPopup();
//		}
//	}
//
//	// Hot Keys 메뉴
//	if (SltMenuId == 2)
//	{
//		ImGui::OpenPopup("Hot Keys");
//		if (ImGui::BeginPopupModal("Hot Keys", 0, ImGuiWindowFlags_AlwaysAutoResize))
//		{	
//			ImGui::Text("Q/q: Auto camera position");
//			ImGui::Text("H/h: Home camera position");
//			ImGui::Separator();
//
//			ImGui::Text("O/o: Orthogonal projection");
//			ImGui::Text("P/p: Perspective projection");
//			ImGui::Separator();
//
//			ImGui::Text("s: Smoothing");
//			ImGui::Separator();
//
//			ImGui::Text("T: Edit position");
//			ImGui::Text("R: Edit orientation");
//			ImGui::Text("S: Edit size");
//			ImGui::Separator();
//
//			ImGui::Text("f: Front view");
//			ImGui::Text("t: Top view");
//			ImGui::Separator();
//
//			ImGui::Text("b: Show boundary");
//			ImGui::Text("g: Show floor");
//			ImGui::Text("w: Wireframe rendering");
//			ImGui::Separator();
//
//			ImGui::Text("F: Select face");
//			ImGui::Text("V: Select vertex");
//			ImGui::Text("G: Select face group");
//			ImGui::Text("B: Select face by brush");
//			ImGui::Text("X: Select mesh point");
//			ImGui::Separator();
//
//			ImGui::Text("x: Rotation about X-axis");
//			ImGui::Text("y: Rotation about Y-axis");
//			ImGui::Text("z: Rotation about Z-axis");
//			ImGui::Separator();
//			if (ImGui::Button("    Ok    "))
//			{
//				ImGui::CloseCurrentPopup();
//				SltMenuId = 0;
//			}
//			ImGui::EndPopup();
//		}
//	}
//}