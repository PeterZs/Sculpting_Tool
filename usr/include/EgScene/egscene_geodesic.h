#pragma once

#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"

/*!
*	\class EgGeodesic
*	\brief ������ ���� �Ÿ� ������ ǥ���ϴ� Ŭ����
*
*	\author ������
*	\date 10 Aug. 2019
*/
class EgGeodesic
{
	// ������ �Լ�
	friend bool operator >(const EgGeodesic &lhs, const EgGeodesic &rhs);

public:
	/*! \brief ������ ���� ������ */
	EgVertex *m_pVert;

	/*! \brief ���������� �ִ� �Ÿ� */
	double m_Distance;

public:
	// ������ �� �Ҹ���
	EgGeodesic(EgVertex *pVert);
	EgGeodesic(const EgGeodesic &cpy);
	~EgGeodesic();

	// ���� ������
	EgGeodesic &operator =(const EgGeodesic &rhs);
};

/*! \brief �� �������� �޽��� �� ���������� ������ ���� �ּ� �Ÿ��� ����ϴ� �Լ� */
void get_edge_dist_field(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, double MaxDistance);

/*! \brief �� �������� �޽��� �� ���������� �����Ÿ��� ����ϴ� �Լ� */
void get_geodesic_dist_field(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, double MaxDistance);

/*! \brief ���õ� ����(�ﰢ��)�鿡�� �޽��� �� ���������� �����Ÿ��� ����ϴ� �Լ� */
void get_geodesic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &ObjList, std::vector<double> &Distances, double MaxDistance);

/*! \brief �ﰢ�� ������ �� ������ �޽��� �� ���������� �����Ÿ��� ����ϴ� �Լ� */
void get_geodesic_dist_field(EgMesh *pMesh, int fidx, EgVec3 Coords, std::vector<double> &Distances, double MaxDistance);

/*!	\brief ���õ� �������� �޽��� �� ���������� �ִܰŸ��� �̿��� ����ǥ�� ����ϴ� �Լ� */
void get_geodesic_polar_coords(EgMesh *pMesh, EgVertex *pVert, std::vector<double> &Distances, std::vector<double> &Angles, double MaxDistance);

/*! \brief �޽� ������ �� ���� ������ �ִ� ��θ� ����ϴ� �Լ� */
void get_geodesic_paths(EgMesh *pMesh, EgVertex *P, EgVertex *Q, std::vector<EgPos> &Paths);

/*! \brief ���õ� �������� �޽��� �� ���������� ���� �Ÿ�(�ּ� ���� �Ÿ�)�� ����ϴ� �Լ� */
void get_topology_dist_field(EgMesh *pMesh, EgVertex *P, std::vector<int> &Distances, int MaxDistance);

/*! \brief ���õ� ����(�ﰢ��)�鿡�� �޽��� �� ���������� isophotic �Ÿ��� ����ϴ� �Լ� */
void get_isophotic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &ObjList, std::vector<double> &Distances, double MaxDistance);

/*!	\brief �޽��� ������ N-�� �̿� ������ ���ϴ� �Լ� */
int get_neighbor_verts(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<std::vector<EgVertex *>> &RingVerts);
