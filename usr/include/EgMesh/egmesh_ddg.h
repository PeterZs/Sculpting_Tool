#pragma once

class EgMesh;

/*!
*	\brief	������ ���� ������ ������ ����Ѵ�.
*	\note	���� ��: Discrete Differential-Geometry Operators for Triangulated 2-Manifolds
*
*	\param	pVert[in]	������ ���� ������
*
*	\return ���� ������ ������ ��ȯ�Ѵ�.
*/
double get_mixed_voronoi_cell_area(EgVertex *pVert);

/*!
*	\brief	������ ���� ���� ������� ����Ʈ�� �����Ѵ�.
*	\note	�ַ� ������� ���� ������ ������ ���
*
*	\param	pMesh[in]		��� �޽�
*	\param	BndryPts[out]	i��° ������ ���� ������ ������� BndryPt[i][]�� ����ȴ�.
*/
void get_mixed_voronoi_cell_bndry(EgMesh *pMesh, std::vector<std::vector<EgPos>> &BndryPts);

/*!
*	\biref	���� ����(Polyline)�� �� ������ ����� ����Ѵ�.
*	\note	������ ������: 2022-04-16
*	\note	�� ������ ����� 0���� ���Ѵ�.
*
*	\param	Pts[in]			���� ������ ���� ����Ʈ
*	\param	Ks[out]			�� ������ ����� ����ȴ�.
*	\param	bSigned[in]		��� ��ȣ�� ����ϸ� true, �ƴϸ� false
*	\param	Up[in]			���� ������ ���� ����� ���� ����
*/
void get_curvature_polyline(std::vector<EgPos> &Pts, std::vector<double> &Ks, bool bSigned, EgVec3 Up);

/*!
*	\biref	������ ���콺 ����� ����Ѵ�.
*	\note	������ ������: 2022-04-16
*
*	\param	pVert[in]		��� ����
*	\param	bLocalAvg[in]	���� �������� ��� ��� ����
*
*	\return ������ ���콺 ����� ��ȯ�Ѵ�.
*/
double get_gaussian_curvature(EgVertex *pVert, bool bLocalAvg);

/*!
*	\biref	�޽��� ���콺 ����� ����Ѵ�.
*	\note	������ ������: 2022-04-16
*
*	\param	pMesh[in]	��� �޽�
*	\param	Ks[out]		i��° ������ ���콺 ����� Ks[i]�� ����ȴ�.
*	\param	Kmin[out]	�ּ� ���콺 ����� ����ȴ�.
*	\param	Kmax[out]	�ִ� ���콺 ����� ����ȴ�.
*/
void get_gaussian_curvature(EgMesh *pMesh, std::vector<double> &Ks, double &Kmin, double &Kmax);

/*!
*	\biref	������ ��� ����� ����Ѵ�(����ȣ).
*	\note	��� ������ ��� �ֺ� ����� ��հ����� ��ü
*
*	@param	pVert[in]		��� ����
*	@param	bLocalAvg[in]	���� �������� ��� ��� ����
*
*	@return ������ ��� ����� ��ȯ�Ѵ�.
*/
double get_mean_curvature(EgVertex *pVert, bool bLocalAvg);

/*!
*	\biref	�޽��� ��� ����� ����Ѵ�.
*
*	\param	pMesh[in]	��� �޽�
*	\param	Hs[out]		i��° ������ ��� ����� Hs[i]�� ����ȴ�.
*	\param	Hmin[out]	�ּ� ��� ����� ����ȴ�.
*	\param	Hmax[out]	�ִ� ��� ����� ����ȴ�.
*/
void get_mean_curvature(EgMesh *pMesh, std::vector<double> &Hs, double &Hmin, double &Hmax);

/*!
*	\biref	������ �ְ���� �ֹ����� ����Ѵ�.
*	\note	1. ���� ����: "A Novel Cubic-Order Algorithm for Approximating Principal Direction Vectors", GOLDFEATHER, J., AND INTERRANTE, V. 2004.
*			2. �ְ���� ����, ��� ��� ���� �� ����
*
*	\param	vtx[in]			�޽� ����
*	\param	k1[out]			�ִ� ����� ����ȴ�.
*	\param	k2[out]			�ּ� ����� ����ȴ�.
*	\param	e1[out]			�ִ� ��� ������ ����ȴ�.
*	\param	e2[out]			�ּ� ��� ������ ����ȴ�.
*	\param	MethodType[in]	��� ����� ���� ���(0: �̻� �̺� ����, 1: ��� ����)
*/
void get_principal_curvature(EgVertex *vtx, double &k1, double &k2, EgVec3 &e1, EgVec3 &e2, int MethodType);

