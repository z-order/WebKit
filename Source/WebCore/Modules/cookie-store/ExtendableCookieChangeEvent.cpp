/*
 * Copyright (C) 2023 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ExtendableCookieChangeEvent.h"

#if ENABLE(SERVICE_WORKER)

#include "CookieListItem.h"
#include "ExtendableCookieChangeEventInit.h"
#include <wtf/IsoMallocInlines.h>
#include <wtf/Ref.h>
#include <wtf/Vector.h>

namespace WebCore {

WTF_MAKE_ISO_ALLOCATED_IMPL(ExtendableCookieChangeEvent);

Ref<ExtendableCookieChangeEvent> ExtendableCookieChangeEvent::create(const AtomString& type, ExtendableCookieChangeEventInit&& eventInitDict, IsTrusted isTrusted)
{
    return adoptRef(*new ExtendableCookieChangeEvent(type, WTFMove(eventInitDict), isTrusted));
}

ExtendableCookieChangeEvent::ExtendableCookieChangeEvent(const AtomString& type, ExtendableCookieChangeEventInit&& eventInitDict, IsTrusted isTrusted)
    : ExtendableEvent(type, eventInitDict, isTrusted)
    , m_changed(WTFMove(eventInitDict.changed))
    , m_deleted(WTFMove(eventInitDict.deleted))
{ }

ExtendableCookieChangeEvent::~ExtendableCookieChangeEvent() = default;

EventInterface ExtendableCookieChangeEvent::eventInterface() const
{
    return ExtendableCookieChangeEventInterfaceType;
}

} // namespace WebCore

#endif // ENABLE(SERVICE_WORKER)
