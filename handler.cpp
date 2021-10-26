#include "handler.h"

Handler::Handler(QString fileName, QObject *parent)
    : QObject(parent)
    , m_fileName(fileName)
{

}

void Handler::run()
{
    QUrl url(m_fileName);
    QFile file(url.toLocalFile());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList list;
    QMap<QString, int> words;
    while (!file.atEnd()) {
        QString line = QTextCodec::codecForName("UTF-8")->toUnicode(file.readLine()).toLower();
        list.append(line.split(QRegExp("\\W+"), Qt::SkipEmptyParts));
        if(list.size() > 20000 || file.atEnd()) {
            for (QString word : list)
                words[word]++;

            typedef QMap<QString,int>::const_iterator Iterator ;

            Iterator i = words.constBegin();
            QVector<Iterator> vec;
            while(i != words.end())
                vec.append(i++);

            //Сортировка по числу вхождений
            std::sort(vec.begin(), vec.end(), [] (Iterator a, Iterator b) {
                return a.value() > b.value();
            });

            //Топ 15
            vec.resize(vec.size() < 15 ? vec.size() : 15);

            int maxValue = vec[0].value();

            //Сортировка по алфавиту
            std::sort(vec.begin(), vec.end(), [] (Iterator a, Iterator b) {
                return a.key() < b.key();
            });

            QStringList topWords;
            QList<QVariant> topValues;
            for(Iterator i: vec){
                topWords << i.key();
                topValues << i .value();
            }
            emit wordsChanges(topWords, topValues, maxValue, (double)file.pos() / (double)file.size());
            list.clear();
        }
    }
}

