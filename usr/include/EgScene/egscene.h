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

// Ŭ���� ����
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
*	\brief	����� ������ ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*
*	\date	02 Sept. 2012
*/
class EgLight
{
public:
	/*! \brief ������ ��ȣ */
	GLenum m_LightNum;

	/*! \brief ������ ��ġ */
	GLfloat m_Position[4];

	/*! \brief ������ �ֺ��� ���� */
	GLfloat m_Ambient[3];

	/*! \brief ������ ���ݻ� ���� */
	GLfloat m_Diffuse[3];

	/*! \brief ������ ���ݻ� ���� */
	GLfloat m_Specular[3];

	/*! \brief ������ Ȱ��ȭ ���� */
	bool m_IsEnabled;

	/*! \brief ���߱��� ���� */
	bool m_IsSpotLight;

	/*! \brief ���߰����� ��� ������ ���� */
	GLfloat m_SpotDirection[3];

	/*! \brief ���߰����� ��� ������ ���� */
	GLfloat m_SpotCutOff;

public:
	/*!
	*	\brief ������
	*
	*	\param[in] _LightNum ������ ������ ��ȣ
	*/
	EgLight(GLenum _LightNum);

	/*!
	*	\brief ���� ������
	*
	*	\param[in] cpy ����� ��ü
	*/
	EgLight(const EgLight &cpy);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgLight();

	/*!
	*	\brief ���Կ�����
	*
	*	\param[in] rhs	�ǿ�����
	*
	*	\return ���Ե� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgLight &operator =(const EgLight &rhs);

	/*!
	*	\brief ������ Ȱ��ȭ �Ѵ�
	*/
	void Enable();

	/*!
	*	\brief ������ ��Ȱ��ȭ �Ѵ�
	*/
	void Disable();

	/*!
	*	\brief ������ ��ġ�� �����Ѵ�.
	*
	*	\param[in] x ������ x��ǥ
	*	\param[in] y ������ y��ǥ
	*	\param[in] z ������ z��ǥ
	*	\param[in] w ������ w��ǥ(1: ������, 0: ���⼺����)
	*/
	void SetPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	/*!
	*	\brief ������ �ֺ��� ������ �����Ѵ�.
	*
	*	\param[in] r ������ ������ �ֺ��� ����
	*	\param[in] g ������ �ʷϻ� �ֺ��� ����
	*	\param[in] b ������ �Ķ��� �ֺ��� ����
	*/
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief ������ ���ݻ籤 ������ �����Ѵ�.
	*
	*	\param[in] r ������ ������ ���ݻ籤 ����
	*	\param[in] g ������ �ʷϻ� ���ݻ籤 ����
	*	\param[in] b ������ �Ķ��� ���ݻ籤 ����
	*/
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief ������ ���ݻ籤 ������ �����Ѵ�.
	*
	*	\param[in] r ������ ������ ���ݻ籤 ����
	*	\param[in] g ������ �ʷϻ� ���ݻ籤 ����
	*	\param[in] b ������ �Ķ��� ���ݻ籤 ����
	*/
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	/*!
	*	\brief ������ ������ ���·� �����Ѵ�.
	*/
	void SetPointLight();

	/*!
	*	\brief ������ ���⼺ ���� ���·� �����Ѵ�.
	*/
	void SetDirectionalLight();

	/*!
	*	\brief ���߱����� ����� ������ �����Ѵ�.
	*
	*	\param[in] vx		���߱����� ������ x����
	*	\param[in] vy		���߱����� ������ y����
	*	\param[in] vz		���߱����� ������ z����
	*	\param[in] cutoff	���߱����� ����
	*/
	void SetSpotLight(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat cutoff);
};

/*! \brief ī�޶��� ���� Ÿ���� �����ϴ� ������ ���� */
enum TypeProjection
{
	PROJECTION_ORTHO = 0,
	PROJECTION_PERS,
};

