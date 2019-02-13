#ifndef SETTINGS_H
#define SETTINGS_H

#include <QCursor>

class Settings
{
public:
    Settings();

    QCursor cursor;
};

extern Settings GlobalSettings;

#endif // SETTINGS_H
