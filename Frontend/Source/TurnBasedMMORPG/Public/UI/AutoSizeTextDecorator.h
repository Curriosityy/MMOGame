#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "AutoSizeTextDecorator.generated.h"

/**
 * 
 */
class FAutoSizeDecorator : public FRichTextDecorator
{
public:
	explicit FAutoSizeDecorator(URichTextBlock* const InOwner)
		: FRichTextDecorator(InOwner)
	{
	}

	virtual ~FAutoSizeDecorator() override
	{
	}

	virtual bool Supports(const FTextRunParseResults& RunInfo, const FString& Text) const override;

	virtual void CreateDecoratorText(const FTextRunInfo& RunInfo, FTextBlockStyle& InOutTextStyle,
	                                 FString& InOutString) const override;
};

UCLASS()
class TURNBASEDMMORPG_API UAutoSizeTextDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

	TSharedPtr<FAutoSizeDecorator> Decorator;

public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;
};
