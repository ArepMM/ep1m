#include    "ep1m.h"

#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EP1m::initSafetyDevices(const QString &modules_dir, const QString &custom_cfg_dir)
{
    (void) modules_dir;
    (void) custom_cfg_dir;

    klub_BEL = new KLUB();
    klub_BEL->setMaxVelocity(140.0);
    klub_BEL->setDirection(dir * orient);
    klub_BEL->setTrainLength(length);

    FileSystem &fs = FileSystem::getInstance();
    QString route_path = fs.getRouteRootDir().c_str();
    route_path += QDir::separator() + route_dir;

    // Загрузка электронной карты в КЛУБ
    QString speeds_name = "speeds";

    if (dir > 0)
        speeds_name += "1";
    else
        speeds_name += "2";

    QString path = route_path + QDir::separator() + speeds_name + ".conf";
    klub_BEL->loadSpeedsMap(path);

    // Загрузка станций в КЛУБ
    path = route_path + QDir::separator() + "stations.conf";
    klub_BEL->loadStationsMap(path);
}
