#ifndef SHAPE_H
#define SHAPE_H
#include <Qt>
#include <QFont>
#include <QPainter>
#include "vector.h"
#include <cmath>
#include "shapebuffer.h"

const std::string SHAPE_IDENTIFIERS[] = {"LINE", "POLYLINE", "POLYGON", "RECTANGLE", "ELIPSE", "TEXT"};

class Shape
{
public:
    Shape() = delete;
    Shape(QPaintDevice* parent);
    Shape(QPaintDevice* parent, ShapeType arg, Qt::GlobalColor gc1, double width,\
          Qt::PenStyle ps, Qt::PenCapStyle pcs, Qt::PenJoinStyle pjs,\
          Qt::GlobalColor gc2, Qt::BrushStyle bs);
    Shape(QPaintDevice *parent, ShapeType arg,\
          QPen rhsPen, QBrush rhsBrush);
    Shape(QPaintDevice *parent, const ShapeBuffer& buffer);

    Shape(Shape&) = delete;
    Shape& operator =(Shape&)= delete;

    virtual ~Shape();

    ShapeType getShape() const;
    const QBrush& getBrush()const;
    const QPen& getPen()const;


    void setShape(ShapeType arg);
    void setPen(Qt::GlobalColor gc1, int width,\
                 Qt::PenStyle ps, Qt::PenCapStyle pcs, Qt::PenJoinStyle pjs);
    void setBrush(Qt::GlobalColor gc2, Qt::BrushStyle bs);

    void defaultStyle();

    virtual void write(std::ostream& os);
    virtual void read(std::istream& is);

    virtual void draw(const int x, const int y) = 0;
   // virtual void draw(QPaintDevice*)=0;

    virtual void move(const int x,const int y) = 0;
    virtual double area() const = 0;
    virtual double perimeter() const =0;
protected:
    QPainter& getQPainter();


private:
    ShapeType getShapeFromString(std::string str);
    QPainter painter;
    int shapeId;
    ShapeType shape;
    QPen pen;
    QBrush brush;
};

#endif // SHAPE_H
