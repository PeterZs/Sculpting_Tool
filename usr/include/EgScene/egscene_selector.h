#pragma once

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

#ifndef SELECT_BUFFER_SIZE
#define SELECT_BUFFER_SIZE 256
#endif // SELECT_BUFFER_SIZE

/*! \brief ���� ���� ������ �����ϴ� ������ Ÿ�� */
enum TypeSelectTool
{
	SELECT_TOOL_RECT = 0,		// �簢�� ���� ���� ����
	SELECT_TOOL_CIRCLE,			// �� ���� ���� ����
	SELECT_TOOL_LASSO,			// �ð��� ���� ���� ����
	SELECT_TOOL_POLY,			// ������ ���� ���� ����
	SELECT_TOOL_BRUSH,			// �귯�� ���� ���� ����
	SELECT_TOOL_MAGIC_WAND_BASIC,		// ���� ��� ������(������) ���� ����
	SELECT_TOOL_MAGIC_WAND_CONCAVE,		// ���� ��� ������ ���� ����
	SELECT_TOOL_MAGIC_WAND_CONVEX,		// ���ϼ� ��� ������ ���� ����
	SELECT_TOOL_DOT_SCISSOR_CONCAVE,	// ���� ��� �� ���� ���� ����
	SELECT_TOOL_DOT_SCISSOR_CONVEX,		// ���ϼ� ��� �� ���� ���� ����
};

/*! \brief ���� ��ü�� ������ �����ϴ� ������ Ÿ�� */
enum TypeSelectObj
{
	SELECT_MESH = 0,			// �޽� ��ü 
	SELECT_VERT,				// �޽� ����
	SELECT_FACE,				// �޽� �ﰢ��
	SELECT_FACE_CONNECTED,		// �޽� ��(����� �ﰢ�� ����)
	SELECT_MESH_PT,				// �޽� ���� ���� ��
	SELECT_CTRL_PT,				// �ҽ� �/��� ������
};

/*! \brief ���� ��带 �����ϴ� ������ Ÿ�� */
enum TypeSelectMode
{
	SELECT_MODE_FRONT_ONLY = 0,	// ���̴� ��ü�� ����
	SELECT_MODE_SEE_THROUGH,	// ������ �ʴ� ��ü�� ����
};

/*!
*	\class	EgSelector
*	\brief	��ü�� ���� ����� ����ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date	2015�� 3�� 12��
*/
class EgSelector
{
	// ������ Ŭ���� �� �Լ�
	friend class EgScene;
	friend class EgEditor;

	// ������ ���
public:	
	/*! \brief ���콺 Ŭ����, ��ũ�� ��ǥ */
	EgVec2 m_MousePt[2];

	/*! \brief ���� �� ����(�簢��, ��, �ð���, �ٰ���, �귯�� ��) */
	TypeSelectTool m_SelectToolType;

	/*! \brief ���� ���(�ո�, ���, ������ ��) */
	TypeSelectMode m_SelectModeType;

	/*! \brief ���� ��ü ����(�޽�, ����, �ﰢ��, ���� ��, ���� �ﰢ�� ��) */
	TypeSelectObj m_SelectObjType;

	/*! \brief ���� ���콺 �����Ϳ� ������ �ﰢ�� ���� ���� ���� ���� */
	EgMeshPt m_MouseOverFacePt;

	/*! \brief ���� ������ �����ϴ� ���� ��ũ�� ��ǥ ����Ʈ */
	std::vector<EgVec2> m_SltRgn2DPtList;

	/*! \brief ���� ������ �����ϴ� ���� ���� ��ǥ ����Ʈ(������ ��) */
	std::vector<EgVec3> m_SltRgn3DPtList;

	/*! \brief ���� ��Ŀ������ ���� ������ ��Ÿ���� ���� */
	bool m_bSelectInProgress;

	/*! \brief �� ���� ���θ� ��Ÿ���� ���� */
	bool m_bInverseSelect;

	/*! \brief ���� ���� �� BRUSH, MAGIC_WAND�� �ݰ�(��� ���� �밢�� ���� ���� 0.0 ~ 1.0) */
	double m_SltRadius;

	/*! \brief ���õ� ��ü ����Ʈ(�޽�, ����, �ﰢ��, ������ ��) */
	std::vector<EgObject *> m_SltObjList;

	/*! \brief MAGIC_WAND, DOT_SCISSOR ���� ��� ���� ����Ʈ(���� ������) */
	std::vector<std::vector<EgPos>> m_IsoSegBndryPts; // LINE_LOOP

	/*! \brief MAGIC_WAND�� ���� ��� ���� ����Ʈ(���� ������) */
	std::vector<std::vector<EgPos>> m_GeoSegBndryPts;

	/*! \brief MAGIC_WAND�� ���� ���� ���� ��� ������ ����Ʈ */
	std::vector<std::vector<EgMeshPt>> m_SegBndryKeyPts;

public:
	/*!
	*	\brief	������
	*/
	EgSelector();

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgSelector();

