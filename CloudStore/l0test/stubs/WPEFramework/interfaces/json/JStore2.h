/*
 * Test stub for Thunder generated interfaces/json/JStore2.h
 *
 * CloudStore registers Store2 JSON-RPC methods via Exchange::JStore2::Register().
 * The CloudStore l0 tests exercise these registrations through IDispatcher::Invoke,
 * so this stub must implement method registration (not just compile-time stubs).
 *
 * This stub is intended ONLY for unit/l0 test builds in this workspace.
 */

#pragma once

#include <core/core.h>
#include <interfaces/IStore2.h>
#include <interfaces/json/JsonData_Store2.h>
#include <plugins/JSONRPC.h>

namespace WPEFramework {

namespace Exchange {

    namespace JStore2 {

        namespace Version {
            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;
        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        static void Register(JSONRPC& module, IStore2* impl)
        {
            ASSERT(impl != nullptr);

            // Keep the same name as generated headers typically use.
            module.RegisterVersion(_T("JStore2"), Version::Major, Version::Minor, Version::Patch);

            // ---- setValue ----
            module.Register<JsonData::Store2::SetValueParamsInfo, void>(
                _T("setValue"),
                [impl](const JsonData::Store2::SetValueParamsInfo& params) -> uint32_t {
                    return impl->SetValue(params.Scope.Value(),
                                          params.Ns.Value(),
                                          params.Key.Value(),
                                          params.Value.Value(),
                                          params.Ttl.Value());
                });

            // ---- getValue ----
            module.Register<JsonData::Store2::GetValueParamsInfo, JsonData::Store2::GetValueResultInfo>(
                _T("getValue"),
                [impl](const JsonData::Store2::GetValueParamsInfo& params, JsonData::Store2::GetValueResultInfo& result) -> uint32_t {
                    string value;
                    uint32_t ttl = 0;

                    const uint32_t rc = impl->GetValue(params.Scope.Value(),
                                                       params.Ns.Value(),
                                                       params.Key.Value(),
                                                       value,
                                                       ttl);

                    if (rc == Core::ERROR_NONE) {
                        result.Value = value;
                        result.Ttl = ttl;
                    }

                    return rc;
                });

            // ---- deleteKey ----
            module.Register<JsonData::Store2::GetValueParamsInfo, void>(
                _T("deleteKey"),
                [impl](const JsonData::Store2::GetValueParamsInfo& params) -> uint32_t {
                    return impl->DeleteKey(params.Scope.Value(),
                                           params.Ns.Value(),
                                           params.Key.Value());
                });

            // ---- deleteNamespace ----
            module.Register<JsonData::Store2::DeleteNamespaceParamsInfo, void>(
                _T("deleteNamespace"),
                [impl](const JsonData::Store2::DeleteNamespaceParamsInfo& params) -> uint32_t {
                    return impl->DeleteNamespace(params.Scope.Value(),
                                                 params.Ns.Value());
                });

            // Compatibility aliases (some generated headers include lower-case variants).
            module.Register<JsonData::Store2::SetValueParamsInfo, void>(
                _T("setvalue"),
                [impl](const JsonData::Store2::SetValueParamsInfo& params) -> uint32_t {
                    return impl->SetValue(params.Scope.Value(),
                                          params.Ns.Value(),
                                          params.Key.Value(),
                                          params.Value.Value(),
                                          params.Ttl.Value());
                });

            module.Register<JsonData::Store2::GetValueParamsInfo, JsonData::Store2::GetValueResultInfo>(
                _T("getvalue"),
                [impl](const JsonData::Store2::GetValueParamsInfo& params, JsonData::Store2::GetValueResultInfo& result) -> uint32_t {
                    string value;
                    uint32_t ttl = 0;

                    const uint32_t rc = impl->GetValue(params.Scope.Value(),
                                                       params.Ns.Value(),
                                                       params.Key.Value(),
                                                       value,
                                                       ttl);

                    if (rc == Core::ERROR_NONE) {
                        result.Value = value;
                        result.Ttl = ttl;
                    }

                    return rc;
                });

            module.Register<JsonData::Store2::GetValueParamsInfo, void>(
                _T("deletekey"),
                [impl](const JsonData::Store2::GetValueParamsInfo& params) -> uint32_t {
                    return impl->DeleteKey(params.Scope.Value(),
                                           params.Ns.Value(),
                                           params.Key.Value());
                });

            module.Register<JsonData::Store2::DeleteNamespaceParamsInfo, void>(
                _T("deletenamespace"),
                [impl](const JsonData::Store2::DeleteNamespaceParamsInfo& params) -> uint32_t {
                    return impl->DeleteNamespace(params.Scope.Value(),
                                                 params.Ns.Value());
                });
        }

        static void Unregister(JSONRPC& module)
        {
            module.Unregister(_T("setValue"));
            module.Unregister(_T("getValue"));
            module.Unregister(_T("deleteKey"));
            module.Unregister(_T("deleteNamespace"));

            module.Unregister(_T("setvalue"));
            module.Unregister(_T("getvalue"));
            module.Unregister(_T("deletekey"));
            module.Unregister(_T("deletenamespace"));
        }

        namespace Event {

            static void ValueChanged(const JSONRPC& module, const JsonData::Store2::ValueChangedParamsData& params)
            {
                module.Notify(_T("valuechanged"), params);
                module.Notify(_T("onValueChanged"), params);
            }

            static void ValueChanged(const JSONRPC& module,
                                     const IStore2::ScopeType scope,
                                     const string& ns,
                                     const string& key,
                                     const string& value)
            {
                JsonData::Store2::ValueChangedParamsData params;
                params.Scope = scope;
                params.Ns = ns;
                params.Key = key;
                params.Value = value;

                ValueChanged(module, params);
            }

        } // namespace Event

    } // namespace JStore2

} // namespace Exchange

} // namespace WPEFramework
