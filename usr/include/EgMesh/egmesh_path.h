#pragma once

/*! \brief �� �������� �ҽ��������� �ִ� �Ÿ� ������ ǥ���ϴ� ��� */
typedef QNode<EgVertex *, double> Dist2Src;

/*! \brief ������ ���� ������ ǥ���ϴ� �ڷ��� */
typedef std::pair<EgEdge *, float> EdgeCut;

/*!
*	\brief	�޽� ���� �� ���� ������ �ﰢ���鰣�� ��ø �ﰢ���� ���Ѵ�.
*
*	\param	P[in]				�޽� ���� ��
*	\param	Q[in]				�޽� ���� ��
*	\param	OverlapFaces[out]	��ø �ﰢ������ ����ȴ�.
*
*	\return ��ø �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int get_one_ring_overlap_faces(EgMeshPt *P, EgMeshPt *Q, std::vector<EgFace *> &OverlapFaces);

/*!
*	\brief	�޽� ���� ������ ��� �Ÿ� �̳��� �� ���������� �ּ� �Ÿ��� ����Ѵ�.
*	\note	1. ��� �ܺ��� �ﰢ�� ����������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�޽� ���� ��
*	\param	Distances[out]		i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	�ҽ� ������ Ÿ�� �������� �Ÿ� ���� �������� ���� �Ÿ����� ����ϴ� �Լ�
*	\note	1. Ÿ�� ������ �Ÿ����� �� �������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�ҽ� ���� ���� ������
*	\param	T[in]				Ÿ�� ���� ���� ������
*	\param	Distances[out]		�ҽ� ������ i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*
*	\return ���� ������ �ִ� �Ÿ��� ��ȯ�Ѵ�.
*/
double get_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, EgMeshPt *T, std::vector<double> &Distances);

/*!
*	\brief	�ҽ� ����(�ﰢ��)�鿡�� ��� �Ÿ�(BndryDistance) �̳��� �ﰢ��(���� ����)�� �� ���������� �ּ� �Ÿ��� ����Ѵ�.
*	\note	1. Ÿ�� ������ �Ÿ����� �� �������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	SrcList[in]			�޽��� �ҽ��� ����Ʈ
*	\param	Distances[out]		i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_geodesic_dist_field(EgMesh *pMesh, std::vector<EgObject *> &SrcList, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	�޽� ���� ������ ��� �Ÿ� �̳��� �� ���������� �ּ� �Ÿ��� ����Ѵ�.
*	\note	1. ��� �ܺ��� �ﰢ�� ����������� �Ÿ��� DBL_MAX�� �����ȴ�.
*			2. ���� ��: Geodesic Distance Computation via Virtual Source Propagation, SGP2021
*
*	\param	pMesh[in]			��� �޽�
*	\param	SrcList[in]			�޽��� �ҽ��� ����Ʈ
*	\param	Distances[out]		i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_geodesic_dist_field_gsp(EgMesh *pMesh, std::vector<EgObject *> &SrcList, std::vector<double> &Distances, double Dist2Bndry);

/*!
*   \brief	�ҽ� �����鿡�� �޽� �� ���������� �ּ� �Ÿ��� Heat Method�� ���� ����Ѵ�.
*
*   \param  pMesh[in]       ��� �޽�
*   \param  SrcVerts[in]	���õ� �޽� ���� ���� ����Ʈ
*   \param  Distances[out]  ���õ� �����鿡�� i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*   \param  Time[in]        �� �ʵ带 ������ �ð�
*
*   \return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_heat_dist_field(EgMesh *pMesh, std::vector<EgVertex *> &SrcVerts, std::vector<double> &Distances, double Time);

/*!
*   \brief	�޽��� ���� �������� �� �ʵ带 �����Ѵ�.
*
*   \param	pMesh[in]		��� �޽�
*   \param	OneVerts[in]	�ҽ� ����(���ప 1�� ���´�)�� ����Ʈ
*   \param	Field[out]		i��° ������ �� �ʵ尪�� Field[i]�� ����ȴ�.
*   \param	Time[in]		�ùķ��̼� �ð�
*/
double get_heat_flow_field(EgMesh *pMesh, std::vector<EgVertex *> &SrcVerts, std::vector<double> &Field, double Time);

