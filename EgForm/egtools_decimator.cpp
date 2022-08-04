#include "egtools_decimator.h"

extern void normalize_uv(double &u, double &v);
//{
//	u = (u > 1.0) ? (u - (int)(u)) : u;
//	u = (u < 0.0) ? (u - (int)(u - 1.0)) : u;
//
//	v = (v > 1.0) ? (v - (int)(v)) : v;
//	v = (v < 0.0) ? (v - (int)(v - 1.0)) : v;
//}

/***************************
EdgeCollapseInfo Ŭ���� ����
/***************************/
/*!
*	\brief ������
*
*	\param pEdge ������ ������ ���� ������
*	\param Pos ���� ���� ��, �� ������ ��ġ
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos)
{
	m_pEdge = pEdge;
	m_Pos = Pos;
	m_Cost = pEdge->m_Cost;
}

/*!
*	\brief ������
*
*	\param pEdge ������ ������ ���� ������
*	\param Pos ���� ���� ��, �� ������ ��ġ
*	\param UV ���� ���� ��, �� ������ �ؽ�ó ��ǥ
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos, EgVec2 UV)
{
	m_pEdge = pEdge;
	m_Pos = Pos;
	m_UV = UV;
	m_Cost = pEdge->m_Cost;
}

/*!
*	\brief ���� ������
*
*	\param cpy ����� ��ü
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(const EdgeCollapseInfo &cpy)
{
	m_pEdge = cpy.m_pEdge;
	m_Pos = cpy.m_Pos;
	m_UV = cpy.m_UV;
	m_Cost = cpy.m_Cost;
}

/*!
*	\brief �Ҹ���
*/
EgDecimator::EdgeCollapseInfo::~EdgeCollapseInfo()
{
}

/*!
*	\brief ���� ������
*
*	\param rhs ���Ե� ��ü
*/
EgDecimator::EdgeCollapseInfo &EgDecimator::EdgeCollapseInfo::operator =(const EdgeCollapseInfo &rhs)
{
	m_pEdge = rhs.m_pEdge;
	m_Pos = rhs.m_Pos;
	m_UV = rhs.m_UV;
	m_Cost = rhs.m_Cost;
	return *this;
}

/*!
*	\brief ��(>) ������
*
*	\param lhs ���� ��ü
*	\param rhs ������ ��ü
*/
bool operator >(const EgDecimator::EdgeCollapseInfo &lhs, const EgDecimator::EdgeCollapseInfo &rhs)
{
	return (lhs.m_Cost > rhs.m_Cost);
}

/**********************
EgDecimator Ŭ���� ����
/**********************/
/*!
*	\brief ������
*
*	\param pMesh �ܼ�ȭ�� ��� �޽��� ���� ������
*	\param bTexture �ؽ�ó �ܼ�ȭ ����
*/
EgDecimator::EgDecimator(EgMesh *pMesh, bool bDecimateTexture)
{
	// ��� �޽��� �ؽ�ó ���� ���θ� �����Ѵ�.
	m_pMesh = pMesh;
	if (!m_pMesh->m_pTexels.empty() && bDecimateTexture)
		m_bTextureDecimate = true;
	else
		m_bTextureDecimate = false;
}

/*!
*	\brief �Ҹ���
*/
EgDecimator::~EgDecimator()
{
}

/*!
*	\brief �ʱ�ȭ �۾��� �����Ѵ�.
*
*	\param CollapseType ���� ���� �ɼ�
*/
void EgDecimator::Init(TypeCollapse CollapseType)
{
	// ���� ���� �ɼ��� �����Ѵ�.
	m_CollapseType = CollapseType;

	// �޽� ������ �ε����� �����Ѵ�.
	int NumVert = m_pMesh->UpdateVertIdx();

	// �ؽ�ó �ܼ�ȭ�� ���� �Ѵٸ� 
	if (m_bTextureDecimate)
	{
		// �ؽ�ó ��ǥ�� ����ȭ �Ѵ�.
		for (EgTexel *t : m_pMesh->m_pTexels)
			::normalize_uv(t->m_UV[0], t->m_UV[1]);

		// ��� ������ ������ �ʱ�ȭ �Ѵ�.
		InitBndryVertInfo_T(NumVert);

		// �޽� ������ QEM ����� �ʱ�ȭ �Ѵ�.
		InitVertQEM_T(NumVert);

		// ������ ���� ����� �ʱ�ȭ �Ѵ�.
		InitCollapseInfo_T();
	}
	else // ���������� �ܼ�ȭ �Ѵٸ�
	{
		// �޽� ������ QEM ����� �ʱ�ȭ �Ѵ�.
		InitVertQEM(NumVert);

		// ������ ���� ����� �ʱ�ȭ �Ѵ�.
		InitCollapseInfo();
	}
}

/*!
*	\brief �޽��� ���(���� + �ؽ�ó) ���� ������ ���Ѵ�.
*
*	\param NumVert �޽� ������ ����
*/
void EgDecimator::InitBndryVertInfo_T(int NumVert)
{
	// ��� ���� ������ �ʱ�ȭ �Ѵ�.
	m_BndryVertInfo.clear();
	m_BndryVertInfo.assign(NumVert, false);

	// �޽� ������ ������ ���Ͽ�
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// �������� �����ϴ� ù ��° ������ �ؼ��� ���Ͽ�
		EgTexel *pTexel = v->m_pEdges[0]->m_pTexel;

		// �������� �����ϴ� ������ ������ ���Ͽ�		
		for (EgEdge *e : v->m_pEdges)
		{
			// ��� ������ �ִٸ� ��� �������� ����Ѵ�.
			if (e->m_pMate == NULL)
			{
				m_BndryVertInfo[v->m_Idx] = true;
				break;
			}
			// �ؽ�ó ��� ������ �ִٸ� ��� �������� ����Ѵ�.
			if (e->m_pTexel->m_UV != pTexel->m_UV)
			{
				m_BndryVertInfo[v->m_Idx] = true;
				break;
			}
		}
	}
}

