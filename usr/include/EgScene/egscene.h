#pragma once

#include <vector>
#include <list>
#include <map>
#include "..\GL\freeglut.h"
#include "..\IL\ilut.h"
#include "egscene_io.h"
#include "egscene_editor.h"
#include "egscene_selector.h"
#include "egscene_util.h"

// 클래스 선언
class EgLight;
class EgCamera;
class EgHud;
class EgScene;
class EgEditor;
class EgSelector;

extern EgScene theScene;
extern EgEditor theEditor;
extern EgSelector theSelector;

#ifndef SELECT_BUFFER_SIZE
#define SELECT_BUFFER_SIZE 256
#endif // SELECT_BUFFER_SIZE

/*!
*	\class	EgLight
*	\brief	장면의 광원을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*
*	\date	02 Sept. 2012
*/
class EgLight
{
public:
	/*! \brief 광원의 번호 */
	GLenum m_LightNum;

	/*! \brief 광원의 위치 */
	GLfloat m_Position[4];

	/*! \brief 광원의 주변광 성분 */
	GLfloat m_Ambient[3];

	/*! \brief 광원의 난반사 성분 */
	GLfloat m_Diffuse[3];

	/*! \brief 광원의 전반사 성분 */
	GLfloat m_Specular[3];

	/*! \brief 광원의 활성화 여부 */
	bool m_IsEnabled;

	/*! \brief 집중광원 여부 */
	bool m_IsSpotLight;

	/*! \brief 집중관원의 경우 광원의 방향 */
	GLfloat m_SpotDirection[3];

	/*! \brief 집중관원의 경우 광원의 범위 */
	GLfloat m_SpotCutOff;

public:
	/*!
	*	\brief 생성자
	*
	*	\param[in] _LightNum 생성할 광원의 번호
	*/
	EgLight(GLenum _LightNum);

	/*!
	*	\brief 복사 생성자
	*
	*	\param[in] cpy 복사될 객체
	*/
	EgLight(const EgLight &cpy);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgLight();

	/*!
	*	\brief 대입연산자
	*
	*	\param[in] rhs	피연산자
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgLight &operator =(const EgLight &rhs);

	/*!
	*	\brief 광원을 활성화 한다
	*/
	void Enable();

	/*!
	*	\brief 광원을 비활성화 한다
	*/
	void Disable();

	/*!
	*	\brief 광원의 위치를 설정한다.
	*
	*	\param[in] x 광원의 x좌표
	*	\param[in] y 광원의 y좌표
	*	\param[in] z 광원의 z좌표
	*	\param[in] w 광원의 w좌표(1: 점광원, 0: 방향성광원)
	*/
	void SetPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	/*!
	*	\brief 광원의 주변광 성분을 설정한다.
	*
	*	\param[in] r 광원의 붉은색 주변광 성분
	*	\param[in] g 광원의 초록색 주변광 성분
	*	\param[in] b 광원의 파란색 주변광 성분
	*/
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief 광원의 난반사광 성분을 설정한다.
	*
	*	\param[in] r 광원의 붉은색 난반사광 성분
	*	\param[in] g 광원의 초록색 난반사광 성분
	*	\param[in] b 광원의 파란색 난반사광 성분
	*/
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief 광원의 전반사광 성분을 설정한다.
	*
	*	\param[in] r 광원의 붉은색 전반사광 성분
	*	\param[in] g 광원의 초록색 전반사광 성분
	*	\param[in] b 광원의 파란색 전반사광 성분
	*/
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief 광원을 점광원 형태로 설정한다.
	*/
	void SetPointLight();

	/*!
	*	\brief 광원을 방향성 광원 형태로 설정한다.
	*/
	void SetDirectionalLight();

	/*!
	*	\brief 집중광원의 방향과 범위를 설정한다.
	*
	*	\param[in] vx		집중광원의 방향의 x성분
	*	\param[in] vy		집중광원의 방향의 y성분
	*	\param[in] vz		집중광원의 방향의 z성분
	*	\param[in] cutoff	집중광원의 범위
	*/
	void SetSpotLight(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat cutoff);
};

/*! \brief 카메라의 투영 타입을 정의하는 열거형 변수 */
enum TypeProjection
{
	PROJECTION_ORTHO = 0,
	PROJECTION_PERS,
};

