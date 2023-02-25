#include "config.h"

QJsonObject Null = {};

QJsonObject SearchObj(ObjType type)
{
    QJsonObject temp;
    if ((temp = QJsonObj()) != Null)
    {
        switch (type)
        {
        case Scene:
            return SceneJsonObj();
            break;

        case View:
            return ViewJsonObj();
            break;

        default:
            return Null;
            break;
        }
    }
    else
        return Null;
}

QJsonObject QJsonObj()
{
    QFile file("config.json");

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