	/*!
	*	\brief ���� ���� ���¸� �ʱ�ȭ�Ѵ�.
	*/
	void Reset();

	/*!
	*	\brief	��ü ������ ���� ��� ������ �ʱ�ȭ �۾��� ����
	*
	*	\param	x[in]	���콺�� x ��ǥ
	*	\param	y[in]	���콺�� y ��ǥ
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief	���콺�� ������ �� ȣ��Ǹ� ���� ������ �����Ѵ�.
	*
	*	\param	x[in]	���콺�� x ��ǥ
	*	\param	y[in]	���콺�� y ��ǥ
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief	���ο� ��ü�� �����Ѵ�.
	*
	*	\param	x[in]	���콺�� x ��ǥ
	*	\param	y[in]	���콺�� y ��ǥ
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief ���� ���� ���� ������ �����Ѵ�.
	*
	*	\param delta ���콺 ���� ����
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief ����� ���� ����(�簢��, ��, �ð���, �ٰ���)���� ��ü�� �����Ѵ�.
	*/
	void SelectByRegion();						// Ȯ��-2022-03-20

	/*!
	*	\brief	�귯�� ���� ��ü�� �����Ѵ�.
	*/
	void SelectByBrush();						// Ȯ��-2022-03-20

	/*!
	*	\brief	���ǵ� ���� �������� �޽��� �����Ѵ�.
	*
	*	\return �޽��� ���õ� ��� true, �׷��� ������ false�� ��ȯ�Ѵ�.
	*/
	bool SelectMesh();							// Ȯ��-2022-03-20

	/*!
	*	\brief	��鿡 ���Ե� �޽��� �����Ѵ�.
	*
	*	\param	Name[in]	������ �޽��� �̸�
	*
	*	\return �޽��� ���õ� ��� true, �׷��� ������ false�� ��ȯ�Ѵ�.
	*/
	bool SelectMesh(std::string Name);			// Ȯ��-2022-03-20

	/*!
	*	\brief	���õ� �޽����� ������ �����Ѵ�.
	*/
	void SelectVert();							// Ȯ��-2022-03-20

	/*!
	*	\brief ���õ� �޽����� Ư�� �ﰢ���� �����Ѵ�.
	*/
	void SelectFace();							// Ȯ��-2022-03-20
	
	/*!
	*	\brief	�޽����� ���� �ﰢ���� ����� ��� �ﰢ���� �����Ѵ�.
	*/
	void SelectFaceConnected();					// Ȯ��-2022-03-20

	/*!
	*	\brief  �޽��� Ư¡ ������ �ﰢ���� �����ϰ�, ���� ��輱�� �����Ѵ�.
	*/
	void SelectFaceByMagicWand();				// Ȯ��-2022-03-25

	/*!
	*	\brief  �޽��� Ư¡ ������ �ﰢ���� �����ϰ�, ���� ��輱�� �����Ѵ�.
	*/
	void SelectFaceByDotScissor();				// Ȯ��-2022-03-25

	/*!
	*	\brief	�/����� �������� �����Ѵ�.
	*/
	void SelectFacePt();						// Ȯ��-2022-03-20

	/*!
	*	\brief �ﰢ�� ������ ���� �����Ѵ�.
	*/
	void SelectCtrlPt();						// Ȯ��-2022-03-20

	/*!
	*	\brief ���� ��ü, ������ �׸��� ���� ������ ������ �Ѵ�.
	*/
	void Render();

	/*!
	*	\brief �簢�� ���� ���� ǥ���Ѵ�.
	*/
	void RenderRectTool();

	/*!
	*	\brief �� ���� ���� ǥ���Ѵ�.
	*/
	void RenderCircleTool();

	/*!
	*	\brief �ð��� ���� ���� ǥ���Ѵ�.
	*/
	void RenderLassoTool();

	/*!
	*	\brief �ٰ��� ���� ���� ǥ���Ѵ�.
	*/
	void RenderPolyTool();

	/*!
	*	\brief �귯�� ���� ���� ǥ���Ѵ�.
	*/
	void RenderBrushTool();

	/*!
	*	\brief	Magic wand ���� �ĺ� ������ ��踦 ǥ���Ѵ�.
	*/
	void RenderMagicWandTool();

	/*!
	*	\brief	Dot scissor ���� circle���� 8�� ���� ǥ���Ѵ�.
	*/
	void RenderDotScissorTool();

	/*!
	*	\brief ���� ���콺 �����Ϳ� ����(���� �����) ������ ������ �Ѵ�.
	*/
	void RenderMouseOverVert();

	/*!
	*	\brief ���� ���콺 �����Ϳ� �����ϴ� �ﰢ��(�簢��)�� ������ �Ѵ�.
	*/
	void RenderMouseOverFace();

