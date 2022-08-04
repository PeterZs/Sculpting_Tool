#pragma once

/*!
*	\brief	평면과 메쉬의 교차점(정보)을 구하는 함수
*	\note	열린 교차선인 경우, 첫 번째 교차 에지와 두 번째 교차 에지는 동일 삼각형에 포함됨
*
*	\param	pMesh[in]			대상 메쉬
*	\param	Pln[in]				절단 평면
*	\param	CutPtList[out]		교차점의 위치가 저장된다.
*	\param	CutEdgeList[out]	교차 정보가 저장된다.
*	\param	bSort[in]			연결된 교차선의 길이에 따른 내림차순으로 정렬 여부
*
*	\return	연결된 교차선의 수를 반환한다.
*/
int intersect_mesh_plane(
	EgMesh *pMesh, 
	EgPlane *Pln, 
	std::vector<std::vector<EgPos>> &CutPtList, 
	std::vector<std::vector<EdgeCut>> &CutEdgeList,
	bool bSort);

/*!
*	\brief	평면과 메쉬의 교차선을 와이어로 추가한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Pln[in]			절단 평면
*	\param	NumWire[in]		와이어를 추가할 교차선의 수(음수이면 모든 교차선을 와이어로 추가한다)
*	\param	WireVerts[out]	새로 생성된 정점(=에지 절단점)들이 순서대로 저장된다.
*	\param	bClosed[out]	추가한 와이어의 닫힘 여부가 저장된다.
*/
void add_wire_by_plane_cut(
	EgMesh *pMesh, 
	EgPlane *Pln, 
	int NumWires,
	std::vector<std::vector<EgVertex *>> &WireVerts, 
	std::vector<bool> &bClosed);

/*!
*	\brief	메쉬 위의 점을 연결하는 측지선을 와이어로 추가한다.
*	\note	추가할 메쉬 위의 점들은 동일한 삼각형 위에 존재해도 가능
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Pts[in]			메쉬 위의 점 리스트
*	\param	WireVerts[out]	추가된 정점의 포인터가 저장됨
*/
void add_wire_by_geodesic(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> Pts, 
	std::vector<EgVertex *> &WireVerts);

/*!
*	\brief	메쉬 위의 점을 연결하는 비등방 측지선을 와이어로 추가한다.
*	\note	메쉬 위의 점들은 서로 다른 삼각형 위에 존재한다고 가정
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Pts[in]			메쉬 위의 점 리스트
*	\param	WireVerts[out]	추가된 정점의 포인터가 저장됨
*/
void add_wire_by_geodesic_aniso(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> Pts, 
	std::vector<EgVertex *> &WireVerts);

/*!
*	\brief	메쉬를 측지선으로 절단하는 함수
*	\note	마지막 수정일: 2021-07-31
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	Pts[in]			측지 경로를 구성하는 메쉬 위의 점 리스트
*
*	\return	성공하면 true, 아니면 false를 반환한다.
*/
bool cut_mesh_by_geodesic(EgMesh *pMesh, std::vector<EgMeshPt> Pts);

/*!
*	\brief	메쉬를 비등방 측지선으로 절단하는 함수
*	\note	마지막 수정일: 2021-10-05
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	Pts[in]			측지 경로를 구성하는 메쉬 위의 점 리스트
*
*	\return	성공하면 true, 아니면 false를 반환한다.
*/
bool cut_mesh_by_geodesic_aniso(EgMesh *pMesh, std::vector<EgMeshPt> Pts);

/*!
*	\brief	메쉬를 두 정점을 잇는 측지선으로 절단하는 함수
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	S[in]		측지선의 시작 정점
*	\param	E[in]		측지선의 끝 정점
*/
void cut_mesh_by_geodesic(EgMesh *pMesh, EgVertex *S, EgVertex *E);

/*!
*	\brief	메쉬 위의 점을 정점으로 추가한다.
*	\note	메쉬 위의 점은 임의의 순서가 가능함
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Pts[in]			추가할 메쉬 위의 점
*	\param	Verts[out]		추가된 새로운 정점들이 저장된다.
*/
void add_mesh_pts(EgMesh *pMesh, const std::vector<EgMeshPt> &Pts, std::vector<EgVertex *> &Verts);

