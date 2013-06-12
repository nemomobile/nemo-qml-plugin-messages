/* Copyright (C) 2012 John Brooks <john.brooks@dereferenced.net>
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

#include "messagescontextprovider.h"

/* ContextProvider is not available for Qt5. This will need to be refactored
 * to use statefs or some other method along with commhistory-daemon. */
#ifdef HAVE_CONTEXTKIT
#include <ContextProvider>
#endif

MessagesContextProvider::MessagesContextProvider(QObject *parent)
    : QObject(parent), mObservedInbox(false)
{
#ifdef HAVE_CONTEXTKIT
    ContextProvider::Service *cpService = new ContextProvider::Service(QDBusConnection::SessionBus,
            "org.nemomobile.qmlmessages.context", this);

    propObservedConversation = new ContextProvider::Property(*cpService, "Messaging.ObservedConversation",
            this);
    if (propObservedConversation && propObservedConversation->isSet())
        propObservedConversation->unsetValue();

    propObservedInbox = new ContextProvider::Property(*cpService, "Messaging.ObservedInbox", this);
    if (propObservedInbox && propObservedInbox->isSet())
        propObservedInbox->unsetValue();
#endif
}

void MessagesContextProvider::updateObservedGroups(const QVariantList &groups)
{
#ifdef HAVE_CONTEXTKIT
    mObservedGroups = groups;
    emit observedGroupsChanged();

    QVariantList observed;

    foreach (const QVariant &value, groups) {
        QObject *group = value.value<QObject*>();
        if (!group)
            continue;

        QString localUid = group->property("localUid").toString();
        QString remoteUid = group->property("remoteUids").toStringList().value(0);
        if (!localUid.isEmpty() && !remoteUid.isEmpty()) {
            // 0 is CommHistory::Group::ChatTypeP2P
            observed << QVariant(QVariantList() << localUid << remoteUid << 0);
        }
    }

    if (!observed.isEmpty())
        propObservedConversation->setValue(observed);
    else
        propObservedConversation->unsetValue();
#else
    qWarning() << Q_FUNC_INFO << "Not implemented";
#endif
}

void MessagesContextProvider::setObservedInbox(bool observed)
{
#ifdef HAVE_CONTEXTKIT
    if (mObservedInbox == observed)
        return;

    mObservedInbox = observed;
    emit observedInboxChanged();

    propObservedInbox->setValue(observed);
#else
    qWarning() << Q_FUNC_INFO << "Not implemented";
#endif
}

