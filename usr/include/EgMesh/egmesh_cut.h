#pragma once

/*!
*	\brief	���� �޽��� ������(����)�� ���ϴ� �Լ�
*	\note	���� �������� ���, ù ��° ���� ������ �� ��° ���� ������ ���� �ﰢ���� ���Ե�
*
*	\param	pMesh[in]			��� �޽�
*	\param	Pln[in]				���� ���
*	\param	CutPtList[out]		�������� ��ġ�� ����ȴ�.
*	\param	CutEdgeList[out]	���� ������ ����ȴ�.
*	\param	bSort[in]			����� �������� ���̿� ���� ������������ ���� ����
*
*	\return	����� �������� ���� ��ȯ�Ѵ�.
*/
int intersect_mesh_plane(
	EgMesh *pMesh, 
	EgPlane *Pln, 
	std::vector<std::vector<EgPos>> &CutPtList, 
	std::vector<std::vector<EdgeCut>> &CutEdgeList,
	bool bSort);

/*!
*	\brief	���� �޽��� �������� ���̾�� �߰��Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	Pln[in]			���� ���
*	\param	NumWire[in]		���̾ �߰��� �������� ��(�����̸� ��� �������� ���̾�� �߰��Ѵ�)
*	\param	WireVerts[out]	���� ������ ����(=���� ������)���� ������� ����ȴ�.
*	\param	bClosed[out]	�߰��� ���̾��� ���� ���ΰ� ����ȴ�.
*/
void add_wire_by_plane_cut(
	EgMesh *pMesh, 
	EgPlane *Pln, 
	int NumWires,
	std::vector<std::vector<EgVertex *>> &WireVerts, 
	std::vector<bool> &bClosed);

/*!
*	\brief	�޽� ���� ���� �����ϴ� �������� ���̾�� �߰��Ѵ�.
*	\note	�߰��� �޽� ���� ������ ������ �ﰢ�� ���� �����ص� ����
*
*	\param	pMesh[in]		��� �޽�
*	\param	Pts[in]			�޽� ���� �� ����Ʈ
*	\param	WireVerts[out]	�߰��� ������ �����Ͱ� �����
*/
void add_wire_by_geodesic(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> Pts, 
	std::vector<EgVertex *> &WireVerts);

/*!
*	\brief	�޽� ���� ���� �����ϴ� ���� �������� ���̾�� �߰��Ѵ�.
*	\note	�޽� ���� ������ ���� �ٸ� �ﰢ�� ���� �����Ѵٰ� ����
*
*	\param	pMesh[in]		��� �޽�
*	\param	Pts[in]			�޽� ���� �� ����Ʈ
*	\param	WireVerts[out]	�߰��� ������ �����Ͱ� �����
*/
void add_wire_by_geodesic_aniso(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> Pts, 
	std::vector<EgVertex *> &WireVerts);

/*!
*	\brief	�޽��� ���������� �����ϴ� �Լ�
*	\note	������ ������: 2021-07-31
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	Pts[in]			���� ��θ� �����ϴ� �޽� ���� �� ����Ʈ
*
*	\return	�����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool cut_mesh_by_geodesic(EgMesh *pMesh, std::vector<EgMeshPt> Pts);

/*!
*	\brief	�޽��� ���� ���������� �����ϴ� �Լ�
*	\note	������ ������: 2021-10-05
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	Pts[in]			���� ��θ� �����ϴ� �޽� ���� �� ����Ʈ
*
*	\return	�����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool cut_mesh_by_geodesic_aniso(EgMesh *pMesh, std::vector<EgMeshPt> Pts);

/*!
*	\brief	�޽��� �� ������ �մ� ���������� �����ϴ� �Լ�
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	S[in]		�������� ���� ����
*	\param	E[in]		�������� �� ����
*/
void cut_mesh_by_geodesic(EgMesh *pMesh, EgVertex *S, EgVertex *E);

/*!
*	\brief	�޽� ���� ���� �������� �߰��Ѵ�.
*	\note	�޽� ���� ���� ������ ������ ������
*
*	\param	pMesh[in]		��� �޽�
*	\param	Pts[in]			�߰��� �޽� ���� ��
*	\param	Verts[out]		�߰��� ���ο� �������� ����ȴ�.
*/
void add_mesh_pts(EgMesh *pMesh, const std::vector<EgMeshPt> &Pts, std::vector<EgVertex *> &Verts);

