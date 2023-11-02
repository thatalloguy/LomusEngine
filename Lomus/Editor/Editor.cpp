#include "Editor.h"


void Lomus::Editor::initStlyle(EditorStyle editorStyle) {
// Visual Studio style by MomoDeve from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
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

            //style.Colors[ImGuiCol_Text] = ImVec4(0.8313725590705872f, 0.8470588326454163f, 0.8784313797950745f, 1.0f);
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

Lomus::Editor::Editor(GLFWwindow *window, EditorStyle style) {
    mConsole.init();
    initStlyle(style);
    Editor::rawWindow = window;

    glfwGetWindowSize(window, Editor::windowWidth, Editor::windowHeight);
    std::cout << "Creating editor at size:" << Editor::windowWidth[0] << "X" << Editor::windowHeight[0] << "\n";

    createFBO(512, 512);

    Lomus::Keyboard::getInstance().setCaptureWindow(rawWindow);
    auto& guizmoStyle = ImGuizmo::GetStyle();

    

    guizmoStyle.HatchedAxisLineThickness = 0;

    // Prepare the color text editor
    auto lang = TextEditor::LanguageDefinition::GLSL();
    textEditor.SetLanguageDefinition(lang);
    std::ifstream in("../../Lomus/Shader/shaders/default.frag", std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        textEditor.SetText(contents);
    } else {
        std::cout << "Couldn't load: ../../Lomus/Shader/shaders/default.frag\n";
        textEditor.SetText("Couldnt load shader file :/\n");
    }


}

void Lomus::Editor::Render(SceneManager& sceneManager, LightManager& lightManager, Camera& camera, EditorMode mode) {
    switch (mode) {
        case EditorMode::debug:
            //renderDebugModeData(sceneManager, lightManager, shader, outlineShader, window, camera, windowWidth, windowHeight);
            std::cerr << "Debug mode is deprecated\n";
        case EditorMode::editor:
            renderTheFullEditor(camera, sceneManager, lightManager);
            break;
        case EditorMode::shader:

            shaderEditor.Render();
            break;
    }
}

void Lomus::Editor::Delete(SceneManager &sceneManager) {

}

void Lomus::Editor::renderDebugModeData(SceneManager &sceneManager,LightManager& lightManager,Shader& shader, Shader& outlineShader, GLFWwindow* window, Camera& camera,  int windowWidth, int windowHeight) {

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
    ImGui::Begin(ICON_FA_TABLE_CELLS_LARGE " Windows", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::BeginTabBar("Bigboi's");


    imTexID = (void*)(intptr_t)texture_id;

    if (ImGui::BeginTabItem("Scene")) {
        ImGui::Image(imTexID, ImVec2(static_cast<float>(oldWindowWidth * 0.745f), static_cast<float>(oldWindowHeight * 0.65f)),ImVec2(0, 1), ImVec2(1, 0));
        currentSceneState = SceneState::world;
        ImGui::EndTabItem();
    }



    ImGui::EndTabBar();


    if (currentId != -1) {
        manipulateGameObjectViaGizmo(sceneManager.getGameobject(currentId), camera);
    }

    ImGui::End();


    renderSelectionPanel(camera, sceneManager, lightManager);

    renderOtherPanel(camera, sceneManager, lightManager);

    renderPropertiesPanel(camera, sceneManager, lightManager);

    handleInputs(camera);

}


void Editor::renderSelectionPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {

    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, 0));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin(ICON_FA_ARROW_POINTER " Selection Panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

    ImGui::BeginTabBar("Selection");

    if (ImGui::BeginTabItem(ICON_FA_CUBES_STACKED " Game Objects")) {
        int i = 0;

        for (auto& pair : sceneManager.currentScene->gameObjects) {
            std::shared_ptr<GameObject> gameObject = pair.second;
            ImGui::PushID(i);
            std::string newName = ICON_FA_CUBE + std::string(" " + gameObject->name);


            if (ImGui::TreeNodeEx(newName.c_str())) {

                currentId = pair.first;
                currentState = EditorState::gameObject;
                ImGui::TreePop();
            }

            i++;
            ImGui::PopID();
        }
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(ICON_FA_OBJECT_UNGROUP" Scenes")) {
        ImGui::Text("Scenes here");
        currentState = EditorState::Scene;
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem(ICON_FA_LIGHTBULB " Lights")) {
        ImGui::Text("Lights here");
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Shader Editor")) {
        if (ImGui::Button("Reload Shader")) {
            shaderList.at(1).reCompile();
            if ( shaderList.at(1).getErrorLine() != -1) {
                errorMarkers.insert(std::make_pair<int, std::string>(shaderList.at(1).getErrorLine(), shaderList.at(1).getErrorMessage().c_str()));
                textEditor.SetErrorMarkers(errorMarkers);
                errorline =shaderList.at(1).getErrorLine();
            } else if (shaderList.at(1).getErrorLine() == -1) {
                errorMarkers.erase(errorline);
                textEditor.SetErrorMarkers(errorMarkers);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Save")) {
            std::ofstream out("../../Lomus/Shader/shaders/default.frag");
            out << textEditor.GetText().c_str();
            out.close();
        }

        textEditor.Render("--Shader editor--");
        currentSceneState = SceneState::texteditor;
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();


    ImGui::End();
}

void Editor::renderOtherPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {
    ImGui::SetNextWindowPos(ImVec2(0, oldWindowHeight * 0.65f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.35f));
    ImGui::Begin(ICON_FA_GEARS " Other", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

    ImGui::BeginTabBar("Other");

    if (ImGui::BeginTabItem(ICON_FA_FOLDER " Files")) {
        ImGui::Text("Files here");
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(ICON_FA_TERMINAL " Console")) {
        mConsole.renderConsole(Editor::rawWindow, oldWindowWidth * 0.75f, oldWindowHeight * 0.35f, camera, sceneManager, Lomus::ConsoleMode::intergrated);
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    ImGui::End();
}

void Editor::renderPropertiesPanel(Camera &camera, SceneManager &sceneManager, LightManager &lightManager) {

    ImGui::SetNextWindowPos(ImVec2(oldWindowWidth * 0.75f, oldWindowHeight * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(oldWindowWidth * 0.25f, oldWindowHeight * 0.5f));
    ImGui::Begin(ICON_FA_INFO " Information & Properties", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);



    switch (currentState){
        case gameObject:

            if (currentId != -1) {
                renderGameObjectProperties(sceneManager.getGameobject(currentId));


            }

            break;
        case Scene:
            renderActiveScene(sceneManager);
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

void Editor::renderGameObjectProperties(std::shared_ptr<GameObject> currentGameObject) {

    ImGuiStyle& style = ImGui::GetStyle();



    ImGui::Text("Name: ");
    ImGui::PushID("name");
    ImGui::SameLine();
    ImGui::InputText("", &currentGameObject->name);
    ImGui::PopID();

    ImGui::Text("ID: "); ImGui::SameLine(); ImGui::Text(  "%s", std::to_string(currentGameObject->id).c_str());

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SetNextItemWidth(windowWidth[0] * 0.175);
    if (ImGui::TreeNodeEx((ICON_FA_GEAR" TransFormation"), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
        ImGui::Spacing();
///     pos
        float tempX[1] = {currentGameObject->position.x};
        float tempY[1] = {currentGameObject->position.y};
        float tempZ[1] = {currentGameObject->position.z};
        // Rot
        float tempRX[1] = {currentGameObject->rotation.x};
        float tempRY[1] = {currentGameObject->rotation.y};
        float tempRZ[1] = {currentGameObject->rotation.z};
        float tempRW[1] = {currentGameObject->rotation.w};
        // Scale

        float tempSX[1] = {currentGameObject->scale.x};
        float tempSY[1] = {currentGameObject->scale.y};
        float tempSZ[1] = {currentGameObject->scale.z};


        ImGui::Text("Position: ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("x");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("Y");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempY, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("z");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempZ, 0.5f);
        ImGui::PopID();


        ImGui::Text(" ");
        // Display Rotation
        ImGui::Text("Orientation: ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("xr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("Yr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRY, 0.5f);
        ImGui::PopID();

        ImGui::Text("             ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("zr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRZ, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.5, 0, 1);
        ImGui::Text("W");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("wr");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempRW, 0.5f);
        ImGui::PopID();

        ImGui::Text(" ");

        ImGui::Text("Scale: ");
        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(1, 0.2, 0.2, 1);
        ImGui::Text("X");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sx");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSX, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();
        style.Colors[ImGuiCol_Text] = ImVec4(0.2, 1, 0.2, 1);
        ImGui::Text("Y");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sY");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSY, 0.5f);
        ImGui::PopID();

        ImGui::SameLine();

        style.Colors[ImGuiCol_Text] = ImVec4(0.3, 0.3, 1, 1);
        ImGui::Text("Z");
        style.Colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);
        ImGui::SameLine();
        ImGui::PushID("sz");
        ImGui::SetNextItemWidth(windowWidth[0] * 0.0375);
        ImGui::DragFloat("", tempSZ, 0.5f);
        ImGui::PopID();




        currentGameObject->position.x = tempX[0];
        currentGameObject->position.y = tempY[0];
        currentGameObject->position.z = tempZ[0];

        currentGameObject->rotation.x = tempRX[0];
        currentGameObject->rotation.y = tempRY[0];
        currentGameObject->rotation.z = tempRZ[0];
        currentGameObject->rotation.w = tempRW[0];

        currentGameObject->scale.x = tempSX[0];
        currentGameObject->scale.y = tempSY[0];
        currentGameObject->scale.z = tempSZ[0];

        ImGui::TreePop();
    }
}

void Editor::manipulateGameObjectViaGizmo(std::shared_ptr<GameObject> gameObject, Camera& camera) {
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);


    // Transform the matrices to their correct form
    trans = glm::translate(trans, -gameObject->position);
    rot = glm::mat4_cast(gameObject->rotation);
    sca = glm::scale(sca, gameObject->scale);

    glm::mat4 editMatrix = glm::mat4(1.0f) * trans * rot * sca;
    ImGuizmo::Enable(true);

    glm::mat4 cameraView;// = glm::mat4(0.0f);
    glm::mat4 emptyMatrix = glm::mat4(1.0f);

    emptyMatrix = glm::translate(glm::vec3(0, 0, 0));

    ImGuizmo::SetRect(0, 0, oldWindowWidth * 0.75f, windowHeight[0] * 0.65f);
    ImGuizmo::SetDrawlist();
    //ImGuizmo::DrawGrid(glm::value_ptr(camera.view), glm::value_ptr(camera.projection), glm::value_ptr(emptyMatrix), 200.0f);
    ImGuizmo::Manipulate(glm::value_ptr(camera.view),  glm::value_ptr(camera.projection), Editor::currentGizmoState, ImGuizmo::WORLD, glm::value_ptr(editMatrix), nullptr,  nullptr);

    glm::quat newRot;
    glm::vec3 newPos;
    glm::vec3 newScale;
    glm::vec3 skew;
    glm::vec4 Perspective;


    glm::decompose(editMatrix, newScale, newRot, newPos, skew, Perspective);

    gameObject->position.x = -newPos.x;
    gameObject->position.y = -newPos.y ;
    gameObject->position.z = -newPos.z ;

    gameObject->scale = newScale;
    newRot.w = -newRot.w;
    gameObject->rotation = glm::conjugate(newRot);

}

void Editor::renderActiveScene(SceneManager &sceneManager) {



    ImGui::BeginTabBar("SceneOverview");

    if (ImGui::BeginTabItem("General")) {
        ImGui::PushID("Scenename");
        ImGui::Text("Scene Name: "); ImGui::SameLine();
        ImGui::InputText("", &sceneManager.currentScene->name);
        ImGui::PopID();
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Shadows")) {
        ImGui::Spacing();
        ImGui::Text("Shadow Depth Texture:");
        ImTextureID imTexID = (void*)(intptr_t)shadowTexture;

        // Display the texture using ImGui::Image
        ImGui::Image(imTexID, ImVec2(static_cast<float>(windowWidth[0] * 0.1f), static_cast<float>(windowHeight[0] * 0.1f)));

        ImGui::Separator();
        ImGui::Text("Shadow Area: ");
        ImGui::SameLine();

        ImGui::PushID("ShadowArea");
        ImGui::DragFloat(" ", shadowArea, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Shadow Near plane: ");
        ImGui::SameLine();

        ImGui::PushID("Shadow Nearplane");
        ImGui::DragFloat(" ", shadowNearPlane, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Shadow Far plane: ");
        ImGui::SameLine();

        ImGui::PushID("Shadow Farplane");
        ImGui::DragFloat(" ", shadowFarPlane, 1.0);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("Baises:");
        ImGui::SameLine();
        ImGui::PushID("SHADOWBIAS");
        ImGui::DragFloat(" ", baises, 0.0001);
        ImGui::PopID();

        ImGui::Separator();
        ImGui::Text("PCF Samples:");
        ImGui::SameLine();
        ImGui::PushID("SHADOWPCF");
        ImGui::DragFloat(" ", shadowSamples, 0.01f);
        ImGui::PopID();

        shaderList.at(1).Activate();
        shaderList.at(1).setFloatUniform("sBaises", baises[0]);
        shaderList.at(1).setFloatUniform("sampleSize", shadowSamples[0]);



        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
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

bool Editor::allowCameraInput() {
    float mouseX = ImGui::GetMousePos().x;
    float mouseY = ImGui::GetMousePos().y;
    float sceneViewWidth = windowWidth[0] * 0.75f;
    float sceneViewHeight = windowHeight[0] * 0.65f;

    return (mouseX >= 0 && mouseX <= sceneViewWidth && mouseY >= 0 && mouseY <= sceneViewHeight && ImGui::IsMouseDown(ImGuiMouseButton_Right)); // Checks if mouse is inside the scene preview frame
}

void Editor::handleInputs(Camera &camera) {
    Lomus::Keyboard& keyboard = Lomus::Keyboard::getInstance();
    if (allowCameraInput()) {
        camera.Speed += ImGui::GetIO().MouseWheel;
    }

    if (keyboard.isKeyPressed(Lomus::Keyboard::R)) {
        currentGizmoState = ImGuizmo::OPERATION::ROTATE;
    }


    if (keyboard.isKeyPressed(Lomus::Keyboard::T)) {
        currentGizmoState = ImGuizmo::OPERATION::TRANSLATE;
    }

    if (keyboard.isKeyPressed(Lomus::Keyboard::Y)) {
        currentGizmoState = ImGuizmo::OPERATION::SCALE;
    }
}



