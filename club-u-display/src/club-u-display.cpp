#include "club-u-display.h"

#include    <QVBoxLayout>
#include    <QDir>
#include    <QLabel>

#include    "CfgReader.h"



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ClubUDisplay::ClubUDisplay(QWidget *parent, Qt::WindowFlags f)
    : AbstractDisplay(parent, f)
    , updateTimer(Q_NULLPTR)
    , alsn_(Q_NULLPTR)
    , topBlock_(Q_NULLPTR)
    , middleBlock_(Q_NULLPTR)
{
    this->setLayout(new QVBoxLayout);
    this-> setFocusPolicy(Qt::FocusPolicy::NoFocus);
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
    loadStations();
    initMainWindow();
    initBlocks_();

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

    if (cfg.load(config_dir + getCfgPath("main.xml")))
    {
        QString sectionName = "Main";
        cfg.getInt(sectionName, "sizeWindow_X", sizeWindow_X);
        cfg.getInt(sectionName, "sizeWindow_Y", sizeWindow_Y);
        cfg.getBool(sectionName, "hideCursor", hideCursor);
        cfg.getInt(sectionName, "timeInterval", timeInterval);
    }

    this->setCursor( hideCursor ? Qt::BlankCursor : Qt::ArrowCursor);

    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    this->resize(sizeWindow_X, sizeWindow_Y);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(0, 0, 0)));

    //
    QLabel* fon = new QLabel(this);
    fon->setFrameShape(QLabel::NoFrame);
    QPixmap pic;
    if (!pic.load(":/rcc/club-u-fon")) { return; }
    fon->setFixedSize(pic.size());
    fon->setPixmap(pic);
    fon->move(0, 0);


    //
    updateTimer = new QTimer;
    connect(updateTimer, &QTimer::timeout,
            this, &ClubUDisplay::slotUpdateTimer, Qt::QueuedConnection);
    updateTimer->setInterval(timeInterval);
    updateTimer->start();
}

void ClubUDisplay::initBlocks_()
{
    // Локомотивный светофор
    alsn_ = new ALSN(QSize(98,350), this);
    alsn_->move(70, 242);
    alsn_->setSignal(ALSN_COLORS::GREEN);

    // Верхний блок
    topBlock_ = new TopBlock(QSize(670, 135), this);
    topBlock_->move(90, 60);
    //this->layout()->addWidget(topBlock_);

    // Центральный блок
    middleBlock_ = new MiddleBlock(QSize(330, 330), this);
    middleBlock_->move(225, 240);
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString ClubUDisplay::getCfgPath(QString cfgName)
{
    return QDir::separator() + QString("CLUB-U") + QDir::separator() + cfgName;
}



//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ClubUDisplay::slotUpdateTimer()
{
    //structs_CLUB_U.wasSendData = false;
}



GET_DISPLAY(ClubUDisplay)