/*! \brief ����� ���� Ÿ���� �����ϴ� ������ ���� */
enum TypeSceneManipulate
{
	SCENE_MANIPULATE_NONE = 0,
	SCENE_MANIPULATE_ROTATE = 1,
	SCENE_MANIPULATE_PAN,
	SCENE_MANIPULATE_ZOOM,
};

/*!
*	\class EgCamera
*	\brief 3���� ���(EgScene)�� �����ϴ� ī�޶� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 06 Sept. 2012
*/
class EgCamera
{
public:	
	/*! \brief ī�޶� ���Ե� ��鿡 ���� ������ */
	EgScene *m_pScene;

	/*! \brief ���� ������ ���� ī�޶��� ȭ��(field of view) */
	double m_Fovy;

	/*! \brief ���� ������ ���� �������� �Ÿ�(>0) */
	double m_Near;

	/*! \brief ���� ������ ���� �������� �Ÿ�(>0) */
	double m_Far;

	/*! \brief ����Ʈ ��ȯ�� ���� �ʺ� */
	int m_ViewWidth;

	/*! \brief ����Ʈ ��ȯ�� ���� ���� */
	int m_ViewHeight;

	/*! \brief ī�޶� �߽ɿ��� ���� ��ǥ������� �Ÿ�(<0) */
	double m_ZoomDist;

	/*! \brief ���� ��ǥ���� ȸ�� ���� */
	EgQuat m_Rot;

	/*! \brief ���� ��ǥ���� �̵� ���� */
	EgVec3 m_Pan;

	/*! \brief �� ��ǥ�迡�� ǥ���� ���� ��ǥ�� (WC = ZoomDist * Rot * Pan) */
	EgTrans m_WC;

	/*! \brief ������ ���콺 ��ġ ���� */
	int m_MousePt[2];

	/*! \brief ī�޶��� ���� Ÿ�� */
	TypeProjection m_CameraType;

	/*! \brief ī�޶��� ȸ�� ��ũ�� Ÿ�� */
	TypeArcBall m_ArcBallType;

	/*! \brief ����� ���� Ÿ�� */
	TypeSceneManipulate m_SceneManipulateType;

	/*! \brief ī�޶��� �𵨺� ��ȯ ��� */
	double m_ModelviewMat[16];

	/*! \brief ī�޶��� ���� ��ȯ ��� */
	double m_ProjectionMat[16];

	/*! \brief ī�޶��� ����Ʈ ��ȯ ���� */
	int m_Viewport[4];

public:
	/*!
	*	\brief ����Ʈ ������
	*/
	EgCamera();

	/*!
	*	\brief ������
	*
	*	\param[in] _pScene		ī�޶� ���ѵ� ��鿡 ���� ������
	*	\param[in] _Fovy		���� ������ ���� ī�޶��� ȭ��
	*	\param[in] _Near		���� ������ �����ϴ� ����� �������� �Ÿ�
	*	\param[in] _Far			���� ������ �����ϴ� �� �������� �Ÿ�
	*	\param[in] _ViewWidth	����Ʈ ��ȯ�� ���� �ʺ�
	*	\param[in] _ViewHeight	����Ʈ ��ȯ�� ���� ����
	*/
	EgCamera(EgScene *_pScene, double _Fovy, double _Near, double _Far, int _ViewWidth, int _ViewHeight);

	/*!
	*	\brief ������
	*
	*	\param[in] _pScene	ī�޶� ���ѵ� ��鿡 ���� ������
	*	\param[in] Eye		���� ��ǥ�迡�� ǥ���� ī�޶� ������ ��ġ
	*	\param[in] Center	ī�޶� �ٶ󺸴� ��� ��ǥ���� �� ��
	*	\param[in] Up		���� ��ǥ�迡�� ǥ���� ī�޶��� ���� ���� ����
	*/
	EgCamera(EgScene *_pScene, EgVec3 Eye, EgVec3 Center, EgVec3 Up);

