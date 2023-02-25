#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QJsonArray>



enum ObjType
{
    Scene,
    View
};

typedef struct color{
    int R;
    int G;
    int B;
}RGB;

typedef struct clamp{
    double min;
    double max;
}Clamp;

typedef struct Sceneconfig{
    RGB BackGround;
    RGB Grid_Normal_Line;
    RGB Grid_Dark_Line;

    double Grid_Normal_Line_Width;
    double Grid_Dark_Line_Width;

    int Grid_Size;
    int Chunk_Size;

    int Screen_Width;
    int Screen_Height;

}Config_Scene;

typedef struct Viewconfig{
    Clamp clamp;
    double zoom_factor;
}Config_View;

QJsonObject SearchObj(ObjType type);
QJsonObject QJsonObj();
QJsonObject SceneJsonObj();
QJsonObject ViewJsonObj();


#endif // CONFIG_H