/*!
*	\brief �Ϲ�ȭ�� Quatric error ����� ���Ѵ�.
*
*	\param K ����� ����� 6 x 6 ���
*	\param p �ﰢ���� �Ϲ�ȭ�� ���� ����
*	\param q �ﰢ���� �Ϲ�ȭ�� ���� ����
*	\param r �ﰢ���� �Ϲ�ȭ�� ���� ����
*/
void EgDecimator::GetErrorMatrix_T(EgMat &K, EgVec &p, EgVec &q, EgVec &r)
{
	// ������ 5���� ���� e1, e2 �����Ѵ�.
	EgVec e1 = (q - p).Normalize();
	EgVec e2 = ((r - p) - ((r - p) * e1) * e1).Normalize();

	// ��� K�� 5 x 5 ��� A�� 5���� ���� b�� ��� c�� �����ȴ�.
	// K = | A    b |
	//     | b^t  c |

	// ��� K�� A�κ��� ���ϰ�,		
	K[0][0] = 1.0 - e1[0] * e1[0] - e2[0] * e2[0];
	K[0][1] = -e1[0] * e1[1] - e2[0] * e2[1];
	K[0][2] = -e1[0] * e1[2] - e2[0] * e2[2];
	K[0][3] = -e1[0] * e1[3] - e2[0] * e2[3];
	K[0][4] = -e1[0] * e1[4] - e2[0] * e2[4];

	K[1][0] = K[0][1];
	K[1][1] = 1.0 - e1[1] * e1[1] - e2[1] * e2[1];
	K[1][2] = -e1[1] * e1[2] - e2[1] * e2[2];
	K[1][3] = -e1[1] * e1[3] - e2[1] * e2[3];
	K[1][4] = -e1[1] * e1[4] - e2[1] * e2[4];

	K[2][0] = K[0][2];
	K[2][1] = K[1][2];
	K[2][2] = 1.0 - e1[2] * e1[2] - e2[2] * e2[2];
	K[2][3] = -e1[2] * e1[3] - e2[2] * e2[3];
	K[2][4] = -e1[2] * e1[4] - e2[2] * e2[4];

	K[3][0] = K[0][3];
	K[3][1] = K[1][3];
	K[3][2] = K[2][3];
	K[3][3] = 1.0 - e1[3] * e1[3] - e2[3] * e2[3];
	K[3][4] = -e1[3] * e1[4] - e2[3] * e2[4];

	K[4][0] = K[0][4];
	K[4][1] = K[1][4];
	K[4][2] = K[2][4];
	K[4][3] = K[3][4];
	K[4][4] = 1.0 - e1[4] * e1[4] - e2[4] * e2[4];

	// ���� b�� ���ϰ�,
	EgVec b = (p * e1) * e1 + (p * e2) * e2 - p;
	K[5][0] = K[0][5] = b[0];
	K[5][1] = K[1][5] = b[1];
	K[5][2] = K[2][5] = b[2];
	K[5][3] = K[3][5] = b[3];
	K[5][4] = K[4][5] = b[4];

	// ��� c�� ����Ѵ�.
	K[5][5] = p * p - SQR(p * e1) - SQR(p * e2);
}

/*!
*	\brief �޽� �������� ���ǵǴ� QEM ����� �ʱ�ȭ �Ѵ�.
*
*	\param NumVert �޽� ������ ����
*/
void EgDecimator::InitVertQEM_T(int NumVert)
{
	// QEM ����Ʈ�� �ʱ�ȭ �Ѵ�.
	m_QEM.clear();
	m_QEM.assign(NumVert, EgMat(6, 6));

	// ������ �ﰢ���� ���Ͽ�
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		// 5������ �� �� p, q, r �����Ѵ�.
		EgVertex *v0 = f->GetVertex(0);
		EgVertex *v1 = f->GetVertex(1);
		EgVertex *v2 = f->GetVertex(2);
		EgTexel *t0 = f->GetTexel(0);
		EgTexel *t1 = f->GetTexel(1);
		EgTexel *t2 = f->GetTexel(2);
		EgVec p(5, v0->m_Pos[0], v0->m_Pos[1], v0->m_Pos[2], t0->m_UV[0], t0->m_UV[1]);
		EgVec q(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
		EgVec r(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

		// �ؽ�ó ��ǥ�� ������ Quadric error ����� ���Ѵ�.
		EgMat K(6, 6);
		GetErrorMatrix_T(K, p, q, r);

		// �ﰢ���� �� ������ QEM�� �����Ѵ�.
		m_QEM[f->GetVertex(0)->m_Idx] += K;
		m_QEM[f->GetVertex(1)->m_Idx] += K;
		m_QEM[f->GetVertex(2)->m_Idx] += K;
	}
}

/*!
*	\brief �޽��� ������ ������ �����ϴ� ����� �ʱ�ȭ �Ѵ�.
*	\note ���� (vi, vk)�� (vk, vi)�� ������ ������ �Ǵ��Ͽ� ��ǥ ������ ���ؼ��� ����� ���Ѵ�.
*/
void EgDecimator::InitCollapseInfo_T()
{
	// ������ ������ ���Ͽ�
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// �������� �����ϴ� ������ ������ ���Ͽ�
		for (EgEdge *e : v->m_pEdges)
		{
			// ��ǥ ����(��� ���� �Ǵ� ���� �湮�� ����)���
			if (e->m_pMate == NULL || e->m_pMate->m_Cost == 0.0)
			{
				// ������ �糡 ������ �ؽ�ó ������ ���Ѵ�.
				EgVertex *v1 = v;
				EgVertex *v2 = EV(e);
				EgTexel *t1 = e->m_pTexel;
				EgTexel *t2 = e->m_pNext->m_pTexel;

				// ������ �糡��(position + texture coord)�� ���Ͽ�,
				EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
				EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

				// ���ο� ������ 6x6 QEM�� ���Ѵ�.
				EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

				// ���ο� ������ 5���� ���� (position + texture coord)�� ���Ѵ�.
				EgVec x(5), b(5), y(6);
				b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

				// 6x6 K ����� �κ���� A�� ���Ͽ� ���ο� ������ ����Ѵ�.
				EgMat A = sub(Q, 0, 0, 4, 4);

				// ���� ���� �ɼǿ� ���� ��ġ�� ����� ����Ѵ�.
				if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
				{
					y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
					double cost1 = y * (Q * y);
					y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? vt1 : vt2;
					e->m_Cost = MIN(cost1, cost2);
					//x = (vt1 + vt2) * 0.5;
					//normalize_uv(x[3], x[4]);
					//y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
					//e->m_Cost = y * (Q * y);
					//printf("Texture boundary cost = %3.10lf\n", e->m_Cost);
				}
				else if (m_CollapseType == COLLAPSE_OPT_POS)
				{
					if (EQ_ZERO(det(A), 1.0e-7))
					{
						x = (vt1 + vt2) * 0.5;
						normalize_uv(x[3], x[4]);
						y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
						e->m_Cost = y * (Q * y);
						//printf("Singular cost = %3.10lf\n", e->m_Cost);
					}
					else
					{
						x = inv(A) * (-b);
						normalize_uv(x[3], x[4]);
						e->m_Cost = x * b + Q[5][5];
					}
				}
				else if (m_CollapseType == COLLAPSE_MID_POS)
				{
					x = (vt1 + vt2) * 0.5;
					normalize_uv(x[3], x[4]);
					y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
					e->m_Cost = y * (Q * y);
				}
				else // COLLAPSE_END_POS
				{
					y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
					double cost1 = y * (Q * y);
					y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? vt1 : vt2;
					e->m_Cost = MIN(cost1, cost2);
				}

				// ��ǥ ���� ���� ������ ���� �߰��Ѵ�.
				EdgeCollapseInfo info(e, EgPos(x[0], x[1], x[2]), EgVec2(x[3], x[4]));
				m_Heap.push(info);
			}
		}
	}
}

