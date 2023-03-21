#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"





typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray,*PAdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc;
	pArr->copyFunc = copyFunc;
    pArr->printFunc = printFunc;
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
        
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}
    if ((pArr->pElemArr)[idx]){
	    pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{  
        if((pArr->pElemArr)[i])
        {
            pArr->delFunc((pArr->pElemArr)[i]);
        }
		
	}
	free(pArr->pElemArr);
	free(pArr);
}


void PrintDB(PAdptArray pArry)
{
    PAdptArray check = pArry;
    if(!check){
        printf("the AdptArray is empty");
    }
    for(int i = 0; i<check->ArrSize;++i){
        if((check->pElemArr)[i]){
            check->printFunc((check->pElemArr)[i]);
        }
    }
}
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if(!pArr){
        printf("The Array is Null\n");
        return NULL;
    }
    if((pArr->pElemArr)[idx])
    {
        return pArr->copyFunc((pArr->pElemArr)[idx]);
    }
    else
    {
        printf("The element in this index is null.\n");
        return NULL;
    }
}
int GetAdptArraySize(PAdptArray pArr){
    if(pArr->ArrSize == 0){
        return -1;
    }
    else return pArr->ArrSize;
}

