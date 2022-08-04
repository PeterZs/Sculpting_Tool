#pragma once
// 8개 API 제공

#include <Windows.h>
#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"
#include "..\GL\freeglut.h"

class EgScene;

/*!
*	\brief 그룹으로 구분된 삼각형의 포인터 배열을 구한다.
*
*	\param pMesh 대상 메쉬에 대한 포인터
*	\param GroupedFaces 그룹명으로 구분된 삼각형 포인터가 저장된다.
*
*	\return 그룹의 개수를 반환한다.
*/
int get_grouped_faces(EgMesh *pMesh, std::map<std::string, std::vector<EgFace *>> &GroupedFaces);

/*!
*	\brief 텍스처 좌표를 0과 1사이로 정규화 한다.
*
*	\param u 텍스처 좌표 u
*	\param v 텍스처 좌표 v
*/
void normalize_uv(double &u, double &v);

/*!
*	\brief	포인트 집합을 불러온다.
*
*	\param	fname[in]	파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool import_pts(const char *fname, std::vector<EgPos> &Pts);

/*!
*	\brief OBJ 파일을 임포트한다.
*
*	\param fname 메쉬 파일의 이름[in]
*
*	\return 임포트된 메쉬의 포인터를 반환한다.
*/
EgMesh *import_obj(const char *fname);

/*!
*	\brief	OBJ 파일을 임포트하여 장면에 추가한다.
*
*	\param	m_pScene[in]	임포트할 메쉬가 포함될 장면에 대한 포인터
*	\param	FileName[in]	전체 경로가 포함된 파일의 이름(열기 대화 상자를 이용할 경우)
*
*	\return 성공이면 true, 실패면 false를 반환한다.
*/
bool import_obj(EgScene *pScene, const char *fname);

/*!
*	\brief 메쉬를 파일(*.obj)로 저장한다.
*
*	\param pMesh 저장할 메쉬의 포인터
*	\param fname 파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool export_obj(EgMesh *pMesh, const char *fname);

/*!
*	\brief	STL 파일을 임포트한다.
*
*	\param	pScene[in]	임포트한 메쉬 파일이 저장될 장면에 대한 포인터
*	\param	fname[in]	임포트할 파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool import_stl(EgScene *pScene, const char *fname);

/*!
*	\brief 메쉬 파일을 STL 파일로 저장한다.
*
*	\param pMesh 저장할 메쉬의 포인터
*	\param fname 파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool export_stl(EgMesh *pMesh, const char *fname);

/*!
*	\brief 메쉬 파일을 TXT 파일로 저장한다.
*
*	\param pMesh 저장할 메쉬의 포인터
*	\param fname 파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool export_txt(EgMesh *pMesh, const char *fname);

/*!
*	\brief OFF 파일을 임포트하여 장면에 추가한다.
*
*	\param m_pScene 임포트할 메쉬가 포함될 장면에 대한 포인터
*	\param FileName 전체 경로가 포함된 파일의 이름(열기 대화 상자를 이용할 경우)
*
*	\return 성공이면 true, 실패면 false를 반환한다.
*/
bool import_off(EgScene *pScene, const char *fname);

/*!
*	\brief 메쉬 파일을 OFF 파일로 저장한다.
*
*	\param pMesh[in] 저장할 메쉬의 포인터
*	\param fname[in] 파일의 이름
*
*	\return 성공: true, 실패: flase
*/
bool export_off(EgMesh *pMesh, const char *fname);