/*!
*	\brief �ݺ������� ������ �����Ͽ� �޽� �ܼ�ȭ�� �����Ѵ�.
*
*	\prarm TarNumVert[in] ��ǥ ������ ����
*	\param FileName[out] ���ŵǴ� ���� ������ ����� ���ϸ�
*/
void EgDecimator::Decimate(int TarNumVert, const char *FileName)
{
	// ��ǥ ������ ������ ���� ������ ���� ���� ũ�ٸ� �����Ѵ�.
	int NumVert = m_pMesh->GetNumVert();
	if (TarNumVert >= NumVert)
		return;

	if (m_bTextureDecimate)
		printf("Start decimation with textures...\n");
	else
		printf("Start decimation w/o textures...\n");

	printf("\tMesh name = %s\n", m_pMesh->m_Name.c_str());
	printf("\tTarget number of vertices = %d\n", TarNumVert);
	clock_t st = clock();

	// ���ŵǴ� ������ ������ ����� ������ �����ϰ� �޽��� �̸��� ����Ѵ�.
	FILE *fp;
	if (FileName != NULL)
	{
		fopen_s(&fp, FileName, "a");
		fprintf_s(fp, "%s\n", m_pMesh->m_Name.c_str());
	}

	// �ݺ������� ������ �����Ͽ� �ﰢ���� ������ ���δ�.
	while (!m_Heap.empty())
	{
		// �ּ� ����� ���� ���� ������ �̾Ƽ�,
		EdgeCollapseInfo Info = m_Heap.top();
		m_Heap.pop();

		// �̹� ���ŵ� �����̰ų�, ���� ���� ����� ����Ǿ��ٸ� ��ŵ�Ѵ�.
		if (Info.m_pEdge->m_pFace->m_Idx == -1 || Info.m_pEdge->m_Cost != Info.m_Cost)
			continue;

		// ���õ� ������ �����ϰ�, �ﰢ�� ���� ���δ�.
		int sIdx, eIdx, result;
		if (m_bTextureDecimate)
			result = CollapseEdge_T(Info, sIdx, eIdx);
		else
			result = CollapseEdge(Info, sIdx, eIdx);
		if (result > 0)
		{
			// ������ ���� ���̰�
			NumVert -= result;

			// ���ŵǴ� ������ ���� �ε����� ����Ѵ�.
			if (FileName != NULL)
				fprintf_s(fp, "%d\t%d\n", sIdx, eIdx);
		}

		// �ﰢ���� ������ ���ϴ� ���� �����ߴٸ� �����Ѵ�.
		if (NumVert <= TarNumVert)
			break;
	}

	// ������ ����� �����Ѵ�.
	if (FileName != NULL)
	{
		fprintf_s(fp, "%d\t%d\n", -1, -1);
		fclose(fp);
	}

	// �޽��� �ﰢ�� ����Ʈ�� �����Ѵ�.
	UpdateFaceList();
	m_pMesh->UpdateNormal();

	// �ܼ�ȭ ������ ����Ѵ�.
	int NumRmvVert, NumRmvTex, NumRmvNormal;
	DeleteUnusedGeometry(NumRmvVert, NumRmvTex, NumRmvNormal);
	printf("\tElapsed time = %u ms\n", clock() - st);
	printf("\tNumber of vertices = %d\n", m_pMesh->GetNumVert());
	printf("\tNumber of texels = %d\n", m_pMesh->GetNumTexel());
	printf("\tNumber of normals = %d\n", m_pMesh->GetNumNormal());
	printf("\tNumber of faces = %d\n", m_pMesh->GetNumFace());
	printf("\tNumber of removed vertices = %d\n", NumRmvVert);
	printf("\tNumber of removed texels = %d\n", NumRmvTex);
	printf("\tNumber of removed normals = %d\n", NumRmvNormal);
	printf("Decimation completed...\n\n");

	// ��� ���ڿ� ������ ���۸� �ʱ�ȭ �Ѵ�.
	m_pMesh->UpdateBndBox();
	m_pMesh->m_VertexBuf.clear();
	m_pMesh->m_NormalBuf.clear();
	m_pMesh->m_TexelBuf.clear();
}

