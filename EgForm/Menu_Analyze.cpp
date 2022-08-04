#include "stdafx.h"
#include "EgForm.h"

void CreateCurvaturePlot(EgMesh *pMesh, std::vector<double> &Field, double RangeMin, double RangeMax)
{
	// 가우스 곡률을 복사하여 오름 차순으로 정렬한다.
	std::vector<double> Copy = Field;
	sort(Copy.begin(), Copy.end());

	// 곡률에서 입력 범위의 최소값과 최대값을 구하고 출력한다.
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
		// 하모닉 필드 생성 메뉴
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

		// 곡률, 주방향 등을 통한 형상 분석
		if (ImGui::BeginMenu("Curvature"))
		{
			bSelected = false;
			bEnabled = (pMesh != NULL) ? true : false;

			// 정점의 국소 영역 분석
			if (ImGui::MenuItem("Mixed Voronoi Cell", 0, bSelected, bEnabled))
			{
				pMesh->CreateDisplayListOfLocalRegion();
			}

			// 평균 곡률 분석
			if (ImGui::MenuItem("Mean Curvature(Discrete)", 0, bSelected, bEnabled))
			{
				// 정점의 평균을 구한다.
				double Hmin, Hmax;
				std::vector<double> Hs;
				::get_mean_curvature(pMesh, Hs, Hmin, Hmax);

				// 곡률을 가시화 한다.
				CreateCurvaturePlot(pMesh, Hs, 0.05, 0.95);
			}
						
			// 가우스 곡률 분석
			if (ImGui::MenuItem("Gaussian Curvature(Discrete)", 0, bSelected, bEnabled))
			{
				// 정점의 가우스 곡률을 구한다.
				double Kmin, Kmax;
				std::vector<double> Ks;				
				::get_gaussian_curvature(pMesh, Ks, Kmin, Kmax);

				// 곡률을 가시화 한다.
				CreateCurvaturePlot(pMesh, Ks, 0.05, 0.95);
			}
						
			// 주곡률 및 주방향 분석
			if (ImGui::MenuItem("Principal Directions(Discrete)", 0, bSelected, bEnabled))
			{
				// 이산 미분 기하학에 의한 계산
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

		// 거리장 분석
		/*! \brief 선택한 정점을 기준으로 측지 거리장을 생성한다. */
		bEnabled = (pMesh != NULL && (theSelector.GetClsNameSltObj() == "EgVertex"
			|| theSelector.GetClsNameSltObj() == "EgFace"
			|| theSelector.GetClsNameSltObj() == "EgMeshPt")) ? true : false;
		bSelected = false;
		if (ImGui::MenuItem("Geodesic Distance Field By Distance Propagation", 0, bSelected, bEnabled))
		{
			// 소스 정점에서 측지 거리장을 계산하고
			gScalarField.clear();
			double MaxDist = ::get_geodesic_dist_field(pMesh, theSelector.m_SltObjList, gScalarField, -1.0);
			pMesh->CreateDisplayListOfScalarField(gScalarField, 0.0, MaxDist, 0, 32, EgVec3(0.8, 0.8, 0.8));
		}

		// 그래디언트 필드 분석
		bEnabled = (pMesh != NULL && !gScalarField.empty()) ? true : false;
		bSelected = false;
		if (ImGui::MenuItem("Gradient Field(from Scalar Field)", 0, bSelected, bEnabled))
		{
			// 메쉬 위의 스칼라 필드에서 그래디언트장을 계산한다.
			std::vector<EgVec3> Gradients;
			::get_gradient_field(pMesh, gScalarField, Gradients, true);

			// 그래디언트장을 가시화 하는 디스플레이 리스트를 생성한다.
			pMesh->CreateDisplayListOfVectorField(Gradients, true, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
		}

		if (ImGui::BeginMenu("Normal Vector"))
		{
			bEnabled = (pMesh != NULL) ? true : false;
			bSelected = false;
			// 삼각형 법선 분석
			if (ImGui::MenuItem("Face Normal", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_FACE);
				std::vector<EgVec3> Normals;
				for (EgNormal *n : pMesh->m_pNormals)
					Normals.push_back(n->m_Dir);

				// 법선 벡터장을 가시화하는 디스플레이 리스트를 생성한다.
				pMesh->CreateDisplayListOfVectorField(Normals, true, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
			}

			// 정점 법선 분석
			if (ImGui::MenuItem("Vertex Normal", 0, bSelected, bEnabled))
			{
				pMesh->UpdateNormal(NORMAL_VERTEX);
				std::vector<EgVec3> Normals;
				for (EgNormal *n : pMesh->m_pNormals)
					Normals.push_back(n->m_Dir);

				// 법선 벡터장을 가시화하는 디스플레이 리스트를 생성한다.
				pMesh->CreateDisplayListOfVectorField(Normals, false, EgVec3(1.0, 1.0, 0.0), EgVec3(0.0, 0.0, 1.0));
			}			
			ImGui::EndMenu();	// NormalVector 메뉴
		}		

		ImGui::EndMenu(); // Analyze 메뉴
	}
}