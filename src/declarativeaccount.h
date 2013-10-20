/* Copyright (C) 2013 Jolla Ltd.
 * Contact: John Brooks <john.brooks@jollamobile.com>
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

#ifndef DECLARATIVEACCOUNT_H
#define DECLARATIVEACCOUNT_H

#include <QObject>
#include <TelepathyQt/Account>

class DeclarativeAccount : public QObject
{
    Q_OBJECT
    Q_ENUMS(ConnectionStatus ConnectionStatusReason)

    Q_PROPERTY(QString localUid READ localUid CONSTANT)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    Q_PROPERTY(bool online READ online NOTIFY onlineChanged)
    Q_PROPERTY(ConnectionStatus connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)
    Q_PROPERTY(ConnectionStatusReason connectionStatusReason READ connectionStatusReason NOTIFY connectionStatusChanged)
    Q_PROPERTY(QString connectionError READ connectionError NOTIFY connectionStatusChanged)

public:
    enum ConnectionStatus {
        Connected = Tp::ConnectionStatusConnected,
        Connecting = Tp::ConnectionStatusConnecting,
        Disconnected = Tp::ConnectionStatusDisconnected
    };

    // Incomplete mapping; other values are converted to one of these choices.
    enum ConnectionStatusReason {
        ReasonNoneSpecified = Tp::ConnectionStatusReasonNoneSpecified,
        ReasonRequested = Tp::ConnectionStatusReasonRequested,
        ReasonNetworkError = Tp::ConnectionStatusReasonNetworkError,
        ReasonAuthenticationFailed = Tp::ConnectionStatusReasonAuthenticationFailed,
        ReasonEncryptionError = Tp::ConnectionStatusReasonEncryptionError
    };

    DeclarativeAccount(const Tp::AccountPtr &account, QObject *parent = 0);

    QString localUid() const;
    QString displayName() const;
    bool online() const;
    ConnectionStatus connectionStatus() const;
    ConnectionStatusReason connectionStatusReason() const;
    QString connectionError() const;

signals:
    void displayNameChanged();
    void onlineChanged();
    void connectionStatusChanged();

private:
    Tp::AccountPtr account;
};

#endif