/*! \brief 장면의 조작 타입을 정의하는 열거형 변수 */
enum TypeSceneManipulate
{
	SCENE_MANIPULATE_NONE = 0,
	SCENE_MANIPULATE_ROTATE = 1,
	SCENE_MANIPULATE_PAN,
	SCENE_MANIPULATE_ZOOM,
};

/*!
*	\class EgCamera
*	\brief 3차원 장면(EgScene)을 관측하는 카메라를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 06 Sept. 2012
*/
class EgCamera
{
public:	
	/*! \brief 카메라가 포함된 장면에 대한 포인터 */
	EgScene *m_pScene;

	/*! \brief 원근 투영을 위한 카메라의 화각(field of view) */
	double m_Fovy;

	/*! \brief 투영 공간의 앞쪽 평면까지의 거리(>0) */
	double m_Near;

	/*! \brief 투영 공간의 뒤쪽 평면까지의 거리(>0) */
	double m_Far;

	/*! \brief 뷰포트 변환에 사용될 너비 */
	int m_ViewWidth;

	/*! \brief 뷰포트 변환에 사용될 높이 */
	int m_ViewHeight;

	/*! \brief 카메라 중심에서 월드 좌표계까지의 거리(<0) */
	double m_ZoomDist;

	/*! \brief 월드 좌표계의 회전 정보 */
	EgQuat m_Rot;

	/*! \brief 월드 좌표계의 이동 정보 */
	EgVec3 m_Pan;

	/*! \brief 뷰 좌표계에서 표현된 월드 좌표계 (WC = ZoomDist * Rot * Pan) */
	EgTrans m_WC;

	/*! \brief 현재의 마우스 위치 정보 */
	int m_MousePt[2];

	/*! \brief 카메라의 투영 타입 */
	TypeProjection m_CameraType;

	/*! \brief 카메라의 회전 아크볼 타입 */
	TypeArcBall m_ArcBallType;

	/*! \brief 장면의 조작 타입 */
	TypeSceneManipulate m_SceneManipulateType;

	/*! \brief 카메라의 모델뷰 변환 행렬 */
	double m_ModelviewMat[16];

	/*! \brief 카메라의 투영 변환 행렬 */
	double m_ProjectionMat[16];

	/*! \brief 카메라의 뷰포트 변환 정보 */
	int m_Viewport[4];

public:
	/*!
	*	\brief 디폴트 생성자
	*/
	EgCamera();

	/*!
	*	\brief 생성자
	*
	*	\param[in] _pScene		카메라가 포한된 장면에 대한 포인터
	*	\param[in] _Fovy		원근 투영을 위한 카메라의 화각
	*	\param[in] _Near		투영 공간을 정의하는 가까운 평면까지의 거리
	*	\param[in] _Far			투영 공간을 정의하는 먼 평면까지의 거리
	*	\param[in] _ViewWidth	뷰포트 변환에 사용될 너비
	*	\param[in] _ViewHeight	뷰포트 변환에 사용될 높이
	*/
	EgCamera(EgScene *_pScene, double _Fovy, double _Near, double _Far, int _ViewWidth, int _ViewHeight);

	/*!
	*	\brief 생성자
	*
	*	\param[in] _pScene	카메라가 포한된 장면에 대한 포인터
	*	\param[in] Eye		월드 좌표계에서 표현된 카메라 원점의 위치
	*	\param[in] Center	카메라가 바라보는 장면 좌표계의 한 점
	*	\param[in] Up		월드 좌표계에서 표현된 카메라의 위쪽 방향 벡터
	*/
	EgCamera(EgScene *_pScene, EgVec3 Eye, EgVec3 Center, EgVec3 Up);

	/*!
	*	\brief 생성자
	*
	*	\param[in] _pScene	카메라가 포한된 장면에 대한 포인터
	*	\param[in] Left		왼쪽 clipping 평면
	*	\param[in] Right	오른쪽clipping 평면
	*	\param[in] Bottom	아래쪽 clipping 평면
	*	\param[in] Top		위쪽 clipping 평면
	*/
	EgCamera(EgScene *_pScene, double _Left, double _Right, double _Bottom, double _Top);

	/*!
	*	\brief 복사 생성자
	*
	*	\param[in] cpy	복사될 카메라 객체
	*/
	EgCamera(const EgCamera &cpy);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgCamera();

