#pragma once

/*! \brief 각 정점에서 소스점까지의 최단 거리 정보를 표현하는 노드 */
typedef QNode<EgVertex *, double> Dist2Src;

/*! \brief 에지의 절단 정보를 표현하는 자료형 */
typedef std::pair<EgEdge *, float> EdgeCut;

/*!
*	\brief	메쉬 위의 두 점의 인접한 삼각형들간의 중첩 삼각형을 구한다.
*
*	\param	P[in]				메쉬 위의 점
*	\param	Q[in]				메쉬 위의 점
*	\param	OverlapFaces[out]	중첩 삼각형들이 저장된다.
*
*	\return 중첩 삼각형의 수를 반환한다.
*/
int get_one_ring_overlap_faces(EgMeshPt *P, EgMeshPt *Q, std::vector<EgFace *> &OverlapFaces);

/*!
*	\brief	메쉬 위의 점에서 경계 거리 이내의 각 정점까지의 최소 거리를 계산한다.
*	\note	1. 경계 외부의 삼각형 정점들까지의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				메쉬 위의 점
*	\param	Distances[out]		i번째 정점까지의 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	소스 점에서 타겟 점까지의 거리 내의 정점들의 측지 거리장을 계산하는 함수
*	\note	1. 타겟 점까지 거리보다 먼 정점들의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				소스 점에 대한 포인터
*	\param	T[in]				타겟 점에 대한 포인터
*	\param	Distances[out]		소스 점에서 i번째 정점까지의 거리가 Distances[i]에 저장된다.
*
*	\return 실제 구해진 최대 거리를 반환한다.
*/
double get_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, EgMeshPt *T, std::vector<double> &Distances);

/*!
*	\brief	소스 정점(삼각형)들에서 경계 거리(BndryDistance) 이내의 삼각형(교차 포함)의 각 정점까지의 최소 거리를 계산한다.
*	\note	1. 타겟 점까지 거리보다 먼 정점들의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	SrcList[in]			메쉬의 소스점 리스트
*	\param	Distances[out]		i번째 정점까지의 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_geodesic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &SrcList, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	메쉬 위의 점에서 경계 거리 이내의 각 정점까지의 최소 거리를 계산한다.
*	\note	1. 경계 외부의 삼각형 정점들까지의 거리는 DBL_MAX로 설정된다.
*			2. 참고 논문: Geodesic Distance Computation via Virtual Source Propagation, SGP2021
*
*	\param	pMesh[in]			대상 메쉬
*	\param	SrcList[in]			메쉬의 소스점 리스트
*	\param	Distances[out]		i번째 정점까지의 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_geodesic_dist_field_gsp(EgMesh *pMesh, std::vector<EgObject *> &SrcList, std::vector<double> &Distances, double Dist2Bndry);

/*!
*   \brief	소스 정점들에서 메쉬 각 정점까지의 최소 거리를 Heat Method에 의해 계산한다.
*
*   \param  pMesh[in]       대상 메쉬
*   \param  SrcVerts[in]	선택된 메쉬 상의 정점 리스트
*   \param  Distances[out]  선택된 정점들에서 i번째 정점까지의 거리가 Distances[i]에 저장된다.
*   \param  Time[in]        열 필드를 구성할 시간
*
*   \return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_heat_dist_field(EgMesh *pMesh, std::vector<EgVertex *> &SrcVerts, std::vector<double> &Distances, double Time);

/*!
*   \brief	메쉬의 제약 정점으로 열 필드를 구성한다.
*
*   \param	pMesh[in]		대상 메쉬
*   \param	OneVerts[in]	소스 정점(제약값 1을 갖는다)의 리스트
*   \param	Field[out]		i번째 정점의 열 필드값이 Field[i]에 저장된다.
*   \param	Time[in]		시뮬레이션 시간
*/
double get_heat_flow_field(EgMesh *pMesh, std::vector<EgVertex *> &SrcVerts, std::vector<double> &Field, double Time);

/*!
*	\brief	소스 정점에서 경계 거리(BndryDistance) 이내의 삼각형(교차 삼각형 포함)의 각 정점까지 에지를 따르는 최소 거리를 계산한다.
*	\note	1. 경계 외부 삼각형의 정점들까지의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				소스 정점에 대한 포인터
*	\param	Distances[out]		소스 정점에서 i번째 정점까지의 에지 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_edge_dist_field(EgMesh *pMesh, EgVertex *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	소스 정점에서 경계 거리 이내의 정점까지의 위상 거리를 계산하는 함수
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				소스 정점
*	\param	Distances[out]		소스 정점에서 i번째 정점까지의 위상 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 위상 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 위상 거리(>= 경계 거리)를 반환한다.
*/
int get_topology_dist_field(EgMesh *pMesh, EgVertex *S, std::vector<int> &Distances, int Dist2Bndry);

