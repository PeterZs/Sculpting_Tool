#pragma once

EgMesh* get_blockout_mesh(
	EgMesh* pMesh,
	EgVec3 BlockoutDirection, 
	std::vector<EgPos>& before = std::vector<EgPos>(),
	std::vector<EgPos>& after = std::vector<EgPos>()
);

/*!
*	\brief	Blockout Direction�� �ݴ�������� Ray�� �� �浹�ϸ� Free vertex, �ƴϸ� Fixed vertex�� �з��Ѵ�.
*	\note	������ ������: 2021-08-19
*
*	\param	pMesh[in]  		        �޽ÿ� ���� ������
*   \param  BlockoutDirection[in]   Blockout�� ����
*	\param	FreeVerts[out]	        Free vertices
*	\param	FixedVerts[out]	        Fixed vertices
*   \param  FreeVertsFlag[out]      Vertex�� idx�� �������� �� Free Vertex�̸� true, Fixed Vertex�� false�� ����
*/
void get_free_vertices(
	EgMesh* pMesh,
	EgVec3 BlockoutDirection, 
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts,
	std::vector<bool> &FreeVertFlag
);

/*!
*	\brief	Mesh ���� Free vertex�� ���� Laplacian system�� Ǭ��. (cot. weight)
*	\note	������ ������: 2021-08-19
*
*	\param	pMesh[in]  		        �޽ÿ� ���� ������
*	\param	FreeVerts[in]	        Free vertices
*	\param	FixedVerts[in]	        Fixed vertices
*/
void solve_laplacian_system_on_free_vertices(
	EgMesh* pMesh,
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts
);

/*!
*	\brief	Mesh ���� Free vertex�� ���� Laplacian system�� Ǭ��. (uniform weight)
*	\note	������ ������: 2021-08-20
*
*	\param	pMesh[in]  		        �޽ÿ� ���� ������
*	\param	FreeVerts[in]	        Free vertices
*	\param	FixedVerts[in]	        Fixed vertices
*/
void solve_uniform_laplacian_system_on_free_vertices(
	EgMesh* pMesh,
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts
);

/*!
*	\brief	���Էο� ���� ������ �� �� Ȥ�� �� ���� fixed vertice�� �������� ���� plane�� ã��, vertex�� �� plane ������ projection ��Ų��.
*	\note	������ ������: 2021-11-03
*
*	\param	pMesh[in]  		    �޽ÿ� ���� ������
*	\param	v[out]			    ����� ���Ÿ� ���� �̵��Ǵ� ����
*	\param	TaperAngle[in]		����� ��� ����
*	\param	BlockoutDir[in]		���Է��� ����
*	\param	FreeVertFlag[out]	����� ������ ����� �÷��� �迭
*/
void find_adjacent_plane_and_projection(
	EgMesh* pMesh,
	EgVertex* v,
	EgVec3 BlockoutDirection,
	double TaperAngle,
	std::vector<bool> &FreeVertFlag,
	std::vector<EgVec3>& dbgP = std::vector<EgVec3>(),
	std::vector<EgVec3>& dbgP2 = std::vector<EgVec3>()
);