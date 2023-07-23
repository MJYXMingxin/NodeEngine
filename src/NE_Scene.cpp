#include "ne_scene.h"

NE_Scene::NE_Scene(QObject *parent)
        : QGraphicsScene{parent},
        _view(nullptr)
{
    loadConfig();

    _scene_background_color.setNamedColor(_config.Scene_Background_Color);
    _dot_normal_color.setNamedColor(_config.Dot_Normal_Color);
    _dot_lighter_color.setNamedColor(_config.Dot_Lighter_Color);

    setBackgroundBrush(_scene_background_color);
    setSceneRect(-static_cast<qreal>(_config.Screen_Width)/2,
                 -static_cast<qreal>(_config.Screen_Height)/2,
                 _config.Screen_Width,
                 _config.Screen_Height);

    _normal_dot_brush = QBrush(_dot_normal_color);
    _normal_line_pen = QPen(_dot_normal_color);

    _normal_line_pen.setWidthF(_config.Line_Normal_Size);

    _lighter_dot_brush = QBrush(_dot_lighter_color);
    _lighter_line_pen = QPen(_dot_lighter_color);
    _lighter_line_pen.setWidthF(_config.Line_Lighter_Size);
}

void NE_Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    switch (Style) {
        case Lines:
            drawLines(painter, rect);
            break;
        case Dots:
            drawDots(painter, rect);
        default:
            break;
    }

}

void NE_Scene::drawLines(QPainter *painter, const QRectF &rect)
{
    int left,right,top,bottom;
    left = qFloor(rect.left());
    right = qFloor(rect.right());
    top = qFloor(rect.top());
    bottom = qFloor(rect.bottom());
    int first_left = left - (left % _config.Line_Grid_Size);
    int first_top = top - (top % _config.Line_Grid_Size);

    QList<QLine> Dark_Lines,Lines;
    //横线
    for(auto i = first_top; i <= bottom; i += _config.Line_Grid_Size)
    {
        auto line = QLine(left,i,right,i);
        i % (_config.Line_Grid_Size * _config.Line_Chunk_Size) == 0?
        Dark_Lines.append(line):Lines.append(line);
    }
    //竖线
    for(auto i = first_left;i <= right; i += _config.Line_Grid_Size)
    {
        auto line = QLine(i,top,i,bottom);
        i % (_config.Line_Grid_Size * _config.Line_Chunk_Size) == 0?
        Dark_Lines.append(line):Lines.append(line);
    }

    //画普通线
    painter->setPen(_normal_line_pen);
    painter->drawLines(Lines);
    //画粗线
    painter->setPen(_lighter_line_pen);
    painter->drawLines(Dark_Lines);
}

void NE_Scene::drawDots(QPainter *painter, const QRectF &rect)
{
    qreal left = int(rect.left()) - (int(rect.left()) % _config.Dot_Grid_Size);
    qreal top = int(rect.top()) - (int(rect.top()) % _config.Dot_Grid_Size);

    QVarLengthArray<QPointF, 100> points;

    for (int x = static_cast<int>(left); x < rect.right(); x += _config.Dot_Grid_Size)
    {
        for (int y = static_cast<int>(top); y < rect.bottom(); y += _config.Dot_Grid_Size)
        {
            points.append(QPointF(x, y));
        }
    }

    painter->setPen(Qt::NoPen);

    for (int i = 0; i < points.size(); ++i)
    {
        if ((int(points.at(i).x()) % (_config.Dot_Grid_Size * _config.Dot_Chunk_Size) == 0)
            && (int(points.at(i).y()) % (_config.Dot_Grid_Size * _config.Dot_Chunk_Size) == 0))
        {
            painter->setBrush(_lighter_dot_brush);
            QPolygonF diamond;
            diamond << QPointF(points.at(i).x(), points.at(i).y() - _config.Dot_Lighter_Size)
                    << QPointF(points.at(i).x() + _config.Dot_Lighter_Size, points.at(i).y())
                    << QPointF(points.at(i).x(), points.at(i).y() + _config.Dot_Lighter_Size)
                    << QPointF(points.at(i).x() - _config.Dot_Lighter_Size, points.at(i).y());
            painter->drawPolygon(diamond);
        }
        else
        {
            painter->setBrush(_normal_dot_brush);
            painter->drawEllipse(points.at(i), _config.Dot_Normal_Size, _config.Dot_Normal_Size);
        }
    }
}

void NE_Scene::setView(NE_View *view) { _view = view; }

void NE_Scene::switchStyle()
{
    switch (Style)
    {
        case Dots:
            Style = Lines;
            break;
        case Lines:
            Style = Dots;
            break;
    }
    update();
}

NE_View *NE_Scene::View() { return _view; }

double NE_Scene::getScale() { return _view->getScale(); }

void NE_Scene::loadConfig()
{
    _obj = SearchObj(Scene);
    _config.Scene_Background_Color = _obj["Scene_Background_Color"].toString();

    _config.Dot_Normal_Color = _obj["Dot_Normal_Color"].toString();

    _config.Dot_Lighter_Color = _obj["Dot_Lighter_Color"].toString();

    _config.Dot_Normal_Size = _obj["Dot_Normal_Size"].toDouble();
    _config.Dot_Lighter_Size = _obj["Dot_Lighter_Size"].toDouble();

    _config.Dot_Grid_Size = _obj["Dot_Grid_Size"].toInt();
    _config.Dot_Chunk_Size = _obj["Dot_Chunk_Size"].toInt();

    _config.Line_Normal_Size = _obj["Line_Normal_Size"].toDouble();
    _config.Line_Lighter_Size = _obj["Line_Lighter_Size"].toDouble();

    _config.Line_Grid_Size = _obj["Line_Grid_Size"].toInt();
    _config.Line_Chunk_Size = _obj["Line_Chunk_Size"].toInt();

    _config.Screen_Width = _obj["editor_screen_width"].toInt();
    _config.Screen_Height = _obj["editor_screen_height"].toInt();

    switch (_obj["canvas_style"].toInt())
    {
        case 1:
            _config.Style = Lines;
            Style = Lines;
            break;
        case 0:
            _config.Style = Dots;
            Style = Dots;
        default:
            break;
    }
}
