#pragma once

#include <QSqlDatabase>
#include <QString>

#include <array>

#include "Player.hpp"

class Database {
public:
    explicit Database(const QString &path);

    void savePlayer(const Player& player);

    std::array<Player, 10> getTopTenPlayer();
private:
    QSqlDatabase m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
};