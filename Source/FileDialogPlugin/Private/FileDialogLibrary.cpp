#include "FileDialogLibrary.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <shlobj.h>
#include <shobjidl.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include <Runtime/Core/Public/HAL/FileManager.h>
#include <Runtime/Core/Public/Misc/Paths.h>
#include <Runtime/Core/Public/Windows/COMPointer.h>
#include "Framework/Application/SlateApplication.h"

// Helper function to get the parent window handle for the dialog
static HWND GetParentWindowHandle()
{
    if (FSlateApplication::IsInitialized())
    {
        TSharedPtr<SWindow> MainWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
        if (MainWindow.IsValid() && MainWindow->GetNativeWindow().IsValid())
        {
            return static_cast<HWND>(MainWindow->GetNativeWindow()->GetOSWindowHandle());
        }
    }
    return nullptr;
}

// Opens a folder selection dialog
bool UFileDialogLibrary::OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName)
{
    bool bSuccess = false;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE)
    {
        return false;
    }

    TComPtr<IFileOpenDialog> FileDialog;
    hr = ::CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&FileDialog));
    if (SUCCEEDED(hr))
    {
        DWORD dwFlags = 0;
        FileDialog->GetOptions(&dwFlags);
        FileDialog->SetOptions(dwFlags | FOS_PICKFOLDERS);

        FileDialog->SetTitle(*DialogTitle);

        if (!DefaultPath.IsEmpty())
        {
            FString DefaultWindowsPath = FPaths::ConvertRelativePathToFull(DefaultPath);
            DefaultWindowsPath.ReplaceInline(TEXT("/"), TEXT("\\"), ESearchCase::CaseSensitive);

            TComPtr<IShellItem> DefaultPathItem;
            if (SUCCEEDED(::SHCreateItemFromParsingName(*DefaultWindowsPath, nullptr, IID_PPV_ARGS(&DefaultPathItem))))
            {
                FileDialog->SetFolder(DefaultPathItem);
            }
        }

        HWND ParentWindowHandle = GetParentWindowHandle();

        if (SUCCEEDED(FileDialog->Show(ParentWindowHandle)))
        {
            TComPtr<IShellItem> Result;
            if (SUCCEEDED(FileDialog->GetResult(&Result)))
            {
                PWSTR pFilePath = nullptr;
                if (SUCCEEDED(Result->GetDisplayName(SIGDN_FILESYSPATH, &pFilePath)))
                {
                    bSuccess = true;
                    OutFolderName = pFilePath;
                    FPaths::NormalizeDirectoryName(OutFolderName);
                    ::CoTaskMemFree(pFilePath);
                }
            }
        }
    }

    CoUninitialize();
    return bSuccess;
}

// Opens a file selection dialog
bool UFileDialogLibrary::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const TArray<EFileType>& FileTypes, FString& OutFileName)
{
    bool bSuccess = false;
    bool bCoInitialized = false;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(hr) || hr == RPC_E_CHANGED_MODE)
    {
        bCoInitialized = true;
    }
    else
    {
        return false;
    }

    TComPtr<IFileOpenDialog> FileDialog;
    hr = ::CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&FileDialog));
    if (SUCCEEDED(hr))
    {
        FileDialog->SetTitle(*DialogTitle);

        // Set file type filters using TPair
        if (FileTypes.Num() > 0)
        {
            TArray<COMDLG_FILTERSPEC> FilterSpecs;
            TArray<FString> FilterNames;
            TArray<FString> FilterPatterns;

            for (const EFileType& FileType : FileTypes)
            {
                TPair<FString, FString> FilterPair = FileTypeLookUp(FileType);
                FilterNames.Add(FilterPair.Key);
                FilterPatterns.Add(FilterPair.Value);
                FilterSpecs.Add({ *FilterNames.Last(), *FilterPatterns.Last() });
            }

            if (FilterSpecs.Num() > 0)
            {
                FileDialog->SetFileTypes(FilterSpecs.Num(), FilterSpecs.GetData());
                FileDialog->SetFileTypeIndex(1); // Default to the first filter
            }
        }

        // Set default folder
        if (!DefaultPath.IsEmpty())
        {
            FString DefaultWindowsPath = FPaths::ConvertRelativePathToFull(DefaultPath);
            DefaultWindowsPath.ReplaceInline(TEXT("/"), TEXT("\\"), ESearchCase::CaseSensitive);

            TComPtr<IShellItem> DefaultPathItem;
            if (SUCCEEDED(::SHCreateItemFromParsingName(*DefaultWindowsPath, nullptr, IID_PPV_ARGS(&DefaultPathItem))))
            {
                FileDialog->SetFolder(DefaultPathItem);
            }
        }

        HWND ParentWindowHandle = GetParentWindowHandle();

        // Show the dialog
        if (SUCCEEDED(FileDialog->Show(ParentWindowHandle)))
        {
            TComPtr<IShellItem> Result;
            if (SUCCEEDED(FileDialog->GetResult(&Result)))
            {
                PWSTR pFilePath = nullptr;
                if (SUCCEEDED(Result->GetDisplayName(SIGDN_FILESYSPATH, &pFilePath)))
                {
                    bSuccess = true;
                    OutFileName = pFilePath;
                    FPaths::NormalizeFilename(OutFileName);
                    ::CoTaskMemFree(pFilePath);
                }
            }
        }
    }

    if (bCoInitialized)
    {
        CoUninitialize();
    }

    return bSuccess;
}

