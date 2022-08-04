#pragma once

EgMesh* get_blockout_mesh(
	EgMesh* pMesh,
	EgVec3 BlockoutDirection, 
	std::vector<EgPos>& before = std::vector<EgPos>(),
	std::vector<EgPos>& after = std::vector<EgPos>()
);

/*!
*	\brief	Blockout Direction의 반대방향으로 Ray를 쏴 충돌하면 Free vertex, 아니면 Fixed vertex로 분류한다.
*	\note	마지막 수정일: 2021-08-19
*
*	\param	pMesh[in]  		        메시에 대한 포인터
*   \param  BlockoutDirection[in]   Blockout의 방향
*	\param	FreeVerts[out]	        Free vertices
*	\param	FixedVerts[out]	        Fixed vertices
*   \param  FreeVertsFlag[out]      Vertex의 idx로 접근했을 때 Free Vertex이면 true, Fixed Vertex면 false를 저장
*/
void get_free_vertices(
	EgMesh* pMesh,
	EgVec3 BlockoutDirection, 
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts,
	std::vector<bool> &FreeVertFlag
);

/*!
*	\brief	Mesh 위의 Free vertex에 대해 Laplacian system을 푼다. (cot. weight)
*	\note	마지막 수정일: 2021-08-19
*
*	\param	pMesh[in]  		        메시에 대한 포인터
*	\param	FreeVerts[in]	        Free vertices
*	\param	FixedVerts[in]	        Fixed vertices
*/
void solve_laplacian_system_on_free_vertices(
	EgMesh* pMesh,
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts
);

/*!
*	\brief	Mesh 위의 Free vertex에 대해 Laplacian system을 푼다. (uniform weight)
*	\note	마지막 수정일: 2021-08-20
*
*	\param	pMesh[in]  		        메시에 대한 포인터
*	\param	FreeVerts[in]	        Free vertices
*	\param	FixedVerts[in]	        Fixed vertices
*/
void solve_uniform_laplacian_system_on_free_vertices(
	EgMesh* pMesh,
	std::vector<EgVertex*>& FreeVerts,
	std::vector<EgVertex*>& FixedVerts
);

/*!
*	\brief	삽입로와 가장 인접한 두 개 혹은 한 개의 fixed vertice를 기준으로 만든 plane을 찾고, vertex를 이 plane 상으로 projection 시킨다.
*	\note	마지막 수정일: 2021-11-03
*
*	\param	pMesh[in]  		    메시에 대한 포인터
*	\param	v[out]			    언더컷 제거를 위해 이동되는 정점
*	\param	TaperAngle[in]		언더컷 허용 각도
*	\param	BlockoutDir[in]		삽입로의 방향
*	\param	FreeVertFlag[out]	언더컷 정점을 기록한 플래그 배열
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