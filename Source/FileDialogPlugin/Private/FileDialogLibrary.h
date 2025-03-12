#pragma once

#define FILEDIALOGPLUGIN_API DLLEXPORT

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FileTypeEnum.h"

#include "FileDialogLibrary.generated.h"

UCLASS()
class FILEDIALOGPLUGIN_API UFileDialogLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "File Dialog")
    static bool OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName);

    UFUNCTION(BlueprintCallable, Category = "File Dialog")
    static bool OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const TArray<EFileType>& FileTypes, FString& OutFileName);

    UFUNCTION(BlueprintCallable, Category = "File Dialog")
    static bool SaveFileDialog(const FString& DialogTitle, const FString& DefaultPath, const TArray<EFileType>& FileTypes, FString& OutFileName);
};
