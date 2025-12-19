#pragma once

#include <string>
#include <vector>
#include <memory>

class UpdateManager {
public:
    UpdateManager();
    ~UpdateManager();

    // Configuration
    void SetRepository(const std::string& owner, const std::string& repo);
    void SetLocalVersion(const std::string& version);

    // Update operations
    bool CheckForUpdates();
    bool DownloadUpdate(const std::string& downloadUrl, const std::string& savePath);
    bool VerifyHash(const std::string& filePath, const std::string& expectedHash);
    
    // Getters
    std::string GetLatestVersion() const;
    std::string GetLatestDownloadUrl() const;
    std::string GetLocalVersion() const;
    bool IsUpdateAvailable() const;

private:
    struct ReleaseInfo {
        std::string tagName;
        std::string assetUrl;
        std::string assetHash;
    };

    std::string owner;
    std::string repo;
    std::string localVersion;
    ReleaseInfo latestRelease;
    bool updateAvailable;

    // Internal helpers
    std::string DownloadJson(const std::string& url);
    std::string GetFileSHA256(const std::string& filePath);
    bool ParseGithubRelease(const std::string& jsonResponse);
    std::string UrlEncode(const std::string& str);
};
