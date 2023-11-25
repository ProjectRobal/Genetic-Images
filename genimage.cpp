#include <QImage>
#include <QColor>
#include <QFile>

#include "genimage.h"


GenImage::GenImage(QString link,std::size_t width,std::size_t height)
{
    this->link=link;
    this->width=width;
    this->height=height;
}

QImage GenImage::to_img()
{
    QImage img(this->width,this->height,QImage::Format_RGB888);

    img.fill(0);

    for(size_t y=0;y<this->height;++y)
    {
        for(size_t x=0;x<this->width;++x)
        {
            size_t index=y*this->width*3 + x*3;

            img.setPixel(x,y,qRgb(this->data[index],this->data[index+1],this->data[index+2]));
        }
    }

    return img;
}

bool GenImage::check()
{
    return QFile::exists(this->link);
}

bool GenImage::load_image()
{

    QImage img;

    if(img.load(this->link))
    {
        img=img.scaled(this->width,this->height,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);

        for(size_t y=0;y<this->height;++y)
        {
            for(size_t x=0;x<this->width;++x)
            {
                data.push_back(img.pixelColor(x,y).red());
                data.push_back(img.pixelColor(x,y).green());
                data.push_back(img.pixelColor(x,y).blue());
            }
        }

        return true;
    }

    return false;
}

bool GenImage::save_image()
{


    QImage img=this->to_img();

    img.save(this->link);

    this->data.clear();

    return true;

}