	/*!
	*	\brief ������
	*
	*	\param[in] _pScene	ī�޶� ���ѵ� ��鿡 ���� ������
	*	\param[in] Left		���� clipping ���
	*	\param[in] Right	������clipping ���
	*	\param[in] Bottom	�Ʒ��� clipping ���
	*	\param[in] Top		���� clipping ���
	*/
	EgCamera(EgScene *_pScene, double _Left, double _Right, double _Bottom, double _Top);

	/*!
	*	\brief ���� ������
	*
	*	\param[in] cpy	����� ī�޶� ��ü
	*/
	EgCamera(const EgCamera &cpy);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgCamera();

	/*!
	*	\brief ���Կ�����
	*
	*	\param[in] rhs	���Ե� �ǿ�����
	*/
	EgCamera &operator =(const EgCamera &rhs);

	/*!
	*	\brief ī�޶��� ���������� �����Ѵ�.
	*/
	void SetupViewFrustum();

	/*!
	*	\brief ī�޶��� ������ȯ�� �����Ѵ�.
	*/
	void SetupViewTransform();

	/*!
	*	\brief ī�޶��� ����Ʈ ��ȯ������ �����Ѵ�.
	*
	*	\param[in] w	����Ʈ ��ȭ�� �ʺ� ����
	*	\param[in] h	����Ʈ ��ȯ�� ���� ����
	*/
	void SetupViewport(int w, int h);

	/*!
	*	\brief ī�޶��� �� ����� �����Ѵ�.
	*/
	void Panning(int x, int y);

	/*!
	*	\brief ī�޶��� ȸ�� ����� �����Ѵ�.
	*
	*	\param[in] x	���콺 x ��ǥ
	*	\param[in] y	���콺 y ��ǥ
	*/
	void Rotating(int x, int y);

	/*!
	*	\brief ī�޶��� �� ��/�ƿ� ����� �����Ѵ�.
	*
	*	\param[in] type	���: �� ��, ����: �� �Ƽ�
	*/
	void Zooming(int type);
	

	/*!
	*	\brief ī�޶��� ȸ�� Ÿ���� �����Ѵ� (��۱���� �����Ѵ�).
	*
	*	\param[in] type	ī�޶��� ������ ȸ�� Ÿ��
	*/
	void SetArcBallType(TypeArcBall type);

	/*!
	*	\brief ���� ��忡 ���� ī�޶��� ����� �����Ѵ�.
	*
	*	\param[in] x	����Ʈ���� ���콺�� ���� ��ġ�� x��ǥ
	*	\param[in] y	����Ʈ���� ���콺�� ���� ��ġ�� y��ǥ
	*/
	void LButtonDown(int x, int y);

	/*!
	*	\brief ���� ��忡 ���� ī�޶��� ����� �����Ѵ�.
	*
	*	\param[in] x ����Ʈ���� ���콺�� ���� ��ġ�� x��ǥ
	*	\param[in] y ����Ʈ���� ���콺�� ���� ��ġ�� y��ǥ
	*/
	void MButtonDown(int x, int y);

	/*!
	*	\brief ī�޶� ���� �������̽��� ������ �Ѵ�.
	*/
	void MouseMove(int x, int y);

	/*!
	*	\brief ī�޶� ���� ��Ҹ� ������ �Ѵ�.
	*/
	void Render();

	/*!
	*	\brief ī�޶��� ��ȯ ������ ����Ѵ�.
	*
	*	\param[in] fname	ī�޶��� ��ȯ ������ ��µ� ���ϸ�
	*/
	void Export(char *fname);

	/*!
	*	\brief ī�޶��� ��ȯ ������ �о�´�.
	*
	*	\param[in] fname	ī�޶��� ��ȯ ������ ���Ե� ���ϸ�
	*/
	void Import(char *fname);

