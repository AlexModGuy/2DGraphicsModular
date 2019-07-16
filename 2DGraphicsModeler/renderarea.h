#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QObject>
#include <QWidget>
#include "shape.h"
#include "line.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include "square.h"
#include "vector.h"
#include "text.h"
#include <vector>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    void createShapeBuffer(QTextStream&);

    bool testValue = true;
protected:
    void transferToShapes();
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:
private:
    std::vector<ShapeBuffer> buffer;
    std::vector<Shape*> shapeVector;
    bool shapeBufferReady = false;
};

#endif // RENDERAREA_H
