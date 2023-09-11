#include "Database.hpp"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>



Database::Database(const QString &path) {
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
    const QSqlQuery query(QStringLiteral("CREATE TABLE IF NOT EXISTS Scores( name VARCHAR(255) PRIMARY KEY, score INT NOT NULL);"));
}

void Database::savePlayer(const Player &player) {
    QSqlQuery query;
    query.prepare(QStringLiteral("INSERT INTO Scores (name, score) VALUES (:name_holder, :score_holder) ON CONFLICT(name) DO UPDATE SET score = max (:score_holder, score);"));
    query.bindValue(QStringLiteral(":name_holder"), player.name);
    query.bindValue(QStringLiteral(":score_holder"), player.score);

    qDebug() << "NamedPlaceholders: " << m_db.driver()->hasFeature(QSqlDriver::NamedPlaceholders);
    qDebug() << "PositionalPlaceholders: " << m_db.driver()->hasFeature(QSqlDriver::PositionalPlaceholders);
    qDebug() << query.boundValue(QStringLiteral(":name_holder"));
    qDebug() << query.boundValue(QStringLiteral(":score_holder"));
    query.exec();
    qDebug() << query.executedQuery();
}

std::array<Player, 10> Database::getTopTenPlayer() {
    QSqlQuery query(QStringLiteral("SELECT name, score FROM Scores ORDER BY score DESC LIMIT 10"));
    std::array<Player, 10> arr{};
    for (int i = 0; query.next(); ++i) {
        arr[i] = {
                .name = query.value(0).toString(),
                .score = query.value(1).toInt()
        };
    }
    return arr;
}
