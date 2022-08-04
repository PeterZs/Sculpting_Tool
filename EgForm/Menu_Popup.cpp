#include "stdafx.h"
#include "EgForm.h"

void CreateMenuMaterial()
{
	EgMesh *pMesh = theSelector.GetSltMesh();
	if (ImGui::MenuItem("Random Material", 0, false, (pMesh != NULL)))
	{
		EgMaterial *pMtl = ::create_material_random();
		pMesh->AddMaterial(pMtl);
		pMesh->SetMaterial(pMtl);
	}
}