/*!
*	\brief ������ ������ ���� ���� ���Ÿ� �����Ѵ�.
*
*	\param fname ���� ������ ���� ������ ����� ����
*/
void EgDecimator::Decimate(const char *fname)
{
	printf("Start decimation from sequence file...\n");
	printf("\tMesh name = %s\n", m_pMesh->m_Name.c_str());
	clock_t st = clock();

	// ������ �б� ���� �����Ѵ�.
	FILE *fp;
	fopen_s(&fp, fname, "r");
	if (fp == NULL)
	{
		printf("File open failed...\n");
		return;
	}

	// ������ �����͸� �ش� �޽��� �̸��� ���ö����� �̵��Ѵ�.
	while (true)
	{
		char buffer[256];
		if (fscanf_s(fp, "%s", buffer, 256) == EOF)
		{
			fclose(fp);
			printf("\t%s decimation sequence does not exist...\n", m_pMesh->m_Name.c_str());
			return;
		}
		if (m_pMesh->m_Name == std::string(buffer))
			break;
	}

	// �޽� �ܼ�ȭ�� �����Ѵ�.
	int vidx1, vidx2;
	while (true)
	{
		// ���Ͽ��� ������ ������ �������� ������ �ε����� �д´�.
		fscanf_s(fp, "%d%d", &vidx1, &vidx2);
		if (vidx1 == -1 && vidx2 == -1)
			break;

		// ������ �������� ������ ���Ͽ�,
		EgVertex *v1 = m_pMesh->m_pVerts[vidx1];
		EgVertex *v2 = m_pMesh->m_pVerts[vidx2];

		// �ش� ������ ã�´�.
		EgEdge *pEdge = NULL;
		for (EgEdge *e : v1->m_pEdges)
		{
			if (EV(e) == v2)
			{
				pEdge = e;
				break;
			}
		}

		// �ؽ�ó�� �ܼ�ȭ �Ѵٸ�
		if (m_bTextureDecimate)
		{
			// ������ �糡 ������ �ؽ�ó ������ ���Ѵ�.
			EgTexel *t1 = pEdge->m_pTexel;
			EgTexel *t2 = pEdge->m_pNext->m_pTexel;

			// ������ �糡��(position + texture coord)�� ���Ͽ�,
			EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
			EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

			// ���ο� ������ QEM�� ���Ѵ�.
			EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

			// ���ο� ������ 5���� ���� (position + texture coord)�� ���Ѵ�.
			EgVec x(5), b(5);
			b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

			// 6x6 K ����� �κ���� A�� ���Ͽ� ���ο� ������ ����Ѵ�.
			EgMat A = sub(Q, 0, 0, 4, 4);

			// ���� ���� �ɼǿ� ���� ��ġ�� ����Ѵ�.
			switch (m_CollapseType)
			{
			case COLLAPSE_OPT_POS:
				if (EQ_ZERO(det(A), 1.0e-6))
				{
					x = (vt1 + vt2) * 0.5;
					x[3] = vt1[3];
					x[4] = vt1[4];
				}
				else
				{
					x = inv(A) * (-b);
				}
				break;

			case COLLAPSE_MID_POS:
				x = (vt1 + vt2) * 0.5;
				x[3] = vt1[3];
				x[4] = vt1[4];
				break;

			case COLLAPSE_END_POS:
				x = vt1;
				break;
			}

			// ������ ������ �ﰢ���� �����Ѵ�(������ ���´�).
			std::vector<EgFace *> DelFaces;
			DelFaces.push_back(pEdge->m_pFace);
			if (pEdge->m_pMate != NULL)
				DelFaces.push_back(pEdge->m_pMate->m_pFace);

			// ������ �ﰢ���� ���Ͽ�
			for (EgFace *f : DelFaces)
			{
				// �ﰢ�� ���� ������ ������ ���Ͽ�
				for (int i = 0; i < 3; ++i)
				{
					EgEdge *e = f->GetEdge(i);
					e->m_Cost = -1.0;
					// �ݴ��� ������ ������ �����ϰ�,
					if (e->m_pMate != NULL)
					{
						e->m_pMate->m_pMate = NULL;
						e->m_pMate = NULL;
					}

					// �������� �����ϴ� ���� ����Ʈ���� ���� ������ �����Ѵ�.
					e->m_pVert->DeleteEdge(e);
				}
			}

			// ������ ������(v1)�� ��ġ�� �����Ѵ�.
			v1->m_Pos.Set(x[0], x[1], x[2]);

			// ������ ���������� �����ϴ� ��� ������ �ؽ�ó ��ǥ�� �����Ѵ�.
			normalize_uv(x[3], x[4]);
			for (EgEdge *e : v1->m_pEdges)
				e->m_pTexel->m_UV = EgVec2(x[3], x[4]);

			// v2���� �����ϴ� ��� �������� �������� v1���� �����Ѵ�.
			for (EgEdge *e : v2->m_pEdges)
			{
				e->m_pVert = v1;
				e->m_pTexel = pEdge->m_pTexel;
				v1->m_pEdges.push_back(e);
			}

			// v2���� �����ϴ� ���� ������ �����ϰ�,
			v2->m_pEdges.clear();

			// v1���� �����ϴ� ������ mate ������ ������ �����Ѵ�.
			m_pMesh->UpdateEdgeMate(v1);

			// v1�� QEM ����� �����Ѵ�.
			m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];
		}
		else // ���������� �ܼ�ȭ �Ѵٸ�
		{
			// ���ο� ������ QEM�� ���Ѵ�.
			EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

			// ���ο� ������ ��ġ�� ���Ѵ�.
			EgVec x(3), b(3);
			b.Set(Q[0][3], Q[1][3], Q[2][3]);
			double det =
				(Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2]) -
				(Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

			// ���� ���� Ÿ�Կ� ���� ��ġ�� ����� ����Ѵ�.
			switch (m_CollapseType)
			{
			case COLLAPSE_OPT_POS:
				if (EQ_ZERO(det, 1.0e-6))
					x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				else
					x = Inv3(Q, det) * (-b);
				break;

			case COLLAPSE_MID_POS:
				x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				break;

			case COLLAPSE_END_POS:
				x = cast_vec(v1->m_Pos);
				break;
			}

			// ������ ������ �ﰢ���� �����Ѵ�(������ ���´�).
			std::vector<EgFace *> DelFaces;
			DelFaces.push_back(pEdge->m_pFace);
			if (pEdge->m_pMate != NULL)
				DelFaces.push_back(pEdge->m_pMate->m_pFace);

			// ������ �ﰢ���� ���Ͽ�
			for (EgFace *f : DelFaces)
			{
				// �ﰢ�� ���� ������ ������ ���Ͽ�
				for (int i = 0; i < 3; ++i)
				{
					EgEdge *e = f->GetEdge(i);
					e->m_Cost = -1.0;
					// �ݴ��� ������ ������ �����ϰ�,
					if (e->m_pMate != NULL)
					{
						e->m_pMate->m_pMate = NULL;
						e->m_pMate = NULL;
					}

					// �������� �����ϴ� ���� ����Ʈ���� ���� ������ �����Ѵ�.
					e->m_pVert->DeleteEdge(e);
				}
			}

			// v1�� ���� ����
			v1->m_Pos = cast_pos(x);

			// v2�� ���� ����
			for (EgEdge *e : v2->m_pEdges)
			{
				e->m_pVert = v1;
				v1->m_pEdges.push_back(e);
			}

			// v2���� �����ϴ� ���� ������ �����ϰ�,
			v2->m_pEdges.clear();

			// v1���� �����ϴ� ������ mate ������ ������ �����Ѵ�.
			m_pMesh->UpdateEdgeMate(v1);

			// v1�� QEM ����� �����Ѵ�.
			m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];
		}
	}

	// ���� �����͸� �ݴ´�.
	fclose(fp);

	// �޽��� �ﰢ�� ����Ʈ�� �����Ѵ�.
	UpdateFaceList();
	m_pMesh->UpdateNormal();

	// �ܼ�ȭ ������ ����Ѵ�.
	int NumRmvVert, NumRmvTex, NumRmvNormal;
	DeleteUnusedGeometry(NumRmvVert, NumRmvTex, NumRmvNormal);
	printf("\tElapsed time = %u ms\n", clock() - st);
	printf("\tNumber of vertices = %d\n", m_pMesh->GetNumVert());
	printf("\tNumber of texels = %d\n", m_pMesh->GetNumTexel());
	printf("\tNumber of normals = %d\n", m_pMesh->GetNumNormal());
	printf("\tNumber of faces = %d\n", m_pMesh->GetNumFace());
	printf("\tNumber of removed vertices = %d\n", NumRmvVert);
	printf("\tNumber of removed texels = %d\n", NumRmvTex);
	printf("\tNumber of removed normals = %d\n", NumRmvNormal);
	printf("Decimation completed...\n\n");

	// ��� ���ڿ� ������ ���۸� �ʱ�ȭ �Ѵ�.
	m_pMesh->UpdateBndBox();
	m_pMesh->m_VertexBuf.clear();
	m_pMesh->m_NormalBuf.clear();
	m_pMesh->m_TexelBuf.clear();
}

