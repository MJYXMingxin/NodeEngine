#include "nodegraphicsscene.h"

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    this->getconfig();
    //设置背景颜色
    this->setBackgroundBrush(QColor(this->_config.BackGround.R,
                                    this->_config.BackGround.G,
                                    this->_config.BackGround.B));
    //设置背景大小
    this->setSceneRect(-this->_config.Screen_Width/2,
                       -this->_config.Screen_Height/2,
                       this->_config.Screen_Width,
                       this->_config.Screen_Height);

    this->_normal_line_pen = QPen(QColor(this->_config.Grid_Normal_Line.R,
                                         this->_config.Grid_Normal_Line.G,
                                         this->_config.Grid_Normal_Line.B));
    this->_normal_line_pen.setWidthF(this->_config.Grid_Normal_Line_Width);

    this->_dark_line_pen = QPen(QColor(this->_config.Grid_Dark_Line.R,
                                         this->_config.Grid_Dark_Line.G,
                                         this->_config.Grid_Dark_Line.B));
    this->_dark_line_pen.setWidthF(this->_config.Grid_Dark_Line_Width);

}

void NodeGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    int left,right,top,bottom;
    left = qFloor(rect.left());
    right = qFloor(rect.right());
    top = qFloor(rect.top());
    bottom = qFloor(rect.bottom());
    int first_left = left - (left % this->_config.Grid_Size);
    int first_top = top - (top % this->_config.Grid_Size);

    //横线
    for(auto i = first_top; i <= bottom; i += this->_config.Grid_Size)
    {
        auto line = QLine(left,i,right,i);
        i % (this->_config.Grid_Size * this->_config.Chunk_Size) == 0?
                    this->Dark_Lines.append(line):this->Lines.append(line);
    }
    //竖线
    for(auto i = first_left;i <= right; i += this->_config.Grid_Size)
    {
        auto line = QLine(i,top,i,bottom);
        i % (this->_config.Grid_Size * this->_config.Chunk_Size) == 0?
                    this->Dark_Lines.append(line):this->Lines.append(line);
    }

    //画普通线
    painter->setPen(this->_normal_line_pen);
    painter->drawLines(this->Lines);
    //画粗线
    painter->setPen(this->_dark_line_pen);
    painter->drawLines(this->Dark_Lines);

}


void NodeGraphicsScene::getconfig()
{
    this->_obj = SearchObj(Scene);
    this->_config.BackGround.R = this->_obj["editor_scene_background_color"].toObject()["R"].toInt();
    this->_config.BackGround.G = this->_obj["editor_scene_background_color"].toObject()["G"].toInt();
    this->_config.BackGround.B = this->_obj["editor_scene_background_color"].toObject()["B"].toInt();

    this->_config.Grid_Normal_Line.R = this->_obj["editor_scene_grid_normal_line_color"].toObject()["R"].toInt();
    this->_config.Grid_Normal_Line.G = this->_obj["editor_scene_grid_normal_line_color"].toObject()["G"].toInt();
    this->_config.Grid_Normal_Line.B = this->_obj["editor_scene_grid_normal_line_color"].toObject()["B"].toInt();

    this->_config.Grid_Dark_Line.R = this->_obj["editor_scene_grid_dark_line_color"].toObject()["R"].toInt();
    this->_config.Grid_Dark_Line.G = this->_obj["editor_scene_grid_dark_line_color"].toObject()["G"].toInt();
    this->_config.Grid_Dark_Line.B = this->_obj["editor_scene_grid_dark_line_color"].toObject()["B"].toInt();

    this->_config.Grid_Normal_Line_Width = this->_obj["editor_scene_grid_normal_line_width"].toDouble();
    this->_config.Grid_Dark_Line_Width = this->_obj["editor_scene_grid_dark_line_width"].toDouble();

    this->_config.Grid_Size = this->_obj["editor_grid_size"].toInt();
    this->_config.Chunk_Size = this->_obj["editor_chunk_size"].toInt();

    this->_config.Screen_Width = this->_obj["editor_screen_width"].toInt();
    this->_config.Screen_Height = this->_obj["editor_screen_height"].toInt();

}
