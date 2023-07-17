#include "config.h"

QJsonObject Null = {};

QString loadStyleSheet(const QString &sheetName)
{
    QFile file(":/resource/styles/" + sheetName + ".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet("");
        styleSheet += QLatin1String(file.readAll());
        return styleSheet;
    }
    return "";
}

QJsonObject SearchObj(ObjType type)
{
    if (QJsonObj() != Null)
    {
        switch (type)
        {
            case Scene:
                return SceneJsonObj();

            case View:
                return ViewJsonObj();

            case Param:
                return ParamJsonObj();

            default:
                return Null;
        }
    }
    else
        return Null;
}

QJsonObject QJsonObj()
{
    QFile file("./config.json");

    if (!file.open(QFile::ReadOnly))
        return Null;
    //将文件内容读取到数组中
    QByteArray data(file.readAll());
    file.close();	//关闭文件
    QJsonParseError jError;	//创建QJsonParseError对象
    //使用QJsonDocument的fromJson函数读取json串，并将QJsonParseError对象传入获取错误值
    QJsonDocument jDoc = QJsonDocument::fromJson(data, &jError);
    //判断QJsonParseError对象获取的error是否包含错误，包含则返回0
    if (jError.error != QJsonParseError::NoError)
        return Null;

    QJsonObject jObj = jDoc.object();
    return jObj;
}

QJsonObject SceneJsonObj()
{
    auto Obj = QJsonObj();
    return Obj["scene"].toObject();
}

QJsonObject ViewJsonObj()
{
    auto Obj = QJsonObj();
    return Obj["view"].toObject();
}

QJsonObject ParamJsonObj()
{
    auto Obj = QJsonObj();
    return Obj["param"].toObject();
}

void checkConfig()
{
    if(!QFile::exists("./config.json"))
    {
        QJsonObject json;
        // 添加一个名为"scene"的子对象
        QJsonObject scene;
        scene["Scene_Background_Color"] = SCENE_BACKGROUND_COLOR;
        scene["Dot_Normal_Color"] = DOT_NORMAL_COLOR;
        scene["Dot_Lighter_Color"] = DOT_LIGHTER_COLOR;
        scene["Dot_Normal_Size"] = DOT_NORMAL_SIZE;
        scene["Dot_Lighter_Size"] = DOT_LIGHTER_SIZE;
        scene["Dot_Grid_Size"] = DOT_GRID_SIZE;
        scene["Dot_Chunk_Size"] = DOT_CHUNK_SIZE;
        scene["Line_Normal_Size"] = LINE_NORMAL_SIZE;
        scene["Line_Lighter_Size"] = LINE_LIGHTER_SIZE;
        scene["Line_Grid_Size"] = LINE_GRID_SIZE;
        scene["Line_Chunk_Size"] = LINE_CHUNK_SIZE;
        scene["editor_screen_width"] = EDITOR_SCREEN_WIDTH;
        scene["editor_screen_height"] = EDITOR_SCREEN_HEIGHT;
        scene["canvas_style"] = CANVAS_STYLE;
        json["scene"] = scene;
        // 添加一个名为"view"的子对象
        QJsonObject view;
        QJsonObject clamp;
        clamp["min"] = CLAMP_MIN;
        clamp["max"] = CLAMP_MAX;
        view["Clamp"] = clamp;
        view["Zoom_factor"] = ZOOM_FACTOR;
        json["view"] = view;
        // 添加一个名为"param"的子对象
        QJsonObject param;
        param["exec"] = PARAM_COLOR_EXEC;
        param["bool"] = PARAM_COLOR_BOOL;
        param["byte"] = PARAM_COLOR_BYTE;
        param["int"] = PARAM_COLOR_INT;
        param["float"] = PARAM_COLOR_FLOAT;
        param["string"] = PARAM_COLOR_STRING;
        param["vec2"] = PARAM_COLOR_VEC2;
        param["vec3"] = PARAM_COLOR_VEC3;
        param["enum"] = PARAM_COLOR_ENUM;
        param["struct"] = PARAM_COLOR_STRUCT;
        param["else"] = PARAM_COLOR_ELSE;
        param["unknown"] = PARAM_COLOR_UNKNOWN;
        json["param"] = param;

        // 将JSON对象转换为文本
        QJsonDocument doc(json);
        QByteArray data = doc.toJson();
        QFile file("config.json");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(data);
            file.close();
        }
        else
        {
            qWarning()<<"Unknown Error";
            exit(-1);
        }
    }
}
