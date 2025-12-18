/*
 * Minimal stub for Thunder generated interfaces/json/JStore2.h
 *
 * The CloudStore plugin uses Exchange::JStore2 helpers for JSON-RPC registration
 * and event emission. Some Thunder/WPEFramework install prefixes don't ship this
 * generated header, so l0 tests fail to compile.
 *
 * This stub is intended ONLY for unit/l0 test builds in this workspace.
 */

#pragma once

#include <core/core.h>
#include <interfaces/IStore2.h>

namespace WPEFramework {

namespace PluginHost {
    class JSONRPC;
}

namespace Exchange {
    namespace JStore2 {

        inline void Register(PluginHost::JSONRPC& /*parent*/, IStore2* /*api*/)
        {
            // no-op stub
        }

        inline void Unregister(PluginHost::JSONRPC& /*parent*/)
        {
            // no-op stub
        }

        struct Event {
            static void ValueChanged(PluginHost::JSONRPC& /*parent*/,
                                     const IStore2::ScopeType /*scope*/,
                                     const string& /*ns*/,
                                     const string& /*key*/,
                                     const string& /*value*/)
            {
                // no-op stub
            }
        };

    } // namespace JStore2
} // namespace Exchange

} // namespace WPEFramework
