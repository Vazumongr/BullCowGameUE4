// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

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
    HiddenWord = TEXT("Peanut");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Welcome to Bulls Cows Salty Spatoon."));

    PrintLine(TEXT("Guess the %i letter word!"),HiddenWord.Len());
    
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
    }

    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
    }
}

bool UBullCowCartridge::IsIsogram(const FString& string) const
{
    for(int i = 0;i < string.Len()-1;i++)
    {
        for(int j = i+1; j < string.Len();j++)
        {
            if(string[i] == string[j])
                return false;
        }
    }
    return true;
}