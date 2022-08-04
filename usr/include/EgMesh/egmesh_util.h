#pragma once

class EgObject;
class EgVertex;
class EgTexel;
class EgNormal;
class EgEdge;
class EgFace;
class EgMeshPt;
class EgMesh;
class EgMaterial;
class EgBox;

/*!
*	\brief ������ ���ڿ��� ��ȯ�Ͽ� ��ȯ�Ѵ�.
*
*	\param i ���ڿ��� ��ȯ�� ����
*
*	\return ���ڿ��� ��ȯ�� ����
*/
std::string cast_str(int i);

/*!
*	\brief �Ǽ��� ���ڿ��� ��ȯ�Ͽ� ��ȯ�Ѵ�.
*
*	\param v ���ڿ��� ��ȯ�� �Ǽ�
*
*	\return ���ڿ��� ��ȯ�� �Ǽ�
*/
std::string cast_str(double v);

/*!
*	\brief �Ǽ��� ���ڿ��� ��ȯ�Ͽ� ��ȯ�Ѵ�.
*
*	\param v ���ڿ��� ��ȯ�� �Ǽ�
*
*	\return ���ڿ��� ��ȯ�� �Ǽ�
*/
std::string cast_str(float v);

/*!
*	\brief �������� ���ε� ���� ���� ����Ѵ�.
*
*	\param val ������ ��
*	\param min ������ ���۰�
*	\param max ������ ����
*	\param Cmin ���۰��� ����
*	\param Cman ������ ����
*
*	\return ���ε� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_map(double val, double min, double max, EgVec3 Cmin, EgVec3 Cmax);

/*!
*	\brief �������� ���ε� ���� ���� ����Ѵ�.
*
*	\param val ������ ��
*	\param min ������ ���۰�
*	\param max ������ ����
*	\param Cmin ���۰��� ����
*	\param Cmin �߰����� ����
*	\param Cman ������ ����
*
*	\return ���ε� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_map(double val, double min, double max, EgVec3 Cmin, EgVec3 Cmid, EgVec3 Cmax);

/*!
*	\brief ������ ���󿡼� ������ ���� ��´�.
*
*	\param t ���� �Ķ����: 0(����) <= t <= 1.0(����)
*
*	\return ������ �߰� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_map_from_rainbow(double t);

/*!
*	\brief BCGYR ���󿡼� ������ ���� ��´�.
*
*	\param t ���� �Ķ����: 0(Blue) <= t <= 1.0(Red)
*
*	\return ������ �߰� ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_map_from_bcgyr(double t);

/*!
*	\brief ������ ������ �����Ѵ�.
*
*	\return ������ ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_random();

/*!
*	\brief �ε����� ���� ������ ������ ��ȯ�Ѵ�.
*
*	\idx ������ �ε���
*
*	\return �ε����� ���� ������ ������ ��ȯ�Ѵ�.
*/
EgVec3 get_color_sequence(int idx);

/*!
*	\brief	���(Ȧ)�� ���̸� ����Ѵ�.
*
*	\param	BndryVerts[in]	���(Ȧ)�� �����ϴ� ������ ����Ʈ
*	\param	bClosed[in]		��� ������ �� ���� ����
*
*	\return ���� ������ ���̸� ��ȯ�Ѵ�.
*/
double get_hole_perimeter(std::vector<EgVertex *> &BndryVerts, bool bClosed);

/*!
*	\brief	�ﰢ�� ���� �Է����� barycentric ��ǥ�� ����ϴ� �Լ�
*
*	\param	P[in]		�Է� ����
*	\param	pFace[in]	���� �ﰢ��
*
	\return	�Է� ������ barycentric ��ǥ�� ��ȯ�Ѵ�.
*/
EgVec3 get_barycentric_coords(EgPos P, EgFace *pFace);

/*!
*	\brief	�޽� ���� ���ǵ� ��Į����(scalar field)�� ������(iso-line) ������ ���ϴ� �Լ�
*	\note	������ ������: 2020-11-22
*	\note	������ ���� ������ ������� ����
*
*	\param	pMesh[in]			��Į������ ���ǵ� �޽�
*	\param	Field[in]			�޽� ���� ��Į����(i��° ������ �� SF[i]�� �����)
*	\param	Min[in]				������ ��Į������ �ּҰ�
*	\param	Max[in]				������ ��Į������ �ִ밪
*	\param	NumLines[in]		������ �������� ��
*	\param	Isolines[out]		i��° �������� j��° ������ �� ������ Isolines[i][j], Isolines[i][j+1]�� ����� (������� ���� �ܼ� ���� ����, (p, q)-(r, s)...)
*	\param	IsolineCuts[out]	i��° �������� j��° ������ �� ������ ���� ������ IsolineCuts[i][j], IsolineCuts[i][j+1]�� �����
*/
void get_iso_line_set(
	EgMesh *pMesh, 
	std::vector<double> &Field,
	double Min, 
	double Max, 
	int NumLines, 
	std::vector<std::vector<EgPos>> &Isolines, 
	std::vector<std::vector<EdgeCut>> &IsolineCuts);