	/*!
	*	\brief ���� ��ǥ�迡�� ǥ���� �������� 3���� ��ǥ�� ����Ѵ�.
	*	\note ������ ��ǥ�� �»���� (0, 0)
	*
	*	\param[in]	wx		�������� ��ũ�� x��ǥ
	*	\param[in]	wy		�������� ��ũ�� y��ǥ
	*	\param[in]	depth	�������� ����(0.0 ~ 1.0) ����
	*	\param[out] ox		�����Ǳ���, ���� ��ǥ�迡���� ������ x��ǥ�� �����
	*	\param[out] oy		�����Ǳ���, ���� ��ǥ�迡���� ������ y��ǥ�� �����
	*	\param[out] oz		�����Ǳ���, ���� ��ǥ�迡���� ������ z��ǥ�� �����
	*	
	*/
	void GetWorldCoord(double wx, double wy, double depth, double *ox, double *oy, double *oz);

	/*!
	*	\brief ��ũ�� ��ǥ�迡�� ǥ���� �������� ��ǥ�踦 ����Ѵ�.
	*	\note ��ũ�� ��ǥ�� �»���� (0, 0)
	*
	*	\param[in]	pVert	��ü�� ������ ���� ������(in)
	*	\param[out] wx		��ũ�� x��ǥ(out)
	*	\param[out] wy		��ũ�� y��ǥ(out)
	*	\param[out] wz		��ũ�� depth(0.0 ~ 1.0) ��ǥ(out)
	*	
	*/
	void GetScreenCoord(EgVertex *pVert, double *wx, double *wy, double *wz);

	/*!
	*	\brief ��ũ�� ��ǥ�迡�� ǥ���� �������� ��ǥ�� ����Ѵ�.
	*
	*	\param[in]	ox	3D ������ x��ǥ
	*	\param[in]	oy	3D ������ y��ǥ
	*	\param[in]	oz	3D ������ z��ǥ
	*	\param[out] wx	��ũ�� x��ǥ
	*	\param[out] wy	��ũ�� y��ǥ
	*	\param[out] wz	��ũ�� depth��ǥ
	*
	*	\note ��ũ�� ��ǥ�� �»���� (0, 0)
	*/
	void GetScreenCoord(double ox, double oy, double oz, double *wx, double *wy, double *wz);

	/*!
	*	\brief ���� ��ǥ�迡�� ǥ���� ��ũ���� ������ ������ �������� ����Ѵ�.
	*
	*	\param[in]	x	������ x ��ǥ
	*	\param[in]	y	������ y ��ǥ
	*
	*	\return		���� ��ǥ�迡�� ǥ���� ��ũ���� ������ ������ �������� ��ȯ�Ѵ�.
	*/
	EgLine GetOrthoRay(double x, double y);

	/*!
	*	\brief ���� ��ǥ�迡�� ǥ���� ���� ���� ���͸� ��ȯ�Ѵ�.
	*
	*	\return ���� ��ǥ�迡�� ǥ���� ���� ���� ���͸� ��ȯ�Ѵ�.
	*/
	EgVec3 GetViewDirection();
};

/*! \brief Head-up Display�� ǥ�� ������ ���� ������ */
#define HUD_VIEW_CUBE	0x0001
#define HUD_FRAME_RATE	0x0002
#define HUD_ORIGIN_AXIS	0x0004

/*!
*	\class EgHud
*	\brief 3���� ����� Head-up Display�� ����ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 02 Sept. 2012
*/
class EgHud
{
public:	
	/*! \brief �������� ���Ե� ��鿡 ���� ������ */
	EgScene *m_pScene;

	/*! \brief �� ť�긦 �������ϱ� ���� �ؽ���� ���� */
	std::vector<EgTexture *> m_TextureList;

	/*! \brief ������ ���������� xy, yz, zx ���� ���������� �Ǵ� */
	bool m_Parallel;

	/*! \brief ���������� ���� �������� */
	double m_ViewFrustum[6];

	/*! \brief HUD�� ǥ�� ���� */
	unsigned int m_DisplayInfo;

