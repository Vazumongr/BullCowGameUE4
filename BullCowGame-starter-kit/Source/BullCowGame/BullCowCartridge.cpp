// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bulls Cows Salty Spatoon."));
    PrintLine(TEXT("Guess the 6 letter word..."));  //Make this adaptable.

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();


    if(Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
    }
    else
    {

        if(Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("HiddenWord is 6 characters long"));
        }
        //Isogram?
        //Correct amount of letters?
        //Decrease life

        //Chec
        PrintLine(TEXT("You have lost!"));
    }
    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("Peanut");
    Lives = 4;
}