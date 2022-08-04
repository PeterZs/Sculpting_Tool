#include "stdafx.h"
#include "EgForm.h"

/*!
*	\brief	메쉬의 정점 배열을 내부 정점 + 경계 정점 순으로 변경한다.
*
*	\param	pMesh[in/out]		대상 메쉬
*	\param	NumIntrVerts[out]	내부 정점의 수가 저장된다.
*	\param	NumBndryVerts[out]	외부 정점의 수가 저장된다.
*/
void rearrange_mesh_vert(EgMesh *pMesh, int &NumIntrVerts, int &NumBndryVerts)
{
	// 내부 정점의 리스트를 구한다.
	std::vector<EgVertex *> IntrVerts;
	NumIntrVerts = ::get_intr_verts(pMesh, IntrVerts);

	// 모든 경계를 구한다.
	std::vector<std::vector<EgVertex *>> BndryList;
	int NumBndry = ::get_bndry_verts(pMesh, BndryList, false, false);

	// Non-manifold 메쉬거나, 경계가 없는 메쉬라면 리턴한다.
	if (NumBndry == -1 || NumBndry == 0)
	{
		printf("No boundary vertices......\n");
		NumBndryVerts = 0;
		return;
	}

	// 경계 정점의 리스트를 구한다.
	std::vector<EgVertex *> BndryVerts;
	for (int i = 0; i < NumBndry; ++i)
		for (EgVertex *v : BndryList[i])
			BndryVerts.push_back(v);
	NumBndryVerts = (int)BndryVerts.size();

	// 메쉬 정점의 순서를 내부정점-경계정점으로 구분한다.
	IntrVerts.insert(IntrVerts.end(), BndryVerts.begin(), BndryVerts.end());
	pMesh->m_pVerts.swap(IntrVerts);
	pMesh->UpdateVertIdx();
}

/*!
*	\brief	메쉬 경계를 고정한 채, 최소 면적을 갖는 메쉬로 변형한다.
*
*	\param	pMesh[in/out]		대상 메쉬
*	\param	bUniformWgt[in]		라플라스 행렬의 균등 가중치 사용 여부
*/
void get_mesh_min_area(EgMesh *pMesh, bool bUniformWgt)
{
	// 1. 메쉬의 정점을 내부 정점(k) + 경계 정점(l) 순으로 배열 한다.
	int k, l;
	rearrange_mesh_vert(pMesh, k, l);

	// 2. Laplace 행렬을 구한다.
	Eigen::SparseMatrix<double> D;	// D = (k + l) by (k + l)
	Eigen::SparseMatrix<double> M;	// M = (k + l) by (k + l)
	// 구현 하세요....

	// 3. M을 블록 행렬로 나누기
	Eigen::SparseMatrix<double> A, B;
	// 구현 하세요....

	// 4. 경계 조건을 이용하여 Ax = b의 우변 벡터 구하기
	Eigen::VectorXd b1(k), b2(k), b3(k);
	// 구현 하세요....
	
	// 5. 선형시스템 Ax1 = b1, Ax2 = b2, Ax3 = b3 풀기
	Eigen::VectorXd x1(k), x2(k), x3(k);
	// 구현 하세요....
	
	// 6. 내부 정점의 좌표를 갱신한다.
	for (int i = 0; i < k; ++i)
		pMesh->m_pVerts[i]->m_Pos.Set(x1[i], x2[i], x3[i]);
	pMesh->UpdateBndBox();
	pMesh->UpdateNormal();
	pMesh->m_VertexBuf.clear();
	pMesh->m_NormalBuf.clear();
	pMesh->m_TexelBuf.clear();
}

//void CreateMenuHw()
//{
//	EgMesh *pMesh = theSelector.GetSltMesh();
//
//	if (ImGui::BeginMenu("Homework"))
//	{
//		if (ImGui::MenuItem("Create Mesh wih Minimal Area", 0, false, pMesh != NULL))
//		{
//			get_mesh_min_area(pMesh, 0);
//		}
//
//		if (ImGui::MenuItem("Decimate", 0, false, pMesh != NULL))
//		{
//			EgDecimator tool(pMesh, false);
//			tool.Init(EgDecimator::TypeCollapse::COLLAPSE_OPT_POS);		// 	COLLAPSE_OPT_POS = 0, COLLAPSE_MID_POS, COLLAPSE_END_POS,
//			tool.Decimate(pMesh->GetNumVert() * 0.5);
//		}
//
//		ImGui::EndMenu(); // Help
//	}
//}