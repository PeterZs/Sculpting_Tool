#pragma once
// 8�� API ����

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

class EgScene;

/*!
*	\brief �׷����� ���е� �ﰢ���� ������ �迭�� ���Ѵ�.
*
*	\param pMesh ��� �޽��� ���� ������
*	\param GroupedFaces �׷������ ���е� �ﰢ�� �����Ͱ� ����ȴ�.
*
*	\return �׷��� ������ ��ȯ�Ѵ�.
*/
int get_grouped_faces(EgMesh *pMesh, std::map<std::string, std::vector<EgFace *>> &GroupedFaces);

/*!
*	\brief �ؽ�ó ��ǥ�� 0�� 1���̷� ����ȭ �Ѵ�.
*
*	\param u �ؽ�ó ��ǥ u
*	\param v �ؽ�ó ��ǥ v
*/
void normalize_uv(double &u, double &v);

/*!
*	\brief	����Ʈ ������ �ҷ��´�.
*
*	\param	fname[in]	������ �̸�
*
*	\return ����: true, ����: flase
*/
bool import_pts(const char *fname, std::vector<EgPos> &Pts);

/*!
*	\brief OBJ ������ ����Ʈ�Ѵ�.
*
*	\param fname �޽� ������ �̸�[in]
*
*	\return ����Ʈ�� �޽��� �����͸� ��ȯ�Ѵ�.
*/
EgMesh *import_obj(const char *fname);

/*!
*	\brief	OBJ ������ ����Ʈ�Ͽ� ��鿡 �߰��Ѵ�.
*
*	\param	m_pScene[in]	����Ʈ�� �޽��� ���Ե� ��鿡 ���� ������
*	\param	FileName[in]	��ü ��ΰ� ���Ե� ������ �̸�(���� ��ȭ ���ڸ� �̿��� ���)
*
*	\return �����̸� true, ���и� false�� ��ȯ�Ѵ�.
*/
bool import_obj(EgScene *pScene, const char *fname);

/*!
*	\brief �޽��� ����(*.obj)�� �����Ѵ�.
*
*	\param pMesh ������ �޽��� ������
*	\param fname ������ �̸�
*
*	\return ����: true, ����: flase
*/
bool export_obj(EgMesh *pMesh, const char *fname);

/*!
*	\brief	STL ������ ����Ʈ�Ѵ�.
*
*	\param	pScene[in]	����Ʈ�� �޽� ������ ����� ��鿡 ���� ������
*	\param	fname[in]	����Ʈ�� ������ �̸�
*
*	\return ����: true, ����: flase
*/
bool import_stl(EgScene *pScene, const char *fname);

/*!
*	\brief �޽� ������ STL ���Ϸ� �����Ѵ�.
*
*	\param pMesh ������ �޽��� ������
*	\param fname ������ �̸�
*
*	\return ����: true, ����: flase
*/
bool export_stl(EgMesh *pMesh, const char *fname);

/*!
*	\brief �޽� ������ TXT ���Ϸ� �����Ѵ�.
*
*	\param pMesh ������ �޽��� ������
*	\param fname ������ �̸�
*
*	\return ����: true, ����: flase
*/
bool export_txt(EgMesh *pMesh, const char *fname);

/*!
*	\brief OFF ������ ����Ʈ�Ͽ� ��鿡 �߰��Ѵ�.
*
*	\param m_pScene ����Ʈ�� �޽��� ���Ե� ��鿡 ���� ������
*	\param FileName ��ü ��ΰ� ���Ե� ������ �̸�(���� ��ȭ ���ڸ� �̿��� ���)
*
*	\return �����̸� true, ���и� false�� ��ȯ�Ѵ�.
*/
bool import_off(EgScene *pScene, const char *fname);

/*!
*	\brief �޽� ������ OFF ���Ϸ� �����Ѵ�.
*
*	\param pMesh[in] ������ �޽��� ������
*	\param fname[in] ������ �̸�
*
*	\return ����: true, ����: flase
*/
bool export_off(EgMesh *pMesh, const char *fname);