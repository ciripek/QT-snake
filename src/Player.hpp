#pragma once

#include <QDebug>
#include <QString>

struct Player{
    friend QDebug operator<<(QDebug stream, const Player &player) {
        stream << "Player(name: " << player.name << "- score:" << player.score << ")";
        return stream;
    }

    QString name;
    int score = 0;
};