/*!
*	\brief	�ҽ� �������� ��� �Ÿ�(BndryDistance) �̳��� �ﰢ��(���� �ﰢ�� ����)�� �� �������� ������ ������ �ּ� �Ÿ��� ����Ѵ�.
*	\note	1. ��� �ܺ� �ﰢ���� ����������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�ҽ� ������ ���� ������
*	\param	Distances[out]		�ҽ� �������� i��° ���������� ���� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_edge_dist_field(EgMesh *pMesh, EgVertex *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	�ҽ� �������� ��� �Ÿ� �̳��� ���������� ���� �Ÿ��� ����ϴ� �Լ�
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�ҽ� ����
*	\param	Distances[out]		�ҽ� �������� i��° ���������� ���� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� ���� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� ���� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
int get_topology_dist_field(EgMesh *pMesh, EgVertex *S, std::vector<int> &Distances, int Dist2Bndry);

/*!
*	\brief	�޽� ���� �� �� ������ �ִ� ��ο� ���� ������ ���ϴ� �Լ�
*
*	\param	S[in]				������
*	\param	E[in]				����
*	\param	Distances[in]		������ ���� ���� �Ÿ���
*	\param	Path[out]			������ ~ �������� �ִ� ��θ� �����ϴ� ����(������ + ���� ������ + ����)�� ����ȴ�.
*	\param	CutEdgeList[out]	������ ~ �������� �ִ� ����� ���� ���� ������ ����ȴ�. (��θ� ��-�·� ����ϴ� ����)
*	\param	bReverse[in]		���� ~ ������������ ��ο� ������ ���� ��� true, �ƴϸ� false
*
*	\return �� �� ������ �ִ� �Ÿ��� ��ȯ�ϰ� �����ϸ� -1�� ��ȯ�Ѵ�.
*/
double get_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<double> &Distances, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);

/*!
*	\brief	�޽� ���� �� �� ������ �ִ� ��ο� ���� ������ ���ϴ� �Լ�
*
*	\param	S[in]			������
*	\param	E[in]			����
*	\param	Path[out]		������ ~ �������� �ִ� ��θ� �����ϴ� ����(������ + ���� ������ + ����)�� ����ȴ�.
*	\param	CutEdges[out]	������ ~ �������� �ִ� ����� ���� ���� ������ ����ȴ�. (��θ� ��-�·� ����ϴ� ����)
*	\param	bReverse[in]	���� ~ ������������ ��ο� ������ ���� ��� true, �ƴϸ� false
*
*	\return �� �� ������ �ִ� �Ÿ��� ��ȯ�Ѵ�.
*/
double get_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdges, bool bReverse = false);

/*!
*	\brief	�� ���� �����ϴ� ��� ���� ��ο� �Ÿ��� ����Ѵ�.
*	\note	��ΰ� Ȧ�� ���� �������� Ȧ�� ����Ͽ� ���� ��θ� �����Ѵ�.
*	\note	������ ������: 2021-01-03
*
*	\param	S[in]			�������� ���� ������
*	\param	E[in]			������ ���� ������
*	\param	Pln[in]			���� ��鿡 ���� ������(���� ���⿡ ���� ���������� ���� ������ ��������).
*	\param	Path[out]		���� ��θ� �����ϴ� ���� �������� ����ȴ�.
*	\param	CutInfo[out]	���� ����� �Ʒ��� ���� ����ϴ� ������ ���� ������ ����ȴ�.
*
*	\return ����� ���̸� ��ȯ�Ѵ�(������ �߻��ϸ� -1.0�� ��ȯ�Ѵ�).
*/
double get_planar_path(EgMeshPt *S, EgMeshPt *E, EgPlane *Pln, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutInfo);

/*!
*	\brief	���� ������ ���� ������ ���ϴ� �Լ�
*	\note	������ ������: 2020-06-29
*	\note	�ߺ� ������ ���ϱ� ���� [������, ����) ������ vertex spliting�� ���
*
*	\param	Pln[in]		��鿡 ���� ������
*	\param	e[in]		������ ���� e=(P, Q)�� ���� ������
*	\param	t[out]		������ ����� �Ʒ��� ���� ������ ���, �������� �Ķ���� ��(0.0 <= t < 1.0)�� ����ȴ�.
*
*	\return	������ ����� �Ʒ��� ���� ������ ��� true, �׷��� ������ false�� ��ȯ�Ѵ�.
*/
bool intersect_plane_edge(EgPlane *Pln, EgEdge *e, float *t = NULL);

/*!
*	\brief	����(������)�� ����(����)�� ���� ������ ���ϴ� �Լ�
*	\note	������ ������: 2020-12-26
*	\note	�ߺ� ������ ���ϱ� ���� ������ [������, ����) ���·� ������ (������, ����]�� ���·� splitting �ǽ�
*
*	\param	Ray[in]		����(������), �������� ���Ե��� �ʴ� ������ ����
*	\param	pEdge[in]	������ ���� e=[P, Q)�� ���� ������
*	\param	t[out]		������ ������ ������ ���, ���� ������ �������� �Ķ���� ��(0.0 <= t < 1.0)�� ����ȴ�.
*	\param	pt[out]		�������� �����
*
*	\return	������ ������ �����ϴ� ��� true, �׷��� ������ false�� ��ȯ�Ѵ�.
*/
bool intersect_ray_edge(EgLine Ray, EgEdge *pEdge, float *t, EgPos *pt);

