#include "Editor.h"


void Lomus::Editor::initStlyle(EditorStyle editorStyle) {
// Visual Studio style by MomoDeve from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    auto& imGuiIO{ ImGui::GetIO() };
    imGuiIO.IniFilename = NULL;
    imGuiIO.LogFilename = NULL;
    switch (editorStyle) {
        case Clean:
            style.Alpha = 1.0f;
            style.DisabledAlpha = 0.6000000238418579f;
            style.WindowPadding = ImVec2(8.0f, 8.0f);
            style.WindowRounding = 0.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = ImVec2(32.0f, 32.0f);
            style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
            style.WindowMenuButtonPosition = ImGuiDir_Left;
            style.ChildRounding = 0.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 0.0f;
            style.PopupBorderSize = 1.0f;
            style.FramePadding = ImVec2(4.0f, 3.0f);
            style.FrameRounding = 0.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = ImVec2(8.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
            style.CellPadding = ImVec2(4.0f, 2.0f);
            style.IndentSpacing = 21.0f;
            style.ColumnsMinSpacing = 6.0f;
            style.ScrollbarSize = 14.0f;
            style.ScrollbarRounding = 0.0f;
            style.GrabMinSize = 10.0f;
            style.GrabRounding = 0.0f;
            style.TabRounding = 0.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.0f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1400980454683304f, 0.1400980454683304f, 0.1400196138620377f, 1.0f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.104f, 1.0f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1350980454683304f, 0.1350980454683304f, 0.1390196138620377f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
            style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
            style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
            style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
            style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
            break;
        case Unreal:

            colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
            colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
            colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
            colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
            colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
            colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
            colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
            colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
            colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
            colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
            colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
            colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
            colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
            colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
            colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
            colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
            colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
            colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
            colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
            colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
            colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
            colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
            colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
            colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
            colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
            colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
            colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
            colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
            colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
            colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
            colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
            colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
            colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
            colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

            style.WindowPadding                     = ImVec2(8.00f, 8.00f);
            style.FramePadding                      = ImVec2(5.00f, 2.00f);
            style.CellPadding                       = ImVec2(6.00f, 6.00f);
            style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
            style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
            style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
            style.IndentSpacing                     = 25;
            style.ScrollbarSize                     = 15;
            style.GrabMinSize                       = 10;
            style.WindowBorderSize                  = 1;
            style.ChildBorderSize                   = 1;
            style.PopupBorderSize                   = 1;
            style.FrameBorderSize                   = 1;
            style.TabBorderSize                     = 1;
            style.WindowRounding                    = 7;
            style.ChildRounding                     = 4;
            style.FrameRounding                     = 3;
            style.PopupRounding                     = 4;
            style.ScrollbarRounding                 = 9;
            style.GrabRounding                      = 3;
            style.LogSliderDeadzone                 = 4;
            style.TabRounding                       = 4;
            break;
        case EditorStyle::Ocean:
            style.Alpha = 1.0f;
            style.DisabledAlpha = 0.5f;
            style.WindowPadding = ImVec2(8.0f, 8.0f);
            style.WindowRounding = 0.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = ImVec2(32.0f, 32.0f);
            style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
            style.WindowMenuButtonPosition = ImGuiDir_Left;
            style.ChildRounding = 0.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 0.0f;
            style.PopupBorderSize = 1.0f;
            style.FramePadding = ImVec2(4.0f, 3.0f);
            style.FrameRounding = 0.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = ImVec2(8.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
            style.CellPadding = ImVec2(4.0f, 2.0f);
            style.IndentSpacing = 21.0f;
            style.ColumnsMinSpacing = 6.0f;
            style.ScrollbarSize = 14.0f;
            style.ScrollbarRounding = 0.0f;
            style.GrabMinSize = 10.0f;
            style.GrabRounding = 0.0f;
            style.TabRounding = 0.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = ImGuiDir_Left;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

            style.Colors[ImGuiCol_Text] = ImVec4(0.8313725590705872f, 0.8470588326454163f, 0.8784313797950745f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.8313725590705872f, 0.8470588326454163f, 0.8784313797950745f, 0.501960813999176f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1725490242242813f, 0.1921568661928177f, 0.2352941185235977f, 1.0f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.1587982773780823f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1725490242242813f, 0.1921568661928177f, 0.2352941185235977f, 1.0f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.501960813999176f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.0f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5333333611488342f, 0.5333333611488342f, 0.5333333611488342f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3333333432674408f, 0.3333333432674408f, 0.3333333432674408f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.239215686917305f, 0.5215686559677124f, 0.8784313797950745f, 1.0f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9803921580314636f, 1.0f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 0.501960813999176f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 0.250980406999588f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1529411822557449f, 0.1725490242242813f, 0.2117647081613541f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3098039329051971f, 0.6235294342041016f, 0.9333333373069763f, 1.0f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
            style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
            style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 0.5021458864212036f);
            style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.03862661123275757f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 1.0f);
            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
            style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.2039215713739395f, 0.2313725501298904f, 0.2823529541492462f, 0.7529411911964417f);
            style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.7529411911964417f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.105882354080677f, 0.1137254908680916f, 0.1372549086809158f, 0.7529411911964417f);
            break;

        case Space:
            style.Alpha = 1.0f;
            style.DisabledAlpha = 0.300000011920929f;
            style.WindowPadding = ImVec2(6.5f, 2.700000047683716f);
            style.WindowRounding = 0.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = ImVec2(20.0f, 32.0f);
            style.WindowTitleAlign = ImVec2(0.0f, 0.6000000238418579f);
            style.WindowMenuButtonPosition = ImGuiDir_None;
            style.ChildRounding = 0.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 10.10000038146973f;
            style.PopupBorderSize = 1.0f;
            style.FramePadding = ImVec2(20.0f, 3.5f);
            style.FrameRounding = 0.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = ImVec2(4.400000095367432f, 4.0f);
            style.ItemInnerSpacing = ImVec2(4.599999904632568f, 3.599999904632568f);
            style.CellPadding = ImVec2(3.099999904632568f, 6.300000190734863f);
            style.IndentSpacing = 4.400000095367432f;
            style.ColumnsMinSpacing = 5.400000095367432f;
            style.ScrollbarSize = 8.800000190734863f;
            style.ScrollbarRounding = 9.0f;
            style.GrabMinSize = 9.399999618530273f;
            style.GrabRounding = 0.0f;
            style.TabRounding = 0.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05098039284348488f, 0.03529411926865578f, 0.03921568766236305f, 1.0f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.1019607856869698f, 0.1019607856869698f, 0.1019607856869698f, 0.5f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1607843190431595f, 0.1490196138620377f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5450980663299561f, 0.4666666686534882f, 0.7176470756530762f, 1.0f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3450980484485626f, 0.294117659330368f, 0.4588235318660736f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3137255012989044f, 0.2588235437870026f, 0.4274509847164154f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.3176470696926117f, 0.2784313857555389f, 0.407843142747879f, 1.0f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4156862795352936f, 0.364705890417099f, 0.529411792755127f, 1.0f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.4039215743541718f, 0.3529411852359772f, 0.5098039507865906f, 1.0f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.3254902064800262f, 0.2862745225429535f, 0.4156862795352936f, 1.0f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.4000000059604645f, 0.3490196168422699f, 0.5058823823928833f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
            style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
            style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
            style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
            style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2784313857555389f, 0.250980406999588f, 0.3372549116611481f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
            style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
            break;

    }


}