// Opens a save file dialog
bool UFileDialogLibrary::SaveFileDialog(const FString& DialogTitle, const FString& DefaultPath, const TArray<EFileType>& FileTypes, FString& OutFileName)
{
    bool bSuccess = false;
    bool bCoInitialized = false;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED); 
    if (SUCCEEDED(hr) || hr == RPC_E_CHANGED_MODE)
    {
        bCoInitialized = true;
    }
    else
    {
        return false;
    }

    TComPtr<IFileSaveDialog> FileDialog;
    hr = ::CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&FileDialog));
    if (SUCCEEDED(hr))
    {
        FileDialog->SetTitle(*DialogTitle);

        // Set file type filters using TPair
        if (FileTypes.Num() > 0)
        {
            TArray<COMDLG_FILTERSPEC> FilterSpecs;
            TArray<FString> FilterNames;
            TArray<FString> FilterPatterns;

            for (const EFileType& FileType : FileTypes)
            {
                TPair<FString, FString> FilterPair = FileTypeLookUp(FileType);
                FilterNames.Add(FilterPair.Key);
                FilterPatterns.Add(FilterPair.Value);
                FilterSpecs.Add({ *FilterNames.Last(), *FilterPatterns.Last() });
            }

            if (FilterSpecs.Num() > 0)
            {
                FileDialog->SetFileTypes(FilterSpecs.Num(), FilterSpecs.GetData());
                FileDialog->SetFileTypeIndex(1); // Default to the first filter
            }
        }

        // Set default folder
        if (!DefaultPath.IsEmpty())
        {
            FString DefaultWindowsPath = FPaths::ConvertRelativePathToFull(DefaultPath);
            DefaultWindowsPath.ReplaceInline(TEXT("/"), TEXT("\\"), ESearchCase::CaseSensitive);

            TComPtr<IShellItem> DefaultPathItem;
            if (SUCCEEDED(::SHCreateItemFromParsingName(*DefaultWindowsPath, nullptr, IID_PPV_ARGS(&DefaultPathItem))))
            {
                FileDialog->SetFolder(DefaultPathItem);
            }
        }

        HWND ParentWindowHandle = GetParentWindowHandle();

        // Show the dialog
        if (SUCCEEDED(FileDialog->Show(ParentWindowHandle)))
        {
            TComPtr<IShellItem> Result;
            if (SUCCEEDED(FileDialog->GetResult(&Result)))
            {
                PWSTR pFilePath = nullptr;
                if (SUCCEEDED(Result->GetDisplayName(SIGDN_FILESYSPATH, &pFilePath)))
                {
                    bSuccess = true;
                    OutFileName = pFilePath;
                    FPaths::NormalizeFilename(OutFileName);
                    ::CoTaskMemFree(pFilePath);
                }
            }
        }
    }

    if (bCoInitialized)
    {
        CoUninitialize();
    }

    return bSuccess;
}