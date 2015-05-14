/*
 * observablequicksort.h
 *
 *  Created on: May 14, 2015
 *      Author: serek8
 */

#ifndef OBSERVABLEQUICKSORTER_H_
#define OBSERVABLEQUICKSORTER_H_


#include "observable.h"
#include "quicksorter.h"

template <class MyListElementType>
class ObservableQuickSorter : public Observable, public QuickSorter<MyListElementType>
{
public:
	ObservableQuickSorter(List<MyListElementType> &list):
		QuickSorter<MyListElementType>::QuickSorter(list){}


	List<MyListElementType> &sort()
	{
		sendStartUpdateToObservers();
		QuickSorter<MyListElementType>::sort();
		sendStopUpdateToObservers();
		return this->list;
	}
	virtual ~ObservableQuickSorter(){};


};


#endif /* OBSERVABLEQUICKSORTER_H_ */