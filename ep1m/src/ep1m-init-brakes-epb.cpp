#include    "filesystem.h"

#include    "ep1m.h"

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void EP1m::initEPB(QString modules_dir)
{
    Q_UNUSED(modules_dir)

    // Преобразователь напряжения для ЭПТ
    epb_converter = new EPBConverter();
    epb_converter->read_config("epb-converter-55V");

    // Контроллер двухпроводного ЭПТ
    epb_control = new EPBControl();
}
