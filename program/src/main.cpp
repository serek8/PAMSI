/*
 * main.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: serek8
 */
/** @file */
#include <iostream>
#include <unistd.h>
#include "multiplybytwo.h"
#include "numbergenerator.h"
#include "dataframe.h"
#include "mybenchmark.h"
#include "mystack.h"
#include "myqueue.h"
#include "stackonarray.h"


int main(int argc, char *argv[])
{
	DataFrame podstawoweInfoIO;
	int quantityRepetitionOfAlgorithm = 0;	/// Ilosc powtorzen przez algorytmu

	int opt;	/// Zmienna uzywana przez GETOPT
	bool isSetNumberGenerator=false; /// Flaga ktora mowi o tym czy wlaczyc generator liczb losowych
	bool isTest=false;

	while ((opt = getopt(argc, argv, "n:t:o:i:gx")) != -1) {
		switch(opt){
		case 'n':	// ilosc liczb do przetworzenia
			podstawoweInfoIO.sizeOfTable = atoi(optarg);
			break;

		case 't':	// wlacza benchmark i przyjmuje liczbe powtorzen dla benchmarka
			quantityRepetitionOfAlgorithm = atoi(optarg);
			break;

		case 'o':
			podstawoweInfoIO.outputFileName = optarg;
			break;

		case 'i':
			podstawoweInfoIO.inputFileName=optarg;
			break;

		case 'g':	// wlacza generator liczb, po zakonczeniu generowania konczy program
			isSetNumberGenerator=true;
			break;

		case 'x':	// miejsce dla programisty dla sprawdzania kodu
			isTest =1;
			break;

		case '?':
		default:
			std::cout<<"\nPodano zly argument";
			return -1;
		}
	}

	// Generator zostal wylaczony do tesow nad wydajnoscia listy
	// poniewaz przy duzej ilosci liczb zjada za duzo RAM
	/*
	 * Sprawdzam czy program zostal uzyty tylko do wygenerowania liczb losowych
	 * jesli tak to tworze te liczby zgodnie quantityNumber i zamykam program
	 */
	/*if(isSetNumberGenerator) {
	NumberGenerator generator;
	std::cout<<"\n+ - - - - Tworzenie tablicy i generacja losowych liczb - - - +\n";
	generator= podstawoweInfoIO;
	MyBenchmark::timerStart();
	generator.generateNumbers();
	std::cout<<"Czas alokowania tablicy:"<<MyBenchmark::timerStop()<<'\n';
	podstawoweInfoIO = generator;


	}
*/

	StackOnArray *arraystack = new StackOnArray();
	std::cout<<"\n+ - - - - - Stos (tablica alokowanie o jeden)- - - - - - +\n";
	MyBenchmark::timerStart();
		for(unsigned int i=0; i<podstawoweInfoIO.sizeOfTable; i++)
		{
			(*arraystack).pushByOneAlloc(i);
		}
	std::cout<<"Czas pushowania:"<<MyBenchmark::timerStop()<<'\n';
	delete arraystack;

	/* kolejny test*/

	arraystack  = new StackOnArray();
	std::cout<<"\n+ - - - - - Stos (tablica alokowanie o 200%)- - - - - - +\n";
	MyBenchmark::timerStart();
		for(unsigned int i=0; i< podstawoweInfoIO.sizeOfTable ; i++)
		{
			(*arraystack).pushByDoubleAlloc(i);
		}
	std::cout<<"Czas pushowania:"<<MyBenchmark::timerStop()<<'\n';
	delete arraystack;

	/**
	 * Stos
	 */
	MyStack stack;
	std::cout<<"\n+ - - - - - - - - Stos (lista)- - - - - - - - +\n";
	MyBenchmark::timerStart();
	for(unsigned int i=0; i<podstawoweInfoIO.sizeOfTable; i++)
	{
		stack.push(i);
	}
	std::cerr<<"Czas pushowania:"<<MyBenchmark::timerStop()<<'\n';




	std::cout<<'\n';
	return 0;
}
