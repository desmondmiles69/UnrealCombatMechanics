#pragma once

namespace Debug
{
	static void Print(const FString& msg, const FColor& color = FColor::MakeRandomColor(), int32 key = -1)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(key, 7.f, color, msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
		}
	}
}