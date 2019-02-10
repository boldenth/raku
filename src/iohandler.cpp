#include "iohandler.h"

#include <QRegularExpression>

void WARN(QString message) {
    qDebug().nospace() << message;
}

void deleteFile(QString path) {
    QFile file(path);
    if (file.exists() && !file.remove()) {
        WARN(QString("Could not delete file '%1': ").arg(path) + file.errorString());
    }
}

QVector<QString> readTextFileLines(QString path) {
    QVector<QString> lines;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        WARN(QString("Could not open file '%1': ").arg(path) + file.errorString());
    } else {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }
    }
    return lines;
}

QString readTextFile(QString path) {
    QString text = QString();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        WARN(QString("Could not open file '%1': ").arg(path) + file.errorString());
    } else {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            text += in.readLine() + "\n";
        }
    }
    return text;
}

void saveTextFile(QString path, QString text) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(text.toUtf8());
    } else {
        WARN(QString("Could not write to file '%1': ").arg(path) + file.errorString());
    }
}

void appendTextFile(QString path, QString text) {
    QFile file(path);
    if (file.open(QIODevice::Append)) {
        file.write(text.toUtf8());
    } else {
        WARN(QString("Could not append to file '%1': ").arg(path) + file.errorString());
    }
}

QVector<QColor> parseJASCPal(QString path) {
    QVector<QColor> palette = QVector<QColor>();
    QVector<QColor> emptyPalette = QVector<QColor>();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        WARN(QString("Could not open the JASC palette file '%1': ").arg(path) + file.errorString());
        return emptyPalette;
    }

    QTextStream in(&file);
    if (in.readLine() != "JASC-PAL" || in.readLine() != "0100") {
        WARN(QString("The JASC palette file '%1' had an invalid format. The first two lines must be 'JASC-PAL' and '0100'.").arg(path));
        file.close();
        return emptyPalette;
    }

    QString numColorsString = in.readLine();
    bool ok;
    int nColors = numColorsString.toInt(&ok);
    if (!ok) {
        WARN(QString("The JASC palette file '%1' had an invalid format. The third line must be the number of colors.").arg(path));
        file.close();
        return emptyPalette;
    }

    QRegularExpression re("(?<red>\\d+)\\s(?<green>\\d+)\\s(?<blue>\\d+)");
    while (!in.atEnd() && --nColors > -1) {
        QString line = in.readLine();
        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            QString redStr = match.captured("red");
            QString greenStr = match.captured("green");
            QString blueStr = match.captured("blue");
            bool redOK, greenOK, blueOK;
            int r = redStr.toInt(&redOK);
            int g = greenStr.toInt(&greenOK);
            int b = blueStr.toInt(&blueOK);
            if (!redOK || !greenOK || !blueOK) {
                WARN(QString("The JASC palette file '%1' had an invalid format. There is an invalid color on this line: '%2'.").arg(path).arg(line));
                return emptyPalette;
            }
            // range of valid values is [0,255]
            palette.append(QColor(r < 0 ? 0 : (r > 255 ? r : 255),
                                  g < 0 ? 0 : (g > 255 ? g : 255),
                                  b < 0 ? 0 : (b > 255 ? b : 255)));
        } else {
            WARN(QString("JASC palette file '%1' had an invalid format. Invalid color '%2'.").arg(path).arg(line));
            file.close();
            return emptyPalette;
        }
    }

    file.close();
    return palette;
}

void saveJASCPal(QString path, QVector<QColor> palette) {
    int nColors = palette.size();
    if (!nColors) {
        WARN(QString("Cannot save a palette with no colors."));
        return;
    }

    QString text = "JASC-PAL\n0100\n";
    text += QString::number(nColors) + "\n";

    for (QColor color : palette) {
        text += QString::number(color.red()) + " "
              + QString::number(color.green()) + " "
              + QString::number(color.blue()) + "\n";
    }

    saveTextFile(path, text);
}
