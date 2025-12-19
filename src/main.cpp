#include "launcher.h"
#include <iostream>
#include <windows.h>

int main() {
    std::cout << "================================\n";
    std::cout << "Launcher Auto-Update System v1.0\n";
    std::cout << "================================\n\n";

    Launcher launcher;
    
    // Initialize launcher
    if (!launcher.Initialize()) {
        std::cerr << "Failed to initialize launcher: " << launcher.GetStatus() << std::endl;
        MessageBoxA(NULL, 
            "Failed to initialize launcher.\nPlease ensure the configuration is correct.",
            "Launcher Error",
            MB_OK | MB_ICONERROR);
        return 1;
    }

    std::cout << "Status: " << launcher.GetStatus() << std::endl;
    std::cout << "Version: " << launcher.GetCurrentVersion() << std::endl << std::endl;

    // Configure for GitHub repository
    launcher.SetRepository("Tron7311", "launcher-auto-update");
    std::cout << "Repository configured\n" << std::endl;

    // Check for updates
    std::cout << "Checking for updates...\n" << std::endl;
    if (launcher.CheckForUpdates()) {
        std::cout << "Update available! Would you like to download it?\n" << std::endl;
        
        int result = MessageBoxA(NULL,
            "A new version is available. Download now?",
            "Update Available",
            MB_YESNO | MB_ICONQUESTION);

        if (result == IDYES) {
            std::cout << "Downloading update...\n" << std::endl;
            // Update download would happen here
        }
    } else {
        std::cout << "No updates available.\n" << std::endl;
    }

    // Display final status
    std::cout << "\nStatus: " << launcher.GetStatus() << std::endl;
    std::cout << "\nLauncher ready to use!\n" << std::endl;

    // Show success message
    MessageBoxA(NULL,
        "LauncherApp v1.0.0\n\nGitHub-based auto-update system.\n\nReady to launch your applications!",
        "Launcher",
        MB_OK | MB_ICONINFORMATION);

    return 0;
}
