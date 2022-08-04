#pragma once

/*!
*	\brief	3���� �׸��� ������ BV�� 1���� �ε����� ���Ѵ�.
*	\note	������ ������: 2021-02-15
*
*	\param	Box[in]		�׸��� �ڽ��� ����
*	\param	nGrid[in]	�׸��� �ڽ��� ũ��(����/����/���� ����)
*	\param	pos[in]		�ڽ� ���� ������ ��ġ
*
*	\return	���� 1���� �ε����� ��ȯ�Ѵ�.
*/
int get_grid_idx(EgBox &Box, int nGrid, EgPos pos);

/*!
*	\brief	���������� ������ ������ ���Ѵ�.
*
*	\param	Pts[in]		���������� ������ ����Ʈ
*	\param	Ns[out]		�� ������ ������ ������ ����ȴ�.
*	\param	bClosed[in]	���� ���������� ��� true
*/
void get_offset_direction(std::vector<EgPos> Pts, std::vector<EgVec3> &Ns, bool bClosed);

/*!
*	\brief	���������� ������ ��踦 ���Ѵ�.
*
*	\param	Pts[in]			���������� ������ ����Ʈ
*	\param	Ns[in]			�� ������ ������ ����
*	\param	Offset[in]		������ �Ÿ�
*	\param	OffsetPts[out]	������ ��� ������ ����ȴ�.
*	\param	bClosed[in]		���� ���������� ��� true
*	\param	bTrimmed[in]	�ڱⱳ���� ������ ��� true
*
*	\return	������ ��� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool get_offset_polyline(
	std::vector<EgPos> Pts,
	std::vector<EgVec3> Ns,
	double Offset,
	std::vector<EgPos> &OffsetPts,
	bool bClosed,
	bool bTrimmed);

/*!
*	\brief	������ �޽��� ���Ѵ�.
*	\note	������ ������: 2021-03-20
*	\note	AABB Ÿ�� BVH�� ����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	Offset[in]		������ �Ÿ�
*	\param	pMeshBvh[in]	��� �޽��� BVH
*	\param	FreeVerts[out]	�ǽ� ���� ������ (����) ������ ����ȴ�.
*	\param	FixedVerts[out]	���� ������ ����ȴ�.
*	\param	bTrimmed[in]	�ǽ� ���� Ʈ���� ����
*	\param	NumIters[in]	���� ������ ���� �ּ�ȭ�� ������ �ݺ� ��(����Ʈ = 7)
*
*	\return	�������� ����� �޽��� ��ȯ�Ѵ�.
*/
EgMesh *get_offset_mesh(
	EgMesh *pMesh,
	double Offset,
	EgBvh *pMeshBvh,	
	std::vector<EgVertex *> &FreeVerts,
	std::vector<EgVertex *> &FixedVerts,
	bool bTrimmed,
	int NumIters = 7);

/*!
*	\brief	������ �޽��� ���Ѵ�.
*	\note	������ ������: 2021-03-20
*	\note	BVH�� ������� �ʴ´�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	Offset[in]		������ �Ÿ�
*	\param	FreeVerts[out]	�ǽ� ���� ������ (����) ������ ����ȴ�.
*	\param	FixedVerts[out]	���� ������ ����ȴ�.
*	\param	bTrimmed[in]	�ǽ� ���� Ʈ���� ����
*	\param	NumIters[in]	���� ������ ���� �ּ�ȭ�� ������ �ݺ� ��(����Ʈ = 7)
*
*	\return	�������� ����� �޽��� ��ȯ�Ѵ�.
*/
EgMesh *get_offset_mesh(
	EgMesh *pMesh,
	double Offset,
	std::vector<EgVertex *> &FreeVerts,
	std::vector<EgVertex *> &FixedVerts,
	bool bTrimmed,
	int NumIters = 7);