/*!
*	\biref	�޽� �� ������ �ְ���� �ֹ����� ����Ѵ�.
*	\note	1. ���� ����: "A Novel Cubic-Order Algorithm for Approximating Principal Direction Vectors", GOLDFEATHER, J., AND INTERRANTE, V. 2004.
*			2. �ְ���� ����, ��� ��� ���� �� ����
*
*	\param	pMesh[in]		��� �޽�
*	\param	K1[out]			i��° ������ �ִ� ����� K1[i]�� ����ȴ�.
*	\param	K2[out]			i��° ������ �ּ� ����� K2[i]�� ����ȴ�.
*	\param	E1[out]			i��° ������ �ִ� ��� ������ E1[i]�� ����ȴ�.
*	\param	E2[out]			i��° ������ �ּ� ��� ������ E2[i]�� ����ȴ�.
*	\param	MethodType[in]	��� ����� ���� ���(0: �̻� �̺� ����, 1: ��� ����)
*/
void get_principal_curvature(EgMesh *pMesh, std::vector<double> &K1, std::vector<double> &K2, std::vector<EgVec3> &E1, std::vector<EgVec3> &E2, int MethodType);

/*!
*	\brief	�޽��� ���ö�þ� ����� ����Ѵ�.
*
*	\param	pMesh[in]	��� �޽�
*	\param	D[out]		���� ������ ����(1/A_i)�� �밢�� ���ҿ� ����ȴ�.
*	\param	M[out]		���ö�þ� ����� ����ȴ�.
*	\param	Type[in]	����ġ Ÿ��(0: uniform, 1: cotangent, 2: concavity-aware, 3: convexity-aware)
*/
void get_laplacian_matrix(EgMesh *pMesh, Eigen::SparseMatrix<double> &D, Eigen::SparseMatrix<double> &M, int WgtType);

/*!
*	\brief	Ư¡ ������ ���� ���ö� ����� ����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	Verts[in]		�κ� ������ ���� ������ ����Ʈ(������ ���� + ���� ���� ������ �����)
*	\param	M[out]			���ö�þ� ����� ����ȴ�.
*	\param	bConcavity[in]	������ Ư¡�� ������ ��� true, ������ Ư¡�� ������ ��� false
*/
void get_laplacian_matrix_roi(EgMesh *pMesh, std::vector<EgVertex *> &Verts, Eigen::SparseMatrix<double> &M, bool bConcavity = true);

/*!
*	\brief	�޽��� �� �ﰢ������ �׷����Ʈ�� ����Ѵ�.
*	\note	������ ������: 2020-11-02
*
*	\param	pMesh[in]		��� �޽�
*	\param	Values[in]		�� ������ �Ҵ�� ��Į�� ��
*	\param	Gradients[out]	Gradients[i]�� i��° �ﰢ���� �׷����Ʈ�� ����ȴ�.
*	\param	bNormalize[in]	�׷����Ʈ�� ����ȭ ����
*/
void get_gradient_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<EgVec3> &Gradients, bool bNormalize);

/*!
*	\brief	�޽��� �� �ﰢ������ �׷����Ʈ ���� ũ�⸦ ����Ѵ�.
*	\note	������ ������: 2022-04-20
*
*	\param	pMesh[in]		��� �޽�
*	\param	Values[in]		�� ������ �Ҵ�� ��Į�� ��
*	\param	Magnitudes[out]	Magnitudes[i]�� i��° �ﰢ���� �׷����Ʈ ũ�Ⱑ ����ȴ�.
*/
void get_gradient_magnitude_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<double> &Magnitudes);

/*!
*   \brief   �޽��� �� ������ �߻��� ����Ѵ�.
*
*   \param   pMesh[in]			��� �޽�
*   \param   Values[in]         �� �ﰢ���� �Ҵ�� ���� ��
*   \param   Divergences[out]   i��° ������ �߻��� Divergence[i]�� ����ȴ�.
*/
void get_divergence_field(EgMesh *pMesh, std::vector<EgVec3> &Values, std::vector<double> &Divergences);

/*!
*	\brief	�޽��� �� ������ ���ö�þ��� ����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	Values[in]			�� ������ �Ҵ�� ��Į�� ��
*	\param	Laplacians[out]		Laplacians[i]�� i��° ������ ���ö�þ��� ����ȴ�.
*	\param	WgtType[in]			���� ����ġ Ÿ�� (0: unifork, 1: cotangent, 2: concavity, 3: convex)
*/
void get_laplacian_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<double> &Laplacians, int WgtType);
