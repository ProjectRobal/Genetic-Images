#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

#include <sys/stat.h>

#include "crossover.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir().mkdir("./tmp");

    this->cross=new Crossover<uint8_t>(0,255);

    this->layout=new QGridLayout();

    this->main=new QWidget();

    image=new QLabel();

    image->setMaximumHeight(600);
    image->setMaximumWidth(800);

    score=new QSpinBox();

    score->setMinimum(0);

    go=new QPushButton();

    go->setText("Next");

    this->layout->addWidget(image,0,0);
    this->layout->addWidget(score,1,0);
    this->layout->addWidget(go,2,0);

    this->main->setLayout(this->layout);

    this->setCentralWidget(this->main);

    for(size_t i=0;i<NUMBER_OF_IMAGES;++i)
    {
        this->images[i]=std::make_shared<GenImage>(GenImage("./tmp/tmp"+QString::number(i)+".jpg",800,600));

        if(!this->images[i]->check())
        {
            this->cross->fill(this->images[i]->getData(),this->images[i]->getSize());
            this->images[i]->save_image();
        }
    }

    current_image=this->images.begin();

    this->update_image();

    QObject::connect(this->go,&QPushButton::clicked,this,&MainWindow::on_go_button_click);

}

inline void MainWindow::update_image()
{
    (*this->current_image)->load_image();
    this->image->setPixmap(QPixmap::fromImage((*current_image)->to_img()));
    (*this->current_image)->clear();
}

void MainWindow::Breeding()
{

    std::sort(this->images.begin(),this->images.end(),[](const std::shared_ptr<GenImage>& a,const std::shared_ptr<GenImage>& b)->bool{
        return a->getScore() >= b->getScore();
    });

    size_t i;

    for(i=0;i<NUMBER_OF_IMAGES/4;++i)
    {
        this->images[2*i]->load_image();
        this->images[2*i + 1]->load_image();
        std::vector<uint8_t> childA=this->cross->cross(this->images[2*i]->getData(),this->images[2*i + 1]->getData());
        std::vector<uint8_t> childB=this->cross->cross(this->images[2*i + 1]->getData(),this->images[2*i]->getData());


        std::move(childA.begin(),childA.end(),this->images[2*i]->getData().begin());
        std::move(childB.begin(),childB.end(),this->images[2*i + 1]->getData().begin());
        this->images[2*i]->save_image();
        this->images[2*i + 1]->save_image();

    }

    for(;i<this->images.size();++i)
    {
        this->images[i]->clear();
        this->cross->fill(this->images[i]->getData(),this->images[i]->getSize());
        this->images[i]->save_image();
    }

    for(const auto& img : this->images)
    {
        img->load_image();
        this->cross->mutate(img->getData());
        img->save_image();
    }
}

void MainWindow::on_go_button_click()
{


    (*current_image)->setScore(this->score->value());

    this->current_image++;

    this->score->setValue(0);

    ui->statusbar->showMessage("Images left: "+QString::number(this->images.end()-this->current_image));

    if(current_image==this->images.end())
    {
        // perform crossover and mutation

        ui->statusbar->showMessage("Starts breeding!");

        qDebug()<<"Performing breeding";

        this->Breeding();

        ui->statusbar->showMessage("Breeding performed!");

        this->current_image=this->images.begin();
    }

    this->update_image();
}

MainWindow::~MainWindow()
{
    delete ui;
}

