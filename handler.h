#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QUrl>
#include <QDebug>
#include <QTextCodec>



class Handler : public QObject, public QRunnable
{
    Q_OBJECT
    QString m_fileName;

public:
    explicit Handler(QString fileName, QObject *parent = nullptr);
    void run();

signals:
    void wordsChanges(QStringList top, QList<QVariant> values, int maxValue, double progress);
};

#endif // HANDLER_H
