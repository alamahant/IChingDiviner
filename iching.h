#ifndef ICHING_H
#define ICHING_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include<QDateTime>
#include<QPoint>
#include<QCryptographicHash>
#include<QMap>
#include<QRandomGenerator>

/*
struct HexagramInfo {
    QString number;
    QString symbol;
    QString name;
    QString description;
    QString chineseName;
    QString pinyin;
    QString binary;
};
*/

struct WilhelmTrigram {
    QString chinese;
    QString symbolic;
    QString alchemical;
};

// Then the text struct (can be used for judgment and image)
struct WilhelmText {
    QString text;
    QString comments;
};

// Then the line struct
struct WilhelmLine {
    QString text;
    QString comments;
};

struct HexagramInfo {
    QString number;
    QString symbol;
    QString name;
    QString chineseName;
    QString pinyin;
    QString binary;
    QString description;           // wilhelm_symbolic
    WilhelmText judgment;          // wilhelm_judgment
    WilhelmText image;             // wilhelm_image
    QMap<int, WilhelmLine> lines;  // wilhelm_lines 1..6
    WilhelmTrigram above;          // wilhelm_above
    WilhelmTrigram below;          // wilhelm_below
};

class IChing : public QObject
{
    Q_OBJECT
public:
    explicit IChing(QObject *parent = nullptr);
    QList<QList<int>> performFullDivination();
    QList<int> performSingleToss();
    void reset();
    void loadHexagramData(const QString &filePath);
    HexagramInfo getHexagramFromBinary(const QString &binary);

    // Added missing methods
    HexagramInfo getSourceHexagram();
    HexagramInfo getModifiedHexagram();
    QStringList getCurrentLines();
    QStringList getModifiedLines();
    QString getResultingBinary(); // after changing lines
    QList<QString> currentLines;

private:
    void parseHexagrams(const QString &rawData);
    QString rawData;
    QList<HexagramInfo> hexagrams;

    // Add to IChing class
    QRandomGenerator randomGen;

public:
    QMap<int, char32_t> hexNumberToUnicode;
    void parseHexagramsFromJson(const QString &filePath);
    QList<int> getChangingLinePositions();
    void generateSeed();
    QList<qint64> entropyData;



};

#endif // ICHING_H