/*!	\brief	��� ������ ���� �ѷ� ��ο� ���̸� ����ϴ� �Լ�
*	\note	������ ������: 2020-06-22
*
*	\param	S[in]			���� ����� �������� ���� ������
*	\param	Pln[in]			���� ��鿡 ���� ������
*	\param	Path[out]		��θ� �����ϴ� �������� ��ġ�� ����ȴ�.
*	\param	CutInfo[out]	���� ����� �Ʒ��� ���� ����ϴ� ������ ���� ������ ����ȴ�.
*
*	\return ��ΰ� �����ϸ� �ѷ��� ���̸� ���ٸ� -1.0�� ��ȯ�Ѵ�.
*/
double get_planar_path_closed(EgMeshPt *P, EgPlane *Pln, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutInfo);

/*!
*	\brief	�޽� ���� �� �� P�� Q�� �����ϴ� ���� ����Ѵ�.
*	\author	������
*
*	\param	pMesh[in]	��� �޽�
*	\param	P[in]		�������� ���� ������
*	\param	Q[in]		������ ���� ������
*	\param	t[in]		���� �Ķ���� 0 <= t <= 1.0
*
*	\return �� �� P�� Q�� t : 1 - t�� �����ϴ� �� R�� ��ȯ�Ѵ�.
*/
EgMeshPt glerp(EgMesh *pMesh, EgMeshPt *P, EgMeshPt *Q, double t);

/*!
*	\brief	�޽� ���� �� �� P�� Q�� �����ϴ� ���� ����Ѵ�.
*	\author	������
*
*	\param	pMesh[in]			��� �޽�
*	\param	P[in]				�������� ���� ������
*	\param	Q[in]				������ ���� ������
*	\param	t[in]				���� �Ķ���� 0 <= t <= 1.0
*	\param	dist[in]			���������� ���������� �Ÿ�
*	\param	CutPts[in]			����� ������ ����Ʈ
*	\param	CutEdgeList[in]		����� ������ ���� ����Ʈ
*
*	\return �� �� P�� Q�� t : 1 - t�� �����ϴ� �� R�� ��ȯ�Ѵ�.
*/
EgMeshPt glerp(EgMesh *pMesh, EgMeshPt *P, EgMeshPt *Q, double t, double dist, std::vector<EgPos> &CutPts, std::vector<EdgeCut> &CutInfo);

/*!
*   \brief  �޽� ���� �� P���� V �������� ���� |V|�� ���� �������� ������ ���Ѵ�.
*	\note	������ ������: 2020-12-16
*
*   \param  pMesh[in]	��� �޽�
*   \param  P[in]		�ﰢ�� ���� ������
*   \param  V[in]		�������� ����� ����(�ﰢ�� ���� �־�� ��)
*   \param  Path[out]	�������� ������ �������� �����
*
*   \return �������� ������ ��ȯ�Ѵ�.
*/
EgMeshPt get_straight_geodesic(EgMesh *pMesh, EgMeshPt *P, EgVec3 V, std::vector<EgPos> &Path);

/*!
*   \brief  �޽� ������ �������� ���� ����(���� ����)�� ���Ѵ�.
*
*   \param  Dir[in]		�������� ����
*   \param  pEdge[in]	�������� ������ ���� �ﰢ�� ���� ����
*
*   \return �������� ���� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_next_geodesic_direction(EgVec3 Dir, EgEdge *pEdge);

/*!
*   \brief	�޽� ���� ������ �������� ���� ������ ���Ѵ�.
*   \author ������
*
*   \param  Dir[in]			�������� ����
*   \param  pEdge[in/out]	������ ����, ������ ���� �� ���� ������ �����Ͱ� �����
*
*   \return	�������� ���� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_next_geodesic_direction_on_vertex(EgVec3 Dir, EgEdge **pEdge);

/*!
*   \brief	���ο� ��ġ�� ���� �̵��� �޽� ���� ���͸� ���Ѵ�.
*
*   \param  v[in]	�Է� ����
*   \param  p[in]	���ο� ������
*
*   \return	���ο� ��ġ�� ���� �̵��� �޽� ���� ���͸� ��ȯ�Ѵ�.
*/
EgMeshVec get_translated_vec(EgMeshVec v, EgMeshPt p);
