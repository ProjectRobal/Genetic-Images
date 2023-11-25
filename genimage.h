#ifndef GENIMAGE_H
#define GENIMAGE_H

#include <QString>
#include <QImage>

class GenImage
{
    QString link;
    std::size_t width;
    std::size_t height;
    uint32_t score;
    std::vector<uint8_t> data;

public:
    GenImage(QString link,std::size_t width,std::size_t height);

    bool load_image();

    bool check();

    bool save_image();

    QImage to_img();

    void clear()
    {
        this->data.clear();
    }

    const uint32_t& getScore() const
    {
        return this->score;
    }

    void setScore(const uint32_t& score)
    {
        this->score=score;
    }

    size_t getSize() const
    {
        return this->width*this->height*3;
    }

    std::vector<uint8_t>& getData()
    {
        return this->data;
    }

    operator std::vector<uint8_t>&()
    {
        return data;
    }

    operator const std::vector<uint8_t>&()
    {
        return data;
    }
};

#endif // GENIMAGE_H
