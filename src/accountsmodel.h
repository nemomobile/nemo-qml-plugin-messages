/* Copyright (C) 2012 John Brooks <john.brooks@dereferenced.net>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ACCOUNTSMODEL_H
#define ACCOUNTSMODEL_H

#include <QAbstractListModel>
#include <TelepathyQt/Types>
#include <TelepathyQt/AccountManager>

class ConversationChannel;

class AccountsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)

    // Hack necessary for SelectionDialog in AccountSelector.qml.
    // The Qt Components dialog expects the model to have a count
    // property, and won't show any items if it doesn't.
    Q_PROPERTY(int count READ count NOTIFY countChanged);
    Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged);

public:
    enum Roles {
        AccountPtrRole = Qt::UserRole,
        AccountUidRole
    };

    AccountsModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;

    Q_INVOKABLE QVariant get(int row, int role = Qt::DisplayRole) const
    {
        return data(index(row, 0), role);
    }

    Q_INVOKABLE QVariant get(const QString &uid, int role = Qt::DisplayRole) const
    {
        return get(indexOfAccount(uid), role);
    }

    Q_INVOKABLE int indexOfAccount(const QString &localUid) const;

    int count() const { return rowCount(); }
    bool isReady() const { return mReady; }

signals:
    void countChanged();
    void readyChanged();

private slots:
    void accountManagerReady(Tp::PendingOperation *op);
    void newAccount(const Tp::AccountPtr &account);

private:
    Tp::AccountManagerPtr mAccountManager;
    QList<Tp::AccountPtr> mAccounts;
    bool mReady;
};

#endif