Lomus::Editor::Editor(GLFWwindow *window) {
    mConsole.init();
    initStlyle(Ocean);
    loadFont();

    Editor::rawWindow = window;

    glfwGetWindowSize(window, Editor::windowWidth, Editor::windowHeight);
    std::cout << "Creating editor at size:" << Editor::windowWidth[0] << "X" << Editor::windowHeight[0] << "\n";

    createFBO(512, 512);


}

void Lomus::Editor::Render(SceneManager& sceneManager, LightManager& lightManager, Camera& camera, EditorMode mode) {
    switch (mode) {
        case EditorMode::debug:
            //renderDebugModeData(sceneManager, lightManager, shader, outlineShader, window, camera, windowWidth, windowHeight);
            std::cerr << "Debug mode is deprecated\n";
        case EditorMode::editor:
            renderTheFullEditor(camera, sceneManager, lightManager);

    }
}

void Lomus::Editor::Delete(SceneManager &sceneManager) {
}

void Lomus::Editor::renderDebugModeData(SceneManager &sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader, GLFWwindow* window, Camera& camera,  int windowWidth, int windowHeight) {
    /*
    if (visible) {
        ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.3, windowHeight * 0.7));
        ImGui::Begin("Editor | Mode: debug");

        ImGui::BeginTabBar("General");

        if (ImGui::BeginTabItem("Lights")) {
            int i = 0;
            for (auto l : lightManager.lightIdMap.at(sceneManager.currentScene.name)) {
                Light& light = l.second;
                std::string temp = "Light: " + light.name;

                if (ImGui::TreeNode(temp.c_str())) {
                    float sd[3] = {light.lightPosition_x, light.lightPosition_y, light.lightPosition_z};
                    ImGui::Text("Position:");
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat3("", sd, 0.5f, 5.0f);
                    ImGui::PopID();
                    light.lightPosition_x = sd[0];
                    light.lightPosition_y = sd[1];
                    light.lightPosition_z = sd[2];



                    ImGui::Spacing();

                    float v[4] = {light.lightColor_r,light.lightColor_g,light.lightColor_b,light.lightColor_a};
                    temp = "col" + std::to_string(i);

                    ImGui::Text("Color:");
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat4("", v, 0.1f, 0.0f, 1.0f);
                    ImGui::PopID();
                    light.lightColor_r = v[0];
                    light.lightColor_g = v[1];
                    light.lightColor_b = v[2];
                    light.lightColor_a = v[3];

                    ImGui::Spacing();

                    temp = "inten" + std::to_string(i);
                    ImGui::Text("Inten");
                    float s[1] = {light.lightInten};
                    ImGui::PushID(temp.c_str());
                    ImGui::DragFloat("", s, 0.1f, 0.0f);
                    ImGui::PopID();
                    light.lightInten = *s;

                    if (light.lightType == 1) {
                        temp = "angle" + std::to_string(i);
                        ImGui::Text("Angle:");
                        ImGui::PushID(temp.c_str());
                        ImGui::DragFloat3("", light.lightAngle, 0.01f, -2.0f);
                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }
                i++;
            }


            if (ImGui::TreeNode("Shadow Textures")) {

                ImGui::Text("Sun Shadow map:");

                ImTextureID imTexID = (void*)(intptr_t)shadowTexture;

                // Display the texture using ImGui::Image
                ImGui::Image(imTexID, ImVec2(static_cast<float>(200), static_cast<float>(200)));


                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }



        if (ImGui::BeginTabItem("Entities")) {


            Scene& curScene = sceneManager.getCurrentScene();
            string temp = "";
            for (auto& gameObject : curScene.gameObjects) {
                if (ImGui::TreeNode(gameObject.second.name.c_str())) {

                    ImGui::Spacing();
                    ImGui::Text("Position: ");
                    temp = gameObject.second.name + "Pos";
                    ImGui::PushID(temp.c_str());
                    float v[3] = {gameObject.second.position.x, gameObject.second.position.y, gameObject.second.position.z};
                    ImGui::DragFloat3("", v, 0.5f, -20, 20);
                    ImGui::PopID();
                    gameObject.second.position.x = v[0];
                    gameObject.second.position.y = v[1];
                    gameObject.second.position.z = v[2];

                    ImGui::Text("Scale: ");
                    temp = gameObject.second.name + "Sac";
                    ImGui::PushID(temp.c_str());
                    float s[3] = {gameObject.second.scale.x, gameObject.second.scale.y, gameObject.second.scale.z};
                    ImGui::DragFloat3("", s, 0.5f, -20, 20);
                    ImGui::PopID();
                    gameObject.second.scale.x = s[0];
                    gameObject.second.scale.y = s[1];
                    gameObject.second.scale.z = s[2];

                    ImGui::TreePop();
                }
            }


            ImGui::EndTabItem();
        }



        if (ImGui::BeginTabItem("Render")) {

                shader.Activate();
                shader.setFloatUniform("sSamples", shadowSamples[0]);
                shader.setFloatUniform("sBiases", baises[0]);
                shader.setFloatUniform("sOffset", offset[0]);
                shader.setFloatUniform("lAmbient", ambient[0]);
                shader.setFloatUniform("shadowAmbient", sAmbient[0]);
                shader.setIntUniform("shadeLevels", celLevel[0]);
                shader.setIntUniform("useNormalMap", useNM[0]);


                outlineShader.Activate();
                outlineShader.setFloatUniform("thickness", outlineThick[0]);
                outlineShader.setVec4Uniform("color", outlineColor[0], outlineColor[1], outlineColor[2], outlineColor[3]);

            ImGui::Spacing();


            ImGui::Spacing();
            ImGui::Separator();

            ImGui::Text("Shadows: ");
            ImGui::Spacing();
            ImGui::Text("Samples:");
            ImGui::PushID("samp");
            ImGui::DragFloat("",Editor::shadowSamples, 0.1f, 1.0f, 10.0f);
            ImGui::PopID();

            ImGui::Text("Baise:");
            ImGui::PushID("bas");
            ImGui::DragFloat("", Editor::baises, 1.0f, 1.0f, 100.0f);
            ImGui::PopID();

            ImGui::Text("Offset:");
            ImGui::PushID("ofs");
            ImGui::DragFloat("", Editor::offset, 0.5f, 1.0f, 100.0f);
            ImGui::PopID();

            ImGui::Text("Shadow Ambient:");
            ImGui::PushID("sA");
            ImGui::DragFloat("", Editor::sAmbient, 0.01f, 0.01f, 3.0f);
            ImGui::PopID();


            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Text("Ambient");
            ImGui::PushID("am");
            ImGui::DragFloat("", Editor::ambient, 0.01f, 0.01f, 1.0f);
            ImGui::PopID();

            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Text("Toon shader");
            ImGui::Spacing();
            ImGui::Text("Cel Levels");
            ImGui::PushID("cl");
            ImGui::DragInt("", Editor::celLevel, 1, 1, 20);
            ImGui::PopID();
            ImGui::Text("Use Normal Maps");
            ImGui::PushID("uNM");
            ImGui::Checkbox("", Editor::useNM);
            ImGui::PopID();

            ImGui::Spacing();
            ImGui::Text("Outline Width:");
            ImGui::PushID("oT");
            ImGui::DragFloat("", Editor::outlineThick, 0.01f, 0.01f, 1);
            ImGui::PopID();
            ImGui::Text("Outline Color");
            ImGui::PushID("oC");
            ImGui::DragFloat4("", Editor::outlineColor, 0.01f, 0, 1);
            ImGui::PopID();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Console")) {
            mConsole.renderConsole(window, 400, 500, camera, sceneManager, Lomus::ConsoleMode::intergrated);
            ImGui::EndTabItem();
        }



        ImGui::EndTabBar();

        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {

            visible = 0;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }
    } else if (!visible) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && togglePressed) {

            visible = 1;
            togglePressed = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            togglePressed = true;
        }
    }
    */
}

