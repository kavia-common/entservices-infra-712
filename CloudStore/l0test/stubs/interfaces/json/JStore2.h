#pragma once

/* Minimal no-op stub for generated JSON glue JStore2 used by CloudStore.
 * This satisfies compile-time references to Register/Unregister and Event::ValueChanged.
 */

#include <plugins/Module.h>

namespace WPEFramework {
namespace Exchange {

    struct IStore2; // fwd decl

    struct JStore2 {
        // Register JSON-RPC methods for IStore2 on the given dispatcher (no-op stub).
        static inline void Register(PluginHost::JSONRPC& /*parent*/, IStore2* /*api*/) {}

        // Unregister JSON-RPC methods from the dispatcher (no-op stub).
        static inline void Unregister(PluginHost::JSONRPC& /*parent*/) {}

        struct Event {
            // Emit ValueChanged event to JSON-RPC subscribers (no-op stub).
            static inline void ValueChanged(PluginHost::JSONRPC& /*parent*/,
                                            const IStore2::ScopeType /*scope*/,
                                            const string& /*ns*/,
                                            const string& /*key*/,
                                            const string& /*value*/) {}
        };
    };

} // namespace Exchange
} // namespace WPEFramework
