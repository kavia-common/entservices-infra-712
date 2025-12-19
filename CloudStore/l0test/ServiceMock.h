/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "../Module.h"
#include <gmock/gmock.h>

// ServiceMock implements IShell and IShell::ICOMLink so CloudStore can call
// service->Register(...) which internally uses COMLink()->Register(...).
class ServiceMock : public WPEFramework::PluginHost::IShell,
                    public WPEFramework::PluginHost::IShell::ICOMLink {
public:
    ~ServiceMock() override = default;

    // Ensure COMLink returns a valid pointer in tests.
    WPEFramework::PluginHost::IShell::ICOMLink* COMLink() override {
        return this;
    }

    // IShell interface
    MOCK_METHOD(std::string, Versions, (), (const, override));
    MOCK_METHOD(std::string, Locator, (), (const, override));
    MOCK_METHOD(std::string, ClassName, (), (const, override));
    MOCK_METHOD(std::string, Callsign, (), (const, override));
    MOCK_METHOD(std::string, WebPrefix, (), (const, override));
    MOCK_METHOD(std::string, ConfigLine, (), (const, override));
    MOCK_METHOD(std::string, PersistentPath, (), (const, override));
    MOCK_METHOD(std::string, VolatilePath, (), (const, override));
    MOCK_METHOD(std::string, DataPath, (), (const, override));
    MOCK_METHOD(std::string, ProxyStubPath, (), (const, override));
    MOCK_METHOD(std::string, SystemPath, (), (const, override));
    MOCK_METHOD(std::string, PluginPath, (), (const, override));
    MOCK_METHOD(std::string, SystemRootPath, (), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, SystemRootPath, (const std::string&), (override));

    MOCK_METHOD(state, State, (), (const, override));
    MOCK_METHOD(bool, Background, (), (const, override));
    MOCK_METHOD(std::string, Model, (), (const, override));
    MOCK_METHOD(std::string, Accessor, (), (const, override));
    MOCK_METHOD(std::string, HashKey, (), (const, override));
    MOCK_METHOD(bool, IsSupported, (const uint8_t), (const, override));
    MOCK_METHOD(void, EnableWebServer, (const std::string&, const std::string&), (override));
    MOCK_METHOD(void, DisableWebServer, (), (override));
    MOCK_METHOD(WPEFramework::PluginHost::ISubSystem*, SubSystems, (), (override));
    MOCK_METHOD(uint32_t, Submit, (const uint32_t, const WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::IElement>&), (override));
    MOCK_METHOD(void, Notify, (const std::string&), (override));
    MOCK_METHOD(void*, QueryInterfaceByCallsign, (const uint32_t, const std::string&), (override));
    MOCK_METHOD(void, Register, (WPEFramework::PluginHost::IPlugin::INotification*), (override));
    MOCK_METHOD(void, Unregister, (WPEFramework::PluginHost::IPlugin::INotification*), (override));
    MOCK_METHOD(WPEFramework::PluginHost::IShell::startup, Startup, (), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, Startup, (const startup), (override));
    MOCK_METHOD(bool, Resumed, (), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, Resumed, (const bool), (override));
    MOCK_METHOD(WPEFramework::Core::hresult, Metadata, (std::string&), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, Hibernate, (const uint32_t), (override));
    MOCK_METHOD(std::string, Substitute, (const std::string&), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, ConfigLine, (const std::string&), (override));
    MOCK_METHOD(WPEFramework::PluginHost::IShell::reason, Reason, (), (const, override));
    MOCK_METHOD(WPEFramework::Core::hresult, Activate, (const reason), (override));
    MOCK_METHOD(WPEFramework::Core::hresult, Deactivate, (const reason), (override));
    MOCK_METHOD(WPEFramework::Core::hresult, Unavailable, (const reason), (override));

    // IShell::ICOMLink interface
    MOCK_METHOD(void, Register, (WPEFramework::RPC::IRemoteConnection::INotification*), (override));
    MOCK_METHOD(void, Unregister, (const WPEFramework::RPC::IRemoteConnection::INotification*), (override));
    MOCK_METHOD(void, Register, (WPEFramework::PluginHost::IShell::ICOMLink::INotification*), (override));
    MOCK_METHOD(void, Unregister, (WPEFramework::PluginHost::IShell::ICOMLink::INotification*), (override));
    MOCK_METHOD(WPEFramework::RPC::IRemoteConnection*, RemoteConnection, (const uint32_t), (override));
    MOCK_METHOD(void*, Instantiate, (const WPEFramework::RPC::Object&, const uint32_t, uint32_t&), (override));

    BEGIN_INTERFACE_MAP(ServiceMock)
        INTERFACE_ENTRY(IShell)
        INTERFACE_ENTRY(IShell::ICOMLink)
    END_INTERFACE_MAP
};
