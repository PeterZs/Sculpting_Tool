#pragma once

#include <Windows.h>
#include "../EgMath/egmath.h"
#include "../GL/freeglut.h"

/* EgMesh 자료 구조 */
class EgVertex;
class EgTexel;
class EgNormal;
class EgEdge;
class EgFace;
class EgMaterial;
class EgMesh;
class EgScene;

// 파일명/문자열 처리함수
std::string get_file_name_ext(std::string full_path);
std::string get_file_name(std::string full_path);
std::string get_file_ext(std::string full_path);
std::string get_file_path(std::string full_path);
std::string cast_str(int i);
std::string cast_str(double v);
std::string cast_str(float v);
void normalize_uv(double &u, double &v);

// OBJ 파일 함수
bool import_obj(EgScene *pScene, const char *fname);
bool export_obj(EgMesh *pMesh, const char *fname);
