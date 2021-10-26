#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QObject>
#include <qqml.h>
#include <handler.h>
#include <QThreadPool>


class TextFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(QStringList topWords READ topWords WRITE setTopWords NOTIFY topWordsChanged)
    Q_PROPERTY(QList<QVariant> topValues READ topValues WRITE setTopValues NOTIFY topValuesChanged)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    QML_ELEMENT
    QString m_fileName;
    double m_progress;
    QStringList m_topWords;
    QList<QVariant> m_topValues;
    int m_maxValue;
    void readFile();

public:
    explicit TextFile(QObject *parent = nullptr);
    const QString &fileName() const;
    void setFileName(const QString &newFileName);
    double progress() const;
    void setProgress(double newProgress);
    const QStringList &topWords() const;
    void setTopWords(QStringList &newTopWords);
    void setWords(QStringList top, QList<QVariant> values, int maxValue, double progress);
    const QList<QVariant> &topValues() const;
    void setTopValues(const QList<QVariant> &newTopValues);
    int maxValue() const;
    void setMaxValue(int newMaxValue);

signals:
    void fileNameChanged();
    void progressChanged();
    void topWordsChanged();
    void topValuesChanged();
    void maxValueChanged();
};

#endif // TEXTFILE_H