	/*!
	*	\brief 대입연산자
	*
	*	\param[in] rhs	대입될 피연산자
	*/
	EgCamera &operator =(const EgCamera &rhs);

	/*!
	*	\brief 카메라의 투영공간을 설정한다.
	*/
	void SetupViewFrustum();

	/*!
	*	\brief 카메라의 관측변환을 설정한다.
	*/
	void SetupViewTransform();

	/*!
	*	\brief 카메라의 뷰포트 변환정보를 설정한다.
	*
	*	\param[in] w	뷰포트 변화의 너비 정보
	*	\param[in] h	뷰포트 변환의 높이 정보
	*/
	void SetupViewport(int w, int h);

	/*!
	*	\brief 카메라의 팬 기능을 수행한다.
	*/
	void Panning(int x, int y);

	/*!
	*	\brief 카메라의 회전 기능을 수행한다.
	*
	*	\param[in] x	마우스 x 좌표
	*	\param[in] y	마우스 y 좌표
	*/
	void Rotating(int x, int y);

	/*!
	*	\brief 카메라의 줌 인/아웃 기능을 수행한다.
	*
	*	\param[in] type	양수: 줌 인, 음수: 줌 아수
	*/
	void Zooming(int type);
	

	/*!
	*	\brief 카메라의 회전 타입을 설정한다 (토글기능을 포함한다).
	*
	*	\param[in] type	카메라의 설정될 회전 타입
	*/
	void SetArcBallType(TypeArcBall type);

	/*!
	*	\brief 현재 모드에 따라 카메라의 기능을 제어한다.
	*
	*	\param[in] x	뷰포트에서 마우스의 현재 위치의 x좌표
	*	\param[in] y	뷰포트에서 마우스의 현재 위치의 y좌표
	*/
	void LButtonDown(int x, int y);

	/*!
	*	\brief 현재 모드에 따라 카메라의 기능을 제어한다.
	*
	*	\param[in] x 뷰포트에서 마우스의 현재 위치의 x좌표
	*	\param[in] y 뷰포트에서 마우스의 현재 위치의 y좌표
	*/
	void MButtonDown(int x, int y);

	/*!
	*	\brief 카메라 제어 인터페이스를 렌더링 한다.
	*/
	void MouseMove(int x, int y);

	/*!
	*	\brief 카메라 관련 요소를 렌더링 한다.
	*/
	void Render();

	/*!
	*	\brief 카메라의 변환 정보를 출력한다.
	*
	*	\param[in] fname	카메라의 변환 정보가 출력될 파일명
	*/
	void Export(char *fname);

	/*!
	*	\brief 카메라의 변환 정보를 읽어온다.
	*
	*	\param[in] fname	카메라의 변환 정보가 포함된 파일명
	*/
	void Import(char *fname);

	/*!
	*	\brief 월드 좌표계에서 표현된 투영점의 3차원 좌표를 계산한다.
	*	\note 윈도우 좌표는 좌상단이 (0, 0)
	*
	*	\param[in]	wx		투영점의 스크린 x좌표
	*	\param[in]	wy		투영점의 스크린 y좌표
	*	\param[in]	depth	투영점의 깊이(0.0 ~ 1.0) 정보
	*	\param[out] ox		투영되기전, 월드 좌표계에서의 정점의 x좌표가 저장됨
	*	\param[out] oy		투영되기전, 월드 좌표계에서의 정점의 y좌표가 저장됨
	*	\param[out] oz		투영되기전, 월드 좌표계에서의 정점의 z좌표가 저장됨
	*	
	*/
	void GetWorldCoord(double wx, double wy, double depth, double *ox, double *oy, double *oz);

	/*!
	*	\brief 스크린 좌표계에서 표현된 투영점의 좌표계를 계산한다.
	*	\note 스크린 좌표는 좌상단이 (0, 0)
	*
	*	\param[in]	pVert	객체의 정점에 대한 포인터(in)
	*	\param[out] wx		스크린 x좌표(out)
	*	\param[out] wy		스크린 y좌표(out)
	*	\param[out] wz		스크린 depth(0.0 ~ 1.0) 좌표(out)
	*	
	*/
	void GetScreenCoord(EgVertex *pVert, double *wx, double *wy, double *wz);