/*!
*	\brief	메쉬 위의 두 점 사이의 최단 경로와 교차 정보를 구하는 함수
*
*	\param	S[in]				시작점
*	\param	E[in]				끝점
*	\param	Distances[in]		시작점 기준 측지 거리장
*	\param	Path[out]			시작점 ~ 끝점으로 최단 경로를 구성하는 점들(시작점 + 에지 교차점 + 끝점)이 저장된다.
*	\param	CutEdgeList[out]	시작점 ~ 끝점으로 최단 경로의 교차 에지 정보가 저장된다. (경로를 우-좌로 통과하는 에지)
*	\param	bReverse[in]		끝점 ~ 시작점으로의 경로와 정보를 구할 경우 true, 아니면 false
*
*	\return 두 점 사이의 최단 거리를 반환하고 실패하면 -1을 반환한다.
*/
double get_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<double> &Distances, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);

/*!
*	\brief	메쉬 위의 두 점 사이의 최단 경로와 교차 정보를 구하는 함수
*
*	\param	S[in]			시작점
*	\param	E[in]			끝점
*	\param	Path[out]		시작점 ~ 끝점으로 최단 경로를 구성하는 점들(시작점 + 에지 교차점 + 끝점)이 저장된다.
*	\param	CutEdges[out]	시작점 ~ 끝점으로 최단 경로의 교차 에지 정보가 저장된다. (경로를 우-좌로 통과하는 에지)
*	\param	bReverse[in]	끝점 ~ 시작점으로의 경로와 정보를 구할 경우 true, 아니면 false
*
*	\return 두 점 사이의 최단 거리를 반환한다.
*/
double get_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdges, bool bReverse = false);

/*!
*	\brief	두 점을 연결하는 평면 절단 경로와 거리를 계산한다.
*	\note	경로가 홀에 의해 끊어지면 홀을 통과하여 절단 경로를 구성한다.
*	\note	마지막 수정일: 2021-01-03
*
*	\param	S[in]			시작점에 대한 포인터
*	\param	E[in]			끝점에 대한 포인터
*	\param	Pln[in]			절단 평면에 대한 포인터(법선 방향에 따라 시작점에서 절단 방향이 정해진다).
*	\param	Path[out]		절단 경로를 구성하는 에지 교차점이 저장된다.
*	\param	CutInfo[out]	절단 평면을 아래서 위로 통과하는 에지의 절단 정보가 저장된다.
*
*	\return 경로의 길이를 반환한다(에러가 발생하면 -1.0을 반환한다).
*/
double get_planar_path(EgMeshPt *S, EgMeshPt *E, EgPlane *Pln, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutInfo);

/*!
*	\brief	평면과 에지의 교차 정보를 구하는 함수
*	\note	마지막 수정일: 2020-06-29
*	\note	중복 교차를 피하기 위해 [시작점, 끝점) 형태의 vertex spliting을 사용
*
*	\param	Pln[in]		평면에 대한 포인터
*	\param	e[in]		조사할 에지 e=(P, Q)에 대한 포인터
*	\param	t[out]		에지가 평면을 아래서 위로 교차할 경우, 교차점의 파라미터 값(0.0 <= t < 1.0)이 저장된다.
*
*	\return	에지가 평면을 아래서 위로 교차할 경우 true, 그렇지 않으면 false를 반환한다.
*/
bool intersect_plane_edge(EgPlane *Pln, EgEdge *e, float *t = NULL);

/*!
*	\brief	광선(반직선)과 에지(선분)의 교차 정보를 구하는 함수
*	\note	마지막 수정일: 2020-12-26
*	\note	중복 교차를 피하기 위해 에지를 [시작점, 끝점) 형태로 광선은 (시작점, 끝점]의 형태로 splitting 실시
*
*	\param	Ray[in]		광선(반직선), 시작점은 포함되지 않는 것으로 간주
*	\param	pEdge[in]	조사할 에지 e=[P, Q)에 대한 포인터
*	\param	t[out]		에지가 광선과 교차할 경우, 에지 위에서 교차점의 파라미터 값(0.0 <= t < 1.0)이 저장된다.
*	\param	pt[out]		교차점이 저장됨
*
*	\return	에지가 광선과 교차하는 경우 true, 그렇지 않으면 false를 반환한다.
*/
bool intersect_ray_edge(EgLine Ray, EgEdge *pEdge, float *t, EgPos *pt);

