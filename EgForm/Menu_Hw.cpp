#include "stdafx.h"
#include "EgForm.h"

/*!
*	\brief	�޽��� ���� �迭�� ���� ���� + ��� ���� ������ �����Ѵ�.
*
*	\param	pMesh[in/out]		��� �޽�
*	\param	NumIntrVerts[out]	���� ������ ���� ����ȴ�.
*	\param	NumBndryVerts[out]	�ܺ� ������ ���� ����ȴ�.
*/
void rearrange_mesh_vert(EgMesh *pMesh, int &NumIntrVerts, int &NumBndryVerts)
{
	// ���� ������ ����Ʈ�� ���Ѵ�.
	std::vector<EgVertex *> IntrVerts;
	NumIntrVerts = ::get_intr_verts(pMesh, IntrVerts);

	// ��� ��踦 ���Ѵ�.
	std::vector<std::vector<EgVertex *>> BndryList;
	int NumBndry = ::get_bndry_verts(pMesh, BndryList, false, false);

	// Non-manifold �޽��ų�, ��谡 ���� �޽���� �����Ѵ�.
	if (NumBndry == -1 || NumBndry == 0)
	{
		printf("No boundary vertices......\n");
		NumBndryVerts = 0;
		return;
	}

	// ��� ������ ����Ʈ�� ���Ѵ�.
	std::vector<EgVertex *> BndryVerts;
	for (int i = 0; i < NumBndry; ++i)
		for (EgVertex *v : BndryList[i])
			BndryVerts.push_back(v);
	NumBndryVerts = (int)BndryVerts.size();

	// �޽� ������ ������ ��������-����������� �����Ѵ�.
	IntrVerts.insert(IntrVerts.end(), BndryVerts.begin(), BndryVerts.end());
	pMesh->m_pVerts.swap(IntrVerts);
	pMesh->UpdateVertIdx();
}

/*!
*	\brief	�޽� ��踦 ������ ä, �ּ� ������ ���� �޽��� �����Ѵ�.
*
*	\param	pMesh[in/out]		��� �޽�
*	\param	bUniformWgt[in]		���ö� ����� �յ� ����ġ ��� ����
*/
void get_mesh_min_area(EgMesh *pMesh, bool bUniformWgt)
{
	// 1. �޽��� ������ ���� ����(k) + ��� ����(l) ������ �迭 �Ѵ�.
	int k, l;
	rearrange_mesh_vert(pMesh, k, l);

	// 2. Laplace ����� ���Ѵ�.
	Eigen::SparseMatrix<double> D;	// D = (k + l) by (k + l)
	Eigen::SparseMatrix<double> M;	// M = (k + l) by (k + l)
	// ���� �ϼ���....

	// 3. M�� ��� ��ķ� ������
	Eigen::SparseMatrix<double> A, B;
	// ���� �ϼ���....

	// 4. ��� ������ �̿��Ͽ� Ax = b�� �캯 ���� ���ϱ�
	Eigen::VectorXd b1(k), b2(k), b3(k);
	// ���� �ϼ���....
	
	// 5. �����ý��� Ax1 = b1, Ax2 = b2, Ax3 = b3 Ǯ��
	Eigen::VectorXd x1(k), x2(k), x3(k);
	// ���� �ϼ���....
	
	// 6. ���� ������ ��ǥ�� �����Ѵ�.
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