/*!
*	\brief ������ ���� �������� �˻��Ѵ�.
*
*	\param pEdge ���� ���� ���θ� ������ ������ ���� ������
*
*	\return ������ ���Ű����� ��� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool EgDecimator::IsCollapsible_T(EgEdge *pEdge)
{
	// ������ ������(v1)�� ����(v2)�� ���Ѵ�.
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// ���� ������ ��� ������ ���Եȴٸ� false�� ��ȯ�Ѵ�.
	if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
		return false;

	// v1�� v2�� 1�� ������ ���� A�� B�� ���Ѵ�.
	std::vector<EgVertex *> A, B;
	v1->GetOneRingVert(A);
	v2->GetOneRingVert(B);

	// A�� B�� �������� ���Ѵ�.
	std::vector<EgVertex *> C;
	for (EgVertex *a : A)
	{
		for (EgVertex *b : B)
		{
			if (a == b)
			{
				C.push_back(a);
				break;
			}
		}
	}

	// ���� ������ ������ ������ ��� true�� ��ȯ�Ѵ�.
	if (pEdge->m_pMate == NULL && C.size() == 1)
		return true;
	if (pEdge->m_pMate != NULL && C.size() == 2)
		return true;

	// ���� ���� ������ �������� ���ϴ� ��� false�� ��ȯ�Ѵ�.
	return false;
}

/*!
*	\brief �޽��� ���� ������ ������ �����Ѵ�.
*
*	\param info ������ ������ ����
*	\param sIdx ������ ������ �������� �ε����� �����
*	\param eIdx ������ ������ ������ ���ؽ��� �����
*
*	\return ���ŵ� ������ ������ ��ȯ�Ѵ�(0: ���� �Ұ���, 1: ���� ����)
*/
int EgDecimator::CollapseEdge_T(EdgeCollapseInfo &info, int &sIdx, int &eIdx)
{
	// ���Ű� �Ұ����� ������� 0�� ��ȯ�Ѵ�.
	if (IsCollapsible_T(info.m_pEdge) == false)
		return 0;

	// ������ ����, �ﰢ��, ������ �����͸� ���ϰ�,	
	EgEdge *pEdge = info.m_pEdge;
	EgEdge *pMateEdge = pEdge->m_pMate;
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// ����(����Ʈ ����)�� ������ �ﰢ���� ���� ������ ����Ѵ�.
	DeleteIncidentFaces(pEdge);

	// v1�� ��ġ �����ϰ�
	v1->m_Pos = info.m_Pos;

	// ���� ������ �ؽ�ó�� �����ϴ� �������� �ؽ�ó ��ǥ�� �����Ѵ�.
	pEdge->m_pTexel->m_UV = info.m_UV;

	// v2���� �����ϴ� ������ ������ ���Ͽ�
	for (EgEdge *e : v2->m_pEdges)
	{
		// �������� v1���� �����ϰ� 
		e->m_pVert = v1;

		// ���� ������ ������ �ؽ�ó ������ �����ϴ� �������� ��ǥ�� �����Ѵ�.
		if (e->m_pTexel == pEdge->m_pNext->m_pTexel)
			e->m_pTexel = pEdge->m_pTexel;

		// v1�� ���� ������ �߰��Ѵ�.
		v1->m_pEdges.push_back(e);
	}

	// v2���� �����ϴ� ���� ������ �����ϰ�,
	v2->m_pEdges.clear();

	// v1���� �����ϴ� ������ mate ������ ������ �����Ѵ�.
	m_pMesh->UpdateEdgeMate(v1);

	// v1�� QEM ����� �����Ѵ�.
	m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];

	// ���ŵǴ� ������ �������� ������ �ε����� �����Ѵ�.
	sIdx = v1->m_Idx;
	eIdx = v2->m_Idx;

	// v1�� ������ �ﰢ���� ��� ���� ����� �����Ѵ�.
	UpdateCollapseInfo_T(v1);

	// ���ŵ� ������ ������ ��ȯ�Ѵ�.
	return 1;
}

/*!
*	\brief ������ ������ ������ ���� ����� �����Ѵ�.
*
*	\param v ������ ���� ������
*/
void EgDecimator::UpdateCollapseInfo_T(EgVertex *v)
{
	// ���� v���� �����ϴ� ������ ������ ���Ͽ�
	for (EgEdge *e : v->m_pEdges)
	{
		// e�� mate ������ ��ǥ �������ٸ�, e�� ��ǥ ������ �����Ѵ�.
		if (e->m_pMate != NULL && e->m_pMate->m_Cost != 0.0)
			e->m_pMate->m_Cost = 0.0;

		// ��ǥ ������ �糡���� ���ϰ�,
		EgVertex *v1 = SV(e);
		EgVertex *v2 = EV(e);
		EgTexel *t1 = e->m_pTexel;
		EgTexel *t2 = e->m_pNext->m_pTexel;

		// ������ �糡��(position + texture coord)�� ���Ͽ�,
		EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
		EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

		// ���ο� ������ 6x6 QEM�� ���Ѵ�.
		EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

		// ���ο� ������ 5���� ���� (position + texture coord)�� ���Ѵ�.
		EgVec x(5), b(5), y(6);
		b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

		// 6x6 K ����� �κ���� A�� ���Ͽ� ���ο� ������ ����Ѵ�.
		EgMat A = sub(Q, 0, 0, 4, 4);

		// ���� ���� �ɼǿ� ���� ��ġ�� ����� ����Ѵ�.
		if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
		{
			y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
			double cost1 = y * (Q * y);
			y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? vt1 : vt2;
			e->m_Cost = MIN(cost1, cost2);
			//x = (vt1 + vt2) * 0.5;
			//normalize_uv(x[3], x[4]);
			//y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
			//e->m_Cost = y * (Q * y);
			//printf("Updated texture boundary cost = %3.10lf\n", e->m_Cost);
		}
		else if (m_CollapseType == COLLAPSE_OPT_POS)
		{
			if (EQ_ZERO(det(A), 1.0e-7))
			{
				x = (vt1 + vt2) * 0.5;
				normalize_uv(x[3], x[4]);
				y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
				e->m_Cost = y * (Q * y);
				//printf("Singular cost = %3.10lf\n", e->m_Cost);
			}
			else
			{
				x = inv(A) * (-b);
				normalize_uv(x[3], x[4]);
				e->m_Cost = x * b + Q[5][5];
			}
		}
		else if (m_CollapseType == COLLAPSE_MID_POS)
		{
			x = (vt1 + vt2) * 0.5;
			normalize_uv(x[3], x[4]);
			y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
			e->m_Cost = y * (Q * y);
		}
		else // COLLAPSE_END_POS
		{
			y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
			double cost1 = y * (Q * y);
			y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? vt1 : vt2;
			e->m_Cost = MIN(cost1, cost2);
		}

		// ��ǥ ���� ���� ������ ���� �߰��Ѵ�.
		EdgeCollapseInfo info(e, cast_pos(x), EgVec2(x[3], x[4]));
		m_Heap.push(info);
	}
}

