#pragma once
// 4개 API 제공

#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"

/*!
*	\brief 경로명을 제외한 파일명(확장명 포함)을 반환한다.
*
*	\param full_path 경로명을 포함한 파일의 이름
*
*	\return \a full_path에서 경로명을 제외한 파일명(확장명)을 반환한다.
*/
std::string get_file_name_ext(std::string full_path);

/*!
*	\brief 경로명을 제외한 파일명(확장명 불포함)을 반환한다.
*
*	\param full_path 경로명을 포함한 파일의 이름
*
*	\return \a full_path에서 경로명을 제외한 파일명(확장명 불포함)을 반환한다.
*/
std::string get_file_name(std::string full_path);

/*!
*	\brief 파일의 확장자를 반환한다.
*
*	\param full_path 경로명을 포함한 파일의 이름
*
*	\return \a full_path에서 파일 확장자를 반환한다.
*/
std::string get_file_ext(std::string full_path);

/*!
*	\brief 파일의 디렉토리 경로명을 반환한다.
*
*	\param full_path 경로명을 포함한 파일의 이름
*
*	\return \a full_path에서 디렉토리 경로명을 반환한다.
*/
std::string get_file_path(std::string full_path);
