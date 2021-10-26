#include "TextFile.h"

TextFile::TextFile(QObject *parent)
    :QObject(parent)
{
}

void TextFile::readFile()
{
    Handler* handler = new Handler( m_fileName );
    QThreadPool::globalInstance()->start( handler );
    QObject::connect(handler, &Handler::wordsChanges, this, &TextFile::setWords);
}

void TextFile::setWords( QStringList top, QList<QVariant> values, int maxValue, double progress)
{
    setMaxValue(maxValue);
    setTopWords(top);
    setTopValues(values);
    setProgress(progress);
}

void TextFile::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
    readFile();
    emit fileNameChanged();
}

const QString &TextFile::fileName() const
{
    return m_fileName;
}

double TextFile::progress() const
{
    return m_progress;
}

void TextFile::setProgress(double newProgress)
{
    if (m_progress == newProgress)
        return;
    m_progress = newProgress;
    emit progressChanged();
}

const QStringList &TextFile::topWords() const
{
    return m_topWords;
}

void TextFile::setTopWords(QStringList &newTopWords)
{
    if (m_topWords == newTopWords)
        return;
    m_topWords = newTopWords;
    emit topWordsChanged();
}

const QList<QVariant> &TextFile::topValues() const
{
    return m_topValues;
}

void TextFile::setTopValues(const QList<QVariant> &newTopValues)
{
    if (m_topValues == newTopValues)
        return;
    m_topValues = newTopValues;
    emit topValuesChanged();
}

int TextFile::maxValue() const
{
    return m_maxValue;
}

void TextFile::setMaxValue(int newMaxValue)
{
    if (m_maxValue == newMaxValue)
        return;
    m_maxValue = newMaxValue;
    emit maxValueChanged();
}