/*!
*	\brief ��� ax + by + cz + d = 0���� �� p���� �Ÿ��� ������ ����ϴ� ����� ���Ѵ�.
*
*	\param K ���� ����� ����ȴ�.
*	\param a ����� �������� ���
*	\param b ����� �������� ���
*	\param c ����� �������� ���
*	\param d ����� �������� ���
*/
void EgDecimator::GetErrorMatrix(EgMat &K, double a, double b, double c, double d)
{
	K[0][0] = a * a;
	K[0][1] = a * b;
	K[0][2] = a * c;
	K[0][3] = a * d;

	K[1][0] = K[0][1];	// ��Ī��
	K[1][1] = b * b;
	K[1][2] = b * c;
	K[1][3] = b * d;

	K[2][0] = K[0][2];	// ��Ī��
	K[2][1] = K[1][2];	// ��Ī��
	K[2][2] = c * c;
	K[2][3] = c * d;

	K[3][0] = K[0][3];	// ��Ī��
	K[3][1] = K[1][3];	// ��Ī��
	K[3][2] = K[2][3];	// ��Ī��
	K[3][3] = d * d;
}

/*
*	\brief 3�� 3���� ��Ī ��� A�� ������� ��ȯ�Ѵ�.
*
*	\param A ��� ���
*	\param det ��� A�� ��Ľ�
*
*	\return ��� A�� ������� ��ȯ�Ѵ�.
*/
EgMat EgDecimator::Inv3(EgMat &A, double det)
{
	EgMat ret(3, 3);
	ret[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / det;
	ret[0][1] = -(A[0][1] * A[2][2] - A[0][2] * A[2][1]) / det;
	ret[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / det;

	ret[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / det;
	ret[1][2] = -(A[0][0] * A[1][2] - A[0][2] * A[1][0]) / det;

	ret[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / det;

	ret[1][0] = ret[0][1];
	ret[2][0] = ret[0][2];
	ret[2][1] = ret[1][2];

	return ret;
}

/*!
*	\brief �޽� �������� ���ǵǴ� QEM ����� �ʱ�ȭ �Ѵ�.
*
*	\param NumVert �޽� ������ ����
*/
void EgDecimator::InitVertQEM(int NumVert)
{
	// QEM ����Ʈ�� �ʱ�ȭ �Ѵ�.
	m_QEM.clear();
	m_QEM.assign(NumVert, EgMat(4, 4));

	// ������ �ﰢ���� ���Ͽ�
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		// �ﰢ���� ������ ����� ������ (ax + by + cz + d = 0)�� ���Ͽ�
		EgVec3 n = f->GetFaceNormal(false); // n = (a, b, c)
		double d = -n * cast_vec3(f->GetVertex(0)->m_Pos);

		// �ﰢ�� f�� ���� fundamental error quadric ����� ���ϰ�
		EgMat K(4, 4);
		GetErrorMatrix(K, n[0], n[1], n[2], d);

		// �ﰢ���� �� ������ K�� �����Ѵ�.
		m_QEM[f->GetVertex(0)->m_Idx] += K;
		m_QEM[f->GetVertex(1)->m_Idx] += K;
		m_QEM[f->GetVertex(2)->m_Idx] += K;

		// �ﰢ���� ������ ������ ���Ͽ�
		for (int i = 0; i < 3; ++i)
		{
			// ��� �������,
			if (f->GetEdge(i)->IsBndry())
			{
				// ������ ������ �ﰢ���� ������ ����� ���ϰ�, 
				EgEdge *e = f->GetEdge(i);
				EgVec3 ei = (EV(e)->m_Pos - SV(e)->m_Pos).Normalize();
				EgVec3 ni = (n ^ ei).Normalize();
				double di = -ni * cast_vec3(e->m_pVert->m_Pos);

				// ������� ���ǵǴ� quadric error ����� ���Ѵ�.
				EgMat Ki(4, 4);
				GetErrorMatrix(Ki, ni[0], ni[1], ni[2], di);

				// ������ �糡���� ���Ѵ�.
				Ki *= 100.0;
				m_QEM[e->m_pVert->m_Idx] += Ki;
			}
		}
	}
}

/*!
*	\brief ������ ������ �����ϴ� �ʱ� ����� ����Ѵ�.
*	\note ���� (vi, vk)�� (vk, vi)�� ������ ������ �����Ͽ� ��ǥ ������ ���ؼ��� ����� ���Ѵ�.
*/
void EgDecimator::InitCollapseInfo()
{
	// ������ ������ ���Ͽ�
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// �������� �����ϴ� ������ ������ ���Ͽ�
		for (EgEdge *e : v->m_pEdges)
		{
			// ��ǥ ����(��迡�� �Ǵ� ���� �湮 ����)���
			if (e->IsBndry() || e->m_pMate->m_Cost == 0.0)
			{
				// ������ �糡���� ���Ͽ�,
				EgVertex *v1 = v;
				EgVertex *v2 = EV(e);

				// ���ο� ������ QEM�� ���Ѵ�.
				EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

				// ���ο� ������ ��ġ�� ���Ѵ�.
				EgVec x(3), b(3), y(4);
				b.Set(Q[0][3], Q[1][3], Q[2][3]);
				double det = (Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2])
					- (Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

				// ���� ���� Ÿ�Կ� ���� ��ġ�� ����� ����Ѵ�.
				if (m_CollapseType == COLLAPSE_OPT_POS)
				{
					if (EQ_ZERO(det, 1.0e-6))
					{
						x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
						y.Set(x[0], x[1], x[2], 1.0);
						e->m_Cost = y * (Q * y);
						//printf("Singular cost = %5.10lf\n", e->m_Cost);
					}
					else
					{
						x = Inv3(Q, det) * (-b);
						e->m_Cost = x * b + Q[3][3];
					}
				}
				else if (m_CollapseType == COLLAPSE_MID_POS)
				{
					x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
					y.Set(x[0], x[1], x[2], 1.0);
					e->m_Cost = y * (Q * y);
				}
				else // COLLAPSE_END_POS
				{
					y.Set(v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], 1.0);
					double cost1 = y * (Q * y);
					y.Set(v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? cast_vec(v1->m_Pos) : cast_vec(v2->m_Pos);
					e->m_Cost = MIN(cost1, cost2);
				}

				// ��ǥ ������ ���� ������ ���� �߰��Ѵ�.				
				EdgeCollapseInfo info(e, cast_pos(x));
				m_Heap.push(info);
			}
		}
	}
}

/*!
*	\brief ������ ���� �������� �˻��Ѵ�.
*
*	\param pEdge ���� ���� ���θ� ������ ������ ���� ������
*
*	\return ������ ���Ű����� ��� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool EgDecimator::IsCollapsible(EgEdge *pEdge)
{
	// ������ ������(v1)�� ����(v2)�� ���Ѵ�.
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// v1�� v2�� 1�� ������ ���� A�� B�� ���Ѵ�.
	std::vector<EgVertex *> A, B;
	v1->GetOneRingVert(A);
	v2->GetOneRingVert(B);

	// A�� B�� �������� ���Ѵ�.
	std::vector<EgVertex *> C;
	for (EgVertex *a : A)
	{
		for (EgVertex *b : B)
		{
			if (a == b)
			{
				C.push_back(a);
				break;
			}
		}
	}

	// ���� ������ ������ ������ ��� true�� ��ȯ�Ѵ�.
	if (pEdge->m_pMate == NULL && C.size() == 1)
		return true;
	if (pEdge->m_pMate != NULL && C.size() == 2)
		return true;

	// ���� ���� ������ �������� ���ϴ� ��� false�� ��ȯ�Ѵ�.
	return false;
}

/*!
*	\brief �޽��� ���� ������ ������ �����Ѵ�.
*
*	\param info ������ ������ ����
*	\param sIdx ������ ������ �������� �ε����� �����
*	\param eIdx ������ ������ ������ ���ؽ��� �����
*
*	\return ���ŵ� ������ ������ ��ȯ�Ѵ�(0: ���� �Ұ���, 1: ���� ����)
*/
int EgDecimator::CollapseEdge(EdgeCollapseInfo &info, int &sIdx, int &eIdx)
{
	// ���Ű� �Ұ����� ������� 0�� ��ȯ�Ѵ�.
	if (IsCollapsible(info.m_pEdge) == false)
		return 0;

	// ������ ������ ������ �����͸� ���ϰ�
	EgEdge *pEdge = info.m_pEdge;
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// ����(����Ʈ ����)�� ������ �ﰢ���� ���� ������ ����Ѵ�.
	DeleteIncidentFaces(pEdge);
	
	// v1�� ��ġ ������ �����ϰ�
	v1->m_Pos = info.m_Pos;

	// v2���� �����ϴ� ������ ������ ���Ͽ�
	for (EgEdge *e : v2->m_pEdges)
	{
		// �������� v1���� �����ϰ� v1�� ���ۿ����� �߰��Ѵ�.
		e->m_pVert = v1;
		v1->m_pEdges.push_back(e);
	}

	// v2���� �����ϴ� ���� ������ �����ϰ�,
	v2->m_pEdges.clear();

	// v1���� �����ϴ� ������ mate ������ ������ �����Ѵ�.
	m_pMesh->UpdateEdgeMate(v1);

	// v1�� QEM ����� �����Ѵ�.
	m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];

	// ���ŵǴ� ������ �������� ������ �ε����� �����Ѵ�.
	sIdx = v1->m_Idx;
	eIdx = v2->m_Idx;

	// v1�� ������ �ﰢ���� ��� ���� ����� �����Ѵ�.
	UpdateCollapseInfo(v1);

	// ���ŵ� ������ ������ ��ȯ�Ѵ�.
	return 1;
}

/*!
*	\brief ������ ������ ������ ���� ����� �����Ѵ�.
*
*	\param v ������ ���� ������
*/
void EgDecimator::UpdateCollapseInfo(EgVertex *v)
{
	// ���� v���� �����ϴ� ������ ������ ���Ͽ�
	for (EgEdge *e : v->m_pEdges)
	{
		// e�� mate ������ ��ǥ �������ٸ�, e�� ��ǥ ������ �����Ѵ�.
		if (e->m_pMate != NULL && e->m_pMate->m_Cost != 0.0)
			e->m_pMate->m_Cost = 0.0;

		// ��ǥ ������ �糡���� ���ϰ�,
		EgVertex *v1 = SV(e);
		EgVertex *v2 = EV(e);

		// ���ο����� QEM ����� ���Ͽ�,
		EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];
		EgVec x(3), b(3), y(4);
		b.Set(Q[0][3], Q[1][3], Q[2][3]);

		// ���ο� ��ġ�� ���ϰ�,
		double det =
			(Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2]) -
			(Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

		// ���� ���� Ÿ�Կ� ���� ��ġ�� ����� ����Ѵ�.
		if (m_CollapseType == COLLAPSE_OPT_POS)
		{
			if (EQ_ZERO(det, 1.0e-6))
			{
				x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				y.Set(x[0], x[1], x[2], 1.0);
				e->m_Cost = y * (Q * y);
			}
			else
			{
				x = Inv3(Q, det) * (-b);
				e->m_Cost = x * b + Q[3][3];
			}
		}
		else if (m_CollapseType == COLLAPSE_MID_POS)
		{
			x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
			y.Set(x[0], x[1], x[2], 1.0);
			e->m_Cost = y * (Q * y);
		}
		else // COLLAPSE_END_POS
		{
			y.Set(v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], 1.0);
			double cost1 = y * (Q * y);
			y.Set(v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? cast_vec(v1->m_Pos) : cast_vec(v2->m_Pos);
			e->m_Cost = MIN(cost1, cost2);
		}

		// ��ǥ ���� ���� ������ ���� �߰��Ѵ�.
		EdgeCollapseInfo info(e, cast_pos(x));
		m_Heap.push(info);
	}
}

