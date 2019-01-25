#ifndef GUARD_IOHANDLER_H
#define GUARD_IOHANDLER_H

#include <QString>
#include <QVector>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QImageIOHandler>

#include "image.h"



void WARN(QString message);

void deleteFile(QString path);

QVector<QString> readTextFileLines(QString path);
QString readTextFile(QString path);
void saveTextFile(QString path, QString text);
void appendTextFile(QString path, QString text);

QVector<QColor> parseJASCPal(QString path);
void saveJASCPal(QString path, QVector<QColor>);

Image readImageFromPng(QString path);
void saveImageToPng(QString path, Image image);

#endif // GUARD_IOHANDLER_H
