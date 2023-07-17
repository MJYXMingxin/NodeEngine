#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QDebug>

#define SCENE_BACKGROUND_COLOR "#212121"
#define DOT_NORMAL_COLOR "#313131"
#define DOT_LIGHTER_COLOR "#151515"
#define DOT_NORMAL_SIZE 5
#define DOT_LIGHTER_SIZE 7.5
#define DOT_GRID_SIZE 100
#define DOT_CHUNK_SIZE 5
#define LINE_NORMAL_SIZE 2
#define LINE_LIGHTER_SIZE 3
#define LINE_GRID_SIZE 50
#define LINE_CHUNK_SIZE 10
#define EDITOR_SCREEN_WIDTH 10000
#define EDITOR_SCREEN_HEIGHT 10000
#define CANVAS_STYLE 0

#define CLAMP_MIN 0.25
#define CLAMP_MAX 5
#define ZOOM_FACTOR 1.1

#define PARAM_COLOR_EXEC "#ffffff"
#define PARAM_COLOR_BOOL "#860000"
#define PARAM_COLOR_BYTE "#005850"
#define PARAM_COLOR_INT "#228b22"
#define PARAM_COLOR_FLOAT "#99ff22"
#define PARAM_COLOR_STRING "#f91ec5"
#define PARAM_COLOR_VEC2 "#57c3c2"
#define PARAM_COLOR_VEC3 "#7cabb1"
#define PARAM_COLOR_ENUM "#1a6840"
#define PARAM_COLOR_STRUCT "#5d3131"
#define PARAM_COLOR_ELSE "#1772b4"
#define PARAM_COLOR_UNKNOWN "#a7a8bd"

enum Class
{
    Exec,
    Bool,
    Byte,
    Int,
    Float,
    String,
    Vec2,
    Vec3,
    Enum,
    Struct,
    Else,
    UNknown
};

enum ObjType
{
    Param,
    Scene,
    View
};

enum Canvas_Style
{
    Dots,
    Lines
};

typedef struct RGBColor{
    int R;
    int G;
    int B;
}RGB;

typedef struct clamp{
    double min;
    double max;
}Clamp;

typedef struct Viewconfig{
    Clamp clamp;
    double zoom_factor;
}Config_View;

typedef struct Sceneconfig{
    QString Scene_Background_Color;
    QString Dot_Normal_Color;
    QString Dot_Lighter_Color;

    double Dot_Normal_Size;
    double Dot_Lighter_Size;

    int Dot_Grid_Size;
    int Dot_Chunk_Size;

    double Line_Normal_Size;
    double Line_Lighter_Size;

    int Line_Grid_Size;
    int Line_Chunk_Size;

    int Screen_Width;
    int Screen_Height;

    Canvas_Style Style;
}Config_Scene;


QJsonObject SearchObj(ObjType type);
QJsonObject QJsonObj();
QJsonObject SceneJsonObj();
QJsonObject ViewJsonObj();
QJsonObject ParamJsonObj();
QString loadStyleSheet(const QString &sheetName);
void checkConfig();


#endif // CONFIG_H