	/*!
	*	\brief ���� ���콺 �����Ϳ� �����ϴ� �ﰢ�� ���� ���� ������ �Ѵ�.
	*/
	void RenderMouseOverFacePt();

	/*!
	*	\brief	�޽� ���� ���콺 ������ �Ǵ� ���� �ڵ��� ������ ���� ������ �Ѵ�.
	*	\note	������ ������: 2021-05-02
	*/
	void RenderForSelect();

	/*!
	*	\brief	�޽��� �ﰢ�� ������ ���� �� �ﰢ���� �ٸ� �������� ������ �Ѵ�.
	*
	*	\param	pMesh[in]	��� �޽�
	*	\param	bClear[in]	Į�� ���� �ʱ�ȭ ����
	*/
	void RenderForSelectFace(EgMesh *pMesh, bool bClear);

	/*!
	*	\brief ���� ���� �ڵ� ������ ���� �� ���� �ڵ��� �ٸ� �������� ������ �Ѵ�.
	*/
	void RenderForSelectHandle();

	/*!
	*	\brief	���� ��ü ���� ��ȯ�Ѵ�.
	*
	*	\return ���� ��ü ���� ��ȯ�Ѵ�.
	*/
	int GetSltObjNum();

	/*!
	*	\brief	���õ� ��ü�� �� ù ��° ��ü�� ���� �޽��� ��ȯ�Ѵ�.
	*
	*	\return ���õ� ��ü�� �� ù ��° ��ü�� ���� �޽��� ��ȯ�Ѵ�.
	*/
	EgMesh *GetSltMesh();

	/*!
	*	\brief	���� ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ���� ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	std::string GetClsNameSltObj();	

	/*!
	*	\brief	���� ��ü�� �߰��Ѵ�.
	*
	*	\param	pObj[in]	�߰��� ��ü
	*/
	void AddToSltObjList(EgObject *pObj);

	/*!
	*	\brief	��ü�� ������ ����Ѵ�.
	*
	*	\param	pObj[in]	����� ��ü
	*/
	void ToggleSltObj(EgObject *pObj);

	/*!
	*	\brief	��ü�� ���� ��ü ����Ʈ���� �����Ѵ�.
	*
	*	\param	pObj[in]	������ ��ü�� ������
	*
	*	\return �����ϸ� true, ������ ��ü�� ���� ��� false�� ��ȯ�Ѵ�.
	*/
	bool DelFromSltObjList(EgObject *pObj);

	/*!
	*	\brief	 ���õ� ���� ��ü����Ʈ�� �ߺ��� �����Ѵ�.
	*	\warning ���õ� ��ü�� ����Ʈ�� �ߺ��� ���ŵ����� ���ĵȴٴ� ������ �ִ�.
	*/
	void UniqueSltObjList();

	/*!
	*	\brief	���� ��ü�� ���� ��ü�� �����Ѵ�.
	*/
	void InverseSltObjList();

	/*!
	*	\brief	���� ���콺�� �������� 3���� ��ǥ�� ��ȯ�Ѵ�.
	*
	*	\param	x[in]	���콺�� x ��ǥ
	*	\param	y[in]	���콺�� y ��ǥ
	*
	*	\return ���콺 �������� 3���� ��ǥ�� ��ȯ�Ѵ�.
	*/
	EgVec3 GetWorldCoord(double x, double y);

	/*!
	*	\brief ���콺 �����Ϳ� �����ϴ� ���� �ڵ��� ã�´�.
	*
	*	\param x ���콺�� x��ǥ
	*	\param y ���콺�� y��ǥ
	*/
	bool SetMouseOverEditHandle(int x, int y);								// Ȯ��

	/*!
	*	\brief	���� ���콺 �����Ϳ� �����ϴ� �ﰢ��, ���� ���� ������ �����Ѵ�.
	*	\note	������ ������: 2021-04-23(������� ���� ����)
	*
	*	\param	x[in]		���콺 x ��ǥ
	*	\param	y[in]		���콺 y ��ǥ
	*	\param	pMesh[in]	��� �޽�
	*
	*	\return ���콺�� ������ �ﰢ��, ������ ������ true, ������ false�� ��ȯ�Ѵ�.
	*/
	bool SetMouseOverFacePt(int x, int y, EgMesh *pMesh = NULL);			// Ȯ�� 

	/*!
	*	\brief	������ ������ ���ο� �����ϴ��� ���θ� �Ǵ�
	*	\note	������ ��迡 ��ġ�� ������ false�� ��ȯ�Ѵ�.
	*
	*	\param	x[in]			������ x��ǥ
	*	\param	y[in]			������ y��ǥ
	*	\param	PtList[in]		�������� �����ϴ� ���� ����Ʈ
	*/
	bool IsPtInPolygon(double x, double y, std::vector<EgVec2> &PtList);	// Ȯ��
};