	/*! \brief HUD�� ����� �޽��� ���ڿ� */
	std::string m_Message;

	/*! \brief ��� ���� */
	EgVec3 m_BkgColor;

public:
	/*!
	*	\brief ������
	*/
	EgHud();

	/*!
	*	\brief ���� ������
	*
	*	\param cpy ����� ��ü
	*/
	EgHud(const EgHud &cpy);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgHud();

	/*!
	*	\brief ���Կ�����
	*
	*	\param rhs ���Ե� ��ü
	*/
	EgHud &operator =(const EgHud &rhs);

	/*!
	*	\brief Control Panel�� ���������� ����Ѵ�.
	*
	*	\param width �������� �ʺ�
	*	\param height �������� ����
	*/
	void Resize(int width, int height);

	/*!
	*	\brief HUD�� ������ ������ �Ѵ�.
	*/
	void Render();

	/*!
	*	\brief ����� �׷����Ʈ ����� ������ �Ѵ�.
	*/
	void RenderBackGround();

	/*!
	*	\brief ����� FPS�� ����Ѵ�.
	*/
	void RenderFPS();

	/*!
	*	\brief ����� ȸ�� �߽����� �������Ѵ�.
	*/
	void RenderOriginAxis();

	/*!
	*	\brief ����� ��ť���� �������Ѵ�.
	*/
	void RenderViewCube();

	/*!
	*	\brief �߰� �޽����� ������ �Ѵ�.
	*/
	void RenderMessage();

	/*!
	*	\brief �ؽ�Ʈ�� ������ �Ѵ�.
	*
	*	\param x �������� �ؽ�Ʈ�� x ��ǥ
	*	\param y �������� �ؽ�Ʈ�� y ��ǥ
	*	\param z �������� �ؽ�Ʈ�� z ��ǥ
	*	\param str �������� �ؽ��� �迭
	*	\param r �������� �ؽ�Ʈ ������ R ����
	*	\param g �������� �ؽ�Ʈ ������ G ����
	*	\param b �������� �ؽ�Ʈ ������ B ����
	*/
	void RenderText(double x, double y, double z, const char *str, double r, double g, double b);

	/*!
	*	\brief Control Panel�� �޴� ���� �� ����� �����Ѵ�.
	*
	*	\param x ���콺�� x ��ǥ
	*	\param y ���콺�� y ��ǥ
	*/
	void LButtonUp(int x, int y);

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetHomeView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetFrontView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetBackView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetLeftView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetRightView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetBottomView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetTopView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetEastView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetWestView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetSouthView();

	/*!
	*	\brief ����� ���������� �����Ѵ�.
	*/
	void SetNorthView();
};

/*! \brief ī�޶��� ���� Ÿ���� �����ϴ� ������ ���� */
enum TypeTimerEvent
{
	TIMER_EVENT_CAMERA_TRANSIT = 0,
};
/*!
*	\class EgScene
*	\brief 3���� ����� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date 02 Sept. 2012
*/
class EgScene
{
	// ������ Ŭ���� �� �Լ�
	friend class EgEditor;
	friend class EgSelector;

	/*!
	*	\brief �ڵ����� ȣ��Ǵ� Ÿ�̸� �Լ�
	*
	*	\param hWnd ������ �ڵ�
	*	\param uMsg Ÿ�̸� �޽��� (WM_TIMER)
	*	\param nIDEvent Ÿ�̸� ��ȣ
	*	\param dwTime ������ ���� �� ����ð�
	*/
	friend void CALLBACK theTimer(HWND hWnd, UINT uMsg, UINT wParam, DWORD lParam);
	
public:
	// ������ ���
	/*! \brief ��θ� ������ ����� ���ϸ� */
	std::string m_Name;

	/*! \brief �������α׷��� ���۵� ���� ��� */
	std::string m_RootDir;

	/*! \brief ���� ���α׷��� �� �������� �ڵ� */
	HWND m_hWndView;

