#pragma once

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

#ifndef SELECT_BUFFER_SIZE
#define SELECT_BUFFER_SIZE 256
#endif // SELECT_BUFFER_SIZE

/*! \brief 선택 툴의 유형을 구별하는 열거형 타입 */
enum TypeSelectTool
{
	SELECT_TOOL_RECT = 0,		// 사각형 영역 선택 도구
	SELECT_TOOL_CIRCLE,			// 원 영역 선택 도구
	SELECT_TOOL_LASSO,			// 올가미 영역 선택 도구
	SELECT_TOOL_POLY,			// 폴리곤 영역 선택 도구
	SELECT_TOOL_BRUSH,			// 브러쉬 영역 선택 도구
	SELECT_TOOL_MAGIC_WAND_BASIC,		// 오목성 기반 마법봉(등위선) 선택 도구
	SELECT_TOOL_MAGIC_WAND_CONCAVE,		// 오목성 기반 마법봉 선택 도구
	SELECT_TOOL_MAGIC_WAND_CONVEX,		// 볼록성 기반 마법봉 선택 도구
	SELECT_TOOL_DOT_SCISSOR_CONCAVE,	// 오목성 기반 점 가위 선택 도구
	SELECT_TOOL_DOT_SCISSOR_CONVEX,		// 볼록성 기반 점 가위 선택 도구
};

/*! \brief 선택 객체의 유형을 구별하는 열거형 타입 */
enum TypeSelectObj
{
	SELECT_MESH = 0,			// 메쉬 객체 
	SELECT_VERT,				// 메쉬 정점
	SELECT_FACE,				// 메쉬 삼각형
	SELECT_FACE_CONNECTED,		// 메쉬 쉘(연결된 삼각형 집합)
	SELECT_MESH_PT,				// 메쉬 위의 임의 점
	SELECT_CTRL_PT,				// 넙스 곡선/곡면 제어점
};

/*! \brief 선택 모드를 구별하는 열거형 타입 */
enum TypeSelectMode
{
	SELECT_MODE_FRONT_ONLY = 0,	// 보이는 객체만 선택
	SELECT_MODE_SEE_THROUGH,	// 보이지 않는 객체도 선택
};

/*!
*	\class	EgSelector
*	\brief	객체의 선택 기능을 담당하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	2015년 3월 12일
*/
class EgSelector
{
	// 프렌드 클래스 및 함수
	friend class EgScene;
	friend class EgEditor;

	// 데이터 멤버
public:	
	/*! \brief 마우스 클릭시, 스크린 좌표 */
	EgVec2 m_MousePt[2];

	/*! \brief 선택 툴 유형(사각형, 원, 올가미, 다각형, 브러쉬 등) */
	TypeSelectTool m_SelectToolType;

	/*! \brief 선택 모드(앞면, 양면, 역선택 중) */
	TypeSelectMode m_SelectModeType;

	/*! \brief 선택 객체 유형(메쉬, 정점, 삼각형, 임의 점, 연결 삼각형 등) */
	TypeSelectObj m_SelectObjType;

	/*! \brief 현재 마우스 포인터와 교차된 삼각형 위의 점에 대한 정보 */
	EgMeshPt m_MouseOverFacePt;

	/*! \brief 선택 영역을 정의하는 점의 스크린 좌표 리스트 */
	std::vector<EgVec2> m_SltRgn2DPtList;

	/*! \brief 선택 영역을 정의하는 점의 월드 좌표 리스트(렌더링 용) */
	std::vector<EgVec3> m_SltRgn3DPtList;

	/*! \brief 선택 매커니즘이 진행 중임을 나타내는 변수 */
	bool m_bSelectInProgress;

	/*! \brief 역 선택 여부를 나타내는 변수 */
	bool m_bInverseSelect;

	/*! \brief 선택 도구 중 BRUSH, MAGIC_WAND의 반경(경계 상자 대각선 길이 비율 0.0 ~ 1.0) */
	double m_SltRadius;

	/*! \brief 선택된 객체 리스트(메쉬, 정점, 삼각형, 제어점 등) */
	std::vector<EgObject *> m_SltObjList;

	/*! \brief MAGIC_WAND, DOT_SCISSOR 분할 경계 정점 리스트(최적 등위값) */
	std::vector<std::vector<EgPos>> m_IsoSegBndryPts; // LINE_LOOP

	/*! \brief MAGIC_WAND의 분할 경계 정점 리스트(비등방 측지선) */
	std::vector<std::vector<EgPos>> m_GeoSegBndryPts;

