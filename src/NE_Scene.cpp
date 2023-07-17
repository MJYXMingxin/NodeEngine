#include "ne_scene.h"

NE_Scene::NE_Scene(QObject *parent)
        : QGraphicsScene{parent}
{
    this->getConfig();

    this->_scene_background_color.setNamedColor(this->_config.Scene_Background_Color);
    this->_dot_normal_color.setNamedColor(this->_config.Dot_Normal_Color);
    this->_dot_lighter_color.setNamedColor(this->_config.Dot_Lighter_Color);

    this->setBackgroundBrush(this->_scene_background_color);
    this->setSceneRect(-this->_config.Screen_Width/2,
                       -this->_config.Screen_Height/2,
                       this->_config.Screen_Width,
                       this->_config.Screen_Height);

    this->_normal_dot_brush = QBrush(this->_dot_normal_color);
    this->_normal_line_pen = QPen(this->_dot_normal_color);

    this->_normal_line_pen.setWidthF(this->_config.Line_Normal_Size);

    this->_lighter_dot_brush = QBrush(this->_dot_lighter_color);
    this->_lighter_line_pen = QPen(this->_dot_lighter_color);
    this->_lighter_line_pen.setWidthF(this->_config.Line_Lighter_Size);
}

void NE_Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    switch (this->Style) {
        case Lines:
            this->drawLines(painter, rect);
            break;
        case Dots:
            this->drawDots(painter, rect);
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
    int first_left = left - (left % this->_config.Line_Grid_Size);
    int first_top = top - (top % this->_config.Line_Grid_Size);

    QList<QLine> Dark_Lines,Lines;
    //横线
    for(auto i = first_top; i <= bottom; i += this->_config.Line_Grid_Size)
    {
        auto line = QLine(left,i,right,i);
        i % (this->_config.Line_Grid_Size * this->_config.Line_Chunk_Size) == 0?
        Dark_Lines.append(line):Lines.append(line);
    }
    //竖线
    for(auto i = first_left;i <= right; i += this->_config.Line_Grid_Size)
    {
        auto line = QLine(i,top,i,bottom);
        i % (this->_config.Line_Grid_Size * this->_config.Line_Chunk_Size) == 0?
        Dark_Lines.append(line):Lines.append(line);
    }

    //画普通线
    painter->setPen(this->_normal_line_pen);
    painter->drawLines(Lines);
    //画粗线
    painter->setPen(this->_lighter_line_pen);
    painter->drawLines(Dark_Lines);
}

void NE_Scene::drawDots(QPainter *painter, const QRectF &rect)
{
    qreal left = int(rect.left()) - (int(rect.left()) % this->_config.Dot_Grid_Size);
    qreal top = int(rect.top()) - (int(rect.top()) % this->_config.Dot_Grid_Size);

    QVarLengthArray<QPointF, 100> points;

    for (int x = left; x < rect.right(); x += this->_config.Dot_Grid_Size)
    {
        for (int y = top; y < rect.bottom(); y += this->_config.Dot_Grid_Size)
        {
            points.append(QPointF(x, y));
        }
    }

    painter->setPen(Qt::NoPen);

    for (int i = 0; i < points.size(); ++i)
    {
        if ((int(points.at(i).x()) % (this->_config.Dot_Grid_Size * this->_config.Dot_Chunk_Size) == 0)
            && (int(points.at(i).y()) % (this->_config.Dot_Grid_Size * this->_config.Dot_Chunk_Size) == 0))
        {
            painter->setBrush(this->_lighter_dot_brush);
            QPolygonF diamond;
            diamond << QPointF(points.at(i).x(), points.at(i).y() - this->_config.Dot_Lighter_Size)
                    << QPointF(points.at(i).x() + this->_config.Dot_Lighter_Size, points.at(i).y())
                    << QPointF(points.at(i).x(), points.at(i).y() + this->_config.Dot_Lighter_Size)
                    << QPointF(points.at(i).x() - this->_config.Dot_Lighter_Size, points.at(i).y());
            painter->drawPolygon(diamond);
        }
        else
        {
            painter->setBrush(this->_normal_dot_brush);
            painter->drawEllipse(points.at(i), this->_config.Dot_Normal_Size, this->_config.Dot_Normal_Size);
        }
    }
}

void NE_Scene::setView(NE_View *view)
{
    this->_view = view;
}

void NE_Scene::switchStyle()
{
    switch (this->Style)
    {
        case Dots:
            this->Style = Lines;
            break;
        case Lines:
            this->Style = Dots;
            break;
    }
    this->update();
}

NE_View *NE_Scene::View()
{
    return this->_view;
}

double NE_Scene::getScale()
{
    return this->_view->getScale();
}

void NE_Scene::getConfig()
{
    this->_obj = SearchObj(Scene);
    this->_config.Scene_Background_Color = this->_obj["Scene_Background_Color"].toString();

    this->_config.Dot_Normal_Color = this->_obj["Dot_Normal_Color"].toString();

    this->_config.Dot_Lighter_Color = this->_obj["Dot_Lighter_Color"].toString();

    this->_config.Dot_Normal_Size = this->_obj["Dot_Normal_Size"].toDouble();
    this->_config.Dot_Lighter_Size = this->_obj["Dot_Lighter_Size"].toDouble();

    this->_config.Dot_Grid_Size = this->_obj["Dot_Grid_Size"].toInt();
    this->_config.Dot_Chunk_Size = this->_obj["Dot_Chunk_Size"].toInt();

    this->_config.Line_Normal_Size = this->_obj["Line_Normal_Size"].toDouble();
    this->_config.Line_Lighter_Size = this->_obj["Line_Lighter_Size"].toDouble();

    this->_config.Line_Grid_Size = this->_obj["Line_Grid_Size"].toInt();
    this->_config.Line_Chunk_Size = this->_obj["Line_Chunk_Size"].toInt();

    this->_config.Screen_Width = this->_obj["editor_screen_width"].toInt();
    this->_config.Screen_Height = this->_obj["editor_screen_height"].toInt();

    switch (this->_obj["canvas_style"].toInt())
    {
        case 1:
            this->_config.Style = Lines;
            this->Style = Lines;
            break;
        case 0:
            this->_config.Style = Dots;
            this->Style = Dots;
        default:
            break;
    }
}
