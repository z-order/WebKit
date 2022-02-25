/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestMapLike.h"

#include "ActiveDOMObject.h"
#include "DOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertAny.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMMapLike.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/BuiltinNames.h>
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_get);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_has);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_entries);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_keys);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_values);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_forEach);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_set);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_clear);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_delete);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestMapLikeConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestMapLike_size);

class JSTestMapLikePrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestMapLikePrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestMapLikePrototype* ptr = new (NotNull, JSC::allocateCell<JSTestMapLikePrototype>(vm)) JSTestMapLikePrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestMapLikePrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestMapLikePrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestMapLikePrototype, JSTestMapLikePrototype::Base);

using JSTestMapLikeDOMConstructor = JSDOMConstructorNotConstructable<JSTestMapLike>;

template<> const ClassInfo JSTestMapLikeDOMConstructor::s_info = { "TestMapLike", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLikeDOMConstructor) };

template<> JSValue JSTestMapLikeDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestMapLikeDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestMapLike"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestMapLike::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestMapLikePrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestMapLikeConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "size", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestMapLike_size), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "get", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_get), (intptr_t) (1) } },
    { "has", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_has), (intptr_t) (1) } },
    { "entries", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_entries), (intptr_t) (0) } },
    { "keys", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_keys), (intptr_t) (0) } },
    { "values", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_values), (intptr_t) (0) } },
    { "forEach", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_forEach), (intptr_t) (1) } },
    { "set", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_set), (intptr_t) (2) } },
    { "clear", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_clear), (intptr_t) (0) } },
    { "delete", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikePrototypeFunction_delete), (intptr_t) (1) } },
};

const ClassInfo JSTestMapLikePrototype::s_info = { "TestMapLike", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLikePrototype) };

void JSTestMapLikePrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestMapLike::info(), JSTestMapLikePrototypeTableValues, *this);
    putDirect(vm, vm.propertyNames->iteratorSymbol, getDirect(vm, vm.propertyNames->builtinNames().entriesPublicName()), static_cast<unsigned>(JSC::PropertyAttribute::DontEnum));
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestMapLike::s_info = { "TestMapLike", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLike) };

JSTestMapLike::JSTestMapLike(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestMapLike>&& impl)
    : JSDOMWrapper<TestMapLike>(structure, globalObject, WTFMove(impl))
{
}

void JSTestMapLike::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestMapLike>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSTestMapLike::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestMapLikePrototype::create(vm, &globalObject, JSTestMapLikePrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestMapLike::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestMapLike>(vm, globalObject);
}

JSValue JSTestMapLike::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestMapLikeDOMConstructor, DOMConstructorID::TestMapLike>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestMapLike::destroy(JSC::JSCell* cell)
{
    JSTestMapLike* thisObject = static_cast<JSTestMapLike*>(cell);
    thisObject->JSTestMapLike::~JSTestMapLike();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestMapLikeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestMapLikePrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestMapLike::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSValue jsTestMapLike_sizeGetter(JSGlobalObject& lexicalGlobalObject, JSTestMapLike& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    RELEASE_AND_RETURN(throwScope, (toJS<IDLAny>(lexicalGlobalObject, throwScope, forwardSizeToMapLike(lexicalGlobalObject, thisObject))));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestMapLike_size, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestMapLike>::get<jsTestMapLike_sizeGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_getBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardGetToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_get, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_getBody>(*lexicalGlobalObject, *callFrame, "get");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_hasBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardHasToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_has, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_hasBody>(*lexicalGlobalObject, *callFrame, "has");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_entriesBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardEntriesToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_entries, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_entriesBody>(*lexicalGlobalObject, *callFrame, "entries");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_keysBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardKeysToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_keys, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_keysBody>(*lexicalGlobalObject, *callFrame, "keys");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_valuesBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardValuesToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_values, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_valuesBody>(*lexicalGlobalObject, *callFrame, "values");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_forEachBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto callback = convert<IDLAny>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardForEachToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(callback)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_forEach, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_forEachBody>(*lexicalGlobalObject, *callFrame, "forEach");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_setBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 2))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto value = convert<IDLDOMString>(*lexicalGlobalObject, argument1.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardSetToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key), WTFMove(value)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_set, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_setBody>(*lexicalGlobalObject, *callFrame, "set");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_clearBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardClearToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_clear, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_clearBody>(*lexicalGlobalObject, *callFrame, "clear");
}

static inline JSC::EncodedJSValue jsTestMapLikePrototypeFunction_deleteBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLike>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardDeleteToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikePrototypeFunction_delete, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLike>::call<jsTestMapLikePrototypeFunction_deleteBody>(*lexicalGlobalObject, *callFrame, "delete");
}

JSC::IsoSubspace* JSTestMapLike::subspaceForImpl(JSC::VM& vm)
{
    auto& clientData = *static_cast<JSVMClientData*>(vm.clientData);
    auto& spaces = clientData.subspaces();
    if (auto* space = spaces.m_subspaceForTestMapLike.get())
        return space;
    static_assert(std::is_base_of_v<JSC::JSDestructibleObject, JSTestMapLike> || !JSTestMapLike::needsDestruction);
    if constexpr (std::is_base_of_v<JSC::JSDestructibleObject, JSTestMapLike>)
        spaces.m_subspaceForTestMapLike = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.destructibleObjectHeapCellType(), JSTestMapLike);
    else
        spaces.m_subspaceForTestMapLike = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.cellHeapCellType(), JSTestMapLike);
    auto* space = spaces.m_subspaceForTestMapLike.get();
IGNORE_WARNINGS_BEGIN("unreachable-code")
IGNORE_WARNINGS_BEGIN("tautological-compare")
    void (*myVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSTestMapLike::visitOutputConstraints;
    void (*jsCellVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSC::JSCell::visitOutputConstraints;
    if (myVisitOutputConstraint != jsCellVisitOutputConstraint)
        clientData.outputConstraintSpaces().append(space);
IGNORE_WARNINGS_END
IGNORE_WARNINGS_END
    return space;
}

void JSTestMapLike::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestMapLike*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestMapLikeOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestMapLikeOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestMapLike = static_cast<JSTestMapLike*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestMapLike->wrapped(), jsTestMapLike);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestMapLike@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore11TestMapLikeE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestMapLike>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    const void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestMapLike@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore11TestMapLikeE[2];
#endif

    // If this fails TestMapLike does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestMapLike>::value, "TestMapLike is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestMapLike has subclasses. If TestMapLike has subclasses that get passed
    // to toJS() we currently require TestMapLike you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestMapLike>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestMapLike& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestMapLike* JSTestMapLike::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestMapLike*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}