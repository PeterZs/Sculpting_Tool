#include "stdafx.h"
#include "EgForm.h"

void CreateCurvaturePlot(EgMesh *pMesh, std::vector<double> &Field, double RangeMin, double RangeMax)
{
	// ���콺 ����� �����Ͽ� ���� �������� �����Ѵ�.
	std::vector<double> Copy = Field;
	sort(Copy.begin(), Copy.end());

	// ������� �Է� ������ �ּҰ��� �ִ밪�� ���ϰ� ����Ѵ�.
	double VisualMin = Copy[(int)(RangeMin * (NUM(Copy) - 1))];
	double VisualMax = Copy[(int)(RangeMax * (NUM(Copy) - 1))];
	printf("\tVisual range(%.0lf%% ~ %.0lf%%) = [%.15lf ~ %.15lf]\n", RangeMin * 100, RangeMax * 100, VisualMin, VisualMax);
	printf("\tColor mapping = [Blue(<=%.15lf) ~ Green(%.15lf) ~ Red(>=%.15lf)]\n\n", VisualMin, (VisualMin + VisualMax) * 0.5, VisualMax);
	pMesh->CreateDisplayListOfScalarField(Field, VisualMin, VisualMax, 2, 0, EgVec3());
}

void CreateMenuAnalyze()
{
	EgMesh *pMesh = theSelector.GetSltMesh();
	bool bEnabled, bSelected;

	EgVec3 a;
	if (ImGui::BeginMenu("Analyze"))
	{
		// �ϸ�� �ʵ� ���� �޴�
		if (ImGui::MenuItem("Create Harmonic Field", 0, false, pMesh != NULL))
		{
			std::vector<EgVertex *> OneVerts;
			std::vector<EgVertex *> HalfVerts;
			std::vector<EgVertex *> ZeroVerts;
			OneVerts.push_back(pMesh->GetVert(5341));
			ZeroVerts.push_back(pMesh->GetVert(4882));
			std::vector<double> Field;
			::get_harmonic_field(pMesh, OneVerts, HalfVerts, ZeroVerts, Field, false, 0);
			pMesh->CreateDisplayListOfScalarField(Field, 0.0, 1.0, 2, 50, EgVec3(1.0, 1.0, 1.0));
		}

		// ���, �ֹ��� ���� ���� ���� �м�
		if (ImGui::BeginMenu("Curvature"))
		{
			bSelected = false;
			bEnabled = (pMesh != NULL) ? true : false;

			// ������ ���� ���� �м�
			if (ImGui::MenuItem("Mixed Voronoi Cell", 0, bSelected, bEnabled))
			{
				pMesh->CreateDisplayListOfLocalRegion();
			}

			// ��� ��� �м�
			if (ImGui::MenuItem("Mean Curvature(Discrete)", 0, bSelected, bEnabled))
			{
				// ������ ����� ���Ѵ�.
				double Hmin, Hmax;
				std::vector<double> Hs;
				::get_mean_curvature(pMesh, Hs, Hmin, Hmax);

				// ����� ����ȭ �Ѵ�.
				CreateCurvaturePlot(pMesh, Hs, 0.05, 0.95);
			}
						
			// ���콺 ��� �м�
			if (ImGui::MenuItem("Gaussian Curvature(Discrete)", 0, bSelected, bEnabled))
			{
				// ������ ���콺 ����� ���Ѵ�.
				double Kmin, Kmax;
				std::vector<double> Ks;				
				::get_gaussian_curvature(pMesh, Ks, Kmin, Kmax);

				// ����� ����ȭ �Ѵ�.
				CreateCurvaturePlot(pMesh, Ks, 0.05, 0.95);
			}
						
			// �ְ�� �� �ֹ��� �м�
			if (ImGui::MenuItem("Principal Directions(Discrete)", 0, bSelected, bEnabled))
			{
				// �̻� �̺� �����п� ���� ���
				int NumVert = pMesh->GetNumVert();
				std::vector<EgVec3> e1, e2;
				for (int i = 0; i < NumVert; ++i)
				{
					double k1, k2;
					EgVec3 v1, v2;
					::get_principal_curvature(pMesh->m_pVerts[i], k1, k2, v1, v2, 0);
					k1 = ABS(k1);
					k2 = ABS(k2);
					if (k1 < k2)
					{
						SWAP(double, k1, k2);
						SWAP(EgVec3, v1, v2);
					}
					e1.push_back(v1);
					e2.push_back(v2);
				}
				pMesh->CreateDisplayListOfVectorField(e1, e2, false, EgVec3(1.0, 0.0, 0.0), EgVec3(1.0, 0.0, 0.0), EgVec3(0.0, 1.0, 0.0), EgVec3(0.0, 1.0, 0.0));
			}
			
			ImGui::EndMenu();
		}

		// �Ÿ��� �м�
		/*! \brief ������ ������ �������� ���� �Ÿ����� �����Ѵ�. */
		bEnabled = (pMesh != NULL && (theSelector.GetClsNameSltObj() == "EgVertex"
			|| theSelector.GetClsNameSltObj() == "EgFace"
			|| theSelector.GetClsNameSltObj() == "EgMeshPt")) ? true : false;
		bSelected = false;
		if (ImGui::MenuItem("Geodesic Distance Field By Distance Propagation", 0, bSelected, bEnabled))
		{
			// �ҽ� �������� ���� �Ÿ����� ����ϰ�
			gScalarField.clear();
			double MaxDist = ::get_geodesic_dist_field(pMesh, theSelector.m_SltObjList, gScalarField, -1.0);
			pMesh->CreateDisplayListOfScalarField(gScalarField, 0.0, MaxDist, 0, 32, EgVec3(0.8, 0.8, 0.8));
		}

		// �׷����Ʈ �ʵ� �м�
		bEnabled = (pMesh != NULL && !gScalarField.empty()) ? true : false;
		bSelected = false;
		if (ImGui::MenuItem("Gradient Field(from Scalar Field)", 0, bSelected, bEnabled))
		{
			// �޽� ���� ��Į�� �ʵ忡�� �׷����Ʈ���� ����Ѵ�.
			std::vector<EgVec3> Gradients;
			::get_gradient_field(pMesh, gScalarField, Gradients, true);

			// �׷����Ʈ���� ����ȭ �ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
			pMesh->CreateDisplayListOfVectorField(Gradients, true, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
		}

		if (ImGui::BeginMenu("Normal Vector"))
		{
			bEnabled = (pMesh != NULL) ? true : false;
			bSelected = false;
			// �ﰢ�� ���� �м�
			if (ImGui::MenuItem("Face Normal", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_FACE);
				std::vector<EgVec3> Normals;
				for (EgNormal *n : pMesh->m_pNormals)
					Normals.push_back(n->m_Dir);

				// ���� �������� ����ȭ�ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
				pMesh->CreateDisplayListOfVectorField(Normals, true, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
			}

			// ���� ���� �м�
			if (ImGui::MenuItem("Vertex Normal", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_VERTEX);
				std::vector<EgVec3> Normals;
				for (EgNormal *n : pMesh->m_pNormals)
					Normals.push_back(n->m_Dir);

				// ���� �������� ����ȭ�ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
				pMesh->CreateDisplayListOfVectorField(Normals, false, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
			}			
			ImGui::EndMenu();	// NormalVector �޴�
		}		

		ImGui::EndMenu(); // Analyze �޴�
	}
}