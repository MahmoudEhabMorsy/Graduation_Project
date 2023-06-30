/**
 * utilities.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Mahmoud Qotp
 **/
#include "utilities.h"


void intToStrBuffered(sint16 number, uint8 *str, uint8 size)
{
    uint8 i = 0, j = 0, k;
    uint8 temp;
    uint8 ovfCheck = 0;

    while (number)
    {
        if(i >= (size - 1))
        {
        	ovfCheck = 1;
            break;
        }
        str[i] = (number % 10) + '0';
        number /= 10;
        i++;
    }

    /*reversing the string*/
    k = i - 1;

    while(j < k)
    {
    	temp = str[j];
    	str[j] = str[k];
    	str[k] = temp;
    	j++;
    	k--;
    }

    if(ovfCheck == 0)
    {
        str[i] = '\0';
    }

    else
    {
        str[size - 1] = '\0';
    }

}

/*NOTE: USE WITH CARE
 * Function can smash the stack if it was misused as there is no buffer.
 * Preferred to use string with more than 10 characters.
 * */
uint8 intToStr(sint32 number, uint8 *str)
{
    uint8 i = 0, j = 0, k;
    uint8 temp;

    if(number == 0)
    {
    	str[i] = '0';
    	i++;
        return i;
    }

    if (number < 0)
    {
        str[i] = '-';
        i++;
        number *= -1;
        j = 1;
    }
    while (number)
    {
        str[i] = (number % 10) + '0';
        number /= 10;
        i++;
    }

    /*reversing the string*/
    k = i - 1;

    while(j < k)
    {
    	temp = str[j];
    	str[j] = str[k];
    	str[k] = temp;
    	j++;
    	k--;
    }

    str[i] = '\0';
    return i;
}


/*NOTE: USE WITH CARE
 * Function can smash the stack if it was misused as there is no buffer.
 * Preferred to use string with more than 20 characters.
 * */
void floatToString(float32 number, uint8 *res)
{
    uint8 temp;
    /*Extract integer part*/
    sint16 integerPart = (sint16)number;
    /*Extract floating part*/
    float64 fractionalPart = number - (float64)integerPart;

    if (fractionalPart < 0)
    {
        fractionalPart *= -1;
    }

    /*convert integer part to string*/
    uint8 i = intToStr(integerPart, res);
    res[i] = '.'; // add dot
    temp = i + 1;

    /*Converting the fractional part into integer to easily access it.*/
    for(i = temp; i < temp + NUMBER_OF_DIGITS_AFTERPOINT; i++)
    {
        fractionalPart = fractionalPart * 10; //
        res[i] = (((uint32)fractionalPart % 10) + '0');
    }
    res[i] = '\0';
}
