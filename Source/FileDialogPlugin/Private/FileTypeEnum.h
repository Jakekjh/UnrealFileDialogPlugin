// FileTypeEnum.h
#pragma once

#include "CoreMinimal.h"
#include "FileTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EFileType : uint8
{
    AllFiles UMETA(DisplayName = "All Files"),
    TextFiles UMETA(DisplayName = "Text Files"),
    PDFFiles UMETA(DisplayName = "PDF Files"),
    WordDocuments UMETA(DisplayName = "Word Documents"),
    ImageFiles UMETA(DisplayName = "Image Files"),
    AudioFiles UMETA(DisplayName = "Audio Files"),
    VideoFiles UMETA(DisplayName = "Video Files"),
    ArchiveFiles UMETA(DisplayName = "Archive Files"),
    CodeFiles UMETA(DisplayName = "Code Files"),
    SpreadsheetFiles UMETA(DisplayName = "Spreadsheet Files"),
    PresentationFiles UMETA(DisplayName = "Presentation Files"),
    DatabaseFiles UMETA(DisplayName = "Database Files"),
    ExecutableFiles UMETA(DisplayName = "Executable Files")
};

static TPair<FString, FString> FileTypeLookUp(EFileType FileType)
{
    switch (FileType)
    {
    case EFileType::AllFiles:
        return TPair<FString, FString>(TEXT("All Files (*.*)"), TEXT("*.*"));

    case EFileType::TextFiles:
        return TPair<FString, FString>(TEXT("Text Files (*.txt)"), TEXT("*.txt"));

    case EFileType::PDFFiles:
        return TPair<FString, FString>(TEXT("PDF Files (*.pdf)"), TEXT("*.pdf"));

    case EFileType::WordDocuments:
        return TPair<FString, FString>(TEXT("Word Documents (*.doc, *.docx)"), TEXT("*.doc;*.docx"));

    case EFileType::ImageFiles:
        return TPair<FString, FString>(TEXT("Image Files (*.jpg, *.jpeg, *.png, *.gif)"), TEXT("*.jpg;*.jpeg;*.png;*.gif"));

    case EFileType::AudioFiles:
        return TPair<FString, FString>(TEXT("Audio Files (*.mp3, *.wav, *.flac)"), TEXT("*.mp3;*.wav;*.flac"));

    case EFileType::VideoFiles:
        return TPair<FString, FString>(TEXT("Video Files (*.mp4, *.avi, *.mov)"), TEXT("*.mp4;*.avi;*.mov"));

    case EFileType::ArchiveFiles:
        return TPair<FString, FString>(TEXT("Archive Files (*.zip, *.rar, *.7z)"), TEXT("*.zip;*.rar;*.7z"));

    case EFileType::CodeFiles:
        return TPair<FString, FString>(TEXT("Code Files (*.cpp, *.h, *.js)"), TEXT("*.cpp;*.h;*.js"));

    case EFileType::SpreadsheetFiles:
        return TPair<FString, FString>(TEXT("Spreadsheet Files (*.xls, *.xlsx)"), TEXT("*.xls;*.xlsx"));

    case EFileType::PresentationFiles:
        return TPair<FString, FString>(TEXT("Presentation Files (*.ppt, *.pptx)"), TEXT("*.ppt;*.pptx"));

    case EFileType::DatabaseFiles:
        return TPair<FString, FString>(TEXT("Database Files (*.mdb)"), TEXT("*.mdb"));

    case EFileType::ExecutableFiles:
        return TPair<FString, FString>(TEXT("Executable Files (*.exe)"), TEXT("*.exe"));

    default:
        return TPair<FString, FString>(TEXT("All Files (*.*)"), TEXT("*.*"));
    }
}