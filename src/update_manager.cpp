#include "update_manager.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ws2_32.lib")

UpdateManager::UpdateManager() 
    : updateAvailable(false) {
}

UpdateManager::~UpdateManager() = default;

void UpdateManager::SetRepository(const std::string& ownerParam, const std::string& repoParam) {
    owner = ownerParam;
    repo = repoParam;
    std::cout << "[UpdateManager] Repository set to: " << owner << "/" << repo << std::endl;
}

void UpdateManager::SetLocalVersion(const std::string& version) {
    localVersion = version;
    std::cout << "[UpdateManager] Local version: " << localVersion << std::endl;
}

bool UpdateManager::CheckForUpdates() {
    if (owner.empty() || repo.empty()) {
        std::cout << "[UpdateManager] Repository not configured" << std::endl;
        return false;
    }

    std::string url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";
    std::cout << "[UpdateManager] Fetching from: " << url << std::endl;

    std::string jsonResponse = DownloadJson(url);
    if (jsonResponse.empty()) {
        std::cout << "[UpdateManager] Failed to download release info" << std::endl;
        return false;
    }

    return ParseGithubRelease(jsonResponse);
}

std::string UpdateManager::DownloadJson(const std::string& url) {
    HINTERNET hInternetSession = InternetOpenA(
        "LauncherApp/1.0.0",
        INTERNET_OPEN_TYPE_DIRECT,
        nullptr,
        nullptr,
        0
    );

    if (!hInternetSession) {
        std::cout << "[UpdateManager] Failed to open Internet session" << std::endl;
        return "";
    }

    HINTERNET hUrl = InternetOpenUrlA(
        hInternetSession,
        url.c_str(),
        nullptr,
        0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE,
        0
    );

    if (!hUrl) {
        std::cout << "[UpdateManager] Failed to open URL: " << url << std::endl;
        InternetCloseHandle(hInternetSession);
        return "";
    }

    std::string result;
    char buffer[4096];
    DWORD bytesRead = 0;

    while (InternetReadFile(hUrl, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        result += buffer;
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternetSession);

    return result;
}

bool UpdateManager::ParseGithubRelease(const std::string& jsonResponse) {
    // Simple JSON parsing for GitHub release response
    size_t tagPos = jsonResponse.find("\"tag_name\"");
    if (tagPos == std::string::npos) {
        std::cout << "[UpdateManager] Invalid response format" << std::endl;
        return false;
    }

    // Extract tag name (version)
    size_t tagStart = jsonResponse.find("\"", tagPos + 11);
    size_t tagEnd = jsonResponse.find("\"", tagStart + 1);
    latestRelease.tagName = jsonResponse.substr(tagStart + 1, tagEnd - tagStart - 1);

    std::cout << "[UpdateManager] Latest release: " << latestRelease.tagName << std::endl;

    // Compare versions
    if (latestRelease.tagName != localVersion && !latestRelease.tagName.empty()) {
        updateAvailable = true;
        std::cout << "[UpdateManager] Update available!" << std::endl;
    }

    return true;
}

bool UpdateManager::DownloadUpdate(const std::string& downloadUrl, const std::string& savePath) {
    std::cout << "[UpdateManager] Downloading from: " << downloadUrl << std::endl;
    std::cout << "[UpdateManager] Saving to: " << savePath << std::endl;
    
    // Download implementation would go here
    return true;
}

bool UpdateManager::VerifyHash(const std::string& filePath, const std::string& expectedHash) {
    std::cout << "[UpdateManager] Verifying hash for: " << filePath << std::endl;
    // Hash verification implementation would go here
    return true;
}

std::string UpdateManager::GetLatestVersion() const {
    return latestRelease.tagName;
}

std::string UpdateManager::GetLatestDownloadUrl() const {
    return latestRelease.assetUrl;
}

std::string UpdateManager::GetLocalVersion() const {
    return localVersion;
}

bool UpdateManager::IsUpdateAvailable() const {
    return updateAvailable;
}

std::string UpdateManager::GetFileSHA256(const std::string& filePath) {
    // SHA256 calculation would go here
    return "";
}

std::string UpdateManager::UrlEncode(const std::string& str) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : str) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << std::setw(2) << int((unsigned char)c);
        }
    }
    return escaped.str();
}
