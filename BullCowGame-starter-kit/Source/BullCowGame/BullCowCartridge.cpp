// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "FileHelper.h"
#include "Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    
    TArray<FString> HiddenWords;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(HiddenWords, *WordListPath);
    Isograms = GetValidWords(HiddenWords);

    SetupGame();

    

    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if(bGameOver)
    {
        //ClearScreen(); 
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }

    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Welcome to Bulls Cows Salty Spatoon."));

    PrintLine(TEXT("Guess the %i letter word!"),HiddenWord.Len());
    PrintLine(HiddenWord);
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    PrintLine(TEXT("Press Enter to restart"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{

    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if(--Lives == 0)
    {
        PrintLine(TEXT("You have lost!"));
        EndGame();
        return;
    }

    PrintLine(TEXT("You have %i lives remaining"),Lives);

    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("HiddenWord is %i characters long"),HiddenWord.Len());
        return;
    }

    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
        return;
    }


    //int32 Bulls, Cows;
    FBullCowCount Count;
    GetBullCows(Guess, Count);

    PrintLine(TEXT("You have %i bulls and %i cows"), Count.Bulls, Count.Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for(int32 i = 0;i < Word.Len()-1;i++)
    {
        for(int32 j = i+1; j < Word.Len();j++)
        {
            if(Word[i] == Word[j])
                return false;
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for(FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount,CowCount = 0;

    for(int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
        {
            BullCount++;
            continue;
        }

        int32 SearchIndex;
        if(HiddenWord.FindChar(Guess[i],SearchIndex))
        {
            CowCount++;
            continue;
        }
    }
}

void UBullCowCartridge::GetBullCows(const FString& Guess, FBullCowCount& Count) const
{
    Count.Bulls,Count.Cows = 0;

    for(int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }

        int32 SearchIndex;
        if(HiddenWord.FindChar(Guess[i],SearchIndex))
        {
            Count.Cows++;
            continue;
        }
    }
}