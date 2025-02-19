//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// SyncVk:
//    Defines the class interface for SyncVk, implementing SyncImpl.
//

#ifndef LIBANGLE_RENDERER_VULKAN_FENCESYNCVK_H_
#define LIBANGLE_RENDERER_VULKAN_FENCESYNCVK_H_

#include "libANGLE/renderer/EGLSyncImpl.h"
#include "libANGLE/renderer/SyncImpl.h"
#include "libANGLE/renderer/vulkan/ResourceVk.h"

namespace egl
{
class AttributeMap;
}

namespace rx
{
namespace vk
{

// Represents an invalid native fence FD.
constexpr int kInvalidFenceFd = EGL_NO_NATIVE_FENCE_FD_ANDROID;

class ExternalFence final : angle::NonCopyable
{
  public:
    ExternalFence();
    ~ExternalFence();

    VkResult init(VkDevice device, const VkFenceCreateInfo &createInfo);
    void init(int fenceFd);

    VkFence getHandle() const { return mFence.getHandle(); }
    VkResult getStatus(VkDevice device) const;
    VkResult wait(VkDevice device, uint64_t timeout) const;

    void exportFd(VkDevice device, const VkFenceGetFdInfoKHR &fenceGetFdInfo);
    VkResult getFenceFdStatus() const { return mFenceFdStatus; }
    int getFenceFd() const { return mFenceFd; }

  private:
    VkDevice mDevice;
    Fence mFence;
    VkResult mFenceFdStatus;
    int mFenceFd;
};

using SharedExternalFence  = std::shared_ptr<ExternalFence>;
using MapVkResultToApiType = std::function<void(VkResult, angle::Result, void *)>;

class SyncHelperInterface : angle::NonCopyable
{
  public:
    virtual ~SyncHelperInterface() = default;

    virtual void releaseToRenderer(RendererVk *renderer) = 0;

    virtual angle::Result clientWait(Context *context,
                                     ContextVk *contextVk,
                                     bool flushCommands,
                                     uint64_t timeout,
                                     VkResult *outResult)                                      = 0;
    virtual angle::Result clientWaitUnlocked(Context *context,
                                             ContextVk *contextVk,
                                             bool flushCommands,
                                             uint64_t timeout,
                                             void *outResult,
                                             MapVkResultToApiType mappingFunction)             = 0;
    virtual angle::Result serverWait(ContextVk *contextVk)                                     = 0;
    virtual angle::Result getStatus(Context *context, ContextVk *contextVk, bool *signaledOut) = 0;
    virtual angle::Result dupNativeFenceFD(Context *context, int *fdOut) const                 = 0;
};

// Implementation of fence types - glFenceSync, and EGLSync(EGL_SYNC_FENCE_KHR).
// The behaviors of SyncVk and EGLFenceSyncVk as fence syncs are currently
// identical for the Vulkan backend, and this class implements both interfaces.
class SyncHelper final : public vk::Resource, public SyncHelperInterface
{
  public:
    SyncHelper();
    ~SyncHelper() override;

    angle::Result initialize(ContextVk *contextVk, bool isEGLSyncObject);

    // SyncHelperInterface

    void releaseToRenderer(RendererVk *renderer) override;

    angle::Result clientWait(Context *context,
                             ContextVk *contextVk,
                             bool flushCommands,
                             uint64_t timeout,
                             VkResult *resultOut) override;
    angle::Result clientWaitUnlocked(Context *context,
                                     ContextVk *contextVk,
                                     bool flushCommands,
                                     uint64_t timeout,
                                     void *resultOut,
                                     MapVkResultToApiType mappingFunction) override;
    angle::Result serverWait(ContextVk *contextVk) override;
    angle::Result getStatus(Context *context, ContextVk *contextVk, bool *signaledOut) override;
    angle::Result dupNativeFenceFD(Context *context, int *fdOut) const override
    {
        return angle::Result::Stop;
    }

  private:
    angle::Result submitSyncIfDeferred(ContextVk *contextVk, RenderPassClosureReason reason);
    angle::Result prepareForClientWait(Context *context,
                                       ContextVk *contextVk,
                                       bool flushCommands,
                                       uint64_t timeout,
                                       VkResult *resultOut);
};

// Implementation of sync types: EGLSync(EGL_SYNC_ANDROID_NATIVE_FENCE_ANDROID).
class SyncHelperNativeFence final : public SyncHelperInterface
{
  public:
    SyncHelperNativeFence();
    ~SyncHelperNativeFence() override;

    angle::Result initializeWithFd(ContextVk *contextVk, int inFd);

    // SyncHelperInterface

    void releaseToRenderer(RendererVk *renderer) override;

    angle::Result clientWait(Context *context,
                             ContextVk *contextVk,
                             bool flushCommands,
                             uint64_t timeout,
                             VkResult *resultOut) override;
    angle::Result clientWaitUnlocked(Context *context,
                                     ContextVk *contextVk,
                                     bool flushCommands,
                                     uint64_t timeout,
                                     void *resultOut,
                                     MapVkResultToApiType mappingFunction) override;
    angle::Result serverWait(ContextVk *contextVk) override;
    angle::Result getStatus(Context *context, ContextVk *contextVk, bool *signaledOut) override;
    angle::Result dupNativeFenceFD(Context *context, int *fdOut) const override;

  private:
    SharedExternalFence mExternalFence;
};

}  // namespace vk

// Implementor for glFenceSync.
class SyncVk final : public SyncImpl
{
  public:
    SyncVk();
    ~SyncVk() override;

    void onDestroy(const gl::Context *context) override;

    angle::Result set(const gl::Context *context, GLenum condition, GLbitfield flags) override;
    angle::Result clientWait(const gl::Context *context,
                             GLbitfield flags,
                             GLuint64 timeout,
                             GLenum *outResult) override;
    angle::Result serverWait(const gl::Context *context,
                             GLbitfield flags,
                             GLuint64 timeout) override;
    angle::Result getStatus(const gl::Context *context, GLint *outResult) override;

  private:
    vk::SyncHelper mSyncHelper;
};

// Implementor for EGLSync.
class EGLSyncVk final : public EGLSyncImpl
{
  public:
    EGLSyncVk(const egl::AttributeMap &attribs);
    ~EGLSyncVk() override;

    void onDestroy(const egl::Display *display) override;

    egl::Error initialize(const egl::Display *display,
                          const gl::Context *context,
                          EGLenum type) override;
    egl::Error clientWait(const egl::Display *display,
                          const gl::Context *context,
                          EGLint flags,
                          EGLTime timeout,
                          EGLint *outResult) override;
    egl::Error serverWait(const egl::Display *display,
                          const gl::Context *context,
                          EGLint flags) override;
    egl::Error getStatus(const egl::Display *display, EGLint *outStatus) override;

    egl::Error dupNativeFenceFD(const egl::Display *display, EGLint *fdOut) const override;

  private:
    EGLenum mType;
    // SyncHelper or SyncHelperNativeFence decided at run-time.
    vk::SyncHelperInterface *mSyncHelper;
    EGLint mNativeFenceFD;
};
}  // namespace rx

#endif  // LIBANGLE_RENDERER_VULKAN_FENCESYNCVK_H_