/*!
*	\brief	����(����Ʈ ����)�� ������ �ﰢ���� ���� ������ ����Ѵ�.
*	\note	������ ���ŵ����� �ʰ�, UpdateFaceList() ��ϵ� ������ �̿��Ͽ� �ϰ� �����Ѵ�.
*
*	\param e ������ ���� ������
*/
void EgDecimator::DeleteIncidentFaces(EgEdge *e)
{
	// ������ �ﰢ���� ���Ͽ�,
	std::vector<EgFace *> Faces;
	e->GetIncidentFace(Faces);

	// ������ �ﰢ���� ���Ͽ�,
	for (EgFace *f : Faces)
	{
		for (int i = 0; i < 3; ++i)
		{
			// ������ ������ ���Ͽ�
			EgEdge *e = f->GetEdge(i);

			// ��� ������ �ƴ϶�� �ݴ��� ������ ������ �����ϰ�,
			if (!e->IsBndry())
			{
				e->m_pMate->m_pMate = NULL;
				e->m_pMate = NULL;
			}

			// ���� ������ ���� ���տ��� ���� ������ �����Ѵ�.
			e->m_pVert->DeleteEdge(e);
		}
		// ������ �ﰢ������ ����Ѵ�.
		f->m_Idx = -1;
	}
}