/*!
*	\brief	�޽� ���� ���ǵ� ��Į����(scalar field)���� �ϳ��� ������(iso-line)�� ���ϴ� �Լ�
*	\note	������ ������: 2021-02-09
*
*	\param	pMesh[in]		��Į������ ���ǵ� �޽�
*	\param	Field[in]		�޽� ���� ��Į����(i��° ������ �� SF[i]�� �����)
*	\param	Isovalue[in]	������ �������� isovalue
*	\param	Isoline[out]	�������� i��° ������ �� ������ IsoLines[i], IsoLines[i+1]�� �����
*	\param	CutInfo[out]	�������� i��° ������ �� ������ ���� ������ CutInfo, CutInfo[i+1]�� �����
*/
void get_iso_line_segment(
	EgMesh *pMesh, 
	std::vector<double> &Field,
	double Isovalue, 
	std::vector<EgPos> &Isoline, 
	std::vector<EdgeCut> &IsolineCut);

/*!
*	\brief	�޽� ���� ���ǵ� ��Į����(scalar field)���� ����� ������(������ ����)�� ���ϴ� �Լ�
*	\note	������ ������: 2021-12-31
*
*	\param	pMesh[in]					��Į������ ���ǵ� �޽�
*	\param	Field[in]					�޽� ���� ��Į����(Field[i]�� i��° ������ ���� �����)
*	\param	Isovalue[in]				������ �������� isovalue
*	\param	ConnectedIsolines[out]		�������� �����ϴ� ������ ����: i��° ������ ���� ������ IsoPts[i]�� �����(����� ����)
*	\param	ConnectedIsolineCuts[out]	�������� �����ϴ� ������ �������� ����: i��° �������� ���� ������ CutEdges[i]�� �����
*/
void get_iso_line_connected(
	EgMesh *pMesh,
	std::vector<double> &Field,
	double Isovalue,
	std::vector<std::vector<EgPos>> &ConnectedIsolines,
	std::vector<std::vector<EdgeCut>> &ConnectedIsolineCuts);

/*!
*	\brief	�������� ���� ȸ�� �ּ�ȭ Ʋ���� ���Ѵ�.
*
*	\param	Pts[in]		���������� ������ ����Ʈ
*	\param	T0[in]		���� �������� ù ��° �຤��(����)
*	\param	R0[in]		���� �������� �� ��° �຤��
*	\param	Ts[out]		�� ���������� ���� ����
*	\param	Rs[out]		�� ���������� �� ��° �຤�Ͱ� ����ȴ�.
*	\param	Ss[out]		�� ���������� �� ��° �຤�Ͱ� ����ȴ�.
*/
void get_rotation_minimizing_frame(
	std::vector<EgPos> Pts,
	EgVec3 T0,
	EgVec3 R0,
	std::vector<EgVec3> &Ts,
	std::vector<EgVec3> &Rs,
	std::vector<EgVec3> &Ss);

/*!
*	\brief	K-Mean Ŭ�����͸��� �����Ѵ�.
*
*	\param	Points[in]			�Է� ������ ����Ʈ
*	\param	K[in]				Ŭ�������� ��
 *	\param	Epochs[in]			�ݺ� ȸ��
*	\param	InitCenter[in]		�� ũ�������� �ʱ� �߽�
*	\param	ClusterIds[out]		�Է� �������� Ŭ������ ���̵� ����ȴ�.
*	\param	Centers[out]		�� Ŭ�������� �߽��� ����ȴ�.
*/
void get_cluster_by_k_mean(
	std::vector<EgVec3> &Points,
	int K,
	int Epochs,
	std::vector<EgVec3> InitCenter,
	std::vector<int> &ClusterIds,
	std::vector<EgVec3> &Centers);

/*!
*	\brief	K-Mean Ŭ�����͸��� �����Ѵ�.
*
*	\param	Points[in]			�Է� ������ ����Ʈ
*	\param	K[in]				Ŭ�������� ��
 *	\param	Epochs[in]			�ݺ� ȸ��
*	\param	InitCenter[in]		�� ũ�������� �ʱ� �߽�
*	\param	ClusterIds[out]		�Է� �������� Ŭ������ ���̵� ����ȴ�.
*	\param	Centers[out]		�� Ŭ�������� �߽��� ����ȴ�.
*/
void get_cluster_by_k_mean(
	std::vector<double> &Points,
	int K,
	int Epochs,
	std::vector<double> InitCenter,
	std::vector<int> &ClusterIds,
	std::vector<double> &Centers);
