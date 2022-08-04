#pragma once

/*! \brief 에지 분할 정보를 표현하는 자료형 */
typedef QNode<EgEdge *, double> EdgeSplit;

/*!
*	\brief	에지 제거 가능 여부를 판단한다.
*
*	\param	e[in]			제거할 에지에 대한 포인터
*	\param	Low[in]			제거할 에지는 길이가 Low보다 짧아야 한다.
*	\param	High[in]		제거후, High보다 긴 에지가 생성되면 제거하지 못한다.
*
*	\return 제거 가능하면 true, 아니면 false를 반환한다.
*/
bool is_collapsable(EgEdge *e, double Low, double High);

/*!
*	\brief	에지 플립 조건을 검사한다.
*
*	\param	e[in]	검사할 에지의 포인터
*
*	\return 플립 조건을 통과하면 true, 아니면 false를 반환한다.
*/
bool is_flippable(EgEdge *e);

/*!
*	\brief	점진적 리메싱을 수행한다.
*	\note	현재 텍스처 미지원
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	TarLenOrRate[in]	목표 에지의 길이 또는 평균 에지 길이 대비 비율
*	\param	bRate[in]			비율이면 true, 길이면 false
*	\param	bFixedBndry[in]		경계를 고정시키려면 true, 아니면 false를 지정
*	\param	FixedVerts[in]		Relaxation 적용시 고정시킬 정점의 리스트
*/
void remesh(EgMesh *pMesh, double TarLenOrRate, bool bRate, bool bFixedBndry, std::vector<EgVertex *> &FixedVerts = std::vector<EgVertex *>());

/*!
*	\brief	메쉬의 에지를 분할한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	High[in]			분할 기준 길이(High 보다 긴 에지를 분할)
*	\param	bUpdateNormal[in]	에지 분할 후, 법선 갱신 여부
*/
void remesh_edge_split(EgMesh *pMesh, double High, bool bUpdateNormal = true);

/*!
*	\brief	메쉬의 에지 e = (v1, v2)를 제거한다.
*	\note	v1이 v2쪽으로 합쳐지고, v1은 사용하지 않는 정점이 된다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	Low[in]				제거 기준 길이(Low 보다 짧은 에지를 제거)
*	\param	High[in]			에지 제거 후, High 보다 긴 에지가 생성되면 제거하지 않는다.
*	\param	bFixedBndry[in]		경계 에지를 무조건 보존하려면 true, 아니면 false
*	\param	bUpdateNormal[in]	에지 분할 후, 법선 갱신 여부
*/
void remesh_edge_collapse(EgMesh *pMesh, double Low, double High, bool bFixedBndry, bool bUpdateNormal = true);

/*!
*	\brief	에지 플립을 통해 정점의 차수를 정규화 한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	bUpdateNormal[in]	에지 플립 후, 법선 갱신 여부
*/
void remesh_edge_flip(EgMesh *pMesh, bool bUpdateNormal = true);

/*!
*	\brief	정점의 위치를 접평면으로 투영한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	FixedVerts[in]		고정시킬 정점의 리스트
*/
void remesh_relaxation(EgMesh *pMesh, std::vector<EgVertex *> &FixedVerts = std::vector<EgVertex *>());

/*!
*	\brief	선택 영역에 대한 점진적 리메싱을 수행한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	TarLenOrRate[in]	타겟 에지 길이 또는 비율
*	\param	bRate[in]			true 이면 타겟 에지 길이, false이면 비율
*	\param	Faces[in]			선택 영역의 삼각형 리스트
*/
void remesh_region(EgMesh *pMesh, double TarLenOrRate, bool bRate, std::vector<EgFace *> &Faces);

/*!
*	\brief	선택 영역의 에지를 분할한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	High[in]		High보다 긴 에지를 분할한다.
*	\param	FixedFaces[in]	고정 영역의 삼각형 리스트
*/
void remesh_edge_split_region(EgMesh *pMesh, double High, std::vector<EgFace *> &FixedFaces);

/*!
*	\brief	선택 영역의 에지 e = (v1, v2)를 제거한다.
*	\note	v1이 v2쪽으로 합쳐지고, v1은 사용하지 않는 정점이 된다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	Low[in]				Low 보다 짧은 에지를 제거한다.
*	\param	High[in]			에지 제거 후, High 보다 긴 에지가 생성되면 제거하지 않는다.
*	\param	bFixedBndry[in]		경계 에지를 무조건 보존하려면 true, 아니면 false
*	\param	FixedFaces[in]		선택 영역의 삼각형 리스트
*/
void remesh_edge_collapse_region(EgMesh *pMesh, double Low, double High, bool bFixedBndry, std::vector<EgFace *> &FixedFaces);

/*!
*	\brief	메쉬 경계를 리메싱 한다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	LenOrRate[in]	목표 에지의 길이 또는 평균 에지 길이 대비 비율
*	\param	bRate[in]		비율이면 true, 길이면 false
*/
void remesh_bndry(EgMesh *pMesh, double TarLenOrRate, bool bRate);
