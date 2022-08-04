#pragma once

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

class EgEditor;

/*! \brief 객체의 편집 모드를 구별하는 열거형 타입 */
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
*	\brief	객체의 편집 기능을 담당하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	02 Sept. 2012
*/
class EgEditor
{
	// 프렌드 클래스 및 함수
	friend class EgScene;
	friend class EgSelector;

public:
	/*! \brief 편집 툴의 좌표계(객체 선택시 업데이트) */
	EgTrans m_EC;

	/*! \brief 편집 툴 유형(이동, 회전, 스케일, Sculpt, Smooth 중) */
	TypeEditTool m_EditToolType;
	
	/*! \brief 편집 매커니즘이 진행 중임을 나타내는 변수 */
	bool m_bEditInProgress;

	/*! \brief 편집을 위한 마우스의 위치 */
	EgVec2 m_MousePt[2];

	/*! \brief 회전 편집을 할 경우, 최초 회전 핸들이 선택된 참조 좌표계 */
	EgTrans m_RotRefX;

	/*! \brief 회전 편집을 할 경우, 회전 핸들의 선택된 지점 */
	EgVec3 m_RotRefPos;

	/*! \brief 편집 영역의 반경 */
	double m_EditRadius;

	/*! \brief 편집 영역의 정점의 리스트(선택 객체가 정점 또는 삼각형의 경우) */
	std::vector<EgVertex *> m_EditVertRgn;

	/*! \brief 편집 영역의 삼각형의 리스트(렌더링 용) */
	std::vector<EgFace *> m_EditFaceRgn;

	/*! \brief 편집 영역의 경계 정점의 리스트(렌더링 용) */
	std::vector<EgPos> m_EditBndryPts;	

public:
	/*!
	*	\brief 생성자
	*/
	EgEditor();

	/*!
	*	\brief 복사 생성자
	*
	*	\param cpy 복사될 객체
	*/
	EgEditor(const EgEditor &cpy);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgEditor();

	/*!
	*	\brief 대입 연산자
	*
	*	\param rhs 대입될 객체
	*/
	EgEditor &operator =(const EgEditor &rhs);

	/*!
	*	\brief 에디터의 핸들 선택한다.
	*	\note ALT 키가 눌러진 경우, 장면의 조작을 중이므로 바로 리턴한다.
	*
	*	\param x 마우스의 X 좌표
	*	\param y 마우스의 Y 좌표
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief 선택 객체를 편집하거나, 선택 영역을 정의한다.
	*
	*	\param x 마우스의 X 좌표
	*	\param y 마우스의 Y 좌표
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief 객체 편집을 종료하거나, 새로운 객체를 선택한다.
	*
	*	\param x 마우스의 X 좌표
	*	\param y 마우스의 Y 좌표
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief 편집 영역의 크기를 조절한다.
	*
	*	\param delta 마우스 휠의 변위
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief 선택된 객체들로부터 에디터의 편집 좌표계를 설정한다.
	*/
	void SetEC();		//확인

	/*!
	*	\brief 에티터의 편집 좌표계를 반환한다.
	*/
	EgTrans GetEC();

	/*!
	*	\brief 편집 후, 편집 툴의 상태를 초기화한다.
	*/
	void Reset();

	/*!
	*	\brief 선택된 객체를 편집한다 (변위는 모두 편집 좌표계에서 표현됨)
	*
	*	\param t 편집될 객체의 이동 변위
	*	\param q 편집될 객체의 회전 변위
	*	\param s 편집될 객체의 스케일 변위
	*/
	void Edit(EgVec3 t, EgQuat q, EgVec3 s);

	/*!
	*	\brief 객체를 이동 편집한다.
	*
	*	\param dx X 축 이동변위
	*	\param dy Y 축 이동변위
	*	\param dz Z 축 이동변위
	*
	*	\return 편집이 된 경우 true, 편집이 되지 않은 겨우 false를 반환한다.
	*/
	bool EditTra(double dx, double dy, double dz);

	/*!
	*	\brief 객체를 회전 편집한다.
	*
	*	\param dx X 축 이동변위
	*	\param dy Y 축 이동변위
	*	\param dz Z 축 이동변위
	*
	*	\return 편집이 된 경우 true, 편집이 되지 않은 겨우 false를 반환한다.
	*/
	bool EditRot(double dx, double dy, double dz);

	/*!
	*	\brief 객체를 스케일 편집한다.
	*
	*	\param dx X 축 이동변위
	*	\param dy Y 축 이동변위
	*	\param dz Z 축 이동변위
	*
	*	\return 편집이 된 경우 true, 편집이 되지 않은 겨우 false를 반환한다.
	*/
	bool EditScl(double dx, double dy, double dz);

	/*!
	*	\brief 메쉬를 Sculpting 한다.
	*
	*	\param x 마우스의 x 좌표
	*	\param y 마우스의 y 좌표
	*
	*	\return 편집이 된 경우 true, 편집이 되지 않은 겨우 false를 반환한다.
	*/
	bool EditSculpt(int x, int y);

	/*!
	*	\brief 메쉬를 Smoothing 한다.
	*
	*	\param x 마우스의 x 좌표
	*	\param y 마우스의 y 좌표
	*
	*	\return 편집이 된 경우 true, 편집이 되지 않은 겨우 false를 반환한다.
	*/
	bool EditSmooth(int x, int y);

	/*!
	*	\brief 선택된 객체를 편집을 종료한다.
	*/
	void EditFinish();

	/*!
	*	\brief 편집 툴의 크기를 계산한다.
	*
	*	\return 편집 툴의 크기를 반환한다.
	*/
	double GetEditToolSize();

	/*!
	*	\brief 편집 객체의 편집 가중치를 계산한다.
	*	\note 호출순서 FindEditWgt() -> FindEditRgn() -> FindEditBndry()
	*/
	void FindEditWgt();

	/*!
	*	\brief	편집 객체의 편집 가중치를 계산한다.
	*/
	void FindEditWgtMouseOver();

	/*!
	*	\brief	측지선 거리장을 이용하여 편집 영역과 편집 가중치를 구한다.
	*	\note	마지막 수정일: 2021-03-22
	*
	*	\param	pMesh[in]		대상 메쉬
	*	\param	Distances[in]	대상 메쉬의 측지 거리장
	*	\param	EditDist[in]	편집 영역의 반경
	*/
	void FindEditRgn(EgMesh *pMesh, std::vector<double> &Distances, double EditDist);

	/*!
	*	\brief	측지선 거리장을 이용하여 대략적인 편집 경계를 구한다.
	*
	*	\param	pMesh[in]		대상 메쉬
	*	\param	Distances[in]	대상 메쉬의 측지 거리장
	*	\param	EditDist[in]	편집 측지 거리
	*/
	void FindEditBndry(EgMesh *pMesh, std::vector<double> &Distances, double EditDist);
	
	/*!
	*	\brief 편집 객체, 에디터 그리고 선택 영역을 렌더링 한다.
	*/
	void Render();

	/*!
	*	\brief	편집 영역을 렌더링 한다.
	*/
	void RenderEditRgn();

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*/
	void RenderTra(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleX(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleY(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleZ(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleXY(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleYZ(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleZX(double len);

	/*!
	*	\brief 에디터의 이동핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderTraHandleXYZ(double len);

	/*!
	*	\brief 에디터의 회전 핸들을 렌더링 한다.
	*
	*	\param len 회전 핸들의 길이
	*/
	void RenderRot(double len);

	/*!
	*	\brief 에디터의 회전 핸들을 렌더링 한다.
	*
	*	\param view_axis 뒤쪽 핸들을 지우기 위한 법선 벡터
	*	\param len 회전 핸들의 길이
	*/
	void RenderRotHandleX(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief 에디터의 회전 핸들을 렌더링 한다.
	*
	*	\param view_axis 뒤쪽 핸들을 지우기 위한 법선 벡터
	*	\param len 회전 핸들의 길이
	*/
	void RenderRotHandleY(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief 에디터의 회전 핸들을 렌더링 한다.
	*
	*	\param view_axis 뒤쪽 핸들을 지우기 위한 법선 벡터
	*	\param len 회전 핸들의 길이
	*/
	void RenderRotHandleZ(const EgVec3 &view_aixs, double len);

	/*!
	*	\brief 편집 툴의 핸들을 선택한다.
	*
	*	\param x 마우스의 X 좌표
	*	\param y 마우스의 Y 좌표
	*/
	bool SelectEditHandle(int x, int y);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 스케일 핸들의 길이
	*/
	void RenderScl(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 스케일 핸들의 길이
	*/
	void RenderSclHandleX(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 스케일 핸들의 길이
	*/
	void RenderSclHandleY(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 스케일 핸들의 길이
	*/
	void RenderSclHandleZ(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderSclHandleXY(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderSclHandleYZ(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 이동 핸들의 길이
	*/
	void RenderSclHandleZX(double len);

	/*!
	*	\brief 에디터의 스케일 핸들을 렌더링 한다.
	*
	*	\param len 스케일 핸들의 길이
	*/
	void RenderSclHandleXYZ(double len);

	/*!
	*	\brief Sculpt 툴을 렌더링한다.
	*/
	void RenderSculptTool();

	/*!
	*	\brief	Smooth 툴을 렌더링한다.
	*/
	void RenderSmoothTool();

	/*!
	*	\brief	선택된 객체들을 참조하는 메쉬 객체의 리스트를 생성한다.
	*
	*	\param	MeshList[out] 참조 메쉬가 저장된다.
	*/
	void GetRefMeshList(std::vector<EgMesh *> &MeshList);

	/*!
	*	\brief 선택된 객체(정점, 삼각형, 메쉬 등)를 삭제한다.
	*/
	void DeleteObject();

	/*!
	*	\brief 선택된 정점을 삭제한다.
	*/
	void DeleteMeshVert();

	/*!
	*	\brief 선택된 삼각형을 삭제한다.
	*/
	void DeleteMeshFace();
};