	/*!
	*	\brief 스크린 좌표계에서 표현된 투영점의 좌표를 계산한다.
	*
	*	\param[in]	ox	3D 정점의 x좌표
	*	\param[in]	oy	3D 정점의 y좌표
	*	\param[in]	oz	3D 정점의 z좌표
	*	\param[out] wx	스크린 x좌표
	*	\param[out] wy	스크린 y좌표
	*	\param[out] wz	스크린 depth좌표
	*
	*	\note 스크린 좌표는 좌상단이 (0, 0)
	*/
	void GetScreenCoord(double ox, double oy, double oz, double *wx, double *wy, double *wz);

	/*!
	*	\brief 월드 좌표계에서 표현된 스크린에 수직한 직선의 방정식을 계산한다.
	*
	*	\param[in]	x	윈도우 x 좌표
	*	\param[in]	y	윈도우 y 좌표
	*
	*	\return		월드 좌표계에서 표현된 스크린에 수직한 직선의 방정식을 반환한다.
	*/
	EgLine GetOrthoRay(double x, double y);

	/*!
	*	\brief 월드 좌표계에서 표현된 관측 방향 벡터를 반환한다.
	*
	*	\return 월드 좌표계에서 표현된 관측 방향 벡터를 반환한다.
	*/
	EgVec3 GetViewDirection();
};

/*! \brief Head-up Display의 표시 정보에 대한 열거형 */
#define HUD_VIEW_CUBE	0x0001
#define HUD_FRAME_RATE	0x0002
#define HUD_ORIGIN_AXIS	0x0004

/*!
*	\class EgHud
*	\brief 3차원 장면의 Head-up Display를 담당하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 02 Sept. 2012
*/
class EgHud
{
public:	
	/*! \brief 제어판이 포함된 장면에 대한 포인터 */
	EgScene *m_pScene;

	/*! \brief 뷰 큐브를 렌더링하기 위한 텍스춰와 재질 */
	std::vector<EgTexture *> m_TextureList;

	/*! \brief 현재의 관측방향이 xy, yz, zx 평면과 평행인지를 판단 */
	bool m_Parallel;

	/*! \brief 직교투영을 위한 관측공간 */
	double m_ViewFrustum[6];

	/*! \brief HUD의 표시 정보 */
	unsigned int m_DisplayInfo;

	/*! \brief HUD에 출력할 메시지 문자열 */
	std::string m_Message;

	/*! \brief 배경 색상 */
	EgVec3 m_BkgColor;

public:
	/*!
	*	\brief 생성자
	*/
	EgHud();

	/*!
	*	\brief 복사 생성자
	*
	*	\param cpy 복사될 객체
	*/
	EgHud(const EgHud &cpy);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgHud();

	/*!
	*	\brief 대입연산자
	*
	*	\param rhs 대입될 객체
	*/
	EgHud &operator =(const EgHud &rhs);

	/*!
	*	\brief Control Panel의 관측공간을 계산한다.
	*
	*	\param width 윈도우의 너비
	*	\param height 윈도우의 높이
	*/
	void Resize(int width, int height);

	/*!
	*	\brief HUD의 정보를 렌더링 한다.
	*/
	void Render();

	/*!
	*	\brief 장면의 그래디언트 배경을 렌더링 한다.
	*/
	void RenderBackGround();

	/*!
	*	\brief 장면의 FPS를 출력한다.
	*/
	void RenderFPS();

	/*!
	*	\brief 장면의 회전 중심축을 렌더링한다.
	*/
	void RenderOriginAxis();

	/*!
	*	\brief 장면의 뷰큐브을 렌더링한다.
	*/
	void RenderViewCube();

	/*!
	*	\brief 추가 메시지를 렌더링 한다.
	*/
	void RenderMessage();

	/*!
	*	\brief 텍스트를 렌더링 한다.
	*
	*	\param x 렌더링될 텍스트의 x 좌표
	*	\param y 렌더링될 텍스트의 y 좌표
	*	\param z 렌더링될 텍스트의 z 좌표
	*	\param str 렌더링될 텍스를 배열
	*	\param r 렌더링될 텍스트 색상의 R 성분
	*	\param g 렌더링될 텍스트 색상의 G 성분
	*	\param b 렌더링될 텍스트 색상의 B 성분
	*/
	void RenderText(double x, double y, double z, const char *str, double r, double g, double b);

