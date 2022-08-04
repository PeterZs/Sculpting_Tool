#pragma once

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

class EgEditor;

/*! \brief ��ü�� ���� ��带 �����ϴ� ������ Ÿ�� */
enum TypeEditTool
{
	EDIT_INACTIVE = 0,
	EDIT_TRA,
	EDIT_TRA_X,
	EDIT_TRA_Y,
	EDIT_TRA_Z,
	EDIT_TRA_XY,
	EDIT_TRA_YZ,
	EDIT_TRA_ZX,
	EDIT_TRA_XYZ,
	EDIT_ROT,
	EDIT_ROT_X,
	EDIT_ROT_Y,
	EDIT_ROT_Z,
	EDIT_SCL,
	EDIT_SCL_X,
	EDIT_SCL_Y,
	EDIT_SCL_Z,
	EDIT_SCL_XY,
	EDIT_SCL_YZ,
	EDIT_SCL_ZX,
	EDIT_SCL_XYZ,
	EDIT_SCULPT_ADD,
	EDIT_SCULPT_REMOVE,
	EDIT_SMOOTH,
};

/*!
*	\class	EgEditor
*	\brief	��ü�� ���� ����� ����ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date	02 Sept. 2012
*/
class EgEditor
{
	// ������ Ŭ���� �� �Լ�
	friend class EgScene;
	friend class EgSelector;

public:
	/*! \brief ���� ���� ��ǥ��(��ü ���ý� ������Ʈ) */
	EgTrans m_EC;

	/*! \brief ���� �� ����(�̵�, ȸ��, ������, Sculpt, Smooth ��) */
	TypeEditTool m_EditToolType;
	
	/*! \brief ���� ��Ŀ������ ���� ������ ��Ÿ���� ���� */
	bool m_bEditInProgress;

	/*! \brief ������ ���� ���콺�� ��ġ */
	EgVec2 m_MousePt[2];

	/*! \brief ȸ�� ������ �� ���, ���� ȸ�� �ڵ��� ���õ� ���� ��ǥ�� */
	EgTrans m_RotRefX;

	/*! \brief ȸ�� ������ �� ���, ȸ�� �ڵ��� ���õ� ���� */
	EgVec3 m_RotRefPos;

	/*! \brief ���� ������ �ݰ� */
	double m_EditRadius;

	/*! \brief ���� ������ ������ ����Ʈ(���� ��ü�� ���� �Ǵ� �ﰢ���� ���) */
	std::vector<EgVertex *> m_EditVertRgn;

	/*! \brief ���� ������ �ﰢ���� ����Ʈ(������ ��) */
	std::vector<EgFace *> m_EditFaceRgn;

	/*! \brief ���� ������ ��� ������ ����Ʈ(������ ��) */
	std::vector<EgPos> m_EditBndryPts;	

public:
	/*!
	*	\brief ������
	*/
	EgEditor();

	/*!
	*	\brief ���� ������
	*
	*	\param cpy ����� ��ü
	*/
	EgEditor(const EgEditor &cpy);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgEditor();

	/*!
	*	\brief ���� ������
	*
	*	\param rhs ���Ե� ��ü
	*/
	EgEditor &operator =(const EgEditor &rhs);

	/*!
	*	\brief �������� �ڵ� �����Ѵ�.
	*	\note ALT Ű�� ������ ���, ����� ������ ���̹Ƿ� �ٷ� �����Ѵ�.
	*
	*	\param x ���콺�� X ��ǥ
	*	\param y ���콺�� Y ��ǥ
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief ���� ��ü�� �����ϰų�, ���� ������ �����Ѵ�.
	*
	*	\param x ���콺�� X ��ǥ
	*	\param y ���콺�� Y ��ǥ
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief ��ü ������ �����ϰų�, ���ο� ��ü�� �����Ѵ�.
	*
	*	\param x ���콺�� X ��ǥ
	*	\param y ���콺�� Y ��ǥ
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief ���� ������ ũ�⸦ �����Ѵ�.
	*
	*	\param delta ���콺 ���� ����
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief ���õ� ��ü��κ��� �������� ���� ��ǥ�踦 �����Ѵ�.
	*/
	void SetEC();		//Ȯ��

	/*!
	*	\brief ��Ƽ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	EgTrans GetEC();

	/*!
	*	\brief ���� ��, ���� ���� ���¸� �ʱ�ȭ�Ѵ�.
	*/
	void Reset();

	/*!
	*	\brief ���õ� ��ü�� �����Ѵ� (������ ��� ���� ��ǥ�迡�� ǥ����)
	*
	*	\param t ������ ��ü�� �̵� ����
	*	\param q ������ ��ü�� ȸ�� ����
	*	\param s ������ ��ü�� ������ ����
	*/
	void Edit(EgVec3 t, EgQuat q, EgVec3 s);

	/*!
	*	\brief ��ü�� �̵� �����Ѵ�.
	*
	*	\param dx X �� �̵�����
	*	\param dy Y �� �̵�����
	*	\param dz Z �� �̵�����
	*
	*	\return ������ �� ��� true, ������ ���� ���� �ܿ� false�� ��ȯ�Ѵ�.
	*/
	bool EditTra(double dx, double dy, double dz);

	/*!
	*	\brief ��ü�� ȸ�� �����Ѵ�.
	*
	*	\param dx X �� �̵�����
	*	\param dy Y �� �̵�����
	*	\param dz Z �� �̵�����
	*
	*	\return ������ �� ��� true, ������ ���� ���� �ܿ� false�� ��ȯ�Ѵ�.
	*/
	bool EditRot(double dx, double dy, double dz);

	/*!
	*	\brief ��ü�� ������ �����Ѵ�.
	*
	*	\param dx X �� �̵�����
	*	\param dy Y �� �̵�����
	*	\param dz Z �� �̵�����
	*
	*	\return ������ �� ��� true, ������ ���� ���� �ܿ� false�� ��ȯ�Ѵ�.
	*/
	bool EditScl(double dx, double dy, double dz);

	/*!
	*	\brief �޽��� Sculpting �Ѵ�.
	*
	*	\param x ���콺�� x ��ǥ
	*	\param y ���콺�� y ��ǥ
	*
	*	\return ������ �� ��� true, ������ ���� ���� �ܿ� false�� ��ȯ�Ѵ�.
	*/
	bool EditSculpt(int x, int y);

	/*!
	*	\brief �޽��� Smoothing �Ѵ�.
	*
	*	\param x ���콺�� x ��ǥ
	*	\param y ���콺�� y ��ǥ
	*
	*	\return ������ �� ��� true, ������ ���� ���� �ܿ� false�� ��ȯ�Ѵ�.
	*/
	bool EditSmooth(int x, int y);

	/*!
	*	\brief ���õ� ��ü�� ������ �����Ѵ�.
	*/
	void EditFinish();

	/*!
	*	\brief ���� ���� ũ�⸦ ����Ѵ�.
	*
	*	\return ���� ���� ũ�⸦ ��ȯ�Ѵ�.
	*/
	double GetEditToolSize();

	/*!
	*	\brief ���� ��ü�� ���� ����ġ�� ����Ѵ�.
	*	\note ȣ����� FindEditWgt() -> FindEditRgn() -> FindEditBndry()
	*/
	void FindEditWgt();

	/*!
	*	\brief	���� ��ü�� ���� ����ġ�� ����Ѵ�.
	*/
	void FindEditWgtMouseOver();

	/*!
	*	\brief	������ �Ÿ����� �̿��Ͽ� ���� ������ ���� ����ġ�� ���Ѵ�.
	*	\note	������ ������: 2021-03-22
	*
	*	\param	pMesh[in]		��� �޽�
	*	\param	Distances[in]	��� �޽��� ���� �Ÿ���
	*	\param	EditDist[in]	���� ������ �ݰ�
	*/
	void FindEditRgn(EgMesh *pMesh, std::vector<double> &Distances, double EditDist);

	/*!
	*	\brief	������ �Ÿ����� �̿��Ͽ� �뷫���� ���� ��踦 ���Ѵ�.
	*
	*	\param	pMesh[in]		��� �޽�
	*	\param	Distances[in]	��� �޽��� ���� �Ÿ���
	*	\param	EditDist[in]	���� ���� �Ÿ�
	*/
	void FindEditBndry(EgMesh *pMesh, std::vector<double> &Distances, double EditDist);
	
	/*!
	*	\brief ���� ��ü, ������ �׸��� ���� ������ ������ �Ѵ�.
	*/
	void Render();

	/*!
	*	\brief	���� ������ ������ �Ѵ�.
	*/
	void RenderEditRgn();

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*/
	void RenderTra(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleX(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleY(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleZ(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleXY(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleYZ(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleZX(double len);

	/*!
	*	\brief �������� �̵��ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderTraHandleXYZ(double len);

	/*!
	*	\brief �������� ȸ�� �ڵ��� ������ �Ѵ�.
	*
	*	\param len ȸ�� �ڵ��� ����
	*/
	void RenderRot(double len);

	/*!
	*	\brief �������� ȸ�� �ڵ��� ������ �Ѵ�.
	*
	*	\param view_axis ���� �ڵ��� ����� ���� ���� ����
	*	\param len ȸ�� �ڵ��� ����
	*/
	void RenderRotHandleX(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief �������� ȸ�� �ڵ��� ������ �Ѵ�.
	*
	*	\param view_axis ���� �ڵ��� ����� ���� ���� ����
	*	\param len ȸ�� �ڵ��� ����
	*/
	void RenderRotHandleY(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief �������� ȸ�� �ڵ��� ������ �Ѵ�.
	*
	*	\param view_axis ���� �ڵ��� ����� ���� ���� ����
	*	\param len ȸ�� �ڵ��� ����
	*/
	void RenderRotHandleZ(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief ���� ���� �ڵ��� �����Ѵ�.
	*
	*	\param x ���콺�� X ��ǥ
	*	\param y ���콺�� Y ��ǥ
	*/
	bool SelectEditHandle(int x, int y);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len ������ �ڵ��� ����
	*/
	void RenderScl(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len ������ �ڵ��� ����
	*/
	void RenderSclHandleX(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len ������ �ڵ��� ����
	*/
	void RenderSclHandleY(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len ������ �ڵ��� ����
	*/
	void RenderSclHandleZ(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderSclHandleXY(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderSclHandleYZ(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len �̵� �ڵ��� ����
	*/
	void RenderSclHandleZX(double len);

	/*!
	*	\brief �������� ������ �ڵ��� ������ �Ѵ�.
	*
	*	\param len ������ �ڵ��� ����
	*/
	void RenderSclHandleXYZ(double len);

	/*!
	*	\brief Sculpt ���� �������Ѵ�.
	*/
	void RenderSculptTool();

	/*!
	*	\brief	Smooth ���� �������Ѵ�.
	*/
	void RenderSmoothTool();

	/*!
	*	\brief	���õ� ��ü���� �����ϴ� �޽� ��ü�� ����Ʈ�� �����Ѵ�.
	*
	*	\param	MeshList[out] ���� �޽��� ����ȴ�.
	*/
	void GetRefMeshList(std::vector<EgMesh *> &MeshList);

	/*!
	*	\brief ���õ� ��ü(����, �ﰢ��, �޽� ��)�� �����Ѵ�.
	*/
	void DeleteObject();

	/*!
	*	\brief ���õ� ������ �����Ѵ�.
	*/
	void DeleteMeshVert();

	/*!
	*	\brief ���õ� �ﰢ���� �����Ѵ�.
	*/
	void DeleteMeshFace();
};
