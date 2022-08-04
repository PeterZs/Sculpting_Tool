#pragma once

class EgVertex;
class EgFace;
class EgMesh;

/*!
*	\brief	�޽����� concave�� ������ ã�´�.
*
*	\param	pMesh[in] ��� �޽�
*	\param	Verts[out] concave�� ������ ����ȴ�.
*
*	\return concave�� ������ ������ ��ȯ�Ѵ�.
*/
int get_concave_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	�޽����� concave�� �ﰢ���� ã�´�.
*
*	\param	pMesh[in] ��� �޽�
*	\param	Faces[out] concave�� �ﰢ���� ����ȴ�.
*
*	\return concave�� �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int get_concave_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces);

/*!
*	\brief	�޽��� ���� �������� �ϸ�� �ʵ带 �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	OneVerts[in]	���ప 1�� ���� ������ ����Ʈ
*	\param	HalfVerts[in]	���ప 0.5�� ���� ������ ����Ʈ
*	\param	ZeroVerts[in]	���ప 0�� ���� ������ ����Ʈ
*	\param	Field[out]		i��° ������ �ϸ�� �ʵ尪�� Field[i]�� ����ȴ�.
*	\param	bBndryCstr[in]	��� ������ �ڵ� ���� ����(0.5) ��� ����
*	\param	FieldType[in]	�ϸ�� �ʵ��� Ÿ��(0: �ε巯�� �ʵ�, 1: ���� ��� �ʵ�, 2: ���ϼ� ��� �ʵ�)
*/
void get_harmonic_field(
	EgMesh *pMesh, 
	std::vector<EgVertex *> &OneVerts, 
	std::vector<EgVertex *> &HalfVerts, 
	std::vector<EgVertex *> &ZeroVerts, 
	std::vector<double> &Field, 
	bool bBndryCstr, 
	int FieldType);

/*!
*	\brief	Dot scissor�� feature-aware �ϸ�� �ʵ带 �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	OneVert[in]		���� 1���� ���� ���� ����
*	\param	ZeroVert[in]	���� 0���� ���� ���� ����
*	\param	Field[out]		i��° ������ �ϸ�� �ʵ尪�� Field[i]�� ����ȴ�.
*	\param	bConcavity[in]	���� ��� �ʵ��� ��� true, ���ϼ� ��� �ʵ��� ��� false
*/
void get_seg_field_by_dot_scissor(
	EgMesh *pMesh, 
	EgVertex *OneVert, 
	EgVertex *ZeroVert, 
	std::vector<double> &Field, 
	bool bConcavity = true);

/*!
*	\brief	Dot scissor ���� �̿��Ͽ� �޽��� Ư¡ ������ ���� ��輱�� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	PtsOnCircle[in]		DotCircle���� 8���� ��
*	\param	SltFaces[out]		���� ��輱�� ���� �Ǵ� �����ϴ� �ﰢ���� ����ȴ�.
*	\param	SegBndryPts[out]	���� ��輱�� ������ ���������� ����ȴ�.
*	\param	KeyPts[out]			���� ��輱�� ��ǥ������ ����ȴ�(������ ������)
*	\param	bConcavity[in]		���� ����� ��� true, ���ϼ� ����� ��� false
*/
void get_seg_bndry_by_dot_scissor(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> PtsOnCircle, 
	std::vector<EgFace *> &SltFaces, 
	std::vector<std::vector<EgPos>> &SegBndryPts, 
	std::vector<std::vector<EgMeshPt>> &KeyPts,
	bool bConcavity);

/*!
*	\brief	Magic wand�� feature-aware �ϸ�� �ʵ带 �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	SeedVerts[in]	�õ� ������ ����Ʈ
*	\param	RoiRadius[in]	���� ������ �ݰ�
*	\param	Field[out]		i��° ������ �ϸ�� �ʵ尪�� Field[i]�� ����ȴ�.
*	\param	bConcavity[in]	���� ���� �ʵ��̸� true, ���ϼ� ���� �ʵ��̸� false
*/
void get_seg_field_by_magic_wand(
	EgMesh *pMesh, 
	std::vector<EgObject *> SeedVerts, 
	double RoiRadius, 
	std::vector<double> &Field,
	bool bConcavity);

/*!
*	\brief	�޽��� Ư¡ ������ ���� ��輱�� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	SeedVerts[in]		������ ���� seed ������ ����Ʈ
*	\param	RoiRadius[in]		�ĺ� ������ �����ϴ� �ݰ�
*	\param	SltFaces[out]		���� ��輱�� ���� �Ǵ� �����ϴ� �ﰢ���� ����ȴ�.
*	\param	SegBndryPts[out]	���� ��輱�� ������ ���������� ����ȴ�.
*	\param	bConcavity[in]		���� ��� ��輱�̸� true, ���ϼ� ��� ��輱�̸� false
*/
void get_seg_bndry_by_magic_wand_basic(
	EgMesh *pMesh,
	std::vector<EgObject *> SeedPts,
	double RoiRadius,
	std::vector<EgFace *> &SltFaces,
	std::vector<std::vector<EgPos>> &SegBndryPts,
	bool bConcavity);

/*!
*	\brief	�޽��� Ư¡ ������ ���� ��輱�� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	SeedVerts[in]		������ ���� seed ������ ����Ʈ
*	\param	RoiRadius[in]		�ĺ� ������ �����ϴ� �ݰ�
*	\param	SltFaces[out]		���� ��輱�� ���� �Ǵ� �����ϴ� �ﰢ���� ����ȴ�.
*	\param	SegBndryPts[out]	���� ��輱�� ������ ���������� ����ȴ�.
*	\param	KeyPts[out]			���� ��輱�� ���������� ����ȴ�(������ ������)
*	\param	KeyPtsOpt[in]		������ ���� �ɼ�(0: �ִ� ��� ���, 1: �ִ� �׷����Ʈ ũ��)
*	\param	bConcavity[in]		���� ��� ��輱�̸� true, ���ϼ� ��� ��輱�̸� false
*/
void get_seg_bndry_by_magic_wand(
	EgMesh *pMesh, 
	std::vector<EgObject *> SeedPts, 
	double RoiRadius,
	std::vector<EgFace *> &SltFaces, 
	std::vector<std::vector<EgPos>> &SegBndryPts, 
	std::vector<std::vector<EgMeshPt>> &KeyPts,
	int KeyPtOpt,
	bool bConcavity);

/*!
*	\brief	�޽��� Ư¡ ������ ���� ��輱�� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	KeyPts[in]			���� ��輱�� ��ǥ�� ����
*	\param	SegBndryPts[out]	��ǥ���� ����ϴ� ���� ��輱(���� ������)�� ����ȴ�.
*/
void get_seg_bndry_by_aniso_geodesic(
	EgMesh *pMesh, 
	std::vector<std::vector<EgMeshPt>> &KeyPts, 
	std::vector<std::vector<EgPos>> &SegBndryPts);

