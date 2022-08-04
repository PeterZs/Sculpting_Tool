#include "stdafx.h"
#include "EgForm.h"

void CreateMenuDelete()
{
	if (ImGui::MenuItem("Delete"))
	{
		theEditor.DeleteObject();
		theSelector.Reset();
	}

	if (ImGui::MenuItem("Exit"))
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplGLUT_Shutdown();
		ImGui::DestroyContext();
		exit(-1);
	}
}