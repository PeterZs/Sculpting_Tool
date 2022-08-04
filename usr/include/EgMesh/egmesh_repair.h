#pragma once

/*!
*	\brief	메쉬의 분리된 쉘(삼각형 집합)을 찾는다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	ShellList[out]	분리된 쉘이 저장된다.
*
*	\return 분리된 삼각형 집합의 수를 반환한다.
*/
int find_isolated_shells(EgMesh *pMesh, std::vector<std::list<EgFace *>> &Shells);

/*!
*	\brief	메쉬의 분리된 쉘(삼각형 집합)을 제거한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거된 쉘의 수를 반환한다.
*/
int delete_isolated_shells(EgMesh *pMesh);

/*!
*	\brief	메쉬의 중복 정점을 찾는다.
*	\note	마지막 수정일: 2021-08-24
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Verts[out]	Non-manifold 정점이 저장된다.
*	\param	eps[in]		수치 허용 오차
*
*	\return 중복 정점 수를 반환한다.
*/
int find_duplicate_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts, double eps = 1.0e-14);

/*!
*	\brief	메쉬의 중복 정점을 제거한다.
*	\note	마지막 수정일: 2021-08-24
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	eps[in]		수치 허용 오차
*
*	\return 제거된 정점 수를 반환한다.
*/
int delete_duplicate_verts(EgMesh *pMesh, double eps = 1.0e-14);

/*!
*	\brief	메쉬의 non-manifold 정점을 찾는다.
*	\note	마지막 수정일: 2021-08-24
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Verts[out]	Non-manifold 정점이 저장된다.
*
*	\return Non-manifold 정점 수를 반환한다.
*/
int find_non_manifold_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	메쉬의 non-manifold 정점을 제거한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거된 정점 수를 반환한다.
*/
int delete_non_manifold_verts(EgMesh *pMesh);

/*!
*	\brief	Non-manifold 에지를 찾는다.
*	\note	마지막 수정일: 2021-08-25
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Edges[out]	Non-manifold 에지가 저장된다.
*
*	\return Non-manifold 에지의 수를 반환한다.
*/
int find_non_manifold_edges(EgMesh *pMesh, std::vector<EgEdge *> &Edges);

/*!
*	\brief	Non-manifold 에지를 제거한다.
*	\note	Non-manifold 에지에 연결된 삼각형을 제거하는게 최선인가???
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거한 non-manifold 에지를 포함한 삼각형의 개수를 반환한다.
*/
int delete_non_manifold_edges(EgMesh *pMesh);

/*!
*	\brief	퇴화된 삼각형(면적이 0에 가까운)을 찾는다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Faces[out]	퇴화된 삼각형들이 저장된다.
*	\param	eps[in]		퇴화된 삼각형을 판단하기 위한 허용 오차
*
*	\return 퇴화된 삼각형 수를 반환한다.
*/
int find_degenerate_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces, double eps = 1.0e-6);

/*!
*	\brief	퇴화(degenerate) 삼각형을 제거한다.
*	\note	마지막 수정일: 2021-08-23
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	eps[in]		퇴화된 삼각형을 판단하기 위한 허용 오차
*
*	\return 제거한 삼각형의 수를 반환한다.
*/
int delete_degenerate_faces(EgMesh *pMesh, double eps = 1.0e-6);

/*!
*	\brief	메쉬의 미사용 정점을 찾는다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Verts[out]	미사용 정점이 저장된다.
*
*	\return 미사용 정점 수를 반환한다.
*/
int find_unused_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	메쉬의 미사용 정점을 제거한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거된 정점의 수를 반환한다.
*/
int delete_unused_verts(EgMesh *pMesh);

/*!
*	\brief	메쉬에서 사용되지 않는 텍셀을 찾는다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	Texels[out]		미사용 텍셀이 저장된다.
*
*	\return 미사용 텍셀 수를 반환한다.
*/
int find_unused_texels(EgMesh *pMesh, std::vector<EgTexel *> &Texels);

/*!
*	\brief	메쉬의 미사용 텍셀을 제거한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거된 텍셀의 수를 반환한다.
*/
int delete_unused_texels(EgMesh *pMesh);

/*!
*	\brief	메쉬에서 미사용 법선을 찾는다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	Normals[out]	미사용 법선이 저장된다.
*
*	\return 미사용 법선의 수를 반환한다.
*/
int find_unused_normals(EgMesh *pMesh, std::vector<EgNormal *> &Normals);

/*!
*	\brief	메쉬에서 미사용 법선을 제거한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*
*	\return 제거된 법선 수를 반환한다.
*/
int delete_unused_normals(EgMesh *pMesh);

/*!
*	\brief	세 점이 모두 경계 정점인 뾰족한 (코너)삼각형을 찾는다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Faces[out]	코너 삼각형이 저장된다.
*
*	\return 코너 삼각형의 수를 반환한다.
*/
int find_corner_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces);

/*!
*	\brief	세 점이 모두 경계 정점인 뾰족한 (코너)삼각형을 제거한다.
*	\note	Non-manifold 정점이 새로 만들어 질 수 있음.
*
*	\param	pMesh[in] 대상 메쉬에 대한 포인터
*
*	\return 제거된 코너 삼각형 수를 반환한다.
*/
int delete_corner_faces(EgMesh *pMesh);

/*!
*	\brief	메쉬의 자기 교차 삼각형을 찾는다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Faces[out]	자기 교차 삼각형들이 저장된다.
*	\param	Lines[out]	교차 라인들이 저장된다
*
*	\return 자기 교차가 발생한 삼각형의 수를 반환한다.
*/
int find_self_intersection(EgMesh *pMesh, std::vector<EgFace *> &Faces,	std::vector<std::pair<EgPos, EgPos>> &Lines);

/*!
*	\brief	메쉬의 자기 교차 삼각형을 제거한다.
*
*	\param	pMesh[in] 대상 메쉬
*
*	\return 제거된 자기 교차 삼각형의 수를 반환한다.
*/
int delete_self_intersection(EgMesh *pMesh);

/*!
*	\brief	메쉬 오류 정보를 출력한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*/
void report_artifact(EgMesh *pMesh);

/*!
*	\brief	메쉬 오류 정보를 수정한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*/
void repair_artifact(EgMesh *pMesh);

/*!
*	\brief	메쉬 오류 정보를 반복적으로 수정한다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	MaxIters[in]	최대 반복 회수(디폴트 50)
*/
void repair_artifact_repeat(EgMesh *pMesh, int MexIters = 30);

/*!
*	\brief	메쉬의 홀을 채운다.
*	\note	홀이 여러 개인 경우, 가장 긴 홀은 채우지 않는다.
*			홀 경계에서 중접된 정점을 제거하기 위해서는 delete_duplicate_verts() 함수를 호출해야 한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	FillType[in]		홀 패치 타입(0: 최소 면적, 1: 최소 곡률합, 2: 최소 곡률 변화율)
*	\param	bStitch[in]			홀 패치와 메쉬의 연결 여부(true: 연결, false: 미연결)
*/
void fill_holes(EgMesh *pMesh, int FillType, bool bStitch);
