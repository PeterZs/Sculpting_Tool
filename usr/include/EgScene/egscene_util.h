#pragma once
// 4�� API ����

#include "..\EgMath\egmath.h"
#include "..\EgMesh\egmesh.h"

/*!
*	\brief ��θ��� ������ ���ϸ�(Ȯ��� ����)�� ��ȯ�Ѵ�.
*
*	\param full_path ��θ��� ������ ������ �̸�
*
*	\return \a full_path���� ��θ��� ������ ���ϸ�(Ȯ���)�� ��ȯ�Ѵ�.
*/
std::string get_file_name_ext(std::string full_path);

/*!
*	\brief ��θ��� ������ ���ϸ�(Ȯ��� ������)�� ��ȯ�Ѵ�.
*
*	\param full_path ��θ��� ������ ������ �̸�
*
*	\return \a full_path���� ��θ��� ������ ���ϸ�(Ȯ��� ������)�� ��ȯ�Ѵ�.
*/
std::string get_file_name(std::string full_path);

/*!
*	\brief ������ Ȯ���ڸ� ��ȯ�Ѵ�.
*
*	\param full_path ��θ��� ������ ������ �̸�
*
*	\return \a full_path���� ���� Ȯ���ڸ� ��ȯ�Ѵ�.
*/
std::string get_file_ext(std::string full_path);

/*!
*	\brief ������ ���丮 ��θ��� ��ȯ�Ѵ�.
*
*	\param full_path ��θ��� ������ ������ �̸�
*
*	\return \a full_path���� ���丮 ��θ��� ��ȯ�Ѵ�.
*/
std::string get_file_path(std::string full_path);
