#pragma once

class EgVertex;
class EgFace;
class EgMesh;

/*!
*	\brief	메쉬의 정점의 N-링 이웃 정점을 구하는 함수
*
*	\param	pMesh[in]		대상 메쉬
*	\param	pVert[in]		조사할 정점
*	\param	N[in]			조사할 이웃 정점의 최대 링수
*	\param	RingVerts[out]	결과가 저장됨(i-링 이웃 정점은 RingVerts[i][0], ..., RingVerts[i][m]에 저장됨)
*
*	\return 실제 구해진 최대 링수를 반환한다(N 보다 작을 수도 있음)
*/
int get_neighbor_verts(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<std::vector<EgVertex *>> &RingVerts);

/*!
*   \brief	메쉬 경계의 N-링 이웃 정점을 구하는 함수
*   \note	수행 후, 모든 정점의 m_EditWgt는 0으로 초기화된다.
*
*   \param  pMesh[in]		대상 메쉬
*   \param  BndryVerts[in]	조사할 경계 정점 리스트
*   \param  N[in]			조사할 이웃 정점의 최대 링수 (음수인 경우 전체 메쉬를 조사한다.)
*   \param  RingVerts[out]	결과가 저장됨(i-링 이웃 정점은 RingVerts[i][0], ..., RingVerts[i][m]에 저장됨)
*
*   \return 실제 구해진 최대 링수를 반환한다(N 보다 작을 수도 있음)
*/
int get_neighbor_verts(EgMesh *pMesh, std::vector<EgVertex *> &BndryVerts, int N, std::vector<std::vector<EgVertex *>> &RingVerts);

/*!
*	\brief	메쉬 정점의 N-링 삼각형을 구하는 함수
*
*	\param	pMesh[in]	대상 메쉬
*	\param	pVert[in]	조사할 정점
*	\param	N[in]		조사할 이웃 정점의 최대 링수
*	\param	Faces[out]	삼각형이 저장됨
*
*	\return 선택된 삼각형의 수를 반환한다.
*/
int get_neighbor_faces(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<EgFace *> &Faces);

/*!
*	\brief	메쉬 경계 또는 홀 정점의 리스트를 구한다.
*	\note	마지막 수정일: 2021-02-10
*
*	\param	pMesh[in]			대상 메쉬
*	\param	BndryVerts[out]		경계 또는 홀 정점이 저장됨
*	\param	bClockWise[in]		true인 경우 경계는 시계, 홀은 반시계 방향으로, false인 경우 경계는 반시계 홀은 시계 방향으로 저장된다.
*	\param	bSortByLen[in]		true인 경우 경계(홀)의 길이에 따라 오름차순으로 정렬된다.
*
*	\return 경계(홀)의 수를 반환한다(non-manifold 정점이 있다면 -1을 반환한다).
*/
int get_bndry_verts(EgMesh *pMesh, std::vector<std::vector<EgVertex *>> &BndryVerts, bool bClockWise, bool bSortByLen);

/*!
*	\brief	메쉬 경계(홀) 정점의 리스트를 구한다.
*	\note	Manifold 또는 non-manifold 구분 없이 경계 정점을 찾는다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	BndryVerts[out]		경계(홀) 정점이 저장된다.
*
*	\return 경계 정점의 수를 반환한다.
*/
int get_bndry_verts(EgMesh *pMesh, std::vector<EgVertex *> &BndryVerts);

/*!
*	@brief	선택 삼각형의 경계(홀) 정점의 리스트를 구한다.
*	@author 박정호
*
*	@param  Faces[in]		선택된 삼각형의 리스트
*	@param	BndryList[out]	경계(홀) 정점이 저장될 리스트
*	@param	bClockWise[in]	true인 경우 경계(홀) 정점이 시계(반시계) 방향으로, false인 경우 경계(홀) 정점이 반시계(시계) 방향으로 저장된다.
*	@param	bSortByLen[in]	true인 경우 경계(홀)의 길이에 따라 오름차순으로 정렬된다.
*
*	@return 경계(홀)의 수를 반환한다(non-manifold 정점이 있다면 -1을 반환한다).
*/
int get_bndry_verts_from_faces(std::vector<EgFace *> &Faces, std::vector<std::vector<EgVertex *>> &BndryList, bool bClockWise, bool bSortByLen);

/*!
*	\brief	정점에 연결된 경계 삼각형 리스트를 구한다.
*
*	\param	BndryVerts[in]		경계(홀) 정점의 리스트
*	\param	BndryFaces[out]		경계(홀) 정점에 연결된 삼각형 리스트가 저장된다.
*
*	\return 삼각형의 수를 반환한다.
*/
int get_bndry_faces(std::vector<EgVertex *> &BndryVerts, std::vector<EgFace *> &BndryFaces);

/*!
*	\brief	메쉬의 모든 경계 정점에 연결된 삼각형 리스트를 구한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	BndryFaces[out]		경계 정점에 연결된 삼각형의 리스트가 저장됨
*
*	\return	삼각형의 수를 반환한다.
*/
int get_bndry_faces(EgMesh *pMesh, std::vector<EgFace *> &BndryFaces);

/*!
*	\brief	시작 에지에서 연결된 경계 에지의 리스트를 구하는 함수
*
*	\param	pStEdge[in]			시작 에지에 대한 포인터
*	\param	BndryEdges[out]		경계 에지의 리스트가 저장됨
*
*	\return	에지의 수를 반환한다.
*/
int get_bndry_edges(EgEdge *pStEdge, std::vector<EgEdge *> &BndryEdges);

/*!
*	\brief 메쉬 내부 정점의 리스트를 구한다.
*
*	\param pMesh[in]		대상 메쉬
*	\param IntrVerts[out]	내부 정점이 저장된다.
*
*	\return 내부 정점의 수를 반환한다.
*/
int get_intr_verts(EgMesh *pMesh, std::vector<EgVertex *> &IntrVerts);

/*!
*	\brief 선택 삼각형의 정점 리스트를 구한다.
*
*	\param Faces[in]	선택된 삼각형의 리스트
*	\param Verts[out]	선택된 삼각형의 정점이 저장된다.
*
*	\return 정점의 수를 반환한다.
*/
int get_verts_from_faces(const std::vector<EgFace *> &Faces, std::vector<EgVertex *> &Verts);

/*!
*	\brief 선택 삼각형의 내부 정점과 외부 정점의 리스트를 구한다.
*
*	\param Faces[in]		선택된 삼각형의 리스트
*	\param IntrVerts[out]	선택된 삼각형의 내부 정점이 저장된다.
*	\param BndryVerts[out]	선택된 삼각형의 외부 정점이 저장된다.
*
*	\return 정점의 수를 반환한다.
*/
int get_verts_from_faces(const std::vector<EgFace *> &Faces, std::vector<EgVertex *> &IntrVerts, std::vector<EgVertex *> &BndryVerts);

/*!
*	\brief 선택 정점의 삼각형 리스트를 구한다.
*
*	\param Verts[in]	선택된 정점의 리스트
*	\param Faces[out]	선택된 정점의 삼각형이 저장된다.
*
*	\return 삼각형 수를 반환한다.
*/
int get_faces_from_verts(const std::vector<EgVertex *> &Verts, std::vector<EgFace *> &Faces);

/*!
*	\brief	메쉬의 정점을 내부-경계 순으로 재배열 한다.
*
*	\param	pMesh[IN/OUT] 대상 메쉬
*
*	\return 경계의 수를 반환한다.
*/
int rearrange_verts(EgMesh *pMesh);

