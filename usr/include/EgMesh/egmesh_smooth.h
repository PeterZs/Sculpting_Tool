#pragma once

/*!
*	\brief	�ﰢ���� �����Ͽ� ����ȭ�� �޽��� �����.
*	\note	���� �Ŀ� UpdateEdgeMate(), UpdateNormal() �Լ��� ȣ���� �־�� �Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*/
void get_refined_mesh(EgMesh *pMesh);

/*!
*	\brief �޽� ��ü�� ������ �Ѵ�.
*
*	\param pMesh[in] ��� �޽��� ���� ������
*/
void get_smooth_mesh(EgMesh *pMesh);

/*!
*	\brief �޽� ���� ������ ������ �Ѵ�.
*
*	\param pMesh[in] ��� �޽��� ���� ������
*	\param Faces[in] ���õ� ������ �ﰢ�� ����Ʈ
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgFace *> &Faces);

/*!
*	\brief �޽� ���� ������ ������ �Ѵ�.
*
*	\param pMesh[in] ��� �޽��� ���� ������
*	\param Verts[in] ���õ� ������ ���� ����Ʈ
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgVertex *> &Verts);

/*!
*	\biref	���õ� ���� �ֺ��� ������ �Ѵ�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	Verts[in]		���õ� ������ ����Ʈ
*	\param	Radius[in]		�������� ������ �Ÿ�(�ݰ�)
*	\param	bFixedBndry[in]	��� ���� ������ ����
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgVertex *> &Verts, double Radius, bool bFixedBndry);

/*!
*	\brief �޽� ��踦 ������ ä �������� �����Ѵ�.
*
*	\param pMesh[in] ��� �޽��� ���� ������
*/
void get_smooth_mesh_interior(EgMesh *pMesh);

/*!
*	\brief �޽� ��迡 �������� �����Ѵ�.
*
*	\param pMesh[in] ��� �޽��� ���� ������
*/
void get_smooth_mesh_boundary(EgMesh *pMesh);

/*!
*	\brief �޽� ������ ������ �Ѵ�.
*
*	\param pMesh[in]	��� �޽��� ���� ������
*/
void get_smooth_mesh_normal(EgMesh *pMesh);

/*!
*	\brief	�޽��� �ϸ�� ������ �̿��Ͽ� ������ �Ѵ�.
*	\note	������ ������: 2020-09-25
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	PassRatio[in]	�޽��� ���� �� ��� ������ ��� ���� ���� (0.0 < PassRatio < 1.0)
*/
void get_smooth_mesh_low_pass_filter(EgMesh *pMesh, double PassRate);

/*!
*	\brief	�޽� ���� ��Į�� �ʵ带 �������Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	Field[in/out]	�Է� �ʵ�, �������� �ʵ�� ��ü�ȴ�.
*/
void get_smooth_field(EgMesh *pMesh, std::vector<double> &Field);

/*!
*	\brief	�޽� ��踦 ������ ���·� ������ �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	bUniformWgt[in]		���ö�þ� ����� �յ� ����ġ ��� ����
*/
void get_fair_mesh_membrane(EgMesh *pMesh, bool bUniformWgt = false);

/*!
*	\brief	���� ������ ������ �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	Faces[in]			���� ������ �ﰢ�� ����Ʈ
*	\param	bUniformWgt[in]		���ö�þ� ����� �յ� ����ġ ��� ����
*/
void get_fair_mesh_membrane(EgMesh *pMesh, const std::vector<EgFace *> &Faces, bool bUniformWgt = false);

/*!
*	\brief	���� �����Ͽ� �޽� ������ �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	FreeVerts[in]		���� ������ ����Ʈ
*	\param	FixedVerts[in]		���� ������ ����Ʈ
*	\param	bUniformWgt[in]		���ö�þ� ����� �յ� ����ġ ��� ����
*/
void get_fair_mesh_membrane(EgMesh *pMesh, const std::vector<EgVertex *> &FreeVerts, const std::vector<EgVertex *> &FixedVerts, bool bUniformWgt);

/*!
*	\brief	�޽� ��踦 ������ ���·� �޽��� ������� �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*	\param	pMesh[in] ��� �޽��� ���� ������
*/
void get_fair_mesh_thin_plate(EgMesh *pMesh);

/*!
*	\brief	���� ������ ������� �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Faces[in]	���� ������ �ﰢ�� ����Ʈ
*/
void get_fair_mesh_thin_plate(EgMesh *pMesh, const std::vector<EgFace *> &Faces);

/*!
*   \brief  �޽� ��踦 ������ ���·� �޽��� ����� ��ȭ���� �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*   \param  pMesh[in]	��� �޽��� ���� ������
*/
void get_fair_mesh_minimum_variation(EgMesh *pMesh);

/*!
*   \brief	���� ������ ��� ��ȭ���� �ּ�ȭ�ϴ� fairing�� �����Ѵ�.
*	\note	ȣ�� ��, UpdateNormal() �Լ��� �̿��Ͽ� ������ �����Ѵ�.
*
*   \param	pMesh[in]	��� �޽��� ���� ������
*   \param  Faces[in]	���� ������ �ﰢ�� ����Ʈ
*/
void get_fair_mesh_minimum_variation(EgMesh *pMesh, const std::vector<EgFace *> &Faces);