	/*!
	*	\brief Control Panel의 메뉴 선택 및 기능을 수행한다.
	*
	*	\param x 마우스의 x 좌표
	*	\param y 마우스의 y 좌표
	*/
	void LButtonUp(int x, int y);

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetHomeView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetFrontView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetBackView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetLeftView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetRightView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetBottomView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetTopView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetEastView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetWestView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetSouthView();

	/*!
	*	\brief 장면의 관측방향을 설정한다.
	*/
	void SetNorthView();
};

/*! \brief 카메라의 조작 타입을 정의하는 열거형 변수 */
enum TypeTimerEvent
{
	TIMER_EVENT_CAMERA_TRANSIT = 0,
};
/*!
*	\class EgScene
*	\brief 3차원 장면을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 02 Sept. 2012
*/
class EgScene
{
	// 프렌드 클래스 및 함수
	friend class EgEditor;
	friend class EgSelector;

	/*!
	*	\brief 자동으로 호출되는 타이머 함수
	*
	*	\param hWnd 윈도우 핸들
	*	\param uMsg 타이머 메시지 (WM_TIMER)
	*	\param nIDEvent 타이머 번호
	*	\param dwTime 윈도우 실행 후 경과시간
	*/
	friend void CALLBACK theTimer(HWND hWnd, UINT uMsg, UINT wParam, DWORD lParam);
	
public:
	// 데이터 멤버
	/*! \brief 경로를 포함한 장면의 파일명 */
	std::string m_Name;

	/*! \brief 응용프로그램이 시작된 최초 경로 */
	std::string m_RootDir;

	/*! \brief 응용 프로그램의 뷰 윈도우의 핸들 */
	HWND m_hWndView;

	/*! \brief 장면에 포함된 메쉬 리스트 */
	std::vector<EgMesh *> m_pMeshList;

	/*! \brief 장면에 포함된 광원의 리스트 */
	std::vector<EgLight> m_LightList;

	/*! \brief 장면의 주 카메라 */
	EgCamera m_MainCamera;

	/*! \brief 장면의 시점 전환을 위한 소스 카메라 */
	EgCamera m_SrcCamera;

	/*! \brief 장면의 시점 전환을 위한 타겟 카메라 */
	EgCamera m_TarCamera;

	/*! \brief 장면에 포함된 Head-up Display */
	EgHud m_HeadUpDisplay;

	/*! \brief 장면의 바닥 평면의 렌더링 여부 */
	bool m_bShowFloor;

	/*! \brief 장면의 배경(그래디에이션) 렌더링 여부 */
	bool m_bShowBkg;

	/*! \brief 장면의 타이머 작동 여부 */
	bool m_bTimer;

	/*! \brief UI의 배경 색상 */
	unsigned char m_UIBkgColor[3];

	/*! \brief UI의 텍스트 생상 */
	unsigned char m_UItxtColor[3];
	
	/*! \biref OpenGL 픽킹용 선택버퍼 */
	GLuint m_SelectBuf[SELECT_BUFFER_SIZE];

public:
	/*!
	*	\brief 생성자
	*
	*	\param fname 장면의 파일명
	*/
	EgScene(const std::string fname = "noname01.gff");

	/*!
	*	\brief 복사생성자
	*
	*	\param cpy 복사될 모델 객체
	*/
	EgScene(const EgScene &cpy);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgScene();

	/*!
	*	\brief 대입연산자
	*
	*	\param rhs 피연산자
	*
	*	\return 대입된 자신을 반환
	*/
	EgScene &operator =(const EgScene &rhs);
	
	/*!
	*	\brief	장면의 OpenGL렌더링 상태를 초기화 한다.
	*	\note	반드시 OpenGL 상태에서 호출되어야 한다.
	*
	*	\param	bInitMeshList[in]	메쉬 리스트 초기화 여부
	*/
	virtual void InitScene(bool bInitMeshList);

	/*!
	*	\brief 장면의 뷰포트 변환을 설정한다.
	*/
	virtual void SetupViewport(int x, int y);

	/*!
	*	\brief 장면의 관측공간과 투영방법을 설정한다.
	*/
	virtual void SetupViewFrustum();

	/*!
	*	\brief 장면의 관측변환을 수행한다.
	*/
	virtual void SetupViewTransform();

	/*!
	*	\brief \a Box를 잘 포함하도록 관측공간을 조정한다.
	*
	*	\param Box 객체의 경계 상자
	*/
	virtual void AdjustViewFrustum(const EgBox &Box);

