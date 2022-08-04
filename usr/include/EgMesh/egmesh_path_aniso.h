#pragma once

/*!
*	\brief	�޽� ���� ������ ��� �Ÿ� �̳��� �� ���������� ���� ���� �Ÿ��� ����Ѵ�.
*	\note	1. ó�� ȣ��� EgMesh::UpdateEdgeLen() �Լ��� �����Ͽ�, ���� ���� �Ÿ��� �ʱ�ȭ �ؾ� �Ѵ�.
*			2. ��� �ܺ��� �ﰢ�� ����������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�޽� ���� �ҽ���
*	\param	Distances[out]		i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*	\param	Dist2Bndry[in]		�������� �Ÿ�(������ ��� ��ü �޽��� ����Ѵ�)
*
*	\return ���� ������ �ִ� �Ÿ�(>= ��� �Ÿ�)�� ��ȯ�Ѵ�.
*/
double get_aniso_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, std::vector<double> &Distances, double Dist2Bndry);

/*!
*	\brief	�ҽ� ������ Ÿ�� �������� �Ÿ� ���� �������� ���� ���� �Ÿ����� ����ϴ� �Լ�
*	\note	1. ó�� ȣ��� EgMesh::UpdateEdgeLen() �Լ��� �����Ͽ�, ���� ���� �Ÿ��� �ʱ�ȭ �ؾ� �Ѵ�.
*			2. Ÿ�� ������ �Ÿ����� �� �������� �Ÿ��� DBL_MAX�� �����ȴ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	S[in]				�ҽ� ���� ���� ������
*	\param	T[in]				Ÿ�� ���� ���� ������
*	\param	Distances[out]		�ҽ� ������ i��° ���������� �Ÿ��� Distances[i]�� ����ȴ�.
*
*	\return ���� ������ �ִ� �Ÿ��� ��ȯ�Ѵ�.
*/
double get_aniso_geodesic_dist_field(EgMesh *pMesh, EgMeshPt *S, EgMeshPt *T, std::vector<double> &Distances);

/*!
*	\brief	�޽� ���� �� �� ������ ���� �ִ� ��ο� ���� ������ ���ϴ� �Լ�
*	\note	1. 2021-06-13: �ʱ� ����
*
*	\param	S[in]				������
*	\param	E[in]				����
*	\param	Distances[in]		������ ������ ���� ���� �Ÿ���
*	\param	Path[out]			������ ~ �������� �ִ� ��θ� �����ϴ� ����(������ + ���� ������ + ����)�� ����ȴ�.
*	\param	CutEdgeList[out]	������ ~ �������� �ִ� ����� ���� ���� ������ ����ȴ�. (��θ� ��-�·� ����ϴ� ����)
*	\param	bReverse[in]		���� ~ ������������ ��θ� ���� ��� true, �ƴϸ� false
*
*	\return �ִ� �Ÿ��� ��ȯ�Ѵ�.
*/
double get_aniso_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<double> &Distances, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);

/*!
*	\brief	�޽� ���� �� �� ������ ���� �ִ� ��ο� ���� ������ ���ϴ� �Լ�
*	\note	������ ������: 2021-10-15
*
*	\param	S[in]				������
*	\param	E[in]				����
*	\param	Distances[in]		������ ������ ���� ���� �Ÿ���
*	\param	Path[out]			������ ~ �������� �ִ� ��θ� �����ϴ� ����(������ + ���� ������ + ����)�� ����ȴ�.
*	\param	CutEdgeList[out]	������ ~ �������� �ִ� ����� ���� ���� ������ ����ȴ�. (��θ� ��-�·� ����ϴ� ����)
*	\param	bReverse[in]		���� ~ ������������ ��θ� ���� ��� true, �ƴϸ� false
*
*	\return �ִ� �Ÿ��� ��ȯ�Ѵ�.
*/
double get_aniso_shortest_path(EgMeshPt *S, EgMeshPt *E, std::vector<EgPos> &Path, std::vector<EdgeCut> &CutEdgeList, bool bReverse = false);