/*!
*	\brief ���� �ر� �Ŀ� ������ �ʴ� ����, �ؼ�, ������ �����Ѵ�
*
*	\param	num_vert ���ŵ� ������ ���� �����
*	\param	num_tex ���ŵ� �ؼ��� ���� �����
*	\param	num_normal ���ŵ� ������ ���� �����
*/
void EgDecimator::DeleteUnusedGeometry(int &num_vert, int &num_tex, int &num_normal)
{
	num_vert = 0;
	num_tex = 0;
	num_normal = 0;

	// ������� �ʴ� ������ �����Ѵ�.
	if (!m_pMesh->m_pVerts.empty())
	{
		// ��� ������ �ε����� -1�� �ʱ�ȭ �Ѵ�.
		for (EgVertex *v : m_pMesh->m_pVerts)
			v->m_Idx = -1;

		// ������ �ﰢ������
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// ������ ����ϴ� ������ �ε����� 1�� ǥ���Ѵ�.
			for (int i = 0; i < 3; ++i)
				f->GetVertex(i)->m_Idx = 1;
		}

		// ���Ǵ� �������� ������ ���ο� ����Ʈ�� �����ϰ�,
		std::vector<EgVertex *> NewVerts;

		// ������ ������ ���Ͽ�
		for (EgVertex *v : m_pMesh->m_pVerts)
		{
			if (v->m_Idx == 1) // ���� �����̶�� ����Ʈ�� �߰��ϰ�,
			{
				v->m_Idx = (int)NewVerts.size();
				NewVerts.push_back(v);
			}
			else // ������ ���� �����̶�� �����Ѵ�.
			{
				num_vert++;
				delete v;
			}
		}

		// ������ ����Ʈ�� ������Ʈ �Ѵ�.
		m_pMesh->m_pVerts = NewVerts;
	}
		
	// ������� �ʴ� �ؼ��� �����Ѵ�
	if (!m_pMesh->m_pTexels.empty())
	{
		// ��� �ؼ��� �ε����� -1�� �ʱ�ȭ�Ѵ�.
		for (EgTexel *t : m_pMesh->m_pTexels)
			t->m_Idx = -1;

		// ������ �ﰢ������
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// ������ ����ϴ� �ؼ��� �ε����� 1�� ǥ���Ѵ�.
			for (int i = 0; i < 3; ++i)
				f->GetTexel(i)->m_Idx = 1;
		}

		// ���Ǵ� �ؼ��� ������ ���ο� ����Ʈ�� �����ϰ�,
		std::vector<EgTexel *> NewTexels;

		// ������ �ؼ��� ���Ͽ�
		for (EgTexel *t : m_pMesh->m_pTexels)
		{
			if (t->m_Idx == 1) // ���� �ؼ��̶�� ����Ʈ�� �߰��ϰ�,
			{
				t->m_Idx = (int)NewTexels.size();
				NewTexels.push_back(t);
			}
			else // ������ �ʴ� �ؼ��̶�� �����Ѵ�.
			{
				num_tex++;
				delete t;
			}
		}

		// �ؼ��� ����Ʈ�� ������Ʈ �Ѵ�.
		m_pMesh->m_pTexels = NewTexels;
	}

	// ������� �ʴ� ������ �����Ѵ�.
	if (!m_pMesh->m_pNormals.empty())
	{
		// ��� ������ �ε����� -1�� �ʱ�ȭ �Ѵ�.
		for (EgNormal *n : m_pMesh->m_pNormals)
			n->m_Idx = -1;

		// ������ �ﰢ������
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// ������ ����ϴ� ������ �ε����� 1�� ǥ���Ѵ�.
			for (int i = 0; i < 3; ++i)
				f->GetNormal(i)->m_Idx = 1;
		}

		// ���Ǵ� �������� ������ ���ο� ����Ʈ�� �����ϰ�,
		std::vector<EgNormal *> NewNormals;

		// ������ ������ ���Ͽ�
		for (EgNormal *n : m_pMesh->m_pNormals)
		{
			if (n->m_Idx == 1) // ���� �����̶�� ����Ʈ�� �߰��ϰ�,
			{
				n->m_Idx = (int)NewNormals.size();
				NewNormals.push_back(n);
			}
			else // ������ ���� �����̶�� �����Ѵ�.
			{
				num_normal++;
				delete n;
			}
		}

		// ������ ����Ʈ�� ������Ʈ �Ѵ�.
		m_pMesh->m_pNormals = NewNormals;
	}
}

/*!
*	\brief �ܼ�ȭ ��, �޽��� �ﰢ�� ����Ʈ�� �����Ѵ�.
*/
void EgDecimator::UpdateFaceList()
{
	// ���� �ﰢ������ ������ �ﰢ���� ����Ʈ�� �籸���Ѵ�.
	std::vector<EgFace *> NewFaces;
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		if (f->m_Idx != -1)
		{
			f->m_Idx = (int)NewFaces.size();
			NewFaces.push_back(f);
		}
		else
			delete f;
	}
	m_pMesh->m_pFaces = NewFaces;
}
