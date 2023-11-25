#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>

#include "genimage.h"
#include "crossover.h"

#define NUMBER_OF_IMAGES 10

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *go;
    QSpinBox *score;
    QLabel *image;
    QGridLayout *layout;

    QWidget* main;

    std::array<std::shared_ptr<GenImage>,NUMBER_OF_IMAGES> images;

    std::array<std::shared_ptr<GenImage>,NUMBER_OF_IMAGES>::iterator current_image;

    Crossover<uint8_t> *cross;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    inline void update_image();

    void Breeding();

public slots:

    void on_go_button_click();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
