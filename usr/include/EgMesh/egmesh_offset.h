#pragma once

/*!
*	\brief	3차원 그리드 형태의 BV의 1차원 인덱스를 구한다.
*	\note	마지막 수정일: 2021-02-15
*
*	\param	Box[in]		그리드 박스의 정보
*	\param	nGrid[in]	그리드 박스의 크기(가로/세로/높이 동일)
*	\param	pos[in]		박스 내의 조사할 위치
*
*	\return	계산된 1차원 인덱스를 반환한다.
*/
int get_grid_idx(EgBox &Box, int nGrid, EgPos pos);

/*!
*	\brief	폴리라인의 오프셋 방향을 구한다.
*
*	\param	Pts[in]		폴리라인의 정점의 리스트
*	\param	Ns[out]		각 정점의 오프셋 방향이 저장된다.
*	\param	bClosed[in]	닫힌 폴리라인의 경우 true
*/
void get_offset_direction(std::vector<EgPos> Pts, std::vector<EgVec3> &Ns, bool bClosed);

/*!
*	\brief	폴리라인의 오프셋 경계를 구한다.
*
*	\param	Pts[in]			폴리라인의 정점의 리스트
*	\param	Ns[in]			각 정점의 오프셋 방향
*	\param	Offset[in]		오프셋 거리
*	\param	OffsetPts[out]	오프셋 경계 정점이 저장된다.
*	\param	bClosed[in]		닫힌 폴리라인의 경우 true
*	\param	bTrimmed[in]	자기교차를 제거할 경우 true
*
*	\return	성공인 경우 true, 아니면 false를 반환한다.
*/
bool get_offset_polyline(
	std::vector<EgPos> Pts,
	std::vector<EgVec3> Ns,
	double Offset,
	std::vector<EgPos> &OffsetPts,
	bool bClosed,
	bool bTrimmed);

/*!
*	\brief	오프셋 메쉬를 구한다.
*	\note	마지막 수정일: 2021-03-20
*	\note	AABB 타입 BVH를 사용한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Offset[in]		오프셋 거리
*	\param	pMeshBvh[in]	대상 메쉬의 BVH
*	\param	FreeVerts[out]	피쉬 테일 영역의 (자유) 정점이 저장된다.
*	\param	FixedVerts[out]	고정 정점이 저장된다.
*	\param	bTrimmed[in]	피쉬 테일 트리밍 여부
*	\param	NumIters[in]	자유 정점의 면적 최소화를 수행할 반복 수(디폴트 = 7)
*
*	\return	오프셋이 적용된 메쉬를 반환한다.
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
*	\brief	오프셋 메쉬를 구한다.
*	\note	마지막 수정일: 2021-03-20
*	\note	BVH를 사용하지 않는다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Offset[in]		오프셋 거리
*	\param	FreeVerts[out]	피쉬 테일 영역의 (자유) 정점이 저장된다.
*	\param	FixedVerts[out]	고정 정점이 저장된다.
*	\param	bTrimmed[in]	피쉬 테일 트리밍 여부
*	\param	NumIters[in]	자유 정점의 면적 최소화를 수행할 반복 수(디폴트 = 7)
*
*	\return	오프셋이 적용된 메쉬를 반환한다.
*/
EgMesh *get_offset_mesh(
	EgMesh *pMesh,
	double Offset,
	std::vector<EgVertex *> &FreeVerts,
	std::vector<EgVertex *> &FixedVerts,
	bool bTrimmed,
	int NumIters = 7);

