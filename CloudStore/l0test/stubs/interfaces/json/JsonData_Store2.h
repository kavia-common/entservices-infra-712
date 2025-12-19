#pragma once

/* Minimal placeholder for Thunder generated JsonData_Store2 interfaces.
 * Provides only the types and methods used by CloudStoreTest.cpp with no-op
 * serialization/deserialization logic. This is sufficient for compilation.
 */

#include <plugins/Module.h>
#include <core/JSON.h>
#include <interfaces/IStore2.h>

namespace WPEFramework {
namespace JsonData {
namespace Store2 {

    // Params for getValue (tests use ToString to create a payload)
    struct GetValueParamsInfo {
        Exchange::IStore2::ScopeType Scope { Exchange::IStore2::ScopeType::DEVICE };
        string Ns;
        string Key;

        inline void ToString(string& out) const {
            // No-op payload (tests are not executed here, only compiled)
            out = "{}";
        }
        inline bool FromString(const string& /*in*/) {
            return true;
        }
    };

    // Result for getValue (tests call FromString and then inspect fields)
    struct GetValueResultData {
        Core::JSON::String Value;
        Core::JSON::DecUInt32 Ttl;

        inline void ToString(string& out) const {
            out = "{}";
        }
        inline bool FromString(const string& /*in*/) {
            // No-op. Values left at default.
            return true;
        }
    };

    // Params for setValue
    struct SetValueParamsData {
        Exchange::IStore2::ScopeType Scope { Exchange::IStore2::ScopeType::DEVICE };
        string Ns;
        string Key;
        string Value;
        uint32_t Ttl { 0 };

        inline void ToString(string& out) const {
            out = "{}";
        }
        inline bool FromString(const string& /*in*/) {
            return true;
        }
    };

    // Params for deleteNamespace
    struct DeleteNamespaceParamsData {
        Exchange::IStore2::ScopeType Scope { Exchange::IStore2::ScopeType::DEVICE };
        string Ns;

        inline void ToString(string& out) const {
            out = "{}";
        }
        inline bool FromString(const string& /*in*/) {
            return true;
        }
    };

} // namespace Store2
} // namespace JsonData
} // namespace WPEFramework
