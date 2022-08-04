#pragma once

/*!
*	\brief	메쉬 위의 점에서 경계 거리 이내의 각 정점까지의 비등방 측지 거리를 계산한다.
*	\note	1. 처음 호출시 EgMesh::UpdateEdgeLen() 함수를 수행하여, 비등방 에지 거리를 초기화 해야 한다.
*			2. 경계 외부의 삼각형 정점들까지의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				메쉬 위의 소스점
*	\param	Distances[out]		i번째 정점까지의 거리가 Distances[i]에 저장된다.
*	\param	Dist2Bndry[in]		경계까지의 거리(음수인 경우 전체 메쉬를 계산한다)
*
*	\return 실제 구해진 최대 거리(>= 경계 거리)를 반환한다.
*/
double get_aniso_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	소스 점에서 타겟 점까지의 거리 내의 정점들의 비등방 측지 거리장을 계산하는 함수
*	\note	1. 처음 호출시 EgMesh::UpdateEdgeLen() 함수를 수행하여, 비등방 에지 거리를 초기화 해야 한다.
*			2. 타겟 점까지 거리보다 먼 정점들의 거리는 DBL_MAX로 설정된다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	S[in]				소스 점에 대한 포인터
*	\param	T[in]				타겟 점에 대한 포인터
*	\param	Distances[out]		소스 점에서 i번째 정점까지의 거리가 Distances[i]에 저장된다.
*
*	\return 실제 구해진 최대 거리를 반환한다.
*/
double get_aniso_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, EgMeshPt *T, std::vector<double> &Distances);

/*!
*	\brief	메쉬 위의 두 점 사이의 비등방 최단 경로와 교차 정보를 구하는 함수
*	\note	1. 2021-06-13: 초기 구현
*
*	\param	S[in]				시작점
*	\param	E[in]				끝점
*	\param	Distances[in]		시작점 기준의 비등방 측지 거리장
*	\param	Path[out]			시작점 ~ 끝점으로 최단 경로를 구성하는 점들(시작점 + 에지 교차점 + 끝점)이 저장된다.
*	\param	CutEdgeList[out]	시작점 ~ 끝점으로 최단 경로의 교차 에지 정보가 저장된다. (경로를 우-좌로 통과하는 에지)
*	\param	bReverse[in]		끝점 ~ 시작점으로의 경로를 구할 경우 true, 아니면 false
*
*	\return 최단 거리를 반환한다.
*/
double get_aniso_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<double> &Distances, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);

/*!
*	\brief	메쉬 위의 두 점 사이의 비등방 최단 경로와 교차 정보를 구하는 함수
*	\note	마지막 수정일: 2021-10-15
*
*	\param	S[in]				시작점
*	\param	E[in]				끝점
*	\param	Distances[in]		시작점 기준의 비등방 측지 거리장
*	\param	Path[out]			시작점 ~ 끝점으로 최단 경로를 구성하는 점들(시작점 + 에지 교차점 + 끝점)이 저장된다.
*	\param	CutEdgeList[out]	시작점 ~ 끝점으로 최단 경로의 교차 에지 정보가 저장된다. (경로를 우-좌로 통과하는 에지)
*	\param	bReverse[in]		끝점 ~ 시작점으로의 경로를 구할 경우 true, 아니면 false
*
*	\return 최단 거리를 반환한다.
*/
double get_aniso_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);