/*!	\brief	평면 절단을 통해 둘레 경로와 길이를 계산하는 함수
*	\note	마지막 수정일: 2020-06-22
*
*	\param	S[in]			절단 경로의 시작점에 대한 포인터
*	\param	Pln[in]			절단 평면에 대한 포인터
*	\param	Path[out]		경로를 구성하는 교차점의 위치가 저장된다.
*	\param	CutInfo[out]	절단 평면을 아래서 위로 통과하는 에지의 절단 정보가 저장된다.
*
*	\return 경로가 존재하면 둘레의 길이를 없다면 -1.0을 반환한다.
*/
double get_planar_path_closed(EgMeshPt *P, EgPlane *Pln, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutInfo);

/*!
*	\brief	메쉬 위의 두 점 P와 Q를 내분하는 점을 계산한다.
*	\author	하유진
*
*	\param	pMesh[in]	대상 메쉬
*	\param	P[in]		시작점에 대한 포인터
*	\param	Q[in]		끝점에 대한 포인터
*	\param	t[in]		내분 파라미터 0 <= t <= 1.0
*
*	\return 두 점 P와 Q를 t : 1 - t로 내분하는 점 R을 반환한다.
*/
EgMeshPt glerp(EgMesh *pMesh, EgMeshPt *P, EgMeshPt *Q, double t);

/*!
*	\brief	메쉬 위의 두 점 P와 Q를 내분하는 점을 계산한다.
*	\author	하유진
*
*	\param	pMesh[in]			대상 메쉬
*	\param	P[in]				시작점에 대한 포인터
*	\param	Q[in]				끝점에 대한 포인터
*	\param	t[in]				내분 파라미터 0 <= t <= 1.0
*	\param	dist[in]			시작점에서 끝점까지의 거리
*	\param	CutPts[in]			경로의 교차점 리스트
*	\param	CutEdgeList[in]		경로의 교차점 정보 리스트
*
*	\return 두 점 P와 Q를 t : 1 - t로 내분하는 점 R을 반환한다.
*/
EgMeshPt glerp(EgMesh *pMesh, EgMeshPt *P, EgMeshPt *Q, double t, double dist, std::vector<EgPos> &CutPts, std::vector<EdgeCut> &CutInfo);

/*!
*   \brief  메쉬 위의 점 P에서 V 방향으로 길이 |V|를 갖는 측지선과 끝점을 구한다.
*	\note	마지막 수정일: 2020-12-16
*
*   \param  pMesh[in]	대상 메쉬
*   \param  P[in]		삼각형 위의 시작점
*   \param  V[in]		측지선의 방향과 길이(삼각형 위에 있어야 함)
*   \param  Path[out]	측지선과 에지의 교차점이 저장됨
*
*   \return 측지선의 끝점을 반환한다.
*/
EgMeshPt get_straight_geodesic(EgMesh *pMesh, EgMeshPt *P, EgVec3 V, std::vector<EgPos> &Path);

/*!
*   \brief  메쉬 위에서 측지선의 다음 방향(단위 길이)을 구한다.
*
*   \param  Dir[in]		측지선의 방향
*   \param  pEdge[in]	측지선과 교차한 다음 삼각형 위의 에지
*
*   \return 측지선의 다음 방향을 반환한다.
*/
EgVec3 get_next_geodesic_direction(EgVec3 Dir, EgEdge *pEdge);

/*!
*   \brief	메쉬 정점 위에서 측지선의 다음 방향을 구한다.
*   \author 하유진
*
*   \param  Dir[in]			측지선의 방향
*   \param  pEdge[in/out]	교차한 엣지, 방향을 구한 후 다음 에지의 포인터가 저장됨
*
*   \return	측지선의 다음 방향을 반환한다.
*/
EgVec3 get_next_geodesic_direction_on_vertex(EgVec3 Dir, EgEdge **pEdge);

/*!
*   \brief	새로운 위치로 평행 이동된 메쉬 위의 벡터를 구한다.
*
*   \param  v[in]	입력 벡터
*   \param  p[in]	새로운 시작점
*
*   \return	새로운 위치로 평행 이동된 메쉬 위의 벡터를 반환한다.
*/
EgMeshVec get_translated_vec(EgMeshVec v, EgMeshPt p);
