#pragma once

#include <string>
#include <memory>

class UpdateManager;

class Launcher {
public:
    Launcher();
    ~Launcher();

    // Configuration
    void SetRepository(const std::string& owner, const std::string& repo);
    void SetVersion(const std::string& version);
    void SetAppPath(const std::string& appPath);

    // Operations
    bool Initialize();
    bool CheckForUpdates();
    bool LaunchApplication();
    bool SelfUpdate();

    // Status
    std::string GetStatus() const;
    std::string GetCurrentVersion() const;

private:
    std::unique_ptr<UpdateManager> updateManager;
    std::string appPath;
    std::string currentVersion;
    std::string statusMessage;

    bool VerifyApplicationExists();
    bool CreateConfigFile();
    bool LoadConfiguration();
};
