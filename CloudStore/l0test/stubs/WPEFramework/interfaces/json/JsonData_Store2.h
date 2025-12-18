// Minimal stub for Thunder generated interfaces/json/JsonData_Store2.h
// Used by CloudStore l0 tests.
//
// NOTE: This is intentionally minimal and only includes types used by:
// - CloudStore/l0test/CloudStoreTest.cpp
// - interfaces/json/JStore2.h registration helpers (test stub).

#pragma once

#include <core/Enumerate.h>
#include <core/JSON.h>
#include <interfaces/IStore2.h>

namespace WPEFramework {

namespace JsonData {

    namespace Store2 {

        class SetValueParamsData : public Core::JSON::Container {
        public:
            SetValueParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("ns"), &Ns);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
                Add(_T("ttl"), &Ttl);
            }

            bool IsValid() const { return true; }

            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
            Core::JSON::String Value;
            Core::JSON::DecUInt32 Ttl;
        };

        using SetValueParamsInfo = SetValueParamsData;

        class GetValueParamsData : public Core::JSON::Container {
        public:
            GetValueParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("ns"), &Ns);
                Add(_T("key"), &Key);
            }

            bool IsValid() const { return true; }

            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
        };

        using GetValueParamsInfo = GetValueParamsData;

        class GetValueResultData : public Core::JSON::Container {
        public:
            GetValueResultData()
                : Core::JSON::Container()
            {
                Add(_T("value"), &Value);
                Add(_T("ttl"), &Ttl);
            }

            bool IsValid() const { return true; }

            Core::JSON::String Value;
            Core::JSON::DecUInt32 Ttl;
        };

        using GetValueResultInfo = GetValueResultData;

        class DeleteNamespaceParamsData : public Core::JSON::Container {
        public:
            DeleteNamespaceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("ns"), &Ns);
            }

            bool IsValid() const { return true; }

            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
        };

        using DeleteNamespaceParamsInfo = DeleteNamespaceParamsData;

        class ValueChangedParamsData : public Core::JSON::Container {
        public:
            ValueChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("ns"), &Ns);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
            }

            bool IsValid() const { return true; }

            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
            Core::JSON::String Value;
        };

    } // namespace Store2

} // namespace JsonData

// Enum conversion handlers (required for Core::JSON::EnumType<Exchange::IStore2::ScopeType>)
ENUM_CONVERSION_BEGIN(Exchange::IStore2::ScopeType)
    { Exchange::IStore2::ScopeType::DEVICE, _T("device"), 6 },
    { Exchange::IStore2::ScopeType::ACCOUNT, _T("account"), 7 },
ENUM_CONVERSION_END(Exchange::IStore2::ScopeType)

ENUM_CONVERSION_HANDLER(Exchange::IStore2::ScopeType)

} // namespace WPEFramework
