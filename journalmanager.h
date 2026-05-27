#ifndef JOURNALMANAGER_H
#define JOURNALMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QVector>
#include <QString>

struct JournalEntry {
    QDateTime timestamp;
    int sourceHexagram;      // e.g., 23 (0 if not applicable)
    int modifiedHexagram;    // e.g., 44 (0 if no change)
    QString deckName;        // e.g., "Classic IChing", "Modern" (can be empty)
    QString filePath;        // Full path to .json file (empty if manual note)
    QString notes;           // User's journal text
};
class JournalManager : public QObject
{
    Q_OBJECT

public:
    static JournalManager& instance();
    //void addEntry(const QString& spreadType, const QString& deckName, const QString& filePath, const QString& notes);
    void addEntry(int sourceHexagram, int modifiedHexagram,
                                  const QString& deckName,
                                  const QString& filePath, const QString& notes);

    QVector<JournalEntry> getEntries() const;
    QVector<JournalEntry> getEntriesForDate(const QDate& date) const;
    void clearAll();
    void addEntry(const JournalEntry& entry);
    void deleteEntriesForDate(const QDate& date);

private:
    JournalManager(QObject* parent = nullptr);
    void load();
    void save();
    
    QVector<JournalEntry> m_entries;
    QString getFilePath() const;

};

#endif