void Editor::setShader(int name, Shader &shader) {
    shaderList.emplace(name, shader);
}

void Editor::renderTheFullEditor(Camera& camera, SceneManager& sceneManager, LightManager& lightManager) {
    oldWindowHeight = windowHeight[0];
    oldWindowWidth = windowWidth[0];


    glfwGetWindowSize(Editor::rawWindow, Editor::windowWidth, Editor::windowHeight);

    if (oldWindowWidth != windowWidth[0] || oldWindowHeight != windowHeight[0]) {
        resizeFrameBuffer(Editor::windowWidth[0], Editor::windowHeight[0]);
        std::cout << "Window size changed to: " << Editor::windowWidth[0] << "X" << Editor::windowHeight[0] << "\n";
    }
    oldWindowHeight = windowHeight[0];
    oldWindowWidth = windowWidth[0];
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.75f,oldWindowHeight * 0.65f));
    ImGui::Begin("Scene preview", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    imTexID = (void*)(intptr_t)texture_id;
    ImGui::Image(imTexID, ImVec2(static_cast<float>(oldWindowWidth * 0.745f), static_cast<float>(oldWindowHeight * 0.65f)),ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();


    renderSelectionPanel(camera, sceneManager, lightManager);
    renderPropertiesPanel(camera, sceneManager, lightManager);
    renderOtherPanel(camera, sceneManager, lightManager);

}


void Editor::renderSelectionPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {

    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, 0));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin("Selection Panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

    ImGui::BeginTabBar("Selection");

    if (ImGui::BeginTabItem("Game Objects")) {
        int i = 0;
        for (auto& pair : sceneManager.currentScene.gameObjects) {
            GameObject& gameObject = pair.second;
            ImGui::PushID(i);
            if (ImGui::TreeNode(" ", (ICON_FA_CUBE " Object" ), ImGuiTreeNodeFlags_CollapsingHeader)) {

                currentId = pair.first;
                currentState = EditorState::gameObject;
                ImGui::TreePop();
                if (i != 0) {
                    ImGui::SetNextItemOpen(false);
                }
            }
            i++;
            ImGui::PopID();
        }
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Scenes")) {
        ImGui::Text("Scenes here");
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Lights")) {
        ImGui::Text("Lights here");
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();


    ImGui::End();
}



void Editor::renderOtherPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {
    ImGui::SetNextWindowPos(ImVec2(0, oldWindowHeight * 0.65f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.35f));
    ImGui::Begin("Other", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

    ImGui::BeginTabBar("Other");

    if (ImGui::BeginTabItem("Files")) {
        ImGui::Text("Files here");
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Console")) {
        mConsole.renderConsole(Editor::rawWindow, oldWindowWidth * 0.75f, oldWindowHeight * 0.35f, camera, sceneManager, Lomus::ConsoleMode::intergrated);
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    ImGui::End();
}

void Editor::renderPropertiesPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {

    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin("Information & Properties", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);



    switch (currentState){
        case gameObject:

            if (currentId != -1) {
                renderGameObjectProperties(sceneManager.getGameobject(currentId));
            }
            break;
        case Scene:
            mConsole.addConsoleLog("Not Ready!\n");
            break;
        case Light:
            mConsole.addConsoleLog("Not Ready!\n");
            break;
        case Script:
            mConsole.addConsoleLog("Not Ready!\n");
            break;

    }
    ImGui::End();

}

void Editor::renderGameObjectProperties(GameObject& currentGameObject) {

    ImGui::Text("Name: ");
    ImGui::PushID("name");
    ImGui::SameLine();
    ImGui::InputText("", &currentGameObject.name);
    ImGui::PopID();
    ImGui::PushID("transform");
    ImGui::SetNextItemOpen(true);
    if (ImGui::TreeNode(" ", "Transformation",  ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PopID();
        float tempPos[3] = {currentGameObject.position.x, currentGameObject.position.y, currentGameObject.position.z};

        ImGui::PushID("pos");
        ImGui::DragFloat3("", tempPos, 0.5f);
        ImGui::PopID();

        ImGui::TreePop();
    }

}







void Editor::createFBO(int width, int height) {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}

void Editor::prepareFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    // Specify the color of the background
    glClearColor(0, 0, 0, 1);
    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Enable depth testing since it's disabled when drawing the framebuffer rectangle
    glEnable(GL_DEPTH_TEST);
}

void Editor::unprepareFrameBuffer() {
    // Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Editor::Delete() {
    glDeleteRenderbuffers(1, &RBO);
    glDeleteTextures(1, &texture_id);
    glDeleteFramebuffers(1, & FBO);

}

void Editor::resizeFrameBuffer(int newWidth, int newHeight) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, newWidth, newHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, newWidth, newHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

void Editor::loadFont() {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    ImFontConfig config;
    config.MergeMode = true;
    config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    io.Fonts->AddFontFromFileTTF("../../Lomus/Resources/Font/Font Awesome 6 Free-Regular-400.otf", 13.0f, &config, icon_ranges);
}
