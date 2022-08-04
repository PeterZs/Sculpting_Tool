#pragma once

#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"

/*!
*	\class EgGeodesic
*	\brief 정점의 측지 거리 정보를 표현하는 클래스
*
*	\author 윤승현
*	\date 10 Aug. 2019
*/
class EgGeodesic
{
	// 프렌드 함수
	friend bool operator >(const EgGeodesic &lhs, const EgGeodesic &rhs);

public:
	/*! \brief 정점에 대한 포인터 */
	EgVertex *m_pVert;

	/*! \brief 정점까지의 최단 거리 */
	double m_Distance;

public:
	// 생성자 및 소멸자
	EgGeodesic(EgVertex *pVert);
	EgGeodesic(const EgGeodesic &cpy);
	~EgGeodesic();

	// 대입 연산자
	EgGeodesic &operator =(const EgGeodesic &rhs);
};

/*! \brief 한 정점에서 메쉬의 각 정점까지의 에지를 따른 최소 거리를 계산하는 함수 */
void get_edge_dist_field(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, double MaxDistance);

/*! \brief 한 정점에서 메쉬의 각 정점까지의 측지거리를 계산하는 함수 */
void get_geodesic_dist_field(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, double MaxDistance);

/*! \brief 선택된 정점(삼각형)들에서 메쉬의 각 정점까지의 측지거리를 계산하는 함수 */
void get_geodesic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &ObjList, std::vector<double> &Distances, double MaxDistance);

/*! \brief 삼각형 내부의 한 점에서 메쉬의 각 정점까지의 측지거리를 계산하는 함수 */
void get_geodesic_dist_field(EgMesh *pMesh, int fidx, EgVec3 Coords, std::vector<double> &Distances, double MaxDistance);

/*!	\brief 선택된 정점에서 메쉬의 각 정점까지의 최단거리를 이용한 극좌표를 계산하는 함수 */
void get_geodesic_polar_coords(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, std::vector<double> &Angles, double MaxDistance);

/*! \brief 메쉬 위에서 두 정점 사이의 최단 경로를 계산하는 함수 */
void get_geodesic_paths(EgMesh *pMesh, EgVertex *P, EgVertex *Q, std::vector<EgPos> &Paths);

/*! \brief 선택된 정점에서 메쉬의 각 정점까지의 위상 거리(최소 에지 거리)를 계산하는 함수 */
void get_topology_dist_field(EgMesh *pMesh, EgVertex *P, std::vector<int> &Distances, int MaxDistance);

/*! \brief 선택된 정점(삼각형)들에서 메쉬의 각 정점까지의 isophotic 거리를 계산하는 함수 */
void get_isophotic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &ObjList, std::vector<double> &Distances, double MaxDistance);

/*!	\brief 메쉬의 정점의 N-링 이웃 정점을 구하는 함수 */
int get_neighbor_verts(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<std::vector<EgVertex *>> &RingVerts);
