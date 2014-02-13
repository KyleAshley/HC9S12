#include "filtersFixed.h"
#include <math.h>



void butterworth_2pole_initF(butterworth_2pole_ft *it,
                            long *feedback_params,
                            long *feedforward_params)
{
  unsigned char i;
  for (i = 0; i < 3; i++) {
    if (i < 2) {
      it->feedback_scale_params[i] = feedback_params[i];
    }
    it->feedforward_scale_params[i] = feedforward_params[i];
    it->delayed_inputs[i] = 0;
  }
  it->di_idx = 2;
}

/*
 * Note that indexing into the previous value cache is done such that
 * prior values are conceptually "ahead" of current values.
 * This is done because hardware will preserve the sign during modulo
 * arithmetic, so, for example, attempting to access array[(i - 2) % 3]
 * would expand to array[-2] if i = 0, as opposed to the expected array[1].
 * Always looking ahead to look back mitigates this issue.
 *
 * Additionally, note that the feedback_scale_params and delayed_inputs
 * are dereferenced via stack variables. This may improve performance as
 * less memory delays are incurred accessing those arrays.
 */
unsigned long butterworth_2pole_putF(butterworth_2pole_ft *it, unsigned long input)
{                                            
  unsigned char i = it->di_idx;
  long *fbsp = it->feedback_scale_params;
  long *di = it->delayed_inputs;
  long param3;
  long param1 = ((fbsp[0]) * di[(i + 1) % 3]),       //result = Q16.32
       param2 = ((fbsp[1]) * di[(i + 2) % 3]);       //result = Q16.32
       
  //param3 = (param2)  (param1);          //result = Q16.32

  
  di[i] = ((input << 16) - param1 - param2);             //input = Q16.16   param3 = Q16.32 
  di[i] = di[i] >> 16;  
  it->di_idx = i ? i - 1 : 2;
  return input;
}

/*
 * Note that the feedforward_scale_params and delayed_inputs
 * are dereferenced via stack variables. This may improve performance as
 * less memory delays are incurred accessing those arrays.
 */
long butterworth_2pole_get_longF(butterworth_2pole_ft *it)
{
  unsigned char i = it->di_idx, k = 0;
  long sum = 0;
  long tmp = 0;
  long *ffsp = it->feedforward_scale_params;
  long *di = it->delayed_inputs;
  for (; k < 3; k++) {
    sum += ((ffsp[k]) * di[(i + k) % 3]);            //di = Q16.16 ffsp = Q16.16--->result = Q16.16
  }
  sum >>= 16;
  return sum;
}

