/*
 * Fedora Media Writer
 * Copyright (C) 2016 Martin Bříza <mbriza@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef WRITEJOB_H
#define WRITEJOB_H

#include <QObject>
#include <QTextStream>
#include <QProcess>
#include <QFile>
#include <QDBusUnixFileDescriptor>

class WriteJob : public QObject
{
    Q_OBJECT
public:
    explicit WriteJob(const QString &what, const QString &where);

    static int staticOnMediaCheckAdvanced(void *data, long long offset, long long total);
    int onMediaCheckAdvanced(long long offset, long long total);

    QDBusUnixFileDescriptor getDescriptor();
    bool write(int fd);
    bool check(int fd);

    // in pages (1024 * 2048 likely)
    const int BUFFER_SIZE { 1024 };
public slots:
    void work();
private:
    QString what;
    QString where;
    QTextStream out { stdout };
    QTextStream err { stderr };

    QProcess *dd { nullptr };
};

#endif // WRITEJOB_H
