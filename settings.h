#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    Settings(bool autoUnlock, bool autoOpen, bool autoClose, QString rootAdr);
    /*const*/ bool autoUnlock;
    /*const*/ bool autoOpen;
    /*const*/ bool autoClose;
    /*const*/ QString rootAdr;
};

#endif // SETTINGS_H