	/*!
	*	\brief	장면을 렌더링 한다.
	*
	*	\param	bOnlyModel 장면에 포함된 객체만 렌더링 할 경우 true, 아니면 false
	*/
	virtual void Render(bool bOnlyModel);

	/*!
	*	\brief 장면을 기준 평면을 렌더링 한다.
	*/
	virtual void RenderFloor();

	/*!
	*	\brief ALT 키가 눌려진 경우, 장면의 회전을 준비한다.
	*
	*	\param x 마우스 x좌표
	*	\param y 마우스 y좌표
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief 장면의 회전을 종료한다.
	*
	*	\param x 마우스 x 좌표
	*	\param y 마우스 y 좌표
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief ALT 키가 눌려진 경우, 장면의 이동을 준비한다.
	*
	*	\param x 마우스 x좌표
	*	\param y 마우스 y좌표
	*/
	virtual void MButtonDown(int x, int y);

	/*!
	*	\brief 장면의 이동을 중지한다.
	*
	*	\param x 마우스 x좌표
	*	\param y 마우스 y좌표
	*/
	virtual void MButtonUp(int x, int y);

	/*!
	*	\brief 마우스 움직임을 통한 장면의 조작(회전, 이동)을 수행한다.
	*
	*	\param x 마우스 x좌표
	*	\param y 마우스 y좌표
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief 장면의 스케일을 수행한다.
	*
	*	\param delta 마우스 휠의 변위
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief 뷰(카메라) 좌표계에서 표현된 월드 좌표계를 반환한다.
	*
	*	\return 뷰(카메라) 좌표계계에서 표현된 월드 좌표계를 반환한다.
	*/
	virtual EgTrans GetWC();

	/*!
	*	\brief	장면에 새로운 메쉬를 추가한다.
	*
	*	\param	pMesh[in]	추가될 메쉬에 대한 포인터
	*	\param	bFront[in]	기존 메쉬의 앞쪽에 추가할 경우 true, 아니면 false를 설정한다.
	*/
	void AddMesh(EgMesh *pMesh, bool bFront = false);

	/*!
	*	\brief 장면에 새로운 광원을 추가한다.
	*
	*	\param Light 추가될 광원
	*/
	void AddLight(const EgLight &Light);

	/*!
	*	\brief 장면에 새로운 카메라를 추가한다.
	*
	*	\param Cam 추가될 카메라
	*/
	void AddCamera(const EgCamera &Cam);

	/*!
	*	\brief 장면에 포함된 메쉬를 찾는다.
	*
	*	\param MeshName 찾을 메쉬의 이름
	*
	*	\return 찾은 메쉬의 포인터를 반환한다.
	*/
	EgMesh *FindMesh(std::string MeshName);

	/*!
	*	\brief	장면에 포함된 마지막 메쉬를 찾는다.
	*	\note	마지막 수정일: 2020-07-26
	*
	*	\return 마지막 추가된 메쉬의 포인터를 반환한다.
	*/
	EgMesh *FindLastMesh();

	/*!
	*	\brief 메쉬 리스트에서 주어진 이름의 메쉬를 제거한다.
	*
	*	\param MeshList 메쉬 리스트
	*	\param Name 제거할 메쉬의 이름
	*/
	void DelMesh(std::vector<EgMesh *> &MeshList, std::string Name);

	/*!
	*	\brief 장면에 타이머를 설치한다.
	*
	*	\param nIDEvent 타이머 번호
	*	\param uElapse 설정된 시간 간격 (ms 단위)
	*/
	void SetTimer(UINT nIDEvent, UINT uElapse);

	/*!
	*	\brief 장면에 타이머를 해제한다.
	*
	*	\param nIDEvent 해제할 타이머 번호
	*/
	void KillTimer(UINT nIDEvent);

	/*!
	*	\brief 장면에 포함된 메쉬의 애니메이션을 수행한다.
	*/
	void AnimateScene();

	/*!
	*	\brief 장면에 포함된 객체의 선택을 위한 선택 메커니즘으로 진입한다.
	*
	*	\param x 마우스의 X 좌표
	*	\param y 마우스의 Y 좌표
	*/
	void BeginSelect(int x, int y);

	/*!
	*	\brief 선택 메커니즘을 종료하고, 일반 렌더링 모드로 돌아온다.
	*
	*	\return 선택된 객체의 개수
	*/
	int EndSelect();
};
