#include "stdafx.h"
#include "EgForm.h"
#include "IconsMaterialDesign.h"
#include "ImGui/imgui.h"

#define FILE_NONE 1000
#define FILE_NEW_SCENE 1001
#define FILE_IMPORT_MESH 1002
#define FILE_EXPORT_MESH 1003
#define FILE_IMPORT_CAMERA 1004
#define FILE_EXPORT_CAMERA 1005

void CreateMenuFile()
{
    static int SltMenuId = FILE_NONE;
    static std::string filePathName = "";
    static std::string path = "C:\\Users\\SHYUN\\Dropbox\\EgProject\\3DModels\\";
    static std::string fileName = "";
    static std::string filter = "";

    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::BeginMenu("File")) {

        // ����� �ʱ�ȭ �Ѵ�.
        if (ImGui::MenuItem("New File")) {
            SltMenuId = FILE_NEW_SCENE;
        }
        ImGui::Separator();

        // �޽��� �ҷ����� �����Ѵ�.
        if (ImGui::MenuItem("Open File..."))
            SltMenuId = FILE_IMPORT_MESH;
        if (ImGui::MenuItem("Save File..."))
            SltMenuId = FILE_EXPORT_MESH;
        ImGui::Separator();

        // ī�޶� ��ġ�� ������ �ҷ����� �����Ѵ�.
        if (ImGui::MenuItem("Open Camera..."))
            SltMenuId = FILE_IMPORT_CAMERA;
        if (ImGui::MenuItem("Save Camera..."))
            SltMenuId = FILE_EXPORT_CAMERA;
        ImGui::Separator();

        // ���α׷��� �����Ѵ�.
        if (ImGui::MenuItem("Exit"))
        {
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplGLUT_Shutdown();
            ImGui::DestroyContext();
            exit(-1);
        }ImGui::EndMenu();
    }

    ImGui::Columns(2);
    ImGui::SetColumnOffset(1, 90);
    //if (ImGui::BeginMenu("File"))

       // ����� �ʱ�ȭ �Ѵ�.
    if (ImGui::Button(ICON_MD_CONTENT_COPY, ImVec2(75, 50))) {
        SltMenuId = FILE_NEW_SCENE;

    }
    ImGui::Spacing();

    if (ImGui::Button(ICON_MD_FOLDER_OPEN, ImVec2(75, 50))) {
        SltMenuId = FILE_IMPORT_MESH;
    }
    ImGui::Spacing();

    // �޽��� �����Ѵ�. 
    if (ImGui::Button(ICON_MD_SAVE, ImVec2(75, 50))) {
        SltMenuId = FILE_EXPORT_MESH;

    }
    ImGui::Spacing();

    // ī�޶� ��ġ�� ������ �ҷ����� �����Ѵ�.
    if (ImGui::Button(ICON_MD_ADD_A_PHOTO, ImVec2(75, 50))) {
        SltMenuId = FILE_IMPORT_CAMERA;
    }
    ImGui::Spacing();

    if (ImGui::Button(ICON_MD_PHOTO_CAMERA, ImVec2(75, 50))) {
        SltMenuId = FILE_EXPORT_CAMERA;

    }
    ImGui::Spacing();


    //���α׷��� �����Ѵ�.
    if (ImGui::Button(ICON_MD_EXIT_TO_APP, ImVec2(75, 50)))
    {
        ImGui::SetTooltip("Exit program");
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplGLUT_Shutdown();
        ImGui::DestroyContext();
        exit(-1);
    }

    ImGui::NextColumn();
    {
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "*How to Manipulate");

        // Zoom In/Out in GUI
        ImGui::Separator();
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "1. Zoom In/Out => Use Mousewheel");

        // Translate in GUI => shift s
        ImGui::Separator();
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "2. Translate => Alt + Click Mousewheel");

        // Mesh Rotation => alt + drag
        ImGui::Separator();
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "3. Mesh Rotation => Alt + Mouse Left Drag");

        // Sculpting => drag
        ImGui::Separator();
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "4. Sculpting => Select->Sculpt->Mouse Drag");

        // Liquify => shift + t
        ImGui::Separator();
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "5. Mesh Deformation");
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "=> Select -> Select Entitiy -> Vertices -> Shift + T");
        ImGui::Separator();

        // 3D Liguify => S + Drag (select) / D + Drag (liquify)
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "6. Liquify");
        ImGui::TextColored({ 0.0f,1.0f,1.0f,1.0f }, "=> S + Drag (select) / D + Drag (liquify)");

    }

    // ����� �ʱ�ȭ �Ѵ�.
    if (SltMenuId == FILE_NEW_SCENE)
    {
        InitScene(NULL);
        SltMenuId = FILE_NONE;
    }

    // �޽� �ҷ����� 
    if (SltMenuId == FILE_IMPORT_MESH)
    {
        if (theFileDialog.FileDialog("Open File", ".obj\0.stl\0.off\0", path, ""))
        {
            if (theFileDialog.IsOk == true)
            {
                filePathName = theFileDialog.GetFilepathName();
                path = theFileDialog.GetCurrentPath();
                fileName = theFileDialog.GetCurrentFileName();
                filter = theFileDialog.GetCurrentFilter();

                // ������ �ҷ��´�.
                InitScene((char*)filePathName.c_str());
                EgMesh* pMesh = theScene.FindLastMesh();
                if (pMesh != NULL)
                {
                    theSelector.SelectMesh(pMesh->m_Name);
                    theScene.AdjustViewFrustum(pMesh->m_BndBox);
                }
                SltMenuId = FILE_NONE;
            }
            else
            {
                filePathName = "";
                fileName = "";
                filter = "";
                SltMenuId = FILE_NONE;
            }
        }
    }

    // �޽� �����ϱ�
    if (SltMenuId == FILE_EXPORT_MESH)
    {
        if (theFileDialog.FileDialog("Save File", ".obj\0.off\0.txt\0", path, ""))
        {
            if (theFileDialog.IsOk == true)
            {
                // ������ �����Ѵ�.
                EgMesh* pMesh = theSelector.GetSltMesh();
                filePathName = theFileDialog.GetFilepathName();
                path = theFileDialog.GetCurrentPath();
                fileName = theFileDialog.GetCurrentFileName();
                filter = theFileDialog.GetCurrentFilter();

                if (filter == ".obj")
                {
                    if (::get_file_ext(filePathName) != "obj")
                        filePathName += ".obj";
                    ::export_obj(pMesh, (char*)filePathName.c_str());
                }
                if (filter == ".txt")
                {
                    if (::get_file_ext(filePathName) != "txt")
                        filePathName += ".txt";
                    ::export_txt(pMesh, (char*)filePathName.c_str());
                }
                if (filter == ".off")
                {
                    if (::get_file_ext(filePathName) != "off")
                        filePathName += ".off";
                    ::export_off(pMesh, (char*)filePathName.c_str());
                }
                SltMenuId = FILE_NONE;
            }
            else
            {
                filePathName = "";
                fileName = "";
                filter = "";
                SltMenuId = FILE_NONE;
            }
        }
    }

    // ī�޶� �ҷ�����
    if (SltMenuId == FILE_IMPORT_CAMERA)
    {
        if (theFileDialog.FileDialog("Open Camera", ".cam\0", path, ""))
        {
            if (theFileDialog.IsOk == true)
            {
                // ī�޶� ������ �ҷ��´�.
                filePathName = theFileDialog.GetFilepathName();
                path = theFileDialog.GetCurrentPath();
                fileName = theFileDialog.GetCurrentFileName();
                filter = theFileDialog.GetCurrentFilter();
                theScene.m_MainCamera.Import((char*)filePathName.c_str());
                SltMenuId = FILE_NONE;
            }
            else
            {
                filePathName = "";
                fileName = "";
                filter = "";
                SltMenuId = FILE_NONE;
            }
        }
    }

    // ī�޶� �����ϱ�
    if (SltMenuId == FILE_EXPORT_CAMERA)
    {
        if (theFileDialog.FileDialog("Save Camera", ".cam\0", path, ""))
        {
            if (theFileDialog.IsOk == true)
            {
                // ī�޶� ������ �����Ѵ�.
                filePathName = theFileDialog.GetFilepathName();
                path = theFileDialog.GetCurrentPath();
                fileName = theFileDialog.GetCurrentFileName();
                filter = theFileDialog.GetCurrentFilter();
                if (::get_file_ext(filePathName) != "cam")
                    filePathName += ".cam";
                theScene.m_MainCamera.Export((char*)filePathName.c_str());
                SltMenuId = FILE_NONE;
            }
            else
            {
                filePathName = "";
                fileName = "";
                filter = "";
                SltMenuId = FILE_NONE;
            }
        }
    }
}