#include "club-u-display.h"

#include    <QVBoxLayout>
#include    <QLabel>
#include    <QDir>

#include    "CfgReader.h"
#include    "club-u-funcs.h"

#include    "ALSN.h"
#include    "block-top.h"
#include    "block-middle.h"
#include    "block-right.h"
#include    "block-bottom.h"



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ClubUDisplay::ClubUDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
    , updateTimer(Q_NULLPTR)
    , alsn_(Q_NULLPTR)
    , topBlock_(Q_NULLPTR)
    , middleBlock_(Q_NULLPTR)
    , rightBlock_(Q_NULLPTR)
    , bottomBlock_(Q_NULLPTR)
{
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(847, 895);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));

    this->setLayout(new QVBoxLayout);
    this-> setFocusPolicy(Qt::FocusPolicy::NoFocus);

    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout,
            this, &ClubUDisplay::slotUpdateTimer);
    updateTimer->setInterval(1000);
    updateTimer->start();
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ClubUDisplay::~ClubUDisplay()
{

}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::init()
{
    //loadStations();
    initMainWindow();
    initBlocks_();

    this->resize(847, 895);

    AbstractDisplay::init();
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::loadStations()
{
    QString path = QDir::toNativeSeparators(route_dir) +
            QDir::separator() +
            "stations.conf";

    QFile stations_file(path);

    if (stations_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!stations_file.atEnd())
        {
            QByteArray line = stations_file.readLine();
            QStringList tokens = QString(line).remove('\n').split(';');

            if (tokens.size() < 3)
                continue;

            stations.push_back(tokens[2]);
        }
    }
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::initMainWindow()
{
    CfgReader cfg;

    int     sizeWindow_X = 847;
    int     sizeWindow_Y = 895;
    bool    hideCursor = false;
    int     timeInterval = 100;

    if (cfg.load(config_dir + getConfigPath("main.xml")))
    {
        QString sectionName = "Main";
        cfg.getInt(sectionName, "sizeWindow_X", sizeWindow_X);
        cfg.getInt(sectionName, "sizeWindow_Y", sizeWindow_Y);
        cfg.getBool(sectionName, "hideCursor", hideCursor);
        cfg.getInt(sectionName, "timeInterval", timeInterval);        
    }

    this->setCursor( hideCursor ? Qt::BlankCursor : Qt::ArrowCursor);

    /*this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(sizeWindow_X, sizeWindow_Y);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));*/


    QLabel* fon = new QLabel(this);
    fon->setFrameShape(QLabel::NoFrame);
    QPixmap pic;
    if (!pic.load(":/rcc/club-u-fon")) { return; }
    fon->setFixedSize(pic.size());
    fon->setPixmap(pic);
    fon->move(0, 0);

    this->layout()->addWidget(fon);
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::initBlocks_()
{
    // пусть к конфигам
    QString cfg_path = config_dir + getConfigPath("");


    // Фоновый виджет
    QLabel* fon = new QLabel(this);
    fon->setFrameShape(QLabel::NoFrame);
    QPixmap pic;
    if (!pic.load(":/rcc/club-u-fon")) { return; }
    fon->setFixedSize(pic.size());
    //fon->setGeometry(0,0, pic.size().width(), pic.size().height());
    fon->setPixmap(pic);
    fon->move(0, 0);
    //fon->setStyleSheet("border: 2px solid red");
    this->layout()->addWidget(fon);


    // Локомотивный светофор
    alsn_ = new ALSN(QSize(98,350), fon);
    alsn_->move(70, 242);
    this->layout()->addWidget(alsn_);

    // Верхний блок
    topBlock_ = new TopBlock(QSize(670, 135), fon);
    topBlock_->move(90, 60);

    // Центральный блок
    middleBlock_ = new MiddleBlock(QSize(330, 330), cfg_path, fon);
    middleBlock_->move(225, 240);
    this->layout()->addWidget(topBlock_);

    // Правый блок
    rightBlock_ = new RightBlock(QSize(155, 372), fon);
    rightBlock_->move(622, 215);
    this->layout()->addWidget(rightBlock_);

    // Нижний блок
    bottomBlock_ = new BottomBlock(QSize(585, 30), fon);
    bottomBlock_->move(133, 622);
    this->layout()->addWidget(bottomBlock_);
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::slotUpdateTimer()
{
//    structs_CLUB_U.wasSendData = false;

    alsn_->setSignal(ALSN_COLORS::GREEN);

    topBlock_->setBditelnost(true);
    topBlock_->setCassete(true);
    topBlock_->setIndM(true);
    topBlock_->setIndP(true);
    topBlock_->setCoordinate(102.9);
    topBlock_->setStationName("Станция");

    middleBlock_->setCurSpeed(62);
    middleBlock_->setCurSpeedLimit(81);
    middleBlock_->setNextSpeedLimit(39);
    middleBlock_->setReverse(1);

    rightBlock_->setPressureTM(0.56);
    rightBlock_->setPressureUR(0.58);
    rightBlock_->setNumTrack("1нп");
    rightBlock_->setAcceleration(0.7);

    bottomBlock_->setDistToTarget(78);
    bottomBlock_->setTargetName("чм2а");    
}



GET_DISPLAY(ClubUDisplay)