	/*! \brief MAGIC_WAND의 비등방 측지 분할 경계 보간점 리스트 */
	std::vector<std::vector<EgMeshPt>> m_SegBndryKeyPts;

public:
	/*!
	*	\brief	생성자
	*/
	EgSelector();

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgSelector();

	/*!
	*	\brief 선택 툴의 상태를 초기화한다.
	*/
	void Reset();

	/*!
	*	\brief	객체 선택을 위한 경계 영역의 초기화 작업을 수행
	*
	*	\param	x[in]	마우스의 x 좌표
	*	\param	y[in]	마우스의 y 좌표
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief	마우스가 움직일 때 호출되며 선택 영역을 정의한다.
	*
	*	\param	x[in]	마우스의 x 좌표
	*	\param	y[in]	마우스의 y 좌표
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief	새로운 객체를 선택한다.
	*
	*	\param	x[in]	마우스의 x 좌표
	*	\param	y[in]	마우스의 y 좌표
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief 선택 툴의 선택 범위를 조절한다.
	*
	*	\param delta 마우스 휠의 변위
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief 사용자 정의 영역(사각형, 원, 올가미, 다각형)으로 객체를 선택한다.
	*/
	void SelectByRegion();						// 확인-2022-03-20

	/*!
	*	\brief	브러쉬 툴로 객체를 선택한다.
	*/
	void SelectByBrush();						// 확인-2022-03-20

	/*!
	*	\brief	정의된 선택 영역내의 메쉬를 선택한다.
	*
	*	\return 메쉬가 선택된 경우 true, 그렇지 않으면 false를 반환한다.
	*/
	bool SelectMesh();							// 확인-2022-03-20

	/*!
	*	\brief	장면에 포함된 메쉬를 선택한다.
	*
	*	\param	Name[in]	선택할 메쉬의 이름
	*
	*	\return 메쉬가 선택된 경우 true, 그렇지 않으면 false를 반환한다.
	*/
	bool SelectMesh(std::string Name);			// 확인-2022-03-20

	/*!
	*	\brief	선택된 메쉬에서 정점을 선택한다.
	*/
	void SelectVert();							// 확인-2022-03-20

	/*!
	*	\brief 선택된 메쉬에서 특정 삼각형을 선택한다.
	*/
	void SelectFace();							// 확인-2022-03-20
	
	/*!
	*	\brief	메쉬에서 선택 삼각형에 연결된 모든 삼각형을 선택한다.
	*/
	void SelectFaceConnected();					// 확인-2022-03-20

	/*!
	*	\brief  메쉬의 특징 영역의 삼각형을 선택하고, 분할 경계선을 생성한다.
	*/
	void SelectFaceByMagicWand();				// 확인-2022-03-25

	/*!
	*	\brief  메쉬의 특징 영역의 삼각형을 선택하고, 분할 경계선을 생성한다.
	*/
	void SelectFaceByDotScissor();				// 확인-2022-03-25

	/*!
	*	\brief	곡선/곡면의 제어점을 선택한다.
	*/
	void SelectFacePt();						// 확인-2022-03-20

	/*!
	*	\brief 삼각형 내부의 점을 선택한다.
	*/
	void SelectCtrlPt();						// 확인-2022-03-20

	/*!
	*	\brief 편집 객체, 에디터 그리고 선택 영역을 렌더링 한다.
	*/
	void Render();

	/*!
	*	\brief 사각형 선택 툴을 표시한다.
	*/
	void RenderRectTool();

	/*!
	*	\brief 원 선택 툴을 표시한다.
	*/
	void RenderCircleTool();

	/*!
	*	\brief 올가미 선택 툴을 표시한다.
	*/
	void RenderLassoTool();

	/*!
	*	\brief 다각형 선택 툴을 표시한다.
	*/
	void RenderPolyTool();

	/*!
	*	\brief 브러시 선택 툴을 표시한다.
	*/
	void RenderBrushTool();

	/*!
	*	\brief	Magic wand 툴의 후보 영역의 경계를 표시한다.
	*/
	void RenderMagicWandTool();

	/*!
	*	\brief	Dot scissor 툴의 circle위의 8개 점을 표시한다.
	*/
	void RenderDotScissorTool();

	/*!
	*	\brief 현재 마우스 포인터와 교차(가장 가까운) 정점을 렌더링 한다.
	*/
	void RenderMouseOverVert();

	/*!
	*	\brief 현재 마우스 포인터와 교차하는 삼각형(사각형)을 렌더링 한다.
	*/
	void RenderMouseOverFace();

	/*!
	*	\brief 현재 마우스 포인터와 교차하는 삼각형 위의 점을 렌더링 한다.
	*/
	void RenderMouseOverFacePt();

	/*!
	*	\brief	메쉬 위의 마우스 교차점 또는 편집 핸들의 선택을 위해 렌더링 한다.
	*	\note	마지막 수정일: 2021-05-02
	*/
	void RenderForSelect();

	/*!
	*	\brief	메쉬의 삼각형 선택을 위해 각 삼각형을 다른 색상으로 렌더링 한다.
	*
	*	\param	pMesh[in]	대상 메쉬
	*	\param	bClear[in]	칼라 버퍼 초기화 여부
	*/
	void RenderForSelectFace(EgMesh *pMesh, bool bClear);

	/*!
	*	\brief 편집 툴의 핸들 선택을 위해 각 툴의 핸들을 다른 색상으로 렌더링 한다.
	*/
	void RenderForSelectHandle();

	/*!
	*	\brief	선택 객체 수를 반환한다.
	*
	*	\return 선택 객체 수를 반환한다.
	*/
	int GetSltObjNum();

	/*!
	*	\brief	선택된 객체들 중 첫 번째 객체의 참조 메쉬를 반환한다.
	*
	*	\return 선택된 객체들 중 첫 번째 객체의 참조 메쉬를 반환한다.
	*/
	EgMesh *GetSltMesh();

	/*!
	*	\brief	선택 객체의 클래스 이름을 반환한다.
	*
	*	\return 선택 객체의 클래스 이름을 반환한다.
	*/
	std::string GetClsNameSltObj();	

	/*!
	*	\brief	선택 객체를 추가한다.
	*
	*	\param	pObj[in]	추가할 객체
	*/
	void AddToSltObjList(EgObject *pObj);

	/*!
	*	\brief	객체의 선택을 토글한다.
	*
	*	\param	pObj[in]	토글할 객체
	*/
	void ToggleSltObj(EgObject *pObj);

	/*!
	*	\brief	객체를 선택 객체 리스트에서 삭제한다.
	*
	*	\param	pObj[in]	삭제할 객체의 포인터
	*
	*	\return 성공하면 true, 삭제할 객체가 없는 경우 false를 반환한다.
	*/
	bool DelFromSltObjList(EgObject *pObj);

	/*!
	*	\brief	 선택된 편집 객체리스트의 중복을 제거한다.
	*	\warning 선택된 객체의 리스트가 중복은 제거되지만 정렬된다는 단점이 있다.
	*/
	void UniqueSltObjList();

	/*!
	*	\brief	선택 객체와 비선택 객체를 반전한다.
	*/
	void InverseSltObjList();

	/*!
	*	\brief	현재 마우스의 포인터의 3차원 좌표를 반환한다.
	*
	*	\param	x[in]	마우스의 x 좌표
	*	\param	y[in]	마우스의 y 좌표
	*
	*	\return 마우스 포인터의 3차원 좌표를 반환한다.
	*/
	EgVec3 GetWorldCoord(double x, double y);

	/*!
	*	\brief 마우스 포인터와 교차하는 편집 핸들을 찾는다.
	*
	*	\param x 마우스의 x좌표
	*	\param y 마우스의 y좌표
	*/
	bool SetMouseOverEditHandle(int x, int y);								// 확인

	/*!
	*	\brief	현재 마우스 포인터와 교차하는 삼각형, 정점 등의 정보를 설정한다.
	*	\note	마지막 수정일: 2021-04-23(현재까지 버그 없음)
	*
	*	\param	x[in]		마우스 x 좌표
	*	\param	y[in]		마우스 y 좌표
	*	\param	pMesh[in]	대상 메쉬
	*
	*	\return 마우스와 교차한 삼각형, 정점이 있으면 true, 없으면 false를 반환한다.
	*/
	bool SetMouseOverFacePt(int x, int y, EgMesh *pMesh = NULL);			// 확인 

	/*!
	*	\brief	정점이 폴리곤 내부에 존재하는지 여부를 판단
	*	\note	폴리곤 경계에 위치한 정점은 false를 반환한다.
	*
	*	\param	x[in]			정점의 x좌표
	*	\param	y[in]			정점의 y좌표
	*	\param	PtList[in]		폴리곤을 구성하는 정점 리스트
	*/
	bool IsPtInPolygon(double x, double y, std::vector<EgVec2> &PtList);	// 확인
};