	/*! \brief ��鿡 ���Ե� �޽� ����Ʈ */
	std::vector<EgMesh *> m_pMeshList;

	/*! \brief ��鿡 ���Ե� ������ ����Ʈ */
	std::vector<EgLight> m_LightList;

	/*! \brief ����� �� ī�޶� */
	EgCamera m_MainCamera;

	/*! \brief ����� ���� ��ȯ�� ���� �ҽ� ī�޶� */
	EgCamera m_SrcCamera;

	/*! \brief ����� ���� ��ȯ�� ���� Ÿ�� ī�޶� */
	EgCamera m_TarCamera;

	/*! \brief ��鿡 ���Ե� Head-up Display */
	EgHud m_HeadUpDisplay;

	/*! \brief ����� �ٴ� ����� ������ ���� */
	bool m_bShowFloor;

	/*! \brief ����� ���(�׷����̼�) ������ ���� */
	bool m_bShowBkg;

	/*! \brief ����� Ÿ�̸� �۵� ���� */
	bool m_bTimer;

	/*! \brief UI�� ��� ���� */
	unsigned char m_UIBkgColor[3];

	/*! \brief UI�� �ؽ�Ʈ ���� */
	unsigned char m_UItxtColor[3];
	
	/*! \biref OpenGL ��ŷ�� ���ù��� */
	GLuint m_SelectBuf[SELECT_BUFFER_SIZE];

public:
	/*!
	*	\brief ������
	*
	*	\param fname ����� ���ϸ�
	*/
	EgScene(const std::string fname = "noname01.gff");

	/*!
	*	\brief ���������
	*
	*	\param cpy ����� �� ��ü
	*/
	EgScene(const EgScene &cpy);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgScene();

	/*!
	*	\brief ���Կ�����
	*
	*	\param rhs �ǿ�����
	*
	*	\return ���Ե� �ڽ��� ��ȯ
	*/
	EgScene &operator =(const EgScene &rhs);
	
	/*!
	*	\brief	����� OpenGL������ ���¸� �ʱ�ȭ �Ѵ�.
	*	\note	�ݵ�� OpenGL ���¿��� ȣ��Ǿ�� �Ѵ�.
	*
	*	\param	bInitMeshList[in]	�޽� ����Ʈ �ʱ�ȭ ����
	*/
	virtual void InitScene(bool bInitMeshList);

	/*!
	*	\brief ����� ����Ʈ ��ȯ�� �����Ѵ�.
	*/
	virtual void SetupViewport(int x, int y);

	/*!
	*	\brief ����� ���������� ��������� �����Ѵ�.
	*/
	virtual void SetupViewFrustum();

	/*!
	*	\brief ����� ������ȯ�� �����Ѵ�.
	*/
	virtual void SetupViewTransform();

	/*!
	*	\brief \a Box�� �� �����ϵ��� ���������� �����Ѵ�.
	*
	*	\param Box ��ü�� ��� ����
	*/
	virtual void AdjustViewFrustum(const EgBox &Box);

	/*!
	*	\brief	����� ������ �Ѵ�.
	*
	*	\param	bOnlyModel ��鿡 ���Ե� ��ü�� ������ �� ��� true, �ƴϸ� false
	*/
	virtual void Render(bool bOnlyModel);

	/*!
	*	\brief ����� ���� ����� ������ �Ѵ�.
	*/
	virtual void RenderFloor();

	/*!
	*	\brief ALT Ű�� ������ ���, ����� ȸ���� �غ��Ѵ�.
	*
	*	\param x ���콺 x��ǥ
	*	\param y ���콺 y��ǥ
	*/
	virtual void LButtonDown(int x, int y);

	/*!
	*	\brief ����� ȸ���� �����Ѵ�.
	*
	*	\param x ���콺 x ��ǥ
	*	\param y ���콺 y ��ǥ
	*/
	virtual void LButtonUp(int x, int y);

