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

#include "declarativeaccount.h"

DeclarativeAccount::DeclarativeAccount(const Tp::AccountPtr &a, QObject *parent)
    : QObject(parent), account(a)
{
    connect(a.data(), SIGNAL(onlinenessChanged(bool)), SIGNAL(onlineChanged()));
    connect(a.data(), SIGNAL(connectionStatusChanged(Tp::ConnectionStatus)), SIGNAL(connectionStatusChanged()));
    connect(a.data(), SIGNAL(displayNameChanged(QString)), SIGNAL(displayNameChanged()));
}

QString DeclarativeAccount::localUid() const
{
    return account->objectPath();
}

QString DeclarativeAccount::displayName() const
{
    return account->displayName();
}

bool DeclarativeAccount::online() const
{
    return account->isOnline();
}

DeclarativeAccount::ConnectionStatus DeclarativeAccount::connectionStatus() const
{
    return static_cast<DeclarativeAccount::ConnectionStatus>(account->connectionStatus());
}

DeclarativeAccount::ConnectionStatusReason DeclarativeAccount::connectionStatusReason() const
{
    switch (account->connectionStatusReason()) {
        case Tp::ConnectionStatusReasonNoneSpecified:
            return ReasonNoneSpecified;
        case Tp::ConnectionStatusReasonRequested:
            return ReasonRequested;
        case Tp::ConnectionStatusReasonNetworkError:
            return ReasonNetworkError;
        case Tp::ConnectionStatusReasonAuthenticationFailed:
            return ReasonAuthenticationFailed;
        case Tp::ConnectionStatusReasonEncryptionError:
        case Tp::ConnectionStatusReasonCertNotProvided:
        case Tp::ConnectionStatusReasonCertUntrusted:
        case Tp::ConnectionStatusReasonCertExpired:
        case Tp::ConnectionStatusReasonCertNotActivated:
        case Tp::ConnectionStatusReasonCertHostnameMismatch:
        case Tp::ConnectionStatusReasonCertFingerprintMismatch:
        case Tp::ConnectionStatusReasonCertSelfSigned:
        case Tp::ConnectionStatusReasonCertOtherError:
        case Tp::ConnectionStatusReasonCertRevoked:
        case Tp::ConnectionStatusReasonCertInsecure:
        case Tp::ConnectionStatusReasonCertLimitExceeded:
            return ReasonEncryptionError;
        default:
            return ReasonNoneSpecified;
    }
}

QString DeclarativeAccount::connectionError() const
{
    return account->connectionError();
}

