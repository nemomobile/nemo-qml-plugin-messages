/*
 * Copyright (C) 2012 John Brooks <john.brooks@dereferenced.net>
 * Copyright (C) 2012 Jolla Ltd.
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

#ifndef MESSAGESCONTEXTPROVIDER_H
#define MESSAGESCONTEXTPROVIDER_H

#include <QObject>
#include <QVariantList>
#include "conversationchannel.h"

namespace ContextProvider {
    class Property;
}

/* commhistory-daemon uses contextkit properties to detect the currently visible
 * conversation and prevent notifications. This class should be updated whenever
 * the actively visible conversation changes, including when minimized.
 *
 * This could ideally be replaced with a generic context provider API, but there
 * are complications due to the types used here. */
class MessagesContextProvider : public QObject
{
    Q_OBJECT

public:
    explicit MessagesContextProvider(QObject *parent = 0);

    Q_PROPERTY(QVariantList observedGroups READ observedGroups WRITE updateObservedGroups NOTIFY observedGroupsChanged)
    QVariantList observedGroups() const { return mObservedGroups; }

    Q_PROPERTY(bool observedInbox READ observedInbox WRITE setObservedInbox NOTIFY observedInboxChanged)
    bool observedInbox() const { return mObservedInbox; }
    void setObservedInbox(bool observed);

public slots:
    void updateObservedGroups(const QVariantList &groups);

signals:
    void observedGroupsChanged();
    void observedInboxChanged();

private:
    ContextProvider::Property *propObservedConversation;
    ContextProvider::Property *propObservedInbox;
    QVariantList mObservedGroups;
    bool mObservedInbox;
};

#endif