	/*!
	*	\brief ALT Ű�� ������ ���, ����� �̵��� �غ��Ѵ�.
	*
	*	\param x ���콺 x��ǥ
	*	\param y ���콺 y��ǥ
	*/
	virtual void MButtonDown(int x, int y);

	/*!
	*	\brief ����� �̵��� �����Ѵ�.
	*
	*	\param x ���콺 x��ǥ
	*	\param y ���콺 y��ǥ
	*/
	virtual void MButtonUp(int x, int y);

	/*!
	*	\brief ���콺 �������� ���� ����� ����(ȸ��, �̵�)�� �����Ѵ�.
	*
	*	\param x ���콺 x��ǥ
	*	\param y ���콺 y��ǥ
	*/
	virtual void MouseMove(int x, int y);

	/*!
	*	\brief ����� �������� �����Ѵ�.
	*
	*	\param delta ���콺 ���� ����
	*/
	virtual void MouseWheel(int delta);

	/*!
	*	\brief ��(ī�޶�) ��ǥ�迡�� ǥ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return ��(ī�޶�) ��ǥ��迡�� ǥ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetWC();

	/*!
	*	\brief	��鿡 ���ο� �޽��� �߰��Ѵ�.
	*
	*	\param	pMesh[in]	�߰��� �޽��� ���� ������
	*	\param	bFront[in]	���� �޽��� ���ʿ� �߰��� ��� true, �ƴϸ� false�� �����Ѵ�.
	*/
	void AddMesh(EgMesh *pMesh, bool bFront = false);

	/*!
	*	\brief ��鿡 ���ο� ������ �߰��Ѵ�.
	*
	*	\param Light �߰��� ����
	*/
	void AddLight(const EgLight &Light);

	/*!
	*	\brief ��鿡 ���ο� ī�޶� �߰��Ѵ�.
	*
	*	\param Cam �߰��� ī�޶�
	*/
	void AddCamera(const EgCamera &Cam);

	/*!
	*	\brief ��鿡 ���Ե� �޽��� ã�´�.
	*
	*	\param MeshName ã�� �޽��� �̸�
	*
	*	\return ã�� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	EgMesh *FindMesh(std::string MeshName);

	/*!
	*	\brief	��鿡 ���Ե� ������ �޽��� ã�´�.
	*	\note	������ ������: 2020-07-26
	*
	*	\return ������ �߰��� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	EgMesh *FindLastMesh();

	/*!
	*	\brief �޽� ����Ʈ���� �־��� �̸��� �޽��� �����Ѵ�.
	*
	*	\param MeshList �޽� ����Ʈ
	*	\param Name ������ �޽��� �̸�
	*/
	void DelMesh(std::vector<EgMesh *> &MeshList, std::string Name);

	/*!
	*	\brief ��鿡 Ÿ�̸Ӹ� ��ġ�Ѵ�.
	*
	*	\param nIDEvent Ÿ�̸� ��ȣ
	*	\param uElapse ������ �ð� ���� (ms ����)
	*/
	void SetTimer(UINT nIDEvent, UINT uElapse);

	/*!
	*	\brief ��鿡 Ÿ�̸Ӹ� �����Ѵ�.
	*
	*	\param nIDEvent ������ Ÿ�̸� ��ȣ
	*/
	void KillTimer(UINT nIDEvent);

	/*!
	*	\brief ��鿡 ���Ե� �޽��� �ִϸ��̼��� �����Ѵ�.
	*/
	void AnimateScene();

	/*!
	*	\brief ��鿡 ���Ե� ��ü�� ������ ���� ���� ��Ŀ�������� �����Ѵ�.
	*
	*	\param x ���콺�� X ��ǥ
	*	\param y ���콺�� Y ��ǥ
	*/
	void BeginSelect(int x, int y);

	/*!
	*	\brief ���� ��Ŀ������ �����ϰ�, �Ϲ� ������ ���� ���ƿ´�.
	*
	*	\return ���õ� ��ü�� ����
	*/
	int EndSelect();
};
