#include "launcher.h"
#include "update_manager.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <shlobj.h>

Launcher::Launcher() 
    : updateManager(std::make_unique<UpdateManager>()),
      currentVersion("1.0.0"),
      statusMessage("Initialized") {
}

Launcher::~Launcher() = default;

void Launcher::SetRepository(const std::string& owner, const std::string& repo) {
    if (updateManager) {
        updateManager->SetRepository(owner, repo);
    }
}

void Launcher::SetVersion(const std::string& version) {
    currentVersion = version;
    if (updateManager) {
        updateManager->SetLocalVersion(version);
    }
}

void Launcher::SetAppPath(const std::string& path) {
    appPath = path;
}

bool Launcher::Initialize() {
    std::cout << "[Launcher] Initializing..." << std::endl;
    
    if (!VerifyApplicationExists()) {
        statusMessage = "Application not found";
        return false;
    }

    if (!LoadConfiguration()) {
        std::cout << "[Launcher] Creating default configuration..." << std::endl;
        CreateConfigFile();
    }

    statusMessage = "Ready";
    std::cout << "[Launcher] Initialization complete. Version: " << currentVersion << std::endl;
    return true;
}

bool Launcher::CheckForUpdates() {
    std::cout << "[Launcher] Checking for updates..." << std::endl;
    
    if (!updateManager) {
        statusMessage = "Update manager not initialized";
        return false;
    }

    if (updateManager->CheckForUpdates()) {
        if (updateManager->IsUpdateAvailable()) {
            std::cout << "[Launcher] Update available: " << updateManager->GetLatestVersion() << std::endl;
            statusMessage = "Update available: " + updateManager->GetLatestVersion();
            return true;
        }
    }

    statusMessage = "No updates available";
    std::cout << "[Launcher] Already up to date (v" << currentVersion << ")" << std::endl;
    return false;
}

bool Launcher::LaunchApplication() {
    std::cout << "[Launcher] Launching application: " << appPath << std::endl;
    
    if (!VerifyApplicationExists()) {
        statusMessage = "Application executable not found";
        std::cout << "[ERROR] Application not found at: " << appPath << std::endl;
        return false;
    }

    SHELLEXECUTEINFOA sei = {};
    sei.cbSize = sizeof(sei);
    sei.lpVerb = "open";
    sei.lpFile = appPath.c_str();
    sei.nShow = SW_SHOW;

    if (ShellExecuteExA(&sei)) {
        statusMessage = "Application launched successfully";
        std::cout << "[Launcher] Application launched successfully" << std::endl;
        return true;
    }

    statusMessage = "Failed to launch application";
    std::cout << "[ERROR] Failed to launch application" << std::endl;
    return false;
}

bool Launcher::SelfUpdate() {
    std::cout << "[Launcher] Checking for self-updates..." << std::endl;
    
    if (!updateManager) {
        return false;
    }

    if (updateManager->CheckForUpdates() && updateManager->IsUpdateAvailable()) {
        std::cout << "[Launcher] Downloading update..." << std::endl;
        // Download and replace launcher executable
        statusMessage = "Self-update in progress";
        return true;
    }

    return false;
}

std::string Launcher::GetStatus() const {
    return statusMessage;
}

std::string Launcher::GetCurrentVersion() const {
    return currentVersion;
}

bool Launcher::VerifyApplicationExists() {
    if (appPath.empty()) {
        return false;
    }

    std::ifstream file(appPath);
    return file.good();
}

bool Launcher::CreateConfigFile() {
    std::string configPath = "config.json";
    std::ofstream file(configPath);
    
    if (!file.is_open()) {
        return false;
    }

    file << "{\n";
    file << "  \"repository\": \"Tron7311/launcher-auto-update\",\n";
    file << "  \"check_interval\": 3600,\n";
    file << "  \"auto_download\": true,\n";
    file << "  \"hash_verification\": true\n";
    file << "}\n";
    
    file.close();
    return true;
}

bool Launcher::LoadConfiguration() {
    std::ifstream file("config.json");
    return file.good